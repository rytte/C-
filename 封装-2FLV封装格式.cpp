/*************************/FLV封装格式/***************************************************************************/

FLV 格式由一个 FLV Header和 FLV Body 组成的。

//FLV 头部（Header）9个字节：
3字节 Signature：文件格式。也就是 "FLV" 的 ASCII 码对应的数字 "0x46 0x4C 0x56"。
1字节 Version：版本号。当前版本号为 1，即"0x01"。
1字节 Flags：用于表示音频和视频的存在。低位第 0 位表示是否存在视频数据，低位第 2 位表示是否存在音频数据。如："0x05"表示都存在。
4字节 Header Size：FLV 头部的大小。通常为 9，即"0x09"。


//FLV 体（Body）由多个 Tag 组成：
FLV body = PreviousTagSize0 + Tag1 + PreviousTagSize1 + Tag2 + ... + PreviousTagSizeN - 1 + TagN

* PreviousTagSizeN 是上一个 Tag 的大小。

Tag 里面还分为两部分，Tag Header + Tag Data

Tag Header 介绍
1、TagType，用于承载音视频数据和元数据（Metadata）。主要有 3 种类型：
Script Tag，TagType 等于 18，只有一个，且在开头的位置，用于承载元数据（Metadata），如分辨率、帧率、码率等。脚本数据标签包含一个脚本数据头部（Header）和一个脚本数据负载（Payload）。脚本数据头部用于描述脚本数据负载的类型和长度。
Video Tag，TagType 等于 9，存放一帧视频的数据。音频标签包含一个音频头部（Header）和一个音频负载（Payload）。音频头部用于描述音频负载的编码格式、采样率、声道数等信息。
Audio Tag，TagType 等于 8，存放一帧音频的数据。视频标签包含一个视频头部（Header）和一个视频负载（Payload）。视频头部用于描述视频负载的编码格式、帧类型等信息。

2、DataSize，后面的 Tag Data 部分的大小。
3、TimeStamp，占 3 字节，当前这一帧视频 或者 音频的解码时间。
4、TimeStampExtended，占1 字节，解码时间扩展，因为 TimeStamp 字段只有 3 字节，如果存不下 dts，就需要用 TimeStampExtended 来扩展。
5、StreamId，这个字段总是0，但是不知道干嘛的，后面补充。


//Tag Data
//1、Script Tag
Script Tag类型中，Tag Data 里面全部都是 AMF 包，Action Message Format（信息表）。

type = 2，代表这是一个 String 包。String size = 10，代表这个字符串是 10 个字节，而 onMetaData 刚好就是 10 字节了。
type = 8，代表这是一个 数组 包。metadata count 等于 16，代表这个数组的长度是 16，可以看到 MetaData 里面刚好有 16 个 Key - value 键值对。
key - value 键值对解析：key 的类型一定是字符串，前面 2 个字节代表字符串的长度，key 字符串之后的第一个字节，就是 value 的 type，value 有好几种类型的，在 FFmpeg 里面有定义，如下：
typedef enum {
	AMF_DATA_TYPE_NUMBER = 0x00,
	AMF_DATA_TYPE_BOOL = 0x01,
	AMF_DATA_TYPE_STRING = 0x02,
	AMF_DATA_TYPE_OBJECT = 0x03,
	AMF_DATA_TYPE_NULL = 0x05,
	AMF_DATA_TYPE_UNDEFINED = 0x06,
	AMF_DATA_TYPE_REFERENCE = 0x07,
	AMF_DATA_TYPE_MIXEDARRAY = 0x08,
	AMF_DATA_TYPE_OBJECT_END = 0x09,
	AMF_DATA_TYPE_ARRAY = 0x0a,
	AMF_DATA_TYPE_DATE = 0x0b,
	AMF_DATA_TYPE_LONG_STRING = 0x0c,
	AMF_DATA_TYPE_UNSUPPORTED = 0x0d,
} AMFDataType;

value 的字节大小是由 type 决定的
如果 value 的 type 是 AMF_DATA_TYPE_NUMBER，那 value 就占 8 字节，存储的是浮点数。
如果 value 的 type 是 AMF_DATA_TYPE_BOOL，那 value 就占 1 个字节，存储的是 0 或者 1。
如果 value 的 type 是 AMF_DATA_TYPE_STRING，那 value 就占 x 个字节，xxx


//2、Video Tag
Video Tag类型中，Tag Data 里面有两个字段是固定的：FrameType 与 CodecID，他们各占 4 位。

CodecID 指名使用的是哪种编码标准
FrameType 帧类型还需要用 AVCPacketType 辅助判断（如果有的话）

当 CodecID 是 7（AVC）的时候，AVCPacketType 有 3 个值，如下：
0，代表后面的数据是 AVC 序列头
1，代表后面的数据是 AVC NALU 单元
2，代表 AVC 序列结束。

Video Data 里面的 CompositionTime Offset 是时间补偿，是用来计算有 B 帧场景的 PTS 的，
Tag Header 里面的 TimeStamp 是解码时间，需要加上 CompositionTime Offset 才是 PTS。


//3、Audio Tag
Audio Tag类型中，Tag Data 里面有 4 个字段是固定的
SoundFormat：音频格式
SoundRate：采样率
SoundSize：采样深度
SoundType：声道

当 SoundFormat 等于 10 （AAC）的时候，AACAUDIODATA 里面的 AACPacketType 有 2 个值：
1、当 AACPacketType 等于 0，代表这是 AudioSpecificConfig（序列头），AudioSpecificConfig 只出现在第一个 Audio Tag 中
2、当 AACPacketType 等于 1，代表这是 AAC Raw frame data，也就是AAC 的裸流


