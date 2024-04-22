/*************************/RTSP协议/***************************************************************************/
RTSP(Real - Time Stream Protocol)是一种基于文本的应用层协议，在语法及一些消息参数等方面，RTSP协议与HTTP协议类似。

该协议定义了一对多应用程序如何有效地通过IP网络传送多媒体数据.
RTSP在体系结构上位于RTP和RTCP之上, 它使用TCP或RTP完成数据传输
该协议用于C / S模型, 是一个基于文本的协议, 用于在客户端和服务器端建立和协商实时流会话


RTP协议：负责传输媒体数据（视频数据）
RTCP协议：在RTP传输过程中提供传输信息（视频质量）
RTSP协议：负责服务器与客户端之间的请求与响应（暂停播放等用户操作）


RTSP负责定义具体的控制信息、操作方法、状态码，以及描述与RTP之间的交互操作。
RTSP传输的一般是TS、MP4格式的流，其传输一般需要2~3个通道，命令和数据通道分离。
使用RTSP协议传输流媒体数据需要有专门的媒体播放器和媒体服务器，也就是需要支持RTSP协议的客户端和服务器。


//一次基本的RTSP操作过程
（1）首先，客户端连接到流服务器并发送一个RTSP描述命令（DESCRIBE）。
（2）流服务器通过一个SDP描述来进行反馈，反馈信息包括流数量、媒体类型等信息。
（3）客户端再分析该SDP描述，并为会话中的每一个流发送一个RTSP建立命令(SETUP)，RTSP建立命令告诉服务器客户端用于接收媒体数据的端口。流媒体连接建立完成后，
（4）客户端发送一个播放命令(PLAY)，服务器就开始在UDP上传送媒体流（RTP包）到客户端。在播放过程中客户端还可以向服务器发送命令来控制快进、快退和暂停等。
（5）最后，客户端可发送一个终止命令(TERADOWN)来结束流媒体会话

//sequenceDiagram :
客户端-> > 服务器:DESCRIBE
服务器-> > 客户端: 200 OK(SDP)
客户端-> > 服务器:SETUP
服务器-> > 客户端: 200 OK
客户端-> > 服务器:PLAY
服务器-> > 客户端: (RTP包)


OPTIONS
C--->S
客户端向服务器端发现OPTIONS，请求可用的方法。
S--->C
服务器端回复客户端，消息中包含当前可用的方法。

DESCRIBE
C--->S
客户端向服务器请求媒体描述文件，一般通过rtsp开头的url来发起请求，格式为sdp。
S--->C
服务器回复客户端sdp文件，该文件告诉客户端服务器有哪些音视频流，有什么属性，如编解码器信息，帧率等。

SETUP
C--->S
客户端向服务器端发起建立连接请求，请求建立会话连接，准备开始接收音视频数据，请求信息描述了期望音视频数据包基于UDP还是TCP传输，指定了RTP，RTCP端口，以及是单播还是组播等信息！
S--->C
服务器端收到客户端请求后，根据客户端请求的端口号确定发送控制数据的端口以及音视频数据的端口!

PLAY
C--->S
客户端向服务端请求播放媒体。
S--->C
服务器回复客户端200 OK!之后开始通过SETUP中指定的端口开始发送数据！

TEARDOWN
C---- > S
结束播放的时候，客户端向服务器端发起结束请求
S--->C
服务端收到消息后，向客户端发送200 OK，之后断开连接
上述的流程基本涵盖了RTSP的流程，当然，RTSP除此之外，还有PAUSE，SCALE，GET_PARAMETER，SET_PARAMETER等参数。


//协议特点
1、可扩展性 : 新方法和参数很容易加入RTSP.
2、易解析 : RTSP可由标准HTTP或MIME解析器解析.
3、安全 : RTSP使用网页安全机制.
4、独立于传输 : RTSP可使用不可靠数据报协议(EDP), 可靠数据报协议(RDP); 如要实现应用级可靠, 可使用可靠流协议.
5、多服务器支持: 每个流可放在不同服务器上, 用户端自动与不同服务器建立几个并发控制连接, 媒体同步在传输层执行.
6、记录设备控制 : 协议可控制记录和回放设备.
7、流控与会议开始分离 : 仅要求会议初始化协议提供, 或可用来创建惟一会议标识号.特殊情况下, 可用SIP或H.323来邀请服务器入会.
8、适合专业应用 : 通过SMPTE时标, RTSP支持帧级精度, 允许远程数字编辑.
9、演示描述中立 : 协议没强加特殊演示或元文件, 可传送所用格式类型; 然而, 演示描述至少必须包括一个RTSP URL.
10、代理与防火墙友好: 协议可由应用和传输层防火墙处理.防火墙需要理解SETUP方法, 为UDP媒体流打开一个“缺口”.
11、HTTP友好 : 此处, RTSP明智地采用HTTP观念, 使现在结构都可重用.结构包括Internet内容选择平台(PICS).由于在大多数情况下控制连续媒体需要服务器状态, RTSP不仅仅向HTFP添加方法.
12、适当的服务器控制 : 如用户启动一个流, 必须也可以停止一个流.
13、传输协调 : 实际处理连续媒体流前, 用户可协调传输方法.
14、性能协调 : 如基本特征无效, 必须有一些清理机制让用户决定哪种方法没生效.这允许用户提出适合的用户界面.


//RTSP协议与HTTP协议区别
1、RTSP引入了几种新的方法，比如DESCRIBE、PLAY、SETUP 等，并且有不同的协议标识符，RTSP为rtsp 1.0, HTTP为http 1.1；
2、HTTP是无状态的协议，而RTSP为每个会话保持状态；
3、RTSP协议的客户端和服务器端都可以发送Request请求，而在HTTP协议中，只有客户端能发送Request请求。
4、在RTSP协议中，载荷数据一般是通过带外方式来传送的(除了交织的情况)，及通过RTP协议在不同的通道中来传送载荷数据。而HTTP协议的载荷数据都是通过带内方式传送的，比如请求的网页数据是在回应的消息体中携带的。
5、使用ISO 10646(UTF - 8) 而不是ISO 8859 - 1，以配合当前HTML的国际化；
6、RTSP使用URI请求时包含绝对URI。而由于历史原因造成的向后兼容性问题，HTTP / 1.1只在请求中包含绝对路径，把主机名放入单独的标题域中；



/*************************/协议格式/***************************************************************************/
//RTSP客户端的请求格式
method url vesion CRLF
CSeq : x CRLF
xxx CRLF
...

method：方法，表明这次请求的方法
url：格式一般为 rtsp://ip:port/session，ip表主机ip，port表端口号，如果不写那么就是默认端口，rtsp的默认端口为554，session表明请求哪一个会话
version：表示rtsp的版本，现在为RTSP / 1.0
CSeq：序列号，每个RTSP请求和响应都对应一个序列号，序列号是递增的

例：OPTIONS  rtsp://192.168.11.130:554  RTSP/1.0


//RTSP服务端的响应格式
vesion 200 OK CRLF
CSeq : x CRLF
xxx CRLF
...

version：表示rtsp的版本，现在为RTSP / 1.0
CSeq：序列号，这个必须与对应请求的序列号相同


//RTSP URL的语法结构
一个终端用户是通过在播放器中输入URL地址开始进行观看流媒体业务的第一步，
而对于使用RTSP协议的移动流媒体点播而言，URL的一般写法如下：
一个以“rtsp”或是“rtspu”开始的URL链接用于指定当前使用的是RTSP 协议。RTSP URL的语法结构如下：

rtsp_url = (”rtsp:” | ”rtspu : ” | ”rtsps : ”) “//” host [“:”port”] /[abs_path]/content_name
* rtsp : 使用可信的底层传输协议，例如TCP
* rtspu : 使用不可信的底层传输协议，例如UDP
* rtsps : 使用可信加密传输协议，例如TCP + TLS
* host：可以是一个有效的域名或是IP地址。
* port：端口号，对于RTSP协议来说，缺省的端口号为554。当我们在确认流媒体服务器提供的端口号为554时，此项可以省略 说明：当HMS服务器使用的端口号为554时，我们在写点播链接时，可以不用写明端口号，但当使用非554端口时，在RTSP URL中一定要指定相应的端口。
* abs_path : 为RTSPServer中的媒体流资源标识
* RTSPURL用来标识RTSPServer的媒体流资源，可以标识单一的媒体流资源，也可以标 识多个媒体流资源的集合。

例如，一个完整的RTSP URL可写为：
rtsp ://192.168.1.67:554/test

又如目前市面上常用的海康网络摄像头的RTSP地址格式为：
rtsp ://[username]:[password]@[ip]:[port]/[codec]/[channel]/[subtype]/av_stream

示例
rtsp ://admin:12345@192.168.1.67:554/h264/ch1/main/av_stream


//请求方法
RTSP请求报文的方法包括：OPTIONS、DESCRIBE、SETUP、TEARDOWN、PLAY、PAUSE、GET_PARAMETER和SET_PARAMETER等。

方法				方向		是否必须		含义
OPTIONS			C->S	否			获在任意时刻由客户端主动发出，取服务器支持的方法。它不影响服务器的状态
DESCRIBE			C->S	否			向服务器获取URL指定的媒体对象的描述，其中Accept字段指定了描述格式
ANNOUNCE		双向		否			当客户端向服务器发送时，表示的是将通过请求 URL 识别的表示描述或者媒体对象提交给服务器
									当服务器向客户端发送时，表示的是通知客户端更新会话信息
SETUP			C->S	是			客户端向服务器请求建立会话并准备传输。请求信息主要包括传输协议和客户端的端口号
PLAY			C->S	是			客户端主动通知服务器以SETUP指定的机制开始发送数据。其中Range字段指定了播放的起止时间，当多个PLAY请求到达时，服务器会将PLAY请求排成队列，顺序执行，即必须等待第一个PLAY的时间完成后，才会继续处理第二个PLAY消息。
PAUSE			C->S	否			客户端请求服务器的媒体流传输临时暂停。可以通过Range参数在指定时间点暂停，也可以指定某股流暂停，例如如果指定音频流暂停，则播放将是无音状态
RECORD			C->S	否			RECORD通知服务器方法客户端将会根据之前的描述开始记录媒体数据。 其中timestamp 字段反映开始和结束时间 (UTC)。如果该字段不存在，则会使用媒体描述中的开始或结束时间。 如果会话已经开始，则立即开始录制。
									服务器决定是将记录的数据存储在 request-URI 下还是另一个 URI 下。 如果服务器不使用 request-URI，则响应应该是 201（已创建）并包含描述请求状态并引用新资源的实体和 Location 标头。
REDIRECT			S->C	否			重定向请求通知客户端它必须连接到另一个服务器位置。 它包含强制标头 Location，它指示客户端应该发出对该 URL 的请求。 它可能包含参数Range，表示重定向何时生效。 如果客户端想要继续发送或接收此 URI 的媒体，客户端必须为当前会话发出 TEARDOWN 请求，并在指定主机上为新会话发出 SETUP。
GET_PARAMETER	双向		否			GET_PARAMETER 请求检索 URI 中指定的表示或流的参数值。 回复和响应的内容留给实现。 没有实体主体的 GET_PARAMETER 可用于测试客户端或服务器的活跃度（“ping”）。
SET_PARAMETER	双向		否			这个方法请求设置演示或URL指定流的参数值。请求仅应包含单个参数，允许客户端决定某个特殊请求为何失败。如请求包含多个参数，所有参数可成功设置，服务器必须只对该请求起作用。服务器必须允许参数可重复设置成同一值，但不让改变参数值。注意：媒体流传输参数必须用SETUP命令设置。将设置传输参数限制为SETUP有利于防火墙。
TEARDOWN		C->S	是			TEARDOWN请求停止给定URL流发送，释放相关资源。


//响应消息格式
响应消息的第一行是状态行（status - line），每个元素之间用空格分开。
语法格式
RTSP - Version 空格Status - Code 空格Reason - Phrase CRLF

//状态码
状态码（Status - Code） 是一个三位数的整数，用于描述接收方对所收到请求消息的执行结果
Status - Code的第一位数字指定了这个回复消息的种类，一共有5类：

1XX: Informational – 请求被接收到，继续处理
2XX : Success – 请求被成功的接收，解析并接受
3XX : Redirection – 为完成请求需要更多的操作
4XX : Client Error – 请求消息中包含语法错误或是不能够被有效执行
5XX : Server Error – 服务器响应失败，无法处理正确的有效的请求消息

错误码	原因短语						方法
100		Continue						All
200		Success						All
201		Created 						RECORD
250		Low on Storage Space			RECORD
300		Multiple Choices 				All
301		Moved Permanently			All
302		Moved Temporarily 			All
303		See Other 					All
305		Use Proxy					All
400		Bad Request					All
401		Unauthorized					All
402		Payment Required				All
403		Forbidden					All
404		Not Found 					All
405		Method Not Allowed 			All
406		Not Acceptable  				All
407		Proxy Authentication Required	All
408		Request Timeout				All
410		Gone						All
411		Length Required				All
412		Precondition Failed				DESCRIBE, SETUP
413		Request Entity Too Larg			All
414		Request - URI Too Long			All
415		Unsupported Media Type		All
451		Invalid parameter				SETUP
452		Illegal Conference Identifier		SETUP
453		Not Enough Bandwidth			SETUP
454		Session Not Found				All
455		Method Not Valid In This State	All
456		Header Field Not Valid 			All
457		Invalid Range					PLAY
458		Parameter Is Read - Only		SET_PARAMETER
459		Aggregate Operation Not Allowed		All
460		Only Aggregate Operation Allowed	All
461		Unsupported Transport  			All
462		Destination Unreachable 		All
500		Internal Server Error			All
501		Not Implemented 				All
502		Bad Gateway    				All
503		Service Unavailable 			All
504		Gateway Timeout 				All
505		 RTSP Version Not Supported		All
551		Option not support   			All



/*************************/SDP格式/***************************************************************************/
sdp信息由多行"<type>=<value>"组成，其中<type>是一个字符串，<value>是一个字符串，
type表示类型，value的格式视type而定，整个协议区分大小写，"="两侧不允许有空格！










