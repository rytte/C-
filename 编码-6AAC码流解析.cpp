/*************************/AAC编码原理/***************************************************************************/
AAC（Advance Audio Coding，高级音频编码）基于MPEG - 2的音频编码技术，被认为是MP3的继任者，相对MP3有更高的压缩效率。
随着MPEG - 4（MP4）标准在2000年的成型，则为AAC也叫M4A。


//SBR
SBR技术即Spectral Band Replication(频段复制)音乐的主要频谱集中在低频段，高频段幅度很小，但很重要，决定了音质。
如果对整个频段编码，若是为了保护高频就会造成低频段编码过细以致文件巨大；
若是保存了低频的主要成分而失去高频成分就会丧失音质。
SBR把频谱切割开来，低频单独编码保存主要成分，高频单独放大编码保存音质，“统筹兼顾”了，
在减少文件大小的情况下还保存了音质，完美的化解这一矛盾。

//PS
PS指“parametric stereo”（参数立体声）。原来的立体声文件文件大小是一个声道的两倍。
但是两个声道的声音存在某种相似性，根据香农信息熵编码定理，相关性应该被去掉才能减小文件大小。
所以PS技术存储了一个声道的全部信息，然后，花很少的字节用参数描述另一个声道和它不同的地方。

//AAC编码规格
MPEG - 2 AAC LC 低复杂度规格（Low Complexity） 注：比较简单，没有增益控制，但提高了编码效率，在中等码率的编码效率以及音质方面，都能找到平衡点
MPEG - 2 AAC Main 主规格
MPEG - 2 AAC SSR 可变采样率规格（Scaleable Sample Rate）
MPEG - 4 AAC LC 低复杂度规格（Low Complexity）-- - 现在的手机比较常见的MP4文件中的音频部份就包括了该规格音频文件
MPEG - 4 AAC Main 主规格 注：包含了除增益控制之外的全部功能，其音质最好
MPEG - 4 AAC SSR 可变采样率规格（Scaleable Sample Rate）
MPEG - 4 AAC LTP 长时期预测规格（Long Term Predicition）
MPEG - 4 AAC LD 低延迟规格（Low Delay）
MPEG - 4 AAC HE 高效率规格（High Efficiency）-- - 这种规格适合用于低码率编码，有Nero ACC 编码器支持

目前使用最多的就是LC和HE（适合降低码率）
流行的Nero AAC编码程序只支持LC，HE，HEv2这三种规格，编码后的AAC音频，规格显示都是LC。
HE其实就是AAC（LC） + SBR技术，HEv2就是AAC（LC） + SBR + PS技术；


//AAC的编码工序
滤波器组（Filter bank）
时域噪音修整（Temporal Noise Shaping，TNS）：这项神奇的技术可以通过在频率域上的预测，来修整时域上的量化噪音的分布。在一些特殊的语音和剧烈变化信号的量化上，TNS技术对音质的提高贡献巨大！
预测（Prediction）：对音频信号进行预测可以减少重复冗余信号的处理，提高效率。
量化（Quantization）：AAC的量化过程是使用两个巢状循环进行反复运算。通过对量化分析的良好控制，比特率能够被更高效地利用。
比特流格式（Bit－stream format）：在AAC中，信息的传输都要经过熵编码，以保证冗余尽可能少。此外AAC拥有一个弹性的比特流结构，使得编码效率进一步提高。
长时期预测（Long Term Prediction，LTP）：这是一个MPEG－4 AAC中才有的工具，它用来减少连续两个编码音框之间的信号冗余，对于处理低码率的语音非常有效。
知觉噪音代替（Perceptual Noise Substitution，PNS）：这也是MPEG－4 AAC中才有的工具，当编码器发现类似噪音的信号时，并不对其进行量化，而是作个标记就忽略过去，当解码时再还原出来，这样就提高了效率。


//AAC音频格式
ADIF(Audio Data Interchage Format，音频数据交换格式）：只有一个统一的头，必须得到所有数据后解码，适用于本地文件。比较少见。
	这种格式的特征是可以确定的找到这个音频数据的开始，不需进行在音频数据流中间开始的解码，
	即它的解码必须在明确定义的开始处进行。故这种格式常用在磁盘文件中。
ADTS(Audio Data Transport Stream，音视数据传输流）：每一帧都有头信息，任意帧解码，适用于传输流。
	这种格式的特征是它是一个有同步字的比特流，解码可以在这个流中任何位置开始。
	它的特征类似于mp3数据流格式。这种格式可以用于广播电视。



/*************************/ADIF帧结构/***************************************************************************/
这个格式比较少见，简单认识一下即可。

ADIF格式的序列，由adif_header、byte_alignment、raw_data_stream三部分组成。
byte_alignment是用来做字节对齐的，也就是说，ADIF格式由一个ADIF头信息(adif_header) 和 原始数据流(raw_data_stream) 构成。

//adif_header
字段							比特数
adif_id						32
copyright_id_present			1
copyright_id					72（copyright_id_present为1时才存在该字段）
original_copy					1
home						1
bitstream_type				1
bitrate						23
num_program_config_elements	4
adif_buffer_fullness				20



/*************************/ADTS帧结构/***************************************************************************/
ADTS的组成单元是ADTS Frame。
ADTS Frame由ADTS_Header和AAC ES组成。
ADTS_Header包含采样率、声道数、帧长度的信息。ADTS头信息的长度是7个字节或9字节（有CRC的情况）。

//ADTS_Header可以分为以下三部分：
adts_fixed_header：每一帧的内容是不变的。
adts_variable_header：每一帧的内容是存在变化的。
crc：16bits，protection_absent字段为0时存在。

adts_fixed_header：
字段						比特数		说明
syncword					12			所有位必须为1，即0xFFF。
ID						1			0代表MPEG - 4, 1代表MPEG - 2。
layer						2			所有位必须为0。
protection_absent			1			1代表没有CRC，0代表有。
profile					2			配置级别（Table1.17）
sampling_frequency_index	4			标识使用的采样频率，具体见表。
private_bit				1			see ISO / IEC 11172 - 3, subclause 2.4.2.3 (Table 8).
channel_configuration		3			取值为0时，通过inband 的PCE设置channel configuration。
original / copy				1			编码时设置为0，解码时忽略。
home					1			编码时设置为0，解码时忽略。

adts_variable_header：
字段								比特数		说明
copyright_identification_bit			1			编码时设置为0，解码时忽略。
copyright_identification_start	1					编码时设置为0，解码时忽略
frame_length						13			帧长度，包括header和crc的长度，单位byte
adts_buffer_fullness					11
number_of_raw_data_blocks_in_frame	2			ADTS帧中的AAC Frames(RDB)数减1, 为了最大的兼容性通常每个ADTS frame 包含一个AAC frame。


//AAC文件处理流程：
（1）判断文件格式，确定为ADIF或ADTS
（2）若为ADIF，解ADIF头信息，跳至第6步。
（3）若为ADTS，寻找同步头。
（4）解ADTS帧头信息。
（5）若有错误检测，进行错误检测。
（6）解块信息。
（7）解元素信息。
注意：有时候在处理AAC音频流的时候（比如：把 AAC 音频的 ES 流从 FLV 封装格式中抽出来送给硬件解码器)，
编码后的 AAC 文件在PC或者手机上不能播放，导致播放错误，
很大可能的原因是 AAC 文件的每一帧缺少 ADTS 头信息文件的包装拼接，这时需要加上头文件 ADTS 即可。









