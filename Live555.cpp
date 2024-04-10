/********************/Live555/************************************************************/

//Live555的目录结构
（1）BasicUsageEnvironment
该目录中定义了Usa​​geEnvironment类的基本实现（即子类），用于简单的控制台应用程序，利用select 实现事件获取和处理。
这个库利用Unix 或者Windows 的控制台作为输入输出，可以用来开发简单的控制台应用程序。

（2）UsageEnvironment
该目录中定义了UsageEnvironment和TaskScheduler抽象类，用于调度延迟事件，
为异步读取事件分配处理程序以及输出错误 / 警告消息。另外其中还有HashTable类定义了通用散列表的接口。

（3）groupsock
该目录是对网络接口的封装，用于收发数据包。groupsock 主要是面向多播数据的收发的，它也同时支持单播数据的收发。

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






