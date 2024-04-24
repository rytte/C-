#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"
#include "GroupsockHelper.hh"
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

#define DUMMY_SINK_RECEIVE_BUFFER_SIZE 100000

//DummySink定义
class DummySink : public MediaSink {
public:
        static DummySink* createNew(UsageEnvironment& env,
                MediaSubsession& subsession, // identifies the kind of data that's being received
                char const* streamId = NULL) // identifies the stream itself (optional)
        {
                return new DummySink(env, subsession, streamId);
        }

private:
        DummySink(UsageEnvironment& env, MediaSubsession& subsession, char const* streamId)
                :MediaSink(env),
                fSubsession(subsession)
        {
                fStreamId = strDup(streamId);
                fReceiveBuffer = new u_int8_t[DUMMY_SINK_RECEIVE_BUFFER_SIZE];
        }

        virtual ~DummySink()
        {
                delete[] fReceiveBuffer;
                delete[] fStreamId;
        }

        static void afterGettingFrame(void* clientData, unsigned frameSize,
                unsigned numTruncatedBytes,
                struct timeval presentationTime,
                unsigned durationInMicroseconds)
        {
                DummySink* sink = (DummySink*)clientData;
                sink->afterGettingFrame(frameSize, numTruncatedBytes, presentationTime, durationInMicroseconds);
        }

        void afterGettingFrame(unsigned frameSize, unsigned numTruncatedBytes,
                struct timeval presentationTime, unsigned durationInMicroseconds)
        {
                // 请求下一帧数据
                continuePlaying();
        }

private:
        virtual Boolean continuePlaying()
        {
                if (fSource == NULL) return False; // 合理性检查（不应发生）
                // 从输入源请求下一帧数据。 "afterGettingFrame() "稍后将在数据到达时被调用：
                fSource->getNextFrame(fReceiveBuffer, DUMMY_SINK_RECEIVE_BUFFER_SIZE,
                        afterGettingFrame, this,
                        onSourceClosure, this);
                return True;
        }

private:
        u_int8_t* fReceiveBuffer;
        MediaSubsession& fSubsession;
        char* fStreamId;
};

//StreamClientState定义
class StreamClientState {
public:
        StreamClientState() : iter(NULL), session(NULL), subsession(NULL), streamTimerTask(NULL), duration(0.0) {}
        virtual ~StreamClientState()
        {
                delete iter;
                if (session != NULL)
                {
                        //我们还需要删除 "session"，并取消对 "streamTimerTask"（如果已设置）的调度
                        UsageEnvironment& env = session->envir(); // alias

                        env.taskScheduler().unscheduleDelayedTask(streamTimerTask);
                        Medium::close(session);
                }
        }

public:
        MediaSubsessionIterator* iter;
        MediaSession* session;
        MediaSubsession* subsession;
        TaskToken streamTimerTask;
        double duration;
};

//ourRTSPClient定义
class ourRTSPClient : public RTSPClient {
public:
        static ourRTSPClient* createNew(UsageEnvironment& env, char const* rtspURL,
                int verbosityLevel = 0,
                char const* applicationName = NULL,
                portNumBits tunnelOverHTTPPortNum = 0)
        {
                return new ourRTSPClient(env, rtspURL, verbosityLevel, applicationName, tunnelOverHTTPPortNum);
        }

protected:
        ourRTSPClient(UsageEnvironment& env, char const* rtspURL,
                int verbosityLevel, char const* applicationName, portNumBits tunnelOverHTTPPortNum)
                : RTSPClient(env, rtspURL, verbosityLevel, applicationName, tunnelOverHTTPPortNum, -1) {}

        virtual ~ourRTSPClient() {}

public:
        StreamClientState scs;
};






void subsessionAfterPlaying(void* clientData)
{
        MediaSubsession* subsession = (MediaSubsession*)clientData;
        RTSPClient* rtspClient = (RTSPClient*)(subsession->miscPtr);

        // Begin by closing this subsession's stream:
        Medium::close(subsession->sink);
        subsession->sink = NULL;

        // Next, check whether *all* subsessions' streams have now been closed:
        MediaSession& session = subsession->parentSession();
        MediaSubsessionIterator iter(session);
        while ((subsession = iter.next()) != NULL) {
                if (subsession->sink != NULL) return; // this subsession is still active
        }
}

void subsessionByeHandler(void* clientData, char const* reason)
{
        MediaSubsession* subsession = (MediaSubsession*)clientData;
        RTSPClient* rtspClient = (RTSPClient*)subsession->miscPtr;
        UsageEnvironment& env = rtspClient->envir(); // alias

        if (reason != NULL) {
                //delete[](char*)reason;
        }

        // Now act as if the subsession had closed:
        subsessionAfterPlaying(subsession);
}

void continueAfterPLAY(RTSPClient* rtspClient, int resultCode, char* resultString)
{
        UsageEnvironment& env = rtspClient->envir(); // alias
        StreamClientState& scs = ((ourRTSPClient*)rtspClient)->scs; // alias

        if (resultCode == 0)
        {
                std::cout << "PLAY success" << std::endl;
        }
        else
        {
                // 处理失败的情况
                std::cout << "PLAY error" << std::endl;
        }
}


void continueAfterSETUP(RTSPClient* rtspClient, int resultCode, char* resultString)
{
        UsageEnvironment& env = rtspClient->envir(); // alias
        StreamClientState& scs = ((ourRTSPClient*)rtspClient)->scs; // alias

        char* const sdpDescription = resultString;
        MediaSession* session = MediaSession::createNew(env, sdpDescription);   //根据SDP信息创建一个MediaSession对象

        if (resultCode == 0)
        {
                /*成功设置子会话后，为其创建一个数据汇，并调用 "startPlaying()"。(这将为数据汇接收数据做好准备；
                来自客户端的实际数据流稍后才会开始、 在我们发送 RTSP "播放 "命令后）。*/

                scs.subsession->sink = DummySink::createNew(env, *scs.subsession, rtspClient->url()); // 可以自定义 "MediaSink "子类来代替它

                if (scs.subsession->sink == NULL)
                        return;

                scs.subsession->miscPtr = rtspClient; // 让子会话处理程序函数从子会话中获取 "RTSPClient "的黑客技术 
                scs.subsession->sink->startPlaying(*(scs.subsession->readSource()), subsessionAfterPlaying, scs.subsession);

                // 同时设置一个处理程序，以便在该子会话收到 RTCP "BYE "时调用：
                if (scs.subsession->rtcpInstance() != NULL)
                        scs.subsession->rtcpInstance()->setByeWithReasonHandler(subsessionByeHandler, scs.subsession);
        }
        else
        {
                // 处理失败的情况
                std::cout << "SETUP error" << std::endl;
        }

}


void continueAfterDESCRIBE(RTSPClient* rtspClient, int resultCode, char* resultString)
{
        UsageEnvironment& env = rtspClient->envir(); // alias
        StreamClientState& scs = ((ourRTSPClient*)rtspClient)->scs; // alias
        char* const sdp = resultString;
        scs.session = MediaSession::createNew(env, sdp);             //根据SDP信息创建一个MediaSession对象

        if (resultCode == 0)
        {
                /*然后，为会话创建并设置数据源对象。 我们的做法是遍历会话的 "子会话"，调用 "MediaSubsession::initiate()"，
                然后在每个子会话上发送 RTSP "SETUP "命令。(每个 "子会话 "都有自己的数据源）。*/
                scs.iter = new MediaSubsessionIterator(*scs.session);

                while (1)
                {
                        scs.subsession = scs.iter->next();
                        if (scs.subsession != NULL)
                        {
                                if (!scs.subsession->initiate())                //初始化失败就下一个subsession
                                        continue;

                                rtspClient->sendSetupCommand(*scs.subsession, continueAfterSETUP);
                        }
                        else
                                break;
                }

                //我们已经完成了所有子会话的设置。 现在，发送 RTSP "PLAY "命令，开始流媒体播放：
                if (scs.session->absStartTime() != NULL)
                {
                        // Special case: The stream is indexed by 'absolute' time, so send an appropriate "PLAY" command:
                        rtspClient->sendPlayCommand(*scs.session, continueAfterPLAY, scs.session->absStartTime(), scs.session->absEndTime());
                }
                else
                {
                        scs.duration = scs.session->playEndTime() - scs.session->playStartTime();
                        rtspClient->sendPlayCommand(*scs.session, continueAfterPLAY);
                }
        }
        else
        {
                // 处理失败的情况
                std::cout << "DESCRIBE error" << std::endl;
        }
}



int main(int argc, char* argv[])
{
        // 设置环境
        TaskScheduler* scheduler = BasicTaskScheduler::createNew();
        UsageEnvironment* env = BasicUsageEnvironment::createNew(*scheduler);

        // 设置 RTSP 客户端的参数
        char const* rtspURL = "rtsp://10.18.22.180/test.264";
        RTSPClient* rtspClient = RTSPClient::createNew(*env, rtspURL, 0, nullptr, 0, -1);

        // 开始接收流数据
        if (rtspClient != nullptr)
                rtspClient->sendDescribeCommand(continueAfterDESCRIBE);
        else
                *env << "Failed to create RTSP client for URL: " << rtspURL << "\n";

        // 开始事件循环
        env->taskScheduler().doEventLoop();

        // 清理资源
        Medium::close(rtspClient);

        return 0;
}
