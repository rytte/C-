/********************/Live555/************************************************************/

//Live555的目录结构
（1）BasicUsageEnvironment
该目录中定义了Usa​​geEnvironment类的基本实现（即子类），用于简单的控制台应用程序，利用select 实现事件获取和处理。
这个库利用Unix 或者Windows 的控制台作为输入输出，可以用来开发简单的控制台应用程序。

（2）UsageEnvironment
该目录中定义了UsageEnvironment和TaskScheduler抽象类，用于调度延迟事件，
为异步读取事件分配处理程序以及输出错误 / 警告消息。另外其中还有HashTable类定义了通用散列表的接口。

（3）groupsock
对各种socket操作的封装，用于收发数据。主要面向组播，但也可以进行单播的收发数据，仅支持UDP，不支持TCP。

（4）liveMedia
该目录中有一系列类，基类是Medium，这些类针对不同的流媒体类型和编码，这是Live555的核心部分。

（5）testProgs
该目录实现一些使用BasicUsageEnvironment的简单程序来演示如何使用这些库开发应用程序。

（6）proxyServer
是一个基于Live555的流媒体代理服务器，只要支持Onvif协议的摄像机都能接入，
适用于将局域网内摄像机加入到代理服务器中从而提高对外服务性能同时，只需要开放默认554端口，可以有效保护内网摄像机安全。

（7）WindowsAudioInputDevice
这是liveMedia库的AudioInputDevice抽象类的实现。这可以由Windows应用程序用于从输入设备读取PCM音频样本。







TaskScheduler：任务调度器，负责管理Live555库中的任务，例如网络I / O操作和定时任务。您可以使用 BasicTaskScheduler::createNew() 方法创建一个新的任务调度器实例。

UsageEnvironment：使用环境，提供了一个抽象接口，用于管理Live555库中的会话、媒体流以及其他资源。您可以使用 BasicUsageEnvironment::createNew(TaskScheduler & taskScheduler) 方法创建一个新的使用环境实例。

RTSPServer：RTSP服务器，用于创建和管理RTSP会话。Live555库提供了一些示例程序，例如 RTSPServer 和 RTSPServerWithREGISTERProxying，可以用于创建简单的RTSP服务器。

MediaSession：媒体会话，代表了一个媒体流，可以包含视频、音频等多媒体数据。您可以使用 RTSPServer 的 addServerMediaSession() 方法将媒体会话添加到RTSP服务器中。

Medium：媒体类型，代表了媒体流的数据格式，例如视频流、音频流等。Live555库提供了一些媒体类型的实现，例如 Medium 和 MPEG4VideoStreamDiscreteFramer。

RTSPClient：RTSP客户端，用于与RTSP服务器建立连接，并发送和接收RTSP请求和响应。Live555库提供了 RTSPClient 类，您可以使用它来创建RTSP客户端实例。

MediaSink：媒体接收器，用于接收从RTSP服务器传输过来的媒体数据。Live555库提供了一些媒体接收器的实现，例如 FileSink 和 RTPSink。

FramedSource：帧源，用于产生媒体数据的帧。您可以使用 FramedSource 类的子类，例如 FramedFileSource 和 MPEG4VideoStreamFramer，来创建帧源实例。





1）Source和Sink

Source是生产数据的对象，例如从RTP读取数据。MediaSource是所有Source的基类。

Sink是消费数据的对象，例如把接受到的数据存储到文件中。MediaSink是所有Sink的基类。

2）数据流

Source->Source(filters)->Sink

从其它Source 接收数据的source 也叫做filters。Module是一个filters或Sink，数据接收的终点是Sink 类，Sink 类实现对数据的处理是通过实现纯虚函数continuePlaying()，通常情况下，continuePlaying 调用getNextFrame 来为Source 设置数据缓冲区，处理数据的回调函数等。不通常的情况下调用processBuffer，从接下来的socket writable或incoming data处理数据。

3）基于liveMedia的应用程序的控制流程

基于liveMedia的应用程序是事件驱动的，使用如下方式的循环：

while (1)
{
	//查找度网络句柄的列表和延迟队列，发现需要完成的任务；
	//完成任务
}
对于每个sink，在进入这个循环之前，应用程序通常调用下面的方法来启动需要做的生成任务： SinkObject->startPlaying()。任何时候，一个Module 需要获取数据都通过调用刚好在它之前的那个Module 的getNextFrame() 方法。



2.  ClientSession
对于每一个连接到服务器的客户端，服务器会为其创建一个ClientSession对象，保存该客户端的socket、ip地址等。
同时在该客户端中定义了各种响应函数用以处理和回应客户端的各种请求。
新版（2014.7.4）的LIVE555增加了ClientConnection类。用于处理一些与正常播放无关的命令。
如命令未找到、命令不支持或媒体文件未找到等。在ClientConnection处理DESCRIBE命令时会创建ClientSession对象，
其他命令在ClientSession中处理。


3.  MediaSession、MediaSubsession、Track
LIVE555使用MediaSession管理一个包含音视频的媒体文件，每个MediaSession使用文件名唯一标识。
使用SubSession管理MediaSession中的一个音频流或视频流。为行文方便我们称音频或视频均为一个媒体文件中的媒体流。因此一个MediaSession可以有多个MediaSubsession，一个管理音频流一个管理视频流。
在上一篇介绍RTSP协议时，客户端在给服务器发送DESCRIBE查询某个文件的SDP信息时，服务器会给客户端返回该媒体文件所包含的多个媒体流信息。并为每个媒体流分配一个TrackID。如视频流分配为Track1，音频流分配为Track2。此后客户端必须在URL指定要为那个Track发送SETUP命令。
因此我们可以认为MediaSubsession代表Server端媒体文件的一个Track，也即对应一个媒体流。MediaSession代表Server端一个媒体文件。对于既包含音频又包含视频的媒体文件，MediaSession内包含两个MediaSubsession。
但MediaSession和MediaSubsession仅代表静态信息，若多个客户端请求同一个文件，服务器仅会创建一个MediaSession。各个客户端公用。为了区分各个MediaSession的状态又定义了StreamState类，用来管理每个媒体流的状态。在MediaSubsession中完成了Souce和Sink连接。Souce对指针象会被设置进sink。在Sink需要数据时，可以通过调用Souce的GetNextFrame来获得。
LIVE555中大量使用简单工厂模式，每个子类均有一个CreateNew静态成员。该子类的构造函数被设置为Protected，因此在外部不能直接通过new来构造。同时，每个类的构造函数的参数中均有一个指向UsageEnvironment的指针，从而可以输出错误信息和将自己加入调度。

4. HashTable
LIVE555内部实现了一个简单哈希表类BasicHashTable。在LIVE555中，有很多地方需要用到该哈希表类。
如：媒体文件名与MediaSession的映射，SessionID与ClientSession的映射，UserName和Password的映射等。

5. SDP
SDP是Session Description Protocol的缩写。是一个用来描述多媒体会话的应用层协议，
它是基于文本的，用于会话建立过程中的媒体类型和编码方案的协商等。
客户端会通过DESCRIBE命令请求查询指定文件的媒体信息。












3.3、RTSP连接的建立
RTSPServer 类用于构建一个RTSP 服务器，该类同时在其内部定义了RTSPClientSession类，用于处理单独的客户会话。相关流程如下：

1）首先创建RTSP 服务器，在创建过程中，先建立Socket(ourSocket) 在TCP 的554 端口进行监听；

2）把连接处理函数句柄(RTSPServer::incomingConnectionHandler)和socket 句柄传给任务调度器(taskScheduler)。

3）任务调度器把socket 句柄放入后面select 调用中用到的socket 句柄集(fReadSet)中，同时将socket 句柄和incomingConnectionHandler 句柄关联起来。

4）主程序开始进入任务调度器的主循环（doEventLoop），在主循环中调用系统函数select 阻塞，等待网络连接。

5）RTSP 客户端输入(rtsp://192.168.2.20/live)连接服务器；

6）select 返回对应的scoket，进而根据前面保存的对应关系， 可找到对应处理函数句柄；

7）在incomingConnectionHandler 中创建RTSPClientSession，开始对这个客户端的会话进行处理。

3.4、DESCRIBE 请求消息处理过程
RTSP 服务器收到客户端的DESCRIBE 请求后，根据请求URL(rtsp://192.168.2.20/1.mpg)，找到对应的流媒体资源， 返回响应消息。live555中的ServerMediaSession 类用来处理会话中描述，它包含多个（音频或视频）的子会话描述(ServerMediaSubsession)。相关处理流程如下

1）服务器收到请求，主循环中的select调用返回，根据socket 句柄找到对应的incomingRequestHandler；

2）进行消息的解析，如果发现请求是DESCRIBE 则进入handleCmd_DESCRIBE 函数;

3）根据客户端请求URL 的后缀(例如是.mpg), 调用成员函数DynamicRTSPServer::lookupServerMediaSession查找对应的流媒信息ServerMediaSession；

4）如果ServerMediaSession 不存在，但是本地存在live文件，则创建一个新的ServerMediaSession；

5）在创建ServerMediaSession 过程中，根据文件后缀.mpg，创建媒体MPEG - 1or2的解复用器(MPEG1or2FileServerDemux)；

6）由MPEG1or2FileServerDemux 创建一个子会话描述

MPEG1or2DemuxedServerMediaSubsession；

7）由ServerMediaSession 完成组装响应消息中的SDP 信息；

8）返回响应消息给客户端，完成DESCRIBE消息交互。

3.5、SETUP 和PLAY 请求消息处理过程
RTSPClientSession类， 用于处理单独的客户会话。其类成员函数handleCmd_SETUP()处理客户端的SETUP 请求。调用parseTransportHeader()对SETUP 请求的传输头解析，调用子会话(实现类OnDemandServerMediaSubsession)的getStreamParameters()函数获取流媒体发送传输参数。将这些参数组装成响应消息，返回给客户端。

获取发送传输参数的过程：

1）调用子会话(具体实现类MPEG1or2DemuxedServerMediaSubsession) 的createNewStreamSource() 创建MPEG1or2VideoStreamFramer，选择发送传输参数；

2）并调用子会话的createNewRTPSink()创建MPEG1or2VideoRTPSink。同时将这些信息保存在StreamState 类对象中，用于记录流的状态。

客户端发送两个SETUP 请求，分别用于建立音频和视频的RTP 接收。PLAY 请求消息处理过程如下：

1）RTSPClientSession 类成员函数handleCmd_PLAY()处理客户端的播放请求。2）调用子会话的startStream(), 在一系列调用中的buildAndSendPacke 内部先设置RTP 包头；

3）内部再调用MultiFramedRTPSink::packFrame()填充编码帧数据;

4）packFrame 内部通过一系列繁琐调用，发送RTP 数据包;

5）计算下一个数据包发送时间，把MultiFramedRTPSink::sendNext()函数句柄传给任务调度器， 作为一个延时事件调度;

6）在主循环中， 当MultiFramedRTPSink::sendNext() 被调度时， 又开始调用MultiFramedRTPSink::buildAndSendPacket()开始新的发送数据过程，这样客户端可以源源不断的收到服务器传来的RTP 包了。






//testProgs

testOnDemandRTSPServer.cpp： 创建一个RTSP服务器，允许按需点播（请求播放）流媒体内容。

testRTSPClient.cpp： 实现RTSP客户端，从RTSP服务器请求并播放流媒体内容。

testRelay.cpp： 将一个RTSP流媒体源服务器的内容中继到另一个RTSP服务器。

testReplicator.cpp： 创建流媒体内容的复制，允许多个客户端同时访问。

testMP3Streamer.cpp： 将MP3音频内容进行流式传输。

testMPEG4VideoStreamer.cpp： 将MPEG - 4视频进行流式传输。

testH264VideoStreamer.cpp / testH265VideoStreamer.cpp： 流式传输H.264 / H.265视频。

testGSMStreamer.cpp： 流式传输GSM音频。

testWAVAudioStreamer.cpp： 流式传输WAV音频。

testMPEG2TransportStreamer.cpp： 流式传输MPEG - 2传输流。

testDVVideoStreamer.cpp： 流式传输DV视频。

testOggStreamer.cpp： 流式传输Ogg音频。

testH264VideoToTransportStream.cpp / testH265VideoToTransportStream.cpp： 将H.264 / H.265视频转换为传输流。

testMPEG2TransportStreamTrickPlay.cpp： 实现MPEG - 2传输流的快进和倒放功能。

testMKVStreamer.cpp / testMKVSplitter.cpp： 流式传输和分割MKV文件内容。

testMPEG1or2VideoStreamer.cpp / testMPEG1or2AudioVideoStreamer.cpp： 流式传输MPEG - 1 / MPEG - 2视频。
