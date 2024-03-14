//h264编码原理
宏块的划分（宏块的组成：宏块类型、预测类型、CPB、QB、宏块颜色数据）
图像分组（有差别的像素只有10% 以内的点，亮度差值变化不超过2% ，而色度差值的变化只有1% 以内，被分为一个GOP）
帧内压缩技术原理
帧间压缩技术原理
DCT
CABAC压缩原理。


//H264帧结构
H264视频码流是由若干个GOP组成，而GOP由一个I帧和多个P帧 / B帧组成。
H264在功能上分为两层：NAL 层，和VLC层。

//NAL
NAL（NetworkAbstraction Layer，网络提取层）在将VLC层数据进行存储或者传输前需要将这些VLC数据映射或者封装到NAL单元中。
负责将VCL产⽣的⽐特字符串适配到各种各样的⽹络和多元环境中，覆盖了所有⽚级以上的语法级别。

//VLC
VLC（VideoCoding Layer，视频编码层）视频图像编码后输出的数据，他表示被压缩后的视频序列。
包括核⼼压缩引擎和块，宏块和⽚的语法级别定义，设计⽬标是尽可能地独⽴于⽹络进⾏⾼效的编码。

//NAL结构
在一帧编码图像中存在一个或多个NAL Unit；
NAL Unit 包含 NAL Unit Header（Nal 单元头）和 NAL Unit Body（Nal 单元主体数据）；
NAL Unit Header 由起始码和Nal Type组成。
NAL Unit Body 通常是RBSP(Raw Byte Sequence Payload 原始字节序列载荷)数据，即编码后的比特流数据。

在解析Nal Unit 的时候首先要找到起始码，根据起始码的位置来判断一个NalUnit的开始或者结束。
Nal Unit 根据类型可以分为 SPS、PPS、I Slice、P slice、B slice等。

SPS（Sequence Paramater Set，序列参数集）主要记录了编码视频的的 Profile、level、图像宽高等。
PPS（Picture Paramater Set，图像参数集）主要记录编码数据所依赖的参数，如参考帧，图像序列计算方法等。
Islice / Pslice / Bslice：编码帧片数据：在编码I帧、P帧或者B帧的时候会将待编码的图像分成一个或多个Slice(片)，对每个Slice单独编码生成Slice编码数据；在多线程的时候多个Slice可以并行编码提高编码速度。

SPS和PPS记录的数据是GOP里面图像的信息或者单个图像的信息，这些信息都是公共的部分，比如一个GOP的图像分辨率都是一样的；
所以通常SPS和PPS Nal Unit数据放在GOP的IDR帧前面或者I帧前面，通常说PPS和SPS在IDR / I帧里面。

