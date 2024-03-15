/*************************/RTCP协议/***************************************************************************/

RTCP定义：Real - time Transport Control Protocol。
RTCP的主要功能：服务质量的监控和反馈、媒体设备间的同步以及多播组中的成员标识。

//RTCP作用
【一】服务质量的监视与反馈
在RTP会话期间，每个会话参与者周期性地向所有其他参与者发送RTCP控制信息包。
每个RTCP信息包不封装声音数据或者视频数据，而是封装发送端或接收端的统计报表。
这些信息包括发送的信息包数目、丢失的信息包数目和信息包的抖动等情况，这些反馈信息反映了当前的网络状况
监控服务质量并传送会话参与者信息，服务器可利用RTCP数据包信息改变传输速率、负载数据类型。
【二】确定 RTP用户源
RTCP为每个RTP用户提供了一个全局唯一的规范名称(Canonical Name)标志符 CNAME，接收者使用它来追踪一个RTP进程的参加者。
当发现冲突或程序重新启动时，RTP中的同步源标识符SSRC可能发生改变，接收者可利用CNAME来跟踪参加者。
同时，接收者也需要利用CNAME在相关RTP连接中的几个数据流之间建立联系。
当 RTP需要进行音视频同步的时候，接受者就需要使用 CNAME来使得同一发送者的音视频数据相关联，然
后根据RTCP包中的计时信息(Network time protocol)来实现音频和视频的同步。
【三】控制 RTCP传输间隔
由于每个对话成员定期发送RTCP信息包，随着参加者不断增加，RTCP信息包频繁发送将占用过多的网络资源，
为了防止拥塞，必须限制RTCP信息包的流量，控制信息所占带宽一般不超过可用带宽的 5 % ，因此就需要调整 RTCP包的发送速率。
由于任意两个RTP终端之间都互发 RTCP包，因此终端的总数很容易估计出来，应用程序根据参加者总数就可以调整RTCP包的发送速率。
【四】传输最小进程控制信息　
这项功能对于参加者可以任意进入和离开的松散会话进程十分有用，参加者可以自由进入或离开，没有成员控制或参数协调。

//RTCP工作原理
RTCP向RTP会话中的所有成员周期性的发送控制包，RTCP使用和RTP数据包相同的传输机制。
RTP会话使用合法的偶数端口（2n），对应的RTCP包使用下一个奇数端口（2n + 1）。



/*************************/RTCP报文分析/***************************************************************************/
//RTCP报文类型
根据所携带的控制信息不同，RTCP信息包可分为五种类型

类型		名称							用途
200		SR（Sender Report）			发送端报告
201		RR（Receiver Report）			接收报告
202		SDES（Source Description Items）	源描述
203		BYE							结束传输
204		APP							特定应用

在一个RTP会话中有发送端和接收端，发送端将数据封装到RTP中发送，
同时以一定的时间间隔周期性发送RTCP中的发送报告（SR），
也收到接收端发过来的接收报告（RR）或从其他发送端发送过来的发送报告（SR）。
接收端获取到RTP数据包后解析数据，取得应用数据，获取其他参与者发送的发送报告（SR），
接收数据的同时通过发送接收报告（RR）将RTCP反馈信息发送出去。


//Sender Report（发送端报告）
发送端报告包，用于发送和接收活动源的统计信息，其通过多播方式向所有接收端报告发送情况。

2位   V（version）：RTCP版本。
1位   P（padding）：如果该位置为1，则该RTCP包的尾部就包含附加的填充字节。
5位   RC（received count）：接收报告计数器。该SR包中的接收报告块的数目，可以为零。
8位   PT（packet type）：包类型。SR包是200。
16位 Length：长度域。RTCP包的长度，包括填充的内容。
32位 同步源（SSRC of sender）：SR包发送者的同步源标识符。与对应RTP包中的SSRC一样。
64位 NTP timestamp（MSW + LWS）：表示发送此报告时以挂钟时间测量的时间点。 结合来自各个接收器的接收报告中返回的时间戳，它可用于估计往返于接收器的往返传播时间。
32位 RTP timestamp：与NTP时间戳对应，与RTP数据包中的RTP时间戳具有相同的单位和随机初始值。
32位 Sender’s packet count：从开始发送包到产生这个SR包这段时间里，发送者发送的RTP数据包的总数.SSRC改变时，这个域清零。
32位 Sender`s octet count：从开始发送包到产生这个SR包这段时间里，发送者发送的净荷数据的总字节数（不包括头部和填充）。发送者改变其SSRC时，这个域要清零。
32位 SSRC_n：在此块中报告其接收的发送者的 SSRC 标识符
8位   丢失率（Fraction Lost） :表明从上一个SR或RR包发出以来从同步源n(SSRC_n)来的RTP数据包的丢失率
24位 累计的包丢失数目（cumulative number of packets lost C ）：从开始接收到SSRC_n的包到发送SR, 从SSRC_n传过来的RTP数据包的丢失总数。
32位 收到的扩展最大序列号(extended highest sequence number received  EHSN)：从SSRC_n收到的RTP数据包中最大的序列号
32位 接收抖动（Interarrival jitter）：RTP数据包接受时间的统计方差估计
32位 上次SR时间戳（Last SR, LSR）：取最近从SSRC_n收到的SR包中的NTP时间戳的中间32比特。如果目前还没收到SR包，则该域清零
32位 上次SR以来的延时（Delay since last SR, DLSR）：上次从SSRC_n收到SR包到发送本报告的延时
扩展字段 profile - specific extensions


//Receiver Report（接收端报告）
除包类型代码外，SR与RR间唯一的差别是源报告包含有一个20字节发送者信息段。
活动源在发出最后一个数据包之后或前一个数据包与下一个数据包间隔期间发送SR；否则，就发送RR。
SR和RR包都可没有接收报告块也可以包括多个接收报告块，其发布报告表示的源不一定是在CSRC列表上的起作用的源，
每个接收报告块提供从特殊源接收数据的统计。最大可有31个接收报告块嵌入在SR 或 RR包中。
丢失包累计数差别给出间隔期间丢包的数量，而系列号的差别给出间隔期间希望发送的包数量，两者之比等于经过间隔期间包丢失百分比。
从发送者信息，第三方监控器可计算载荷平均数据速率与没收到数据间隔的平均包速率，两者比值给出平均载荷大小。
如假设包丢失与包大小无关，那么特殊接收者收到的包数量给出此接收者收到的表观流量。

2位   V
1位   P
5位   RC
8位   PT = RR = 201
16位 length
32位 同步源（SSRC of sender）
32位 SSRC_n
8位   丢失率（Fraction Lost）
24位 累计的包丢失数目（cumulative number of packets lost C）
32位 收到的扩展最大序列号(extended highest sequence number received  EHSN)
32位 接收抖动（Interarrival jitter）：RTP数据包接受时间的统计方差估计
32位 上次SR时间戳（Last SR, LSR）
32位 上次SR以来的延时（Delay since last SR, DLSR）
扩展字段 profile - specific extensions


//Source Description RTCP Packets（源点描述）
SDES源描述包提供了直观的文本信息来描述会话的参加者，包括CNAME、NAME、EMAIL、PHONE、LOC等源描述项，
这些为接收方获取发送方的有关信息提供了方便。SDES 包由包头与数据块组成，数据块可以没有，也可有多个。

2位   V
1位   P
5位   RC
8位   PT = RR = 202
16位 length
32位 SSRC/CSRC_1
SDES items
32位 SSRC/CSRC_2
SDES items
8位   CNAME
8位   lenth
user and domain name


//BYE（结束）
参与者发送 BYE 数据包以指示一个或多个源不再活动，可选择给出离开的理由。
作为可选项，BYE包可包括一个8位八进制计数，后跟文本信息，表示离开原因，如："cameramalfunction"或"RTPloop detected"。
字符串的编码与在SDES 项中所描述的相同。
如字符串信息至BYE包下32位边界结束处，字符串就不以空结尾；否则，BYE包以空八进制填充。

2位   V
1位   P
5位   RC
8位   PT = RR = 203
16位 length
32位 SSRC / CSRC_1
8位   lenth
reason for leaving（opt）


//APP
APP包用于开发新应用和新特征的实验，不要求注册包类型值。带有不可识别名称的APP包应被忽略掉。
测试后，如确定应用广泛，推荐重新定义每个APP包，而不用向IANA注册子类型和名称段。



