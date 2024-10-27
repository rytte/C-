

WAV、MP3、AAC、FLAC

//WAV

WAV（Waveform Audio File Format）是一种用于存储音频波形数据的容器格式，基于 RIFF（Resource Interchange File Format）结构。WAV 文件一般由两个主要部分组成：文件头（包含音频参数）和数据块（存储实际音频数据）。以下是 WAV 文件的基本结构解析：

{
	"RIFF_Header":
	{
		"ChunkID": "RIFF",             // 固定为 "RIFF"，表示 RIFF 文件
		"ChunkSize" : 36 + Subchunk2Size, // 文件大小，等于 4 + (8 + Subchunk1Size) + (8 + Subchunk2Size)
		"Format" : "WAVE"               // 文件格式类型，固定为 "WAVE"
	},
	"Format_Subchunk":
	{
		"Subchunk1ID": "fmt ",          // 格式块标识符，固定为 "fmt "
		"Subchunk1Size" : 16,            // 格式块的大小，PCM 格式为 16 字节
		"AudioFormat" : 1,               // 音频格式代码，1 为 PCM（无压缩），其他值表示压缩格式
		"NumChannels" : 2,               // 声道数（1 为单声道，2 为立体声）
		"SampleRate" : 44100,            // 采样率（每秒采样次数，单位为 Hz）
		"ByteRate" : 176400,             // 字节速率（= SampleRate * NumChannels * BitsPerSample / 8）
		"BlockAlign" : 4,                // 数据块对齐（= NumChannels * BitsPerSample / 8）
		"BitsPerSample" : 16             // 每个样本的位数（例如 8 位、16 位）
	},
	"Data_Subchunk":
	{
		"Subchunk2ID": "data",          // 数据块标识符，固定为 "data"
		"Subchunk2Size" : 100000,        // 数据块的大小（音频数据的字节数，= NumSamples * NumChannels * BitsPerSample / 8）
		"Data" : "..."                   // 音频数据，原始 PCM 采样数据
	}
}

//结构说明
RIFF_Header :
ChunkID：固定为 "RIFF"，标明文件类型为 RIFF。
ChunkSize：文件总大小，等于文件实际大小减去前 8 字节。
Format：固定为 "WAVE"，表明文件格式为 WAV 音频。

Format_Subchunk :
Subchunk1ID：格式块标识，固定为 "fmt "。
Subchunk1Size：格式块大小，通常 PCM 格式为 16 字节。
AudioFormat：音频格式代码，1 表示 PCM 格式（无压缩），其他值为压缩格式。
NumChannels：声道数，1 表示单声道，2 表示立体声。
SampleRate：采样率，单位为 Hz。
ByteRate：字节速率，即每秒所需的字节数。
BlockAlign：数据块对齐大小，即一个采样的字节数。
BitsPerSample：每个采样的位数。

Data_Subchunk :
Subchunk2ID：数据块标识，固定为 "data"。
Subchunk2Size：音频数据大小，单位为字节。
Data：实际的音频数据，存储了 PCM 采样数据。



//MP3
MP3（MPEG - 1 Audio Layer III）是一种有损音频压缩格式，主要由帧头信息和音频数据组成。MP3 文件是由一个个帧（Frame）组成的，
每帧都是一个最小的压缩单元，包含一个帧头（Frame Header）和帧数据（Frame Data），帧头信息用来描述音频数据的格式与参数。

{
	"MP3_File":
	[
		{
			"Frame":
			{
				"Frame_Header":
				{
					"Sync": "11位同步字",                // 帧同步标识符，值固定为 0xFFF
					"MPEG_Audio_Version_ID" : "2位",       // 音频版本 ID，如 MPEG-1、MPEG-2
					"Layer" : "2位",                       // 音频层，MP3 为 Layer III，值为 01
					"Protection_Bit" : "1位",              // 保护位，0 表示有 CRC 校验，1 表示无校验
					"Bitrate_Index" : "4位",               // 比特率索引，指定音频的比特率
					"Sampling_Rate_Index" : "2位",         // 采样率索引，指定音频的采样率
					"Padding_Bit" : "1位",                 // 填充位，用于帧的字节对齐
					"Private_Bit" : "1位",                 // 私有位，应用程序可以自定义使用
					"Channel_Mode" : "2位",                // 声道模式，如立体声、单声道
					"Mode_Extension" : "2位",              // 模式扩展，用于 Joint Stereo
					"Copyright" : "1位",                   // 版权标识位
					"Original" : "1位",                    // 原版标识位，0 表示复制品，1 表示原版
					"Emphasis" : "2位"                     // 强调模式，用于处理高频部分
				},
				"Frame_Data": "音频数据"                  // 帧数据，实际的音频内容，经过压缩编码
			}
		},
		"..."
	]
}

//结构说明
Frame：
每个 MP3 文件由一个个帧（Frame）组成，每帧都是一个独立的压缩单元。

Frame_Header：
Sync（同步字）：11 位固定同步标识符，值固定为 0xFFF，用于表示帧的开始。
MPEG Audio Version ID：音频版本 ID，2 位，表示 MPEG 版本，如 MPEG - 1、MPEG - 2。
Layer：音频层信息，2 位。MP3 对应的是 Layer III，值为 01。
Protection Bit：保护位，1 位，0 表示有 CRC 校验，1 表示无 CRC 校验。
Bitrate Index：比特率索引，4 位，定义了音频的比特率。
Sampling Rate Index：采样率索引，2 位，指定音频的采样率，如 44100 Hz 等。
Padding Bit：填充位，1 位，用于对齐帧的字节数。
Private Bit：私有位，1 位，应用程序可以自由使用。
Channel Mode：声道模式，2 位，定义音频的声道模式，如立体声、单声道。
Mode Extension：模式扩展，2 位，用于 Joint Stereo（联合立体声）模式。
Copyright：版权标识位，1 位，指示音频是否有版权。
Original：原版标识位，1 位，0 表示该文件是复制品，1 表示为原版。
Emphasis：强调模式，2 位，用于音频的高频处理。

Frame_Data：
每帧的音频数据，是实际经过压缩编码的内容。这部分存储了音频的 PCM 数据，经过了 MPEG Layer III 压缩。




//AAC
AAC（Advanced Audio Coding）是一种高效的有损音频压缩格式，通常用于 MP4 等容器中。AAC 的音频流分为许多帧（Frame），每个帧包含帧头（ADTS Header）和压缩音频数据（AAC Data）。
AAC 格式通常采用 ADTS（Audio Data Transport Stream）封装格式，便于流式传输。

{
	"ADTS_Frame":
	{
		"ADTS_Header":
		{
			"Syncword": "12位",                      // 同步字，固定为 0xFFF，表示帧的开始
			"ID" : "1位",                              // MPEG 标志，0 表示 MPEG-4，1 表示 MPEG-2
			"Layer" : "2位",                          // 固定为 00
			"Protection_absent" : "1位",               // 是否有 CRC 校验，1 表示无校验
			"Profile" : "2位",                        // 表示 AAC 配置文件（如 AAC-LC 等）
			"Sampling_frequency_index" : "4位",       // 采样率索引（如 44100 Hz 等）
			"Private_bit" : "1位",                     // 私有位
			"Channel_configuration" : "3位",          // 通道配置（如单声道、立体声等）
			"Original_copy" : "1位",                   // 原始或拷贝标识
			"Home" : "1 位"                            // 主页标志
		},
		"ADTS_Variable_Header":
		{
			"Copyright_identification_bit": "1位",    // 版权标志位
			"Copyright_identification_start" : "1位",  // 版权起始位
			"AAC_frame_length" : "13位",              // AAC 数据帧长度，包括 ADTS 头和 AAC 音频数据
			"Adts_buffer_fullness" : "11位",          // ADTS 缓冲区的状态
			"Number_of_raw_data_blocks_in_frame" : "2位" // 每帧的 AAC 原始数据块数
		},
		"AAC_Raw_Data_Block": "变长"                       // AAC 编码的音频数据
	}
}

//结构说明
ADTS_Header：
SyncWord（同步字）：12 位，固定值为 0xFFF，用于标识帧的开始。
ID：1 位，表示 MPEG 版本。0 表示 MPEG - 4，1 表示 MPEG - 2。
Layer：2 位，层级，固定为 00。
ProtectionAbsent：1 位，保护位，0 表示有 CRC 校验，1 表示无 CRC 校验。
Profile：2 位，表示音频配置文件。常见的配置有 AAC - LC（低复杂度）等。
SamplingFrequencyIndex：4 位，采样率索引，用于指定采样率。例如 44100 Hz、48000 Hz。
PrivateBit：1 位，应用程序可以自由使用。
ChannelConfiguration：3 位，指定声道配置。0 表示未指定，1 表示单声道，2 表示立体声等。
OriginalCopy：1 位，指示音频是否为原始副本。
Home：1 位，广播应用中使用，通常为 0。
FrameLength：13 位，表示 ADTS 帧的总长度，包括 ADTS Header 和 AAC Data 部分。
BufferFullness：11 位，指示比特流的缓冲区状态，用于比特率控制。
NumberOfAACFrames：2 位，表示每个 ADTS 帧中的 AAC 帧数。一般为 1。

AAC_Data：
存储了实际的音频数据，包含经过 AAC 压缩的 PCM 采样数据。这部分是 ADTS 帧的核心内容。





//FLAC
FLAC（Free Lossless Audio Codec）是一种无损音频压缩格式，通常用于高质量音频存储。
FLAC 文件由一个文件头（FLAC Header）、元数据块（Metadata Blocks）和音频帧（Audio Frames）组成。

{
	"FLAC_File":
	{
		"FLAC_Header":
		{
			"MagicNumber": "4字节",                      // 固定标识符 "fLaC"
		},
		"Metadata_Blocks" :
		[
			{
				"Metadata_Block_Header":
				{
					"LastMetadataBlockFlag": "1位",       // 指示是否是最后一个元数据块
					"BlockType" : "7位",                   // 元数据块类型（如 STREAMINFO、VORBIS_COMMENT 等）
					"BlockSize" : "24位"                   // 元数据块大小，单位为字节
				},
				"Metadata_Block_Data":
				{
					"STREAMINFO":
					{
						"MinimumBlockSize": "2字节",      // 最小块大小，单位为样本
						"MaximumBlockSize" : "2字节",      // 最大块大小，单位为样本
						"MinimumFrameSize" : "3字节",      // 最小帧大小，单位为字节
						"MaximumFrameSize" : "3字节",      // 最大帧大小，单位为字节
						"SampleRate" : "20位",             // 采样率，单位为 Hz
						"Channels" : "3位",               // 声道数
						"BitsPerSample" : "5位",           // 每个样本的位深度
						"TotalSamples" : "36位",           // 总样本数
						"MD5Signature" : "16字节"          // 音频数据的 MD5 校验和
					},
					"...": "其它元数据块类型"
				}
			},
			"..."
		],
		"Audio_Frames":
		[
			{
				"Frame_Header":
				{
					"SyncCode": "14位",                   // 同步代码，值为 0x3FFE
					"BlockingStrategy" : "1位",           // 块策略，0 表示固定块大小，1 表示可变块大小
					"BlockSize" : "4位",                  // 块大小
					"SampleRate" : "4位",                 // 采样率
					"ChannelAssignment" : "4位",          // 声道分配
					"SampleSize" : "3位",                 // 采样大小（如 16 位、24 位）
					"Reserved" : "1位",                   // 保留位，始终为 0
					"FrameNumberOrSampleNumber" : "8位或UTF-8编码",  // 帧编号或样本编号
					"CRC8" : "8位"                       // 帧头的 CRC 校验码
				},
				"Subframes":
				[
					{
						"Subframe_Header":
						{
							"SubframeType": "1-6位",     // 子帧类型
							"WastedBitsFlag" : "1位"      // 指示是否存在废弃的位
						},
						"Subframe_Data" : "子帧音频数据"  // 实际的音频样本数据
					},
					"..."
				] ,
				"Frame_Footer":
				{
					"CRC16": "16位"                      // 帧数据的 CRC 校验码
				}
			},
			"..."
		]
	}
}

//结构说明
FLAC_Header：
MagicNumber：固定的 4 字节标识符 "fLaC"，用于标识 FLAC 文件格式。

Metadata_Blocks：
FLAC 文件头之后是一个或多个元数据块，元数据块的类型可以包括 STREAMINFO、VORBIS_COMMENT、PADDING、APPLICATION、SEEKTABLE 等。
Metadata_Block_Header：
LastMetadataBlockFlag：1 位，表示是否为最后一个元数据块。
BlockType：7 位，表示元数据块的类型。常见的类型包括 STREAMINFO、SEEKTABLE、VORBIS_COMMENT 等。
BlockSize：24 位，表示元数据块的大小，以字节为单位。
Metadata_Block_Data：
STREAMINFO：包含音频文件的基本信息，如采样率、声道数、总样本数和 MD5 校验和。
其它元数据块类型：如 VORBIS_COMMENT 用于存储标签信息，PADDING 用于填充等。

Audio_Frames：
包含音频数据的帧，每个帧由帧头、子帧和帧尾组成。
Frame_Header：
SyncCode：14 位的同步代码，用于标识帧的开始，固定为 0x3FFE。
BlockingStrategy：1 位，0 表示固定块大小，1 表示可变块大小。
BlockSize：4 位，表示块的大小。
SampleRate：4 位，表示采样率。
ChannelAssignment：4 位，表示声道配置。
SampleSize：3 位，表示采样大小。
FrameNumberOrSampleNumber：帧编号或样本编号，用于定位。
CRC8：帧头的 8 位 CRC 校验码。
Subframes：每个音频帧可能包含多个子帧，每个子帧代表一个声道的音频数据。
Subframe_Header：子帧的头部信息，包含子帧类型和废弃位标志。
Subframe_Data：实际的音频数据样本。
Frame_Footer：
CRC16：帧尾的 16 位 CRC 校验码，用于帧数据的完整性校验。

