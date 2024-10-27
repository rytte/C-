;

FLV、MKV、TS、MP4、AVI;


//FLV
{
	"FLV Header": 
	{
		"FLV头": 
		{
			"Signature": "FLV",      // 3个字节，文件格式标识符
			"Version" : 1,           // 版本号，1字节
			"Flags" : 5,             // 音视频流存在，1字节，音频位和视频位
			"HeaderSize" : 9         // FLV头大小，4字节
		}
	},
	"FLV Body": 
	{
		"PreviousTagSize": 0,    // 4字节，前一个Tag的大小，初始为0
		"ScriptTag" : 
		{
			"Tag header": 
			{
				"TagType": 18,               // 1字节，18表示ScriptData
				"DataSize" : 0,              // 3字节，后面的Tag Data部分的大小（初始为0）
				"TimeStamp" : 0,             // 3字节，当前这一帧视频或者音频的解码时间
				"TimeStampExtended" : 0,     // 1字节，解码时间扩展
				"StreamId" : 0               // 3字节，这个字段总是0
			},
			"Tag Data": 
			{
				"ScriptData": 
				{
					"DataType": "String",    // 数据类型，可能是字符串、数字等
					"Key" : "onMetaData",    // 关键字，一般为 "onMetaData"
					"MetaData" :		     // 元数据内容，包含多种信息
					{               
						"duration": 0,       // 视频时长
						"width" : 0,         // 视频宽度
						"height" : 0,        // 视频高度
						"framerate" : 0,     // 帧率
						"videocodecid" : 0,  // 视频编码ID
						"audiosamplerate" : 0,// 音频采样率
						"audiosamplesize" : 0,// 音频样本大小
						"audiochannels" : 0   // 音频通道数
					}
				}
			}
		},

		"PreviousTagSize": 383,
		"VideoTag": 
		{
			"Tag header": 
			{
				"TagType": 9,                // 1字节，9表示视频标签
				"DataSize" : 0,               // 3字节，后面的Tag Data部分的大小（初始为0）
				"TimeStamp" : 0,              // 3字节，当前视频帧的解码时间
				"TimeStampExtended" : 0,      // 1字节，解码时间扩展
				"StreamId" : 0                // 3字节，这个字段总是0
			},
			"Tag Data": 
			{
				"FrameType": 1,               // 1字节，帧类型，1表示关键帧
				"CodecID" : 7,                 // 1字节，视频编码ID，7表示H.264
				"AVCPacketType" : 0,           // 1字节，AVC数据包类型，0表示NALU单元
				"CompositionTime" : 0,          // 3字节，显示时间偏移
				"VideoData" : {}                // 视频数据，具体视频帧内容
			}
		},

		"PreviousTagSize": 54,
		"AudioTag": 
		{
			"Tag header": 
			{
				"TagType": 8,                // 1字节，8表示音频标签
				"DataSize" : 0,               // 3字节，后面的Tag Data部分的大小（初始为0）
				"TimeStamp" : 0,              // 3字节，当前音频帧的解码时间
				"TimeStampExtended" : 0,      // 1字节，解码时间扩展
				"StreamId" : 0                // 3字节，这个字段总是0
			},
			"Tag Data": 
			{
				"SoundFormat": 10,           // 1字节，音频格式，10表示AAC
				"SoundRate" : 3,              // 1字节，音频采样率，3表示48kHz
				"SoundSize" : 1,              // 1字节，音频样本大小，1表示16位
				"SoundType" : 1,              // 1字节，音频通道，1表示立体声
				"AudioData" : {}               // 音频数据，具体音频帧内容
			}
		}
	}
}

//补充说明
VideoTag：

TagType : 9表示该标签是视频标签。
FrameType : 表示帧类型（1为关键帧，2为非关键帧等）。
CodecID : 指示视频编码格式（例如7表示H.264）。
AVCPacketType : 指定AVC数据包的类型。
CompositionTime : 显示时间偏移，通常用于帧的显示顺序。
VideoData : 实际的视频帧数据。
AudioTag：

TagType : 8表示该标签是音频标签。
SoundFormat : 指示音频编码格式（10表示AAC）。
SoundRate : 表示音频的采样率（例如3表示48kHz）。
SoundSize : 表示音频样本大小（1表示16位）。
SoundType : 表示音频通道类型（1表示立体声）。
AudioData : 实际的音频帧数据。





//MKV
MKV（Matroska Video）是一种流行的开源容器格式，支持多种视频、音频、字幕和其他元数据流。以下是 MKV 文件格式的基本结构解析，包括其主要元素和每个部分的描述。

{
	"EBML":
	{
		"EBMLVersion": 1,               // EBML版本号
		"EBMLReadVersion" : 1,           // EBML读取版本号
		"EBMLMaxIDLength" : 4,           // EBML ID最大长度
		"EBMLMaxSizeLength" : 8           // EBML大小最大长度
	},
	"Segment":
	{
		"SegmentUID": "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx", // 16字节，唯一标识符
		"SegmentFilename" : "",            // 可选，文件名
		"PrevUID" : "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx",     // 可选，前一个分段的UID
		"PrevSize" : 0,                    // 可选，前一个分段的大小
		"TimecodeScale" : 1000000,         // 时间码缩放
		"Duration" : 0,                     // 可选，总持续时间
		"SegmentInformation" :
		{
			"Title": "Sample Title",       // 可选，片段标题
			"MuxingApp" : "mkvmerge vXX.X", // 可选，复用应用程序
			"WritingApp" : "Sample App"     // 可选，编写应用程序
		},
		"Tracks":
		[
			{
				"TrackNumber": 1,            // 轨道编号
				"TrackUID" : 12345,           // 轨道唯一标识符
				"TrackType" : "video",         // 轨道类型（video/audio/subtitle）
				"CodecID" : "V_MPEG4/ISO/AVC", // 编码类型
				"CodecPrivate" : "",           // 可选，私有数据
				"Width" : 1920,                // 视频宽度
				"Height" : 1080,               // 视频高度
				"DefaultDuration" : 416666,    // 默认持续时间（以纳秒为单位）
				"Language" : "eng"             // 可选，语言
			},
			{
				"TrackNumber": 2,            // 轨道编号
				"TrackUID" : 67890,           // 轨道唯一标识符
				"TrackType" : "audio",         // 轨道类型
				"CodecID" : "A_AAC",           // 编码类型
				"CodecPrivate" : "",           // 可选，私有数据
				"SamplingFrequency" : 48000,    // 采样率
				"Channels" : 2,                // 声道数
				"Language" : "eng"             // 可选，语言
			}
		],
		"Chapters":
		{
			"EditionEntry":
			[
				{
					"EditionUID": 1,           // 章节唯一标识符
					"ChapterAtom" :
					[
						{
							"ChapterUID": 1,       // 章节唯一标识符
							"ChapterString" : "Chapter 1", // 章节标题
							"StartTime" : 0,         // 章节开始时间
							"EndTime" : 6000000      // 章节结束时间
						}
					]
				}
			]
		},
		"Attachments":
		{
			"AttachedFile":
			[
				{
					"FileName": "sample.jpg",    // 附加文件名
					"FileData" : "",               // 附加文件数据
					"MimeType" : "image/jpeg"     // MIME类型
				}
			]
		}
	}
}

//主要结构说明
EBML :

EBML（Extensible Binary Meta Language）是 MKV 格式的底层结构，包含文件的版本和ID长度等信息。
Segment :

这是 MKV 文件的核心部分，包含所有其他信息。每个 MKV 文件可以有多个段。

SegmentUID : 唯一标识符，用于标识这个段。

SegmentInformation : 段的元数据，例如标题、复用应用程序和编写应用程序。

Tracks : 包含视频、音频和字幕轨道的信息。每个轨道都有自己的编号、类型、编码信息等。

Chapters : 章节信息，允许用户快速导航到文件中的特定部分。

Attachments : 附加文件信息，例如封面图像等。

轨道详细信息
TrackNumber : 轨道的序号。
TrackUID : 唯一标识符，用于标识轨道。
TrackType : 指示轨道的类型（视频、音频或字幕）。
CodecID : 指示使用的编码格式（例如 H.264、AAC 等）。
CodecPrivate : 可选字段，包含特定编解码器的私有数据。
Width 和 Height : 视频轨道的分辨率（仅对视频轨道有效）。
SamplingFrequency : 音频轨道的采样率。
Channels : 音频轨道的声道数。
该结构提供了对 MKV 文件的全面解析，适用于需要读取或创建 MKV 文件的应用程序。可以根据需求进行扩展或调整。




//TS
{
	"TSHeader":
	{
		"SyncByte": 0x47,               // 同步字节，固定为 0x47
		"TransportErrorIndicator" : 0,    // 传输错误指示符（1 位）
		"PayloadUnitStartIndicator" : 0,  // 有效负载单元起始指示符（1 位）
		"TransportPriority" : 0,           // 传输优先级（1 位）
		"PID" : 0,                         // 13 位的包标识符
		"TransportScramblingControl" : 0,  // 传输加扰控制（2 位）
		"AdaptationFieldControl" : 0,      // 自适应字段控制（2 位）
		"ContinuityCounter" : 0            // 连续计数器（4 位）
	},
	"AdaptationField":
	{
		"AdaptationFieldLength": 0,       // 自适应字段长度
		"DiscontinuityIndicator" : 0,       // 不连续指示符
		"RandomAccessIndicator" : 0,        // 随机访问指示符
		"ElementaryStreamPriorityIndicator" : 0, // 重点流指示符
		"PCRFlag" : 0,                      // PCR 标志
		"OPCRFlag" : 0,                     // OPCR 标志
		"SplicingPointFlag" : 0,            // 拼接点标志
		"TransportPrivateDataFlag" : 0,     // 传输私有数据标志
		"AdaptationFieldExtensionFlag" : 0, // 自适应字段扩展标志
		"PCR" : 0,                          // 程序时钟参考
		"OPCR" : 0                          // 其他程序时钟参考
	},
	"Payload":
	{
		"PacketID": 0,                     // 数据包标识符
		"PayloadUnitStartIndicator" : 0,    // 有效负载单元起始指示符
		"PayloadData" :
		{
			"VideoData":
			{
				"FrameType": "I/P/B",      // 帧类型（I帧、P帧、B帧）
				"CodecID" : "AVC",          // 编码类型（如 H.264）
				"Width" : 1920,              // 视频宽度
				"Height" : 1080,             // 视频高度
				"BitRate" : 5000000,         // 比特率
				"FrameRate" : 30             // 帧率
			},
			"AudioData":
			{
				"CodecID": "AAC",           // 编码类型（如 AAC）
				"SamplingFrequency" : 48000,  // 采样率
				"Channels" : 2,               // 声道数
				"BitRate" : 192000            // 比特率
			}
		}
	},
	"TSFooter":
	{
		"CRC32": "xxxxxxxx"               // 可选，32位循环冗余校验
	}
}

//主要结构说明
TSHeader :

TS 文件的开头部分，包含同步字节、传输错误指示符、有效负载单元起始指示符、包标识符（PID）等信息。
AdaptationField :

自适应字段，包含与包的传输相关的额外信息，如时钟参考、数据流控制和私有数据。
Payload :

有效负载部分，包含视频和音频数据的具体信息。有效负载可以包含多种类型的数据流，如视频、音频和字幕。

VideoData :

包含视频数据的属性，如帧类型（I帧、P帧、B帧）、编码类型、分辨率和比特率等。
AudioData :

包含音频数据的属性，如编码类型、采样率、声道数和比特率等。
TSFooter :

TS 文件的结束部分，可选字段，通常用于校验。
TS包结构
每个 TS 包的大小为 188 字节（常用大小），其中包括 TSHeader、AdaptationField 和 Payload 部分。可以根据需要调整这些部分以适应具体的应用场景。



//MP4
MP4（MPEG - 4 Part 14）是一种流行的多媒体容器格式，广泛用于存储视频、音频和其他媒体数据（例如字幕和元数据）。
MP4 文件使用了一种基于盒子（Box）的结构，每个 Box 是一个数据单元，用于存储媒体数据或描述数据。以下是 MP4 格式的基本结构解析：

{
	"FileTypeBox (ftyp)":
	{
		"Size": 24,                    // Box的大小
		"Type" : "ftyp",                 // Box类型
		"MajorBrand" : "isom",           // 主品牌标识
		"MinorVersion" : 512,            // 次版本号
		"CompatibleBrands" : ["isom", "iso2", "avc1", "mp41"] // 兼容的品牌
	},
	"MovieBox (moov)":
	{
		"Size": 512,                    // Box的大小
		"Type" : "moov",                 // Box类型
		"MovieHeaderBox (mvhd)" :
		{
			"Size": 108,                 // Box的大小
			"Type" : "mvhd",              // Box类型
			"Version" : 0,                // 版本号
			"CreationTime" : 0,           // 创建时间
			"ModificationTime" : 0,       // 修改时间
			"TimeScale" : 1000,           // 时间尺度
			"Duration" : 120000,          // 时长（在指定的时间尺度下）
			"PreferredRate" : 1.0,        // 推荐的播放速率
			"PreferredVolume" : 1.0,      // 推荐的播放音量
			"MatrixStructure" : "0x00010000" // 视频矩阵
		},
		"TrackBox (trak)":
		[
			{
				"Size": 300,                // Box的大小
				"Type" : "trak",             // Box类型
				"TrackHeaderBox (tkhd)" :
				{
					"Size": 92,             // Box的大小
					"Type" : "tkhd",         // Box类型
					"Version" : 0,           // 版本号
					"TrackID" : 1,           // 轨道ID
					"Duration" : 120000,     // 轨道持续时间
					"Layer" : 0,             // 轨道层级
					"AlternateGroup" : 0,    // 替代组
					"Volume" : 1.0,          // 音量（对于音频轨道）
					"Width" : 1920,          // 视频宽度
					"Height" : 1080          // 视频高度
				},
				"MediaBox (mdia)":
				{
					"Size": 200,            // Box的大小
					"Type" : "mdia",         // Box类型
					"MediaHeaderBox (mdhd)" :
					{
						"Size": 32,         // Box的大小
						"Type" : "mdhd",     // Box类型
						"TimeScale" : 48000, // 音频时间尺度
						"Duration" : 5760000, // 持续时间
						"Language" : "eng"   // 语言
					},
					"HandlerBox (hdlr)":
					{
						"Size": 33,         // Box的大小
						"Type" : "hdlr",     // Box类型
						"HandlerType" : "vide", // 处理类型（视频：vide，音频：soun）
						"Name" : "VideoHandler" // 处理名称
					},
					"MediaInformationBox (minf)":
					{
						"Size": 100,        // Box的大小
						"Type" : "minf",     // Box类型
						"VideoMediaHeaderBox (vmhd)" :
						{
							"Size": 20,     // Box的大小
							"Type" : "vmhd", // Box类型
							"GraphicsMode" : 0 // 图形模式
						},
						"SampleTableBox (stbl)":
						{
							"Size": 200,    // Box的大小
							"Type" : "stbl", // Box类型
							"SampleDescriptionBox (stsd)" :
							{
								"Size": 50, // Box的大小
								"Type" : "stsd", // Box类型
								"Entries" : [
									{
										"Codec": "avc1", // 编解码器类型
										"Width" : 1920,   // 视频宽度
										"Height" : 1080   // 视频高度
									}
								]
							},
							"TimeToSampleBox (stts)":
							{
								"Size": 24, // Box的大小
								"Type" : "stts", // Box类型
								"Entries" : [{ "SampleCount": 100, "SampleDelta" : 1001 }]
							}
						}
					}
				}
			}
		]
	},
	"MediaDataBox (mdat)":
	{
		"Size": 1048576,                 // Box的大小
		"Type" : "mdat",                  // Box类型
		"Data" : "Raw media data..."      // 原始媒体数据
	}
}

//主要结构说明
FileTypeBox(ftyp) :

文件类型 Box，包含文件的主要品牌、次版本号和兼容品牌列表。它帮助解码器识别文件类型。
MovieBox(moov) :

包含文件中所有媒体的描述信息，不包含实际媒体数据。
MovieHeaderBox(mvhd) : 包含整个文件的元数据，如创建时间、时长、时间尺度等。
TrackBox(trak) : 表示一个轨道，可以是视频轨道、音频轨道等。
TrackHeaderBox(tkhd) : 轨道的元数据，包括轨道 ID、时长、尺寸等。
MediaBox(mdia) : 包含媒体数据的详细信息。
MediaHeaderBox(mdhd) : 指定媒体的时间尺度、时长和语言。
HandlerBox(hdlr) : 指定轨道的处理类型（视频或音频）。
MediaInformationBox(minf) : 存储媒体类型的特定信息。
VideoMediaHeaderBox(vmhd) : 视频专用的 header，定义视频轨道的渲染信息。
SampleTableBox(stbl) : 采样表 Box，存储采样信息。
SampleDescriptionBox(stsd) : 描述每种采样的详细信息，如编解码器类型和视频尺寸。
TimeToSampleBox(stts) : 定义采样时间，以便播放器准确重现视频 / 音频。
MediaDataBox(mdat) :

媒体数据 Box，包含视频、音频等媒体数据的原始二进制内容。




//AVI
AVI（Audio Video Interleave）是一种多媒体容器格式，用于同步播放音频和视频。AVI 文件基于 RIFF(Resource Interchange File Format) 格式，其结构类似树状，由“块”（Chunk）构成，每个块包含头标识、大小和数据。以下是 AVI 格式的基本结构解析：

{
	"RIFF_Header":
	{
		"ChunkID": "RIFF",             // 固定为 "RIFF"，表明是 RIFF 文件
		"ChunkSize" : 4096,             // 文件大小（不包括 ChunkID 和 ChunkSize 字段）
		"Format" : "AVI",               // 文件格式类型，固定为 "AVI"
	},
	"AVI_Main_Header":
	{
		"ChunkID": "LIST",             // 表明是一个列表
		"ChunkSize" : 2048,             // 主头信息的大小
		"Format" : "hdrl",              // 列表类型为 "hdrl"，即主头列表
		"AVI_Header" :
		{
			"ChunkID": "avih",         // AVI 文件头块
			"ChunkSize" : 56,           // 文件头的大小
			"MicroSecPerFrame" : 33333, // 每帧的时间（微秒），用于视频帧率计算
			"MaxBytesPerSec" : 250000,  // 每秒最大数据量
			"PaddingGranularity" : 0,   // 填充的粒度（对齐要求）
			"Flags" : 16,               // 文件标志，如是否有索引
			"TotalFrames" : 1000,       // 视频总帧数
			"InitialFrames" : 0,        // 初始帧数
			"Streams" : 2,              // 文件中流的数量
			"SuggestedBufferSize" : 0,  // 建议的缓冲区大小
			"Width" : 1920,             // 视频宽度
			"Height" : 1080,            // 视频高度
			"Reserved" : [0, 0, 0, 0]   // 保留字段
		}
	},
	"Stream_Header_List":
	[
		{
			"ChunkID": "LIST",          // 表明是一个列表
			"ChunkSize" : 1024,          // 视频流头信息的大小
			"Format" : "strl",           // 列表类型为 "strl"，即流列表
			"Stream_Header" :
			{
				"ChunkID": "strh",       // 流头块
				"ChunkSize" : 56,         // 流头的大小
				"StreamType" : "vids",    // 流的类型（视频："vids"，音频："auds"）
				"Handler" : "MJPG",       // 编解码器标识符，如视频的 MJPG
				"Flags" : 0,              // 流的标志
				"Priority" : 0,           // 优先级
				"Language" : 0,           // 语言
				"InitialFrames" : 0,      // 初始帧数
				"Scale" : 1,              // 缩放值，用于帧速率计算
				"Rate" : 30,              // 帧率（Rate/Scale 即帧速率）
				"Start" : 0,              // 起始时间
				"Length" : 1000,          // 流的长度
				"SuggestedBufferSize" : 0,// 建议的缓冲区大小
				"Quality" : -1,           // 数据质量
				"SampleSize" : 0          // 每个样本的大小
			},
			"Stream_Format":
			{
				"ChunkID": "strf",       // 流格式块
				"ChunkSize" : 40,         // 流格式的大小
				"VideoFormat" :
				{
					"BiSize": 40,        // 格式大小
					"BiWidth" : 1920,     // 视频宽度
					"BiHeight" : 1080,    // 视频高度
					"BiPlanes" : 1,       // 位面数
					"BiBitCount" : 24,    // 每像素位数
					"BiCompression" : "MJPG", // 压缩类型
					"BiSizeImage" : 0,    // 图像大小
					"BiXPelsPerMeter" : 0,// 像素/米（水平）
					"BiYPelsPerMeter" : 0,// 像素/米（垂直）
					"BiClrUsed" : 0,      // 使用的颜色数
					"BiClrImportant" : 0  // 重要颜色数
				}
			}
		},
		{
			"ChunkID": "LIST",          // 表明是一个列表
			"ChunkSize" : 512,           // 音频流头信息的大小
			"Format" : "strl",           // 列表类型为 "strl"，即流列表
			"Stream_Header" :
			{
				"ChunkID": "strh",       // 流头块
				"ChunkSize" : 56,         // 流头的大小
				"StreamType" : "auds",    // 流的类型（音频："auds"）
				"Handler" : "PCM ",       // 编解码器标识符
				"Flags" : 0,              // 流的标志
				"Priority" : 0,           // 优先级
				"Language" : 0,           // 语言
				"InitialFrames" : 0,      // 初始帧数
				"Scale" : 1,              // 缩放值
				"Rate" : 48000,           // 采样率
				"Start" : 0,              // 起始时间
				"Length" : 1000,          // 流的长度
				"SuggestedBufferSize" : 0,// 建议的缓冲区大小
				"Quality" : -1,           // 数据质量
				"SampleSize" : 2          // 每个样本的大小
			},
			"Stream_Format":
			{
				"ChunkID": "strf",       // 流格式块
				"ChunkSize" : 16,         // 流格式的大小
				"AudioFormat" :
				{
					"WFormatTag": 1,      // 音频格式类型（例如 PCM 为 1）
					"NChannels" : 2,       // 声道数
					"NSamplesPerSec" : 48000, // 采样率
					"NAvgBytesPerSec" : 192000, // 每秒平均字节数
					"NBlockAlign" : 4,     // 数据块对齐
					"WBitsPerSample" : 16  // 每个样本的位数
				}
			}
		}
	],
	"Movie_Data":
	{
		"ChunkID": "movi",               // 视频数据块
		"ChunkSize" : 1000000,            // 数据块大小
		"Frames" :
		[
			{
				"ChunkID": "00db",       // 视频帧标识（视频数据：xxdb）
				"ChunkSize" : 4096,       // 帧数据大小
				"Data" : "..."            // 帧数据
			},
			{
				"ChunkID": "01wb",       // 音频帧标识（音频数据：xxwb）
				"ChunkSize" : 2048,       // 音频数据大小
				"Data" : "..."            // 音频数据
			}
		]
	},
	"Index":
	{
		"ChunkID": "idx1",                // 索引块
		"ChunkSize" : 4096,                // 索引块大小
		"Entries" :
		[
			{
				"ChunkID": "00db",       // 数据块 ID
				"Flags" : 16,             // 索引标志（关键帧标志）
				"Offset" : 512,           // 数据块的偏移量
				"Size" : 4096             // 数据块的大小
			},
			{
				"ChunkID": "01wb",       // 音频数据块 ID
				"Flags" : 0,              // 标志
				"Offset" : 8192,          // 数据块的偏移量
				"Size" : 2048             // 数据块的大小
			}
		]
	}
}

//结构说明
RIFF_Header :

文件的根头部信息，定义了文件的基本类型和格式。
AVI_Main_Header :

文件的主要头部信息，包含了视频帧率、总帧数、流的数量和视频分辨率