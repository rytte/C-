


这个程序演示了如何利用RTSPServer这个类来对媒体文件进行单播，OnDemand的意思是收到RTSP客户端请求时才进行流化和单播。
createNew() 是一个简单工厂函数。

int main(int argc, char** argv)
{
        // 初始化调度器和使用环境
        TaskScheduler* scheduler = BasicTaskScheduler::createNew();
        UsageEnvironment* env = BasicUsageEnvironment::createNew(*scheduler);

        // 创建 RTSP 服务器。使用指定的端口（8554）创建一个TCP的socket用于等待客户端的连接，然后 new 一个RTSPServer实例。
        RTSPServer* rtspServer = RTSPServer::createNew(*env, 8554);

        if (rtspServer == nullptr) {
                *env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
                return 1;
        }

        // 添加一个 RTSP 流。每个ServerMediaSubsession又叫一个track
        ServerMediaSession* sms = ServerMediaSession::createNew(*env, "test.264", "Live stream", "Session description");
        sms->addSubsession( H264VideoFileServerMediaSubsession::createNew(*env, "test.264", NULL) );//创建传H264文件的服务器。
        rtspServer->addServerMediaSession(sms);
        cout << rtspServer->ipv4rtspURL(sms) << endl;

        // 开启 RTSP 服务。doEventLoop函数出进入无限循环，在这个循环中不断地查看事件队列是否有事件需要去处理，有就去处理，没有则休眠一小会儿
        env->taskScheduler().doEventLoop();

        // 清理资源
        Medium::close(rtspServer);
        delete scheduler;

        return 0;
}











