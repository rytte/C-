/*************************/H264帧结构/***************************************************************************/
H.264，也称为MPEG - 4 AVC（Advanced Video Coding，高级视频编码）


//H264帧结构
MPEG 视频基本码流（Elementary Stream，ES）结构分为五层
图像组(GOP)、帧(Frame)、【NALU】、⽚(Slice)、宏块(Macroblock)、⼦块(subblock)、【像素】五个层次。
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


//结构拆分
H264比特流 = 起始码 + NALU + 起始码 + NALU
NALU = NALU Header + EBSP
EBSP = RBSP（0x03处理）
RBSP = SODB + rbsp_trailing_bits

H264比特流 = （起始码 + NALU Header + SODB + rbsp_trailing_bits） * N
H264比特流 = （0x000001 0x67 SODB 0x01 0x00） * N


//码流分析
0x000001	0x67 0xXX      0x000001 0x68 0xXX	0x000001 0x65 0xXX     0x000001			0x41	 0xXX     0x000001			0x41	 0xXX
起始码	SPS   sps数据			PPS	pps数据			I帧	 i帧数据(像素数据+预测方向)	P帧	 p帧数据(运动矢量+差异数据)   B帧	 b帧数据(运动矢量)

*单个宏块包含：   像素数据、    预测方向、   运动矢量
（H265说法）：（编码单元）（预测单元）（变换单元）

//RBSP、SODB、EBSP三者的区别和联系
（1）SODB（String Of Data Bits，原始数据比特流）：最原始的编码数据，没有任何附加数据
（2）RBSP（Raw Byte Sequence Payload，原始字节序列载荷）：在 SODB 的基础上加了rbsp_stop_ont_bit（bit 值为 1）并用 0 按字节补位对齐
（3）EBSP（Encapsulated Byte Sequence Payload，扩展字节序列载荷）：在 RBSP 的基础上增加了防止伪起始码字节（0X03）
（4）NALU是对RBSP的封装。而RTP之类的是对NALU的封装。


//RBSP尾部
有两种，大多数类型的NALU，使用RBSP尾部。nal_unit_type等于1~5时，使用条带RBSP尾部。
RBSP尾部（rbsp_trailing_bits）：含rbsp_stop_one_bit（值为1）并使用rbsp_alignment_zero_bit（值为0）字节对齐补齐
条带RBSP尾部（rbsp_slice_trailing_bits）：含rbsp_trailing_bits（即上一尾部），
——当entropy_coding_mode_flag值为1即当前采用的熵编码为CABAC，而且more_rbsp_trailing_data()返回为true，
——也即RBSP中有更多数据时，添加一个或多个0x0000。


//特殊数据
0x000000		结束码
0x000001		起始码
0x000002		保留使用
0x000003		防止竞争


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

通常每个GOP中只有一个SPS和一个PPS，放在IDR / I帧之前(内部)，且SPS在PPS的前面，他们记录了整个GOP中的每张图像的信息或者单个图像的信息。
I/IDR帧内部：SPS、PPS、I Slice * n


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



/*************************/发包/***************************************************************************/
1、SPS、PPS采用单包模式发送。
2、I帧、P帧采用FU - A分包模式发送。
3、注意RTP Header中Mark标记位的设置和相对时间戳的设置。 MARK标记的是首包


//AUD
一般文档没有对AUD进行描叙，其实这是一个帧开始的标志，字节顺序为：00 00 00 01 09 f1，
从结构上看，有start code, 所以确实是一个NALU，类型09在H264定义里就是AUD（分割器）。
大部分播放器可以在没有AUD的情况下正常播放。
紧随AUD，一般是SPS / PPS / SEI / IDR的组合或者简单就是一个SLICE，也就是一个帧的开始。
像Flash这样的播放器，每次需要一个完整的帧数据，那么把2个AUD之间的数据按照格式打包给播放器就可以了。



/********************/AVCC 和 Annex - B/************************************************************/
//AVCC和Annex-B
AVCC 和 Annex - B 是 H.264（或 HEVC）码流的两种封装格式，主要区别在于它们如何 标识 NAL 单元（NALU），也就是编码后的一帧一帧数据的组织方式。

Annex - B：适合直播或流式传输（如 RTSP、MPEG - TS），播放器边收边播。
AVCC：适合本地文件或点播（如 MP4），支持快速定位和精准索引，节省空间。


//主要区别
区别有两点：一个是参数集(SPS, PPS)组织格式；一个是分隔。
Annex - B：使用起始码分隔NAL(起始码为三字节或四字节，0x000001或0x00000001，一般是四字节)；SPS和PPS按流的方式写在头部。
AVCC：使用NALU长度（4字节）分隔NAL；在头部包含extradata(或sequence header)的结构体。（extradata包含分隔的字节数、SPS和PPS）


//AVCC和Annex-B区别
特性					Annex - B									AVCC（又叫 AVC1）
NALU 分隔符			使用起始码（Start Code）						使用长度前缀（Length Prefix）
起始码格式			0x000001 或 0x00000001						无起始码
结构					[0x00000001][NALU][0x00000001][NALU] ...	[4字节长度][NALU][4字节长度][NALU] ...
封装用途				TS、FLV(RTMP)、裸流、RTSP 等流式封装			MP4、FLV、MKV、MOV
是否包含 SPS / PPS	通常每个关键帧前包含 SPS / PPS				SPS / PPS 在 mp4 的 extradata 中



aligned(8) class AVCDecoderConfigurationRecord {
    unsigned int(8) configurationVersion = 1;
    unsigned int(8) AVCProfileIndication;
    unsigned int(8) profile_compatibility;
    unsigned int(8) AVCLevelIndication;
    bit(6) reserved = ‘111111’b;
    unsigned int(2) lengthSizeMinusOne;
    bit(3) reserved = ‘111’b;
    unsigned int(5) numOfSequenceParameterSets;
    for (i = 0; i < numOfSequenceParameterSets; i++) {
        unsigned int(16) sequenceParameterSetLength;
        bit(8 * sequenceParameterSetLength) sequenceParameterSetNALUnit;
    }
    unsigned int(8) numOfPictureParameterSets;
    for (i = 0; i < numOfPictureParameterSets; i++) {
        unsigned int(16) pictureParameterSetLength;
        bit(8 * pictureParameterSetLength) pictureParameterSetNALUnit;
    }
}

//extradata
/*
 * extradata: [1字节编码格式][4字节 SPS 的数量][2字节SPS的NALU长度][SPS的NALU][2字节PPS的NALU长度][PPS的NALU]
 *
 * extradata = {
 *     0x01,                    // 标识数据格式（在某些情况下为 0x01 表示 AVCC 格式）
 *     0x06, 0x00, 0x1E, 0xFF,  // 第5个字节的低5位为 SPS 的数量
 *     0x00, 0x1F,              // SPS NAL unit 的长度，此处表示长度为 31 字节，如果是 AnnexB 格式的话，此处为起始码
 *     0x67, 0x64, 0x00, 0x1F,  // SPS NAL unit (0x67开头; 包括图像大小、色彩信息等)
 *     0x4D, 0x40, 0x1F, 0xD5,
 *     0xA9, 0x90, 0x6F, 0x21,
 *     0x00, 0x1F,              // PPS NAL unit 的长度，此处表示长度为 31 字节
 *     0x68, 0x64, 0x00, 0x1F,  // PPS NAL unit (0x68开头; 编码的图像参数)
 *     0x4D, 0x40, 0x1F, 0xD5,
 *     0xA9, 0x90, 0x6F, 0x22
 * };
 */

AVCProfileIndication 一般取值为 66、77、88、100、110、122、244，对应的 Profile 分别是 Baseline、Main、Extended、High、High10、High422、High444。
AVCLevelIndication 一般取值为 30、31、32、40、41、42、50、51、52，对应的 Level 分别是 3.0、3.1、3.2、4.0、4.1、4.2、5.0、5.1、5.2。


AVCProfileIndication(8 bits)
这是一个 8 位的值，表示 AVC 编码器使用的 Profile（编码配置文件）。

常见的 H.264 Profile 值如下：
0x42：Baseline Profile
0x4D：Main Profile
0x58：High Profile
这个值用于指示解码器支持的 Profile 类型，它与编码视频时选择的 Profile 类型匹配。

profile_compatibility(8 bits)
这也是一个 8 位的值，表示 Profile Compatibility（配置文件兼容性）。它是一个位字段，每一位表示对特定 Profile 的支持。例如，如果一个位为 1，表示支持该 Profile。
该字段的各个比特位通常用于表示支持的其他 Profile，如：
比特0：是否支持 Baseline Profile
比特1：是否支持 Main Profile
比特2：是否支持 High Profile
等等...

AVCLevelIndication(8 bits)
这是一个 8 位的值，表示 AVC Level（级别）。AVC Level 定义了视频的编码复杂度和分辨率限制。
这个值表明视频流的级别限制，影响视频的分辨率、帧率等。

reserved(6 bits)
这 6 位是保留位，通常被设为 111111，意味着这些位应保持为 1，并且没有实际的用途。它们只用于对齐和协议兼容性。

lengthSizeMinusOne(2 bits)
这 2 位表示 NAL 单元长度字段 的大小，值为 lengthSizeMinusOne。
它用于指示 NALU 长度字段的大小。lengthSizeMinusOne 是 NALU 长度字段大小减去 1。具体来说，它表示：
00 表示 NAL 单元大小为 1 字节（即 4 字节）
01 表示 NAL 单元大小为 2 字节（即 16 字节）
10 表示 NAL 单元大小为 4 字节（即 64 字节）
11 是无效的。



//✅ Annex - B 示例（用于流媒体）
00 00 00 01 67 64 00 29 ...  ← SPS（起始码 + NALU）
00 00 00 01 68 EE 3C 80 ...  ← PPS
00 00 00 01 65 88 84 ...     ← I 帧数据（IDR）

每个 NALU 用 0x00000001 开头；
解码器读取起始码就知道下一段是一个 NALU。


//✅ AVCC 示例（用于 MP4 封装）
00 00 00 1A 67 64 00 29 ...  ← SPS（4字节长度前缀）
00 00 00 06 68 EE 3C 80 ...  ← PPS
00 00 00 25 65 88 84 ...     ← I 帧数据

每个 NALU 前 4 字节表示其长度；
适合用于随机访问的封装格式如 MP4。


//转换
"ffmpeg -i input.h264 -c:v copy output.mp4"								//Annex-B → AVCC（用于 MP4）
"ffmpeg -i input.mp4 -c:v copy -bsf:v h264_mp4toannexb output.ts"		//AVCC → Annex-B（用于 TS）



