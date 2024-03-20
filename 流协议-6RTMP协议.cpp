/*************************/RTMP协议/***************************************************************************/

RTMP的工作原理是：通过建立和维护RTMP客户端和RTMP服务端之间的通信路径来实现快速、可靠的数据传输。
RTMP也是将多媒体流分割成切片：通常情况下，音频为64字节，视频为128字节。切片的大小可以由客户端和服务端之间协商获得。

RTMP协议中基本的数据单元称为消息（Message）。
当RTMP协议在互联网中传输数据的时候，消息会被拆分成更小的单元，称为消息块（Chunk）。


//RTMPdump
RTMPDump是一个开源工具库，使用c代码编写，
实现了用RTMP（Real Time Messaging Protocol，实时信息传输协议）上传音视频流的相关功能。
RTMP协议由Adobe公司提出，用于实时传递音视频媒体数据，其工作于TCP层，默认端口是1935。
RTMPDump在建立长连接时使用了Socket。

//librtmp
librtmp是一个库，它为开发者提供了RTMP协议的实现，使得开发者可以在自己的应用程序中集成RTMP的功能，实现实时流媒体传输。
librtmp更偏向于提供开发者使用的库，而RTMPdump则更偏向于提供命令行工具进行RTMP流的抓取和分析。



/*************************/RTMP工作原理/***************************************************************************/
RTMP连接设置：握手、连接、推拉流


//第一步：握手
RTMP中的握手过程相对简单，在建立TCP连接后进行。
在此握手过程中，每一方（客户端和服务端）发送三个数据包，分别为 C0、C1、C2 （客户端）和 S0、S1 、S2（服务端）。
1、客户端向服务器发送C0数据包，数据包中包含客户端请求的RTMP版本。
2、然后客户端在没有等到服务器表示已接收到C0的情况下，发送包含了1536字节随机数据的C1。
3、此时，服务器必须等到它收到C0才能响应S0和S1（可选）。在这个阶段，服务器知道客户端所请求的RTMP版本。服务器响应S0和S1——它们本质上是C0和C1的副本。
4、然后客户端和服务器交换C2和S2，之后握手完成，连接建立。


//第二步：连接
握手后进行连接，客户端和服务器使用AMF编码交换编码过的信息。
AMF（Action Message Format），用于在Adobe Flash客户端和Flash媒体服务器之间发送信息。
或者，程序员可以使用AFM序列化ActionScript和XML的对象图。
AMF在RTMP流传输中用于客户端和服务器之间的通信，表明信息类型和内容。

下面的示例显示了由客户端向RTMP服务器发出的信息。
其中使用了连接URL、音频编解码器、视频编解码器和所使用的AMF版本号3.0。

(Invoke) "connect"
(Transaction ID) 1.0
(Object1) {
	app: "sample", flashVer : "MAC 10,2,153,2", swfUrl : null,
	tcUrl : "rtmpt://127.0.0.1/sample ", fpad : false,
	capabilities : 9947.75, audioCodecs : 3191, videoCodecs : 252,
	videoFunction : 1, pageUrl : null, objectEncoding : 3.0
	}

RTMP服务器的响应信息：
(Invoke) "_result"
(transaction ID) 1.0
(Object1) { fmsVer: "FMS/3,5,5,2004", capabilities : 31.0, mode : 1.0 }
(Object2) {
	level: "status", code : "NetConnection.Connect.Success",
	description : "Connection succeeded",
	data : (array) { version: "3,5,5,2004" },
	clientId : 1728724019, objectEncoding : 3.0
	}

在这一步中，客户端和服务器还会交换Set Peer Bandwidth和Window Acknowledgement Size协议信息。
当成功执行，这些信息会表示连接的建立，然后服务器就可以传输视频数据了。


 //第三步：推拉流
在RTMP握手和连接步骤后，RTMP客户端和RTMP服务器之间的连接已经建立，现在就可以传送数据了。
为了实现数据的传输，RTMP规范定义了下面几个命令：

createStream
play
play2
deleteStream
closeStream
receiveAudio
receiveVideo
publish
seek
pause


//RTMP的变体
RTMPS、RTMPT、RTMFP、RTMPE、RTMP Proper

RTMPS： RTMPS只是基于TLS / SSL 连接的RTMP。与RTMPE相比，设置和使用RTMPS要复杂一些，但是能够确保一定程度的安全性。如果你计划使用RTMP将视频传输到Facebook Live，你需要使用RTMPS
RTMPE： RTMPE使用了包含Diffie–Hellman key exchange和HMACSHA256的行业标准加密。它生成了一对RC4密钥，其中：
第一个密钥用于加密从服务器向客户端发出的媒体数据。
第二个密钥用于加密向服务器发送的数据。
RTMP Proper : 是指使用1935端口、基于TCP的RTMP的别名。
RTMPT： RTMPT建立在HTTP协议之上，是通过HTTP封装后的RTMP协议。它允许RTMP信息穿过防火墙，封装的信息可以是RTMP Proper、RTMPS 或 RTMPE 数据包。
RTMFP : RTMPF基于UDP协议（而非TCP），而且没有使用RTMP Chunk Stream。RTMFP 设计用于直接在P2P之间进行低延迟、实时的音频和视频通信，而无需通过RTMP服务器。

