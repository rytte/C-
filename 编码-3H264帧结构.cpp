/*************************/H264帧结构/***************************************************************************/
H.264，也称为MPEG - 4 AVC（Advanced Video Coding，高级视频编码）


//H264帧结构
H264将其组织成为序列(GOP)、图⽚(pictrue)、⽚(Slice)、宏块(Macroblock)、⼦块(subblock)五个层次。
H264视频码流是由若干个GOP组成，而GOP由一个I帧和多个P帧 / B帧组成，一个帧含一个或多个片。
如果采用DP（数据分割）机制，那么一个片由多个NALU组成。不采用DP机制时，一个片就是一个NALU。
同时片也由宏块（MB）组成。宏块是编码处理的基本单元。


//NAL与VLC
H264在功能上分为两层：NAL 层，和VLC层。
NAL（NetworkAbstraction Layer，网络抽象层）在将VLC层数据进行存储或者传输前需要将这些VLC数据映射或者封装到NAL单元中。
VLC（VideoCoding Layer，视频编码层）视频图像编码后输出的数据，他表示被压缩后的视频序列。

//NAL结构
在一帧编码图像中存在一个或多个NAL Unit；
NAL Unit 包含 NAL Unit Header（Nal 单元头信息）和 NAL Unit Body（Nal 单元主体数据）；
NAL Unit Header 由起始码和Nal Type组成。
NAL Unit Body 通常是RBSP数据，即编码后的比特流数据。


//RBSP、SODB、EBSP三者的区别和联系
（1）SODB（String Of Data Bits，原始数据比特流）：最原始的编码数据，没有任何附加数据
（2）RBSP（Raw Byte Sequence Payload，原始字节序列载荷）：在 SODB 的基础上加了rbsp_stop_ont_bit（bit 值为 1）并用 0 按字节补位对齐
（3）EBSP（Encapsulated Byte Sequence Payload，扩展字节序列载荷）：在 RBSP 的基础上增加了防止伪起始码字节（0X03）
（4）NALU是对RBSP的封装。而RTP之类的是对NALU的封装。

NALU = NALU Header + RBSP
其实严格来说，这个等式是不成立的，因为RBSP并不等于NALU刨去NALU Header。严格来说，NALU的组成部分应为：
NALU = NALU Header + EBSP

//RBSP尾部
有两种，大多数类型的NALU，使用RBSP尾部。nal_unit_type等于1~5时，使用条带RBSP尾部。
RBSP尾部（rbsp_trailing_bits）：含rbsp_stop_one_bit（值为1）并使用rbsp_alignment_zero_bit（值为0）字节对齐补齐
条带RBSP尾部（rbsp_slice_trailing_bits）：含rbsp_trailing_bits（即上一尾部），
——当entropy_coding_mode_flag值为1即当前采用的熵编码为CABAC，而且more_rbsp_trailing_data()返回为true，
——也即RBSP中有更多数据时，添加一个或多个0x0000。

//防止竞争
EBSP相较于RBSP，多了防止竞争的一个字节：0x03。

我们知道，H.264编码时，每个NALU的起始码为0x000001或0x00000001，
同时H264规定，解码器在码流中检测到起始码为0x000000或0x00000000时，表示当前NALU的结束。
因此为了防止NAL内部出现0x000001的数据，H.264又提出"防止竞争 emulation prevention"机制，
在编码器编码完一个NAL时，应该检测NALU内部，如果检测出有连续两个0x00字节（如下左侧的四个序列），就在后面插入一个0x03。
当编码器检测到它们存在时，就在最后一个字节前，插入一个新的字节：0x03。
当解码器在NAL内部检测到0x000003的数据，就把0x03抛弃，恢复原始字节序列载荷（RBSP）。
0x000000 -----------> 0x00000300
0x000001 -----------> 0x00000301
0x000002 -----------> 0x00000302
0x000003 -----------> 0x00000303


//结构拆分
H264比特流 = 起始码 + NALU + 起始码 + NALU
NALU = NALU Header + EBSP
EBSP =  RBSP（0x03处理）
RBSP = SODB + rbsp_trailing_bits

H264比特流 = （起始码 + NALU Header + SODB + rbsp_trailing_bits）* N
H264比特流 = （0x000001 0x67 SODB 0x01 0x00）* N


//特殊数据
0x000000		结束码
0x000001		起始码
0x000002		保留使用
0x000003		防止竞争



/*************************/NAL单元（NALU）的组成/***************************************************************************/
NALU 分为VCL和no - VCL。（NALU 单元 TYPE 值等于 1 到 5 和 12 的 NAL 单元是VCL NAL单元，其他的 NAL 单元都是非 VCL NAL 单元）
VCL 是图像编码数据
NO - VCL是非视频信息，配置信息


//NALU起始码
分为3或者4字节的0x000001和0x00000001两种的开始码，主要用于分隔每个NALU。

//NALU头信息（一个字节）
1位 F（forbidden_zero_bit，禁止位）：网络发现NAL单元有比特错误时可设置该比特为1，以便接收方丢掉该单元。
2位 NRI（nal_ref_dic，重要性指示位）：标志该NAL单元用于重建时的重要性，值越大，越重要。取00~11。
5位 TYPE（nal_unit_type，NALU类型）：1~23表示单个NAL包，24~31需要分包或者组合发送。

nal_unit_type取值含义
0		没有定义
1-23		NAL单元，单个NAL单元包
1		不分区，非IDR图像的片
2		片分区A
3		片分区B
4		片分区C
5		IDR图像中的片
6		补充加强信息单元
7		SPS
8		PPS
9		序列结束
10		序列结束
11		码流借宿
12		填充
13		序列参数集扩展
14-23	保留
24		STAP - A单一时间的组合包
25		STAP - B单一时间的组合包
26		MTAP16单一时间的组合包
27		MTAP24单一时间的组合包
28		FU - A分片的单元
29		FU - B分片的单元
30-31	没有定义

//NAL Payload
具体的NAL内容payload


//解析
在解析Nal Unit 的时候首先要找到起始码，根据起始码的位置来判断一个Nal Unit的开始或者结束。
Nal Unit 根据类型可以分为 SPS、PPS、I Slice、P slice、B slice等。

SPS（Sequence Paramater Set，序列参数集）主要记录了编码视频的的 Profile、level、图像宽高等。
PPS（Picture Paramater Set，图像参数集）主要记录编码数据所依赖的参数，如参考帧，图像序列计算方法等。
Islice / Pslice / Bslice：编码帧片数据：在编码I帧、P帧或者B帧的时候会将待编码的图像分成一个或多个Slice(片)，对每个Slice单独编码生成Slice编码数据；在多线程的时候多个Slice可以并行编码提高编码速度。

SPS和PPS记录的数据是GOP里面图像的信息或者单个图像的信息，这些信息都是公共的部分，比如一个GOP的图像分辨率都是一样的；
所以通常SPS和PPS Nal Unit数据放在GOP的IDR帧前面或者I帧前面，通常说PPS和SPS在IDR / I帧里面。


//举例
NALU头为0x67, 转换为二进制0110 0111
禁止位为0
NAL重要性为11，即3，表示最重要
NALU类型为[00111], 即7，类型为7表示该NALU是SPS



/*************************/RTP报文的封包格式/***************************************************************************/
RTP报文的封包格式 一共有三种模式：

//1、单一NALU模式（即一个RTP包仅由一个完整的NALU组成）
删除起始码，添加RTP Header后即为RTP包
RTP Payload = [NAL Header] + [NAL Payload]

//2、组合封包模式（当H264 NALU的长度较小时，将几个NALU单元封装在一个RTP数据包中）
开头一字节是NALU头信息，接着1个或多个聚合单元，后面是可选的RTP填充。
组合包模式有四种类型：24 STAP-A，25 STAP-B，26 MTAP16，27 MTAP24。

//3、分片封包模式（当H264 NALU的长度超过 MTU 时, 就必须对 NALU 单元进行分片封包）
主要包含28 FU - A和29 FU - B两种形式
FU - A分包格式：8位 FU indicator + 8位 FU Header + FU payload + RTP填充字节
FU indicator格式与NALU Header的头信息一致（F、NRI、TYPE）
FU Header格式如下：
1位 S：值为1，表示NAL分包的开始，其余情况值为0。
1位 E：值为1，表示NAL分包的结束，其余情况为0。
1位 R：值为0，表示保留位。
5位 Type：值为H264 NALU Header中的Type。



/*************************/H264封装示例/***************************************************************************/
1、SPS、PPS采用单包模式发送。
2、I帧、P帧采用FU - A分包模式发送。
3、注意RTP Header中Mark标记位的设置和相对时间戳的设置。 MARK标记的是首包


//AUD
一般文档没有对AUD进行描叙，其实这是一个帧开始的标志，字节顺序为：00 00 00 01 09 f1，
从结构上看，有start code, 所以确实是一个NALU，类型09在H264定义里就是AUD（分割器）。
大部分播放器可以在没有AUD的情况下正常播放。
紧随AUD，一般是SPS / PPS / SEI / IDR的组合或者简单就是一个SLICE，也就是一个帧的开始。
像Flash这样的播放器，每次需要一个完整的帧数据，那么把2个AUD之间的数据按照格式打包给播放器就可以了。


//总结
总的来说，H264的码流的打包方式有两种, 一种为annex - b（也叫byte stream format）的格式，
这个是绝大部分编码器的默认输出格式，就是每个帧的开头的3~4个字节是H264的start_code, 0x00000001或者0x000001；
另一种是原始的NAL打包格式AVCC，就是开始的若干字节（1，2，4字节）是NAL的长度，而不是start_code, 
此时必须借助某个全局的数据来获得编码器的profile, level, PPS, SPS等信息才可以解码。


//H.264的NALU单元组织格式
这里需要了解下H264打包方式，所谓打包方式就是如何组织一连串的NALU单元为完整的H264码流，目前有两种主流格式：
Annex-B 和 AVCC，两种格式都有防止竞争字节。

//一、Annex-B:
通过起始码startCode(0x00000001或0x000001)来分割NALU,打包方式如下：
[start Code]–[NALU]–[start code]–[NALU]…

Annex B格式通常用于实时的流格式，比如说传输流，通过无线传输的广播、DVD等。
在这些格式中通常会周期性的重复SPS和PPS包，经常是在每一个关键帧之前，
因此据此建立解码器可以一个随机访问的点，这样就可以加入一个正在进行的流，及播放一个已经在传输的流。

//二、AVCC:（主要应用于MP4、FLV、MKV格式）
([extradata]) | ([length] NALU) | ([length] NALU) | …
这种模式也叫AVC1格式，和上述Annex-b相比没有起始码。 
其中AVCC这种格式下NALU一般没有sps、pps等参数信息，这些信息属于额外数据extradata存放在其他地方。
extradata后面就是nalu数据，在每帧前面几个字节（通常是4字节）是帧长度。

AVCC格式的一个优点是在开始配置解码器的时候可以跳到流的中间播放，
这种格式通常用于可以被随机访问的多媒体数据，如存储在硬盘的文件。
也因为这个特性，MP4、MKV通常用AVCC格式来存储。

第1字节：version(通常0x01)
第2字节：avc profile(值同第1个sps的第2字节)
第3字节：avc compatibility(值同第1个sps的第3字节)
第4字节：avc level(值同第1个sps的第3字节)
第5字节前6位：保留全1
第5字节后2位：NALU Length 字段大小减1，通常这个值为3，即NAL码流中使用3 + 1 = 4字节表示NALU的长度
第6字节前3位：保留，全1
第6字节后5位：SPS NALU的个数，通常为1
第7字节开始后接1个或者多个SPS数据
SPS结构[16位 SPS长度][SPS NALU data]

SPS数据后
第1字节：PPS的个数，通常为1
第2字节开始接1个或多个PPS数据
PPS结构[16位 PPS长度][SPS NALU data]


