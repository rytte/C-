/*************************/RTP协议/***************************************************************************/

RTP定义：Real - time Transport Protocol，为IP上的语音、图像等需要实时传输的多媒体数据提供端对端的传输服务，
但本身无法保证服务质量（QoS），因此，需要配合实时传输控制协议（RTCP）一起使用。

RTCP定义：Real - time Transport Control Protocol，监控服务质量并传送会话参与者信息，
服务器可利用RTCP数据包信息改变传输速率、负载数据类型。

//混频器（Mixer）
混频器是一种中间系统，将一个或多个源的RTP数据包合成一个新的RTP数据包，然后转发出去。
混频器可能会改变数据包的数据格式，并对各个流组合的新数据包生成一个新SSRC（SSRC: 同步信源标识符，即 RTP包的来源）。

//转换器（Translator）
转换器是一种中间系统，转发RTP数据包但不改变数据包的同步源标识符，
可用于通过IP多播无法直接到达的用户区，如在防火墙两端使用转换器，外侧转换器通过安全连接将数据传输到内侧转换器。

//RTP数据包传输流程
流1 + 流2 -> 混频器 -> 转换器 + 流3 + 流4 -> 混频器 -> 接收端

//RTP工作原理
RTP和RTCP位于传输层，但运行在UDP协议之上。
UDP协议实时性更好，可减少数据传输延时，另外，应用程序在UDP上运行RTP还可利用UDP的多路复用，校验和服务。

RTCP向RTP会话中的所有成员周期性的发送控制包，RTCP使用和RTP数据包相同的传输机制。
RTP会话使用合法的偶数端口（2n），对应的RTCP包使用下一个奇数端口（2n + 1）。

RTP包的头部标识了该包的数据类型，以便消息发送器来改变数据的编码。
例如，针对低带宽的与会者进行一些调节，或者对网络拥堵作出反应。
像UDP这类包类型的网络，偶尔会丢包，乱序，延迟不定长时间。
为了解决这类意外情况，RTP包中包含了时间信息和序列号，这样接受者就可以通过它们重排数据包的时序。

//RTP报文分析
每帧RTP报文都是由头部（Header）和负载数据(Payload)两部分组成, 头部前12个字节固定，
存在于每一个RTP数据包中，最后的CSRC列表只在Mixer中使用。负载数据可以是音频数据或视频数据。

每帧报文结构：[IP报头、UDP报头、RTP报头、RTP负载数据(Payload)]

V（Version）[2 bits]：标识RTP版本，RFC3550规定设置为2
P（Padding）[1 bit]：设定报文末端的填充字节，设置为1时指示报文末端附加填充字节
X（Extension）[1 bit]：设定固定报头后的报文扩展，设置为1时固定报头后必须有扩展
CC（CSRC Count）[4 bits]：标识固定报头后的CSRC数量，最大值为15
M（Marker）[1 bit]：由配置文件（profile）定义，需根据具体用途解释意义，可用来标记流数据中的重要事件
PT（Payload Type）[7 bits]：标识数据类型，内容包含编码算法、媒体类型、时钟频率及承载通道

序列号（sequence number）[16 bits]：标识数据包序列号，用于接收方重构数据包序列并记录丢包量，序列号初始值是随机产生的，每发送一个RTP数据包，序列号加1
时间戳（timestamp）[32 bits]：标识RTP数据包中第一个字节的采样时间，时间戳初始值也是随机数，每个采样周期时间戳加1，接收端利用时间戳来去除由网络引起的数据包抖动，并且在接收端提供同步功能
SSRC（Synchronization Source）[32 bits]：同步源标识符用于标识RTP数据流的起源，在一个RTP会话中，每个数据流的SSRC都不同，同步源标识符的值是随机数
CSRC list(Contributing Source)[N * 32 bits]：贡献源列表用于标识此RTP数据包中数据来源，由混频器将所有贡献源的SSRC标识符放入此表中，数量N由CC决定，最大数量为15，因此，当数量N超过15时，仅识别15个

//RTCP报文分析
RTCP的主要功能：服务质量的监控和反馈、媒体设备间的同步以及多播组中的成员标识。
在RTP会话期间，各参与者周期性传送RTCP数据包，RTCP数据包中包含已发送的数据包数量、丢失的数据包数量等信息，
各参与者通过这些信息动态改变传输速率或传输的数据类型。

RTCP可划分成五种类型，如下表所示
类型		名称		用途
200		SR		发送报告
201		RR		接收报告
202		SDES	源描述
203		BYE		结束传输
204		APP		特定应用

在一个RTP会话中有发送端和接收端，发送端将数据封装到RTP中发送，
同时以一定的时间间隔周期性发送RTCP中的发送报告（SR），
也收到接收端发过来的接收报告（RR）或从其他发送端发送过来的发送报告（SR）。
接收端获取到RTP数据包后解析数据，取得应用数据，获取其他参与者发送的发送报告（SR），
接收数据的同时通过发送接收报告（RR）将RTCP反馈信息发送出去。


https://zhuanlan.zhihu.com/p/352932897
https://zhuanlan.zhihu.com/p/86919417


#include <iostream>
#include <cstdint>

// 定义RTP报文头部结构
struct RTPHeader {
	uint16_t version : 2;     // RTP协议版本
	uint16_t padding : 1;     // 是否有填充位
	uint16_t extension : 1;   // 是否有扩展位
	uint16_t csrcCount : 4;   // CSRC计数
	uint16_t marker : 1;      // 标记位
	uint16_t payloadType : 7; // 负载类型
	uint16_t sequenceNumber; // 序列号
	uint32_t timestamp;     // 时间戳
	uint32_t ssrc;          // 同步信源
};

int main() {
	// 创建一个RTP报文头部
	RTPHeader rtpHeader;
	rtpHeader.version = 2;  // RTP协议版本
	rtpHeader.padding = 0;  // 无填充位
	rtpHeader.extension = 0; // 无扩展位
	rtpHeader.csrcCount = 0; // 无CSRC计数
	rtpHeader.marker = 0;    // 无标记位
	rtpHeader.payloadType = 96; // 负载类型
	rtpHeader.sequenceNumber = 12345; // 序列号
	rtpHeader.timestamp = 987654321; // 时间戳
	rtpHeader.ssrc = 12345678; // 同步信源

	return 0;
}



