/********************/SIP协议/************************************************************/
SIP（Session Initiation Protocol，会话发起协议）是一个应用层的信令协议，主要用于创建、修改和终止多媒体会话，
如语音通话、视频通话、即时消息等，广泛应用于VoIP（网络电话）、视频会议和 IMS（IP多媒体子系统）等领域。


//🔁 信令协议 ≠ 媒体协议
信令协议：控制建立连接（像打电话时拨号）
媒体协议：传输音视频数据（像电话连通后听到声音）


//🌐 基本特性
1、应用层协议：运行在TCP、UDP之上，主要工作是控制通信会话的建立与管理。
2、文本协议：消息格式类似HTTP，易于读取和调试。
3、基于请求 / 响应模型：SIP 使用类似 HTTP 的机制进行通信。
4、独立于传输层：既可以在UDP、TCP上运行，也支持TLS（加密）和SCTP等。


//📌 SIP 能做什么？
1、会话控制：
发起 / 终止语音或视频通话
加入 / 退出会议
更改媒体参数（如从音频切换到视频）

2、位置定位：
确定用户的位置（SIP 地址到IP地址的解析）

3、注册服务：
用户上线时将地址注册到SIP服务器


//📦 典型组件
组件							功能
User Agent（UA）				用户终端，可以是软电话或SIP设备
User Agent Client（UAC）		发起请求的一方
User Agent Server（UAS）		接收并响应请求的一方
Registrar					注册服务器，记录用户位置信息
Proxy Server				中转请求，类似路由器
Redirect Server				告知客户端重定向地址
Location Server				存储用户位置（与 Registrar 协作）


//📨 常见的 SIP 消息
SIP 是一个文本协议，格式类似 HTTP，以下是一些常见的请求方法：

方法				说明
INVITE			建立会话
ACK				确认会话建立
BYE				终止会话
CANCEL			取消会话建立请求
REGISTER		用户注册到服务器
OPTIONS			查询服务器能力

响应以状态码区分，类似 HTTP，例如：
1xx：临时响应（如 180 Ringing）
2xx：成功（如 200 OK）
4xx：客户端错误（如 404 Not Found）
5xx：服务器错误
6xx：全局失败


//🛠 示例
一个用户通过 SIP 拨打另一个用户的流程大致如下：
1、UAC 发送 INVITE
2、代理服务器转发 INVITE 给 UAS
3、UAS 响应 180 Ringing
4、UAS 接听，发送 200 OK
5、UAC 回复 ACK
6、双方进行音视频数据传输（通常使用 RTP 协议）
7、任一方发送 BYE，终止会话


//SIP消息体结构（与HTTP协议结构相似）
• 请求行(request - line) or 状态行(status - line)
• 消息头(header)
• 正文(body)
R"(
INVITE sip:bob@zte.com SIP/2.0 /r/n
SIP/2.0 200 OK /r/n

MESSAGE sip:0210011140114@10.192.39.37:17017 SIP/2.0
Via: SIP/2.0/UDP 10.192.39.194:15069;rport;branch=z9hG4bK2000324456
From: <sip:0100012000002@10.192.39.194:15069>;tag=2253307030
To: sip:0210011140114@10.192.39.37:17017
Contact: <sip:0100012000002@10.192.39.194:15069>
Call-ID: 755416301
CSeq: 20 MESSAGE
Content-Type: Application/MANSCDP+xml
Max-Forwards: 70
User-Agent: eXosip/3.3.0
Content-Length:   161
)"

