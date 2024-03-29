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






