

TS（Transport Stream）：MPEG - 2编码标准，常用于数字电视传输，支持实时传输。结构冗余少，适合网络流和直播应用。


//多路复用
多路复用（Multiplexing，简称“mux”） 是将多个独立的数据流（如视频流、音频流、字幕流等）组合成一个综合流的过程。

传输流（TS）多路复用：常用于直播和广播，支持实时传输和容错，适合 IPTV、DVB 等应用。
程序流（PS）多路复用：常用于本地视频存储，结构紧凑，如 VOB 格式的视频文件。
文件多路复用：如 MP4、MKV、AVI，将多个音视频流封装在一个文件中，通常有索引和元数据，便于回放和随机访问。

TS（Transport Stream） 传输流多路复用 由多个固定大小的TS数据包组成，每个数据包的大小为 188 字节。TS码流的固定包结构具有较强的抵抗传输误码的能力。
PS（Program Stream  ） 节目流多路复用 的包结构是可变长度的。PS 封装格式主要用在 不容易发生错误的环境，例如 DVD 光盘。
MPEG - PS 跟 MPEG - TS 都是 基于 PES 进行封装，所以两者可以相互转换。

//TS格式三层结构
ES，Elementary Stream（基本流），ES 是独立的音频或视频流（例如，视频的 H.264 流、音频的 AAC 流），但是 ES 不只是音视频帧，也不含头信息或元数据及时间戳等。
PES（Packetized Elementary Stream）：在 TS 流中，用于封装 ES 的基础单元，通过加入 PTS 和 DTS 等时间信息来帮助音视频同步。
TS（Transport Stream）：将 PES 包进一步分割、加上头部信息（同步字节、PID 等），适合实时传输。TS 流中可以包含多个音视频 ES，经过多路复用后形成单一的传输流。

关系：TS流 = TS包头 + TS负载（PES包头 + PES负载（ES音视频编码数据））


//TS包头解析
TS包，Transport Packet（传输包），固定188个字节，一个大的 PES 包会拆成多个小的块，封装进去 TS 包进行传输。

头部4字节：01000111 01000000 00010001 00010000 （47 40 11 10）
{
	8bit 0x47 sync_byte，TS 包的同步字节，用于标识数据包的开始，每个 TS 包以 0x47 开头
	1bit 0 transport_error_indicator，传输错误标记，通常表示传输中是否有错误，0 表示无错误。在可靠的 TCP / UDP 传输中，这个标记通常为 0;
	1bit 1 payload_unit_start_indicator，有效负载单元开始标记;
	1bit 0 transport_priority ，表示数据包的优先级。互联网场景中一般不用关注此字段，通常设置为 0;
	13bit 0x1001 PID（Packet Identifier），用于标识数据包的内容类型。例如，0x0000 表示节目关联表(PAT) 数据包。PID 的值可以帮助识别负载的数据类型;
	2bit 0 transport_scrambling_control，指示数据包是否被加扰。00 表示未加扰，通常用于免费内容;
	2bit 1 adaptation_field_control，表示是否有自适应字段以及有效负载。01 表示有有效负载没有自适应字段，10 表示有自适应字段没有有效负载，11 表示同时具有自适应字段和有效负载;
	4bit 0 continuity_counter，TS包里面如果有 playload，这个字段会递增;
}
Nbit   data_byte，从这里开始是实际的数据负载内容（Payload）。一个 TS 包通常是 188 字节，去掉头部（4 字节），剩余部分为 184 字节的有效负载数据，只包含单一流的数据。


TS 包是对 PES 包的封装，还可以是对 PSI（Program Specific Information，可以理解成 节目特定信息）数据的封装。
注意 PSI 不是一个表，PSI 是一个统称， PAT，PMT，CAT，NIT 这些都是 PSI。
SI：Specific Information 特定信息，PSI中无法提供的相关信息，SI定义了NIT、SDT、EIT和TDT等9张表，方便用户查看多种信息。

在 FFmpeg 的 AVPacket 里面 data 指针 指向的 是 H264 编码的实际数据， pos 字段指向的是 TS 包的开始位置，可以看到 0x47 0x41 这种 TS 的标志数字。



//PES包头结构
头部6~9字节
{
	8 bits stream_id : 标识PES包的流类型。值为224（0xE0）;
	16 bits PES_packet_length : PES包的长度。值为0表示不固定长度;
	2 bits PES_scrambling_control : 用于加扰控制。0表示未加扰;
	1 bit PES_priority : PES包的优先级。0表示正常优先级;
	1 bit data_alignment_indicator : 数据对齐指示符。0表示数据未对齐;
	1 bit copyright : 版权标志。0表示无版权;
	1 bit original_or_copy : 原件或副本标志。0表示副本;
	2 bits PTS_DTS_flags : 指示是否存在PTS和DTS。值为2表示只有PTS存在;
	1 bit ESCR_flag : ESCR标志。0表示没有ESCR;
	1 bit ES_rate_flag : ES速率标志。0表示没有速率信息;
	1 bit DSM_trick_mode_flag : DSM特技模式标志。0表示没有特技模式;
	1 bit additional_copy_info_flag : 附加拷贝信息标志。0表示没有附加信息;
	1 bit PES_CRC_flag : PES包的CRC标志。0表示没有CRC;
	1 bit PES_extension_flag : PES扩展标志。0表示没有扩展;
	8 bits PES_header_data_length : PES头数据的长度。值为5;
	33 bits PTS : 显示时间戳，用于同步音视频。这里的值是126000，表示时间为00:00 : 01 : 400;
}


//TS 流解析流程
1、复用的MPEG - TS流中解析出TS包；
2、从TS包中获取PAT及对应的PMT（程序描述信息）；
3、从而获取特定节目的音视频PID；
4、通过PID筛选出特定音视频相关的TS包，并解析出PES；
5、从PES中读取到PTS / DTS，并从PES中解析出基本码流ES；
6、将ES交给解码器，获得压缩前的原始音视频数据。



