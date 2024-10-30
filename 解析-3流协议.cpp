

//RTP
{
	"RTP_Packet":
	{
		"RTP_Header":
		{
			"V" : "2 位",                              // 版本号，固定为2
			"P" : "1 位",                              // 填充标志位
			"X" : "1 位",                              // 扩展标志位
			"CC" : "4 位",                             // 头部扩展长度
			"M" : "1 位",                              // 标记位
			"PT" : "7 位",                             // 负载类型（Payload Type）
			"Sequence_Number" : "16 位",              // 序列号，标识RTP包的顺序
			"Timestamp" : "32 位",                     // 时间戳，表示采样时间
			"SSRC" : "32 位",                          // 同步源标识符，标识发送源
			"CSRC" : "0 到 15 * 32 位"                  // 贡献源标识符，0到15个，表示混合源
		},
		"RTP_Payload":
		{
			"Payload_Type": "变长",                     // 负载类型，具体格式根据PT字段确定
			"Payload_Data" : "变长"                      // 实际的媒体数据（音频/视频数据）
		}
	}
}

//说明：
RTP_Header：包含了RTP包的头部信息。

V（Version）：表示RTP协议的版本，当前版本为2。
P（Padding）：指示该包是否有填充字节。
X（Extension）：指示该包是否有扩展头。
CC（CSRC Count）：指示CSRC字段的数量。
M（Marker）：用于标识特定的事件（如帧开始或结束）。
PT（Payload Type）：指示负载数据的类型（如音频、视频）。
Sequence_Number：RTP包的序列号，用于接收方排序。
Timestamp：用于同步，表示RTP包中第一个媒体样本的采样时间。
SSRC（Synchronization Source）：标识发送源的标识符。
CSRC（Contributing Sources）：包含一个或多个贡献源的标识符。
RTP_Payload：包含了具体的负载数据和其类型。

Payload_Type：根据PT字段的值确定的具体负载类型。
Payload_Data：实际的音频或视频数据。





//RTCP
{
	"RTCP_Packet":
	{
		"RTCP_Header":
		{
			"V" : "2 位",                              // 版本号，固定为2
			"PT" : "8 位",                             // 负载类型（Payload Type），指示RTCP包类型
			"Length" : "16 位",                        // 包长度，以32位字为单位
			"SSRC" : "32 位"                           // 同步源标识符，标识发送源
		},
		"RTCP_Reports":
		{
			"Reception_Report":
			{
				"SSRC" : "32 位",                     // 被报告的源的SSRC
				"Fraction_Lost" : "8 位",             // 丢包率，表示自上次报告以来丢失的分组百分比
				"Cumulative_Lost" : "24 位",          // 累计丢失的分组数量
				"Last_SRR" : "32 位",                 // 上次接收到的RTP包的序列号
				"Jitter" : "32 位",                   // 抖动，表示延迟的变化
				"LSR" : "32 位",                      // 上次接收的时间戳
				"DLSR" : "32 位"                      // 上次接收时间的延迟
			},
			"Sender_Report":
			{
				"SSRC" : "32 位",                     // 发送源的SSRC
				"NTP_Timestamp" : "64 位",            // NTP时间戳，表示发送时间
				"RTP_Timestamp" : "32 位",            // RTP时间戳
				"Packet_Count" : "32 位",             // 发送的RTP包的数量
				"Octet_Count" : "32 位"               // 发送的字节数
			}
		},
		"RTCP_Farewell":
		{
			"SSRC" : "32 位",                       // 离开的源的SSRC
			"Reason" : "变长"                       // 离开的原因，可选
		}
	}
}

//说明：
1、RTCP_Header：包含了RTCP包的头部信息。
V（Version）：表示RTCP协议的版本，当前版本为2。
PT（Payload Type）：指示RTCP包的类型，比如Sender Report(SR) 或 Reception Report(RR)。
Length：包的长度，以32位字为单位（长度不包括头部）。
SSRC（Synchronization Source）：标识发送源的标识符。
RTCP_Reports：包含了接收报告和发送报告的信息。

2、Reception_Report：报告接收到的数据包信息。
SSRC：被报告的源的SSRC。
Fraction_Lost：指示丢失的包的百分比。
Cumulative_Lost：自上次报告以来丢失的包的总数。
Last_SRR：上次接收到的RTP包的序列号。
Jitter：抖动，表示延迟的变化。
LSR（Last Sender Report）：最后发送报告的时间戳。
DLSR（Delay since Last Sender Report）：自最后发送报告以来的延迟。

Sender_Report：发送者的报告。
SSRC：发送源的SSRC。
NTP_Timestamp：发送时间的NTP时间戳。
RTP_Timestamp：RTP时间戳。
Packet_Count：发送的RTP包的数量。
Octet_Count：发送的字节数。

3、RTCP_Farewell：可选的告别包，指示某个源已离开会话。
SSRC：离开的源的SSRC。
Reason：离开的原因，可以是可选的字符串。




//RTSP
{
	"RTSP_Message":
	{
		"Request":
		{
			"Request_Line":
			{
				"Method": "方法",                        // RTSP方法，例如 OPTIONS、DESCRIBE、SETUP、PLAY、PAUSE、TEARDOWN 等
				"Request_URL" : "请求URL",               // RTSP请求的URL
				"RTSP_Version" : "RTSP版本"               // RTSP协议的版本，例如 RTSP/1.0
			},
			"Headers":
			{
				"CSeq": "序列号",                        // 请求序列号，标识请求的顺序
				"Session" : "会话ID",                     // 会话标识符，用于标识RTSP会话
				"Transport" : "传输",                     // 传输协议和端口信息，例如 RTP/AVP;unicast;client_port=8000-8001
				"Accept" : "可接受格式",                  // 表示可接受的媒体类型
				"User_Agent" : "用户代理"                 // 客户端信息
			}
		},
		"Response":
		{
			"Response_Line":
			{
				"RTSP_Version": "RTSP版本",               // RTSP协议的版本，例如 RTSP/1.0
				"Status_Code" : "状态码",                 // 响应状态码，例如 200 OK、404 Not Found
				"Reason_Phrase" : "原因短语"               // 状态码的原因短语，例如 OK、Not Found
			},
			"Headers":
			{
				"CSeq": "序列号",                        // 响应的序列号，标识请求的顺序
				"Session" : "会话ID",                     // 会话标识符，用于标识RTSP会话
				"Transport" : "传输",                     // 传输协议和端口信息
				"Content_Length" : "内容长度",             // 响应体的长度
				"Content_Type" : "内容类型"                // 响应内容的媒体类型，例如 application/sdp
			},
			"Body": "变长"                             // 响应体内容，通常为媒体描述信息
		}
	}
}

//说明
1、RTSP_Message：包含请求和响应的整体结构。
2、Request：描述客户端发送的RTSP请求。
Request_Line：请求行的结构。
Method：指定请求的方法，如 DESCRIBE、SETUP、PLAY 等。
Request_URL：请求的资源URL。
RTSP_Version：指定使用的RTSP版本。

Headers：请求的头部字段。
CSeq：请求的序列号。
Session：标识会话的ID。
Transport：描述传输信息，包括传输协议和端口。
Accept：可接受的媒体类型。
User_Agent：客户端的信息。

3、Response：描述服务器返回的RTSP响应。
Response_Line：响应行的结构。
RTSP_Version：使用的RTSP版本。
Status_Code：响应的状态码。
Reason_Phrase：状态码的原因短语。

Headers：响应的头部字段。
CSeq：响应的序列号。
Session：会话标识符。
Transport：传输协议和端口信息。
Content_Length：响应体的长度。
Content_Type：响应内容的媒体类型。
Body：响应体内容，通常包含媒体描述信息（如SDP描述）。




//RTMP
{
	"RTMP_Packet":
	{
		"RTMP_Header":
		{
			"Format": "2 位",                        // RTMP头格式，指示头的类型
			"Chunk_Stream_ID" : "1-3 字节",           // 数据块流标识符，指示RTMP流的来源
			"Timestamp" : "3 字节或 4 字节",          // 时间戳，指示数据包的时间
			"Message_Length" : "4 字节",              // 消息长度，以字节为单位
			"Message_Type_ID" : "1 字节",             // 消息类型标识符，指示数据包的类型
			"Message_Stream_ID" : "4 字节"            // 消息流标识符，指示数据的流
		},
		"RTMP_Message":
		{
			"Message_Type":
			{
				"Audio": "音频数据",                   // 音频消息
				"Video" : "视频数据",                  // 视频消息
				"Data" : "数据消息",                   // 数据消息
				"Command" : "命令消息"                 // 命令消息
			},
			"Payload":
			{
				"Audio_Data": "变长",                 // 音频数据的负载
				"Video_Data" : "变长",                 // 视频数据的负载
				"Data_Message" : "变长",                // 数据消息的负载
				"Command_Message" : "变长"              // 命令消息的负载
			}
		},
		"RTMP_Control_Message":
		{
			"Control_Type":
			{
				"Set_Window_Ack_Size": "设置窗口确认大小", // 设置窗口确认大小
				"Set_Buffer_Length" : "设置缓冲长度",       // 设置缓冲长度
				"User_Control" : "用户控制消息"            // 用户控制消息
			},
			"Payload": "变长"                          // 控制消息的负载
		}
	}
}

//说明
1、RTMP_Packet：包含RTMP数据包的整体结构。
2、RTMP_Header：数据包的头部信息。
Format：指示RTMP头的格式类型，可能影响字段的长度。
Chunk_Stream_ID：数据块流的标识符，标识数据包属于哪个流。
Timestamp：数据包的时间戳，使用3字节或4字节的格式，视头格式而定。
Message_Length：消息的长度，以字节为单位，指示消息体的大小。
Message_Type_ID：消息类型的标识符，标识数据包的内容类型。
Message_Stream_ID：消息流标识符，指示数据的流。
3、RTMP_Message：数据包的消息部分。
Message_Type：定义消息的类型。
Audio：音频消息。
Video：视频消息。
Data：数据消息。
Command：命令消息。

Payload：消息的负载部分，包含实际的数据。
Audio_Data：音频数据的负载。
Video_Data：视频数据的负载。
Data_Message：数据消息的负载。
Command_Message：命令消息的负载。
4、RTMP_Control_Message：控制消息结构。
Control_Type：指示控制消息的类型。
Set_Window_Ack_Size：设置窗口确认大小的控制消息。
Set_Buffer_Length：设置缓冲长度的控制消息。
User_Control：用户控制消息。
Payload：控制消息的负载部分。





//SIP
{
	"SIP_Message":
	{
		"Request":
		{
			"Request_Line":
			{
				"Method": "方法",                        // SIP方法，例如 INVITE、ACK、BYE、REGISTER、OPTIONS、CANCEL 等
				"Request_URI" : "请求URI",                // 请求的目标URI
				"SIP_Version" : "SIP版本"                  // SIP协议的版本，例如 SIP/2.0
			},
			"Headers":
			{
				"Via": "路径",                           // 指示请求的传输路径
				"From" : "发起者",                        // 发起者信息，包括 URI 和标签
				"To" : "接收者",                          // 接收者信息，包括 URI 和标签
				"CSeq" : "序列号",                        // 请求的序列号
				"Contact" : "联系方式",                   // 发起者的联系方式
				"Content_Type" : "内容类型",               // 消息体的内容类型，例如 application/sdp
				"Content_Length" : "内容长度"              // 消息体的长度
			},
			"Body": "变长"                             // 请求体内容，通常为SDP描述
		},
		"Response":
		{
			"Response_Line":
			{
				"SIP_Version": "SIP版本",                 // SIP协议的版本，例如 SIP/2.0
				"Status_Code" : "状态码",                  // 响应状态码，例如 200 OK、404 Not Found
				"Reason_Phrase" : "原因短语"                // 状态码的原因短语，例如 OK、Not Found
			},
			"Headers":
			{
				"Via": "路径",                           // 指示请求的传输路径
				"From" : "发起者",                        // 发起者信息
				"To" : "接收者",                          // 接收者信息
				"CSeq" : "序列号",                        // 响应的序列号
				"Contact" : "联系方式",                   // 发起者的联系方式
				"Content_Type" : "内容类型",               // 响应内容的类型
				"Content_Length" : "内容长度"              // 响应体的长度
			},
			"Body": "变长"                             // 响应体内容，通常为SDP描述
		}
	}
}

//说明
1、SIP_Message：包含请求和响应的整体结构。
2、Request：描述客户端发送的SIP请求。
Request_Line：请求行的结构。
Method：指定请求的方法，如 INVITE、BYE、REGISTER 等。
Request_URI：请求的目标URI。
SIP_Version：指定使用的SIP版本。

Headers：请求的头部字段。
Via：指示请求的传输路径，包含代理和传输信息。
From：发起者的信息，包括 URI 和标签。
To：接收者的信息，包括 URI 和标签。
CSeq：请求的序列号，标识请求的顺序。
Contact：发起者的联系方式。
Content_Type：消息体的内容类型。
Content_Length：消息体的长度。
Body：请求体内容，通常包含会话描述协议（SDP）信息。

3、Response：描述服务器返回的SIP响应。
Response_Line：响应行的结构。
SIP_Version：使用的SIP版本。
Status_Code：响应的状态码。
Reason_Phrase：状态码的原因短语。

Headers：响应的头部字段。
Via：指示请求的传输路径。
From：发起者的信息。
To：接收者的信息。
CSeq：响应的序列号。
Contact：发起者的联系方式。
Content_Type：响应内容的类型。
Content_Length：响应体的长度。
Body：响应体内容，通常包含会话描述协议（SDP）信息。

这个结构可以用于理解SIP协议在VoIP（语音通信）和多媒体会话中的工作原理。





//HTTP-FLV
{
	"HTTP-FLV":
	{
		"FLV_Header":
		{
			"Signature": "3 字节",                     // 固定值 "FLV"，标识文件类型
			"Version" : "1 字节",                       // FLV版本号，当前版本通常为 1
			"Flags" : "1 字节",                         // 音视频流标志位，指示音频和视频流的存在
			"Header_Size" : "4 字节"                    // FLV头的大小，固定为 9
		},
		"Previous_Tag_Sizes": "0 或多个 4 字节",     // 前一个标签的大小，只有在有标签数据时才存在
		"Tag_Data" :
		{
			"Video_Tag":
			{
				"Tag_Header":
				{
					"Tag_Type": "1 字节",                // 标签类型，值为 9 表示视频标签
					"Data_Size" : "3 字节",                // 标签数据部分的大小
					"Timestamp" : "3 字节",                // 当前标签的时间戳
					"Timestamp_Extended" : "1 字节",       // 时间戳扩展
					"Stream_ID" : "3 字节"                 // 流标识，固定为 0
				},
				"Tag_Data":
				{
					"Frame_Type": "4 位",                // 帧类型，0x1 表示关键帧，0x2 表示非关键帧
					"Codec_ID" : "4 位",                  // 编码器标识，值为 7 表示 H.264
					"AVCPacketType" : "1 字节",            // AVC 数据包类型，0 表示 NALU，1 表示 SPS，2 表示 PPS
					"Composition_Time" : "3 字节",         // 组合时间
					"Payload" : "变长"                      // 具体视频帧数据
				}
			},
			"Audio_Tag":
			{
				"Tag_Header":
				{
					"Tag_Type": "1 字节",                // 标签类型，值为 8 表示音频标签
					"Data_Size" : "3 字节",                // 标签数据部分的大小
					"Timestamp" : "3 字节",                // 当前标签的时间戳
					"Timestamp_Extended" : "1 字节",       // 时间戳扩展
					"Stream_ID" : "3 字节"                 // 流标识，固定为 0
				},
				"Tag_Data":
				{
					"Sound_Format": "4 位",               // 声音格式，0 表示 PCM，1 表示 ADPCM，2 表示 MP3 等
					"SoundRate" : "2 位",                   // 声音采样率
					"SoundSize" : "1 位",                   // 声音大小，0 表示 8 位，1 表示 16 位
					"SoundType" : "1 位",                   // 声音类型，0 表示单声道，1 表示立体声
					"Payload" : "变长"                      // 具体音频数据
				}
			},
			"Script_Tag":
			{
				"Tag_Header":
				{
					"Tag_Type": "1 字节",                // 标签类型，值为 18 表示脚本标签
					"Data_Size" : "3 字节",                // 标签数据部分的大小
					"Timestamp" : "3 字节",                // 当前标签的时间戳
					"Timestamp_Extended" : "1 字节",       // 时间戳扩展
					"Stream_ID" : "3 字节"                 // 流标识，固定为 0
				},
				"Tag_Data":
				{
					"Data": "变长"                        // 脚本标签数据
				}
			}
		}
	}
}

//说明：
1、HTTP - FLV：整体结构，表示 HTTP - FLV 文件格式。
2、FLV_Header：FLV 文件头部。
Signature：文件签名，确保文件为 FLV 格式。
Version：当前使用的 FLV 版本。
Flags：指示音频和视频流的存在。
Header_Size：FLV 头的大小，固定为 9 字节。
3、Previous_Tag_Sizes：前一个标签的大小，0 或多个 4 字节的值，用于指示前一个标签的大小，方便流媒体的播放。
4、Tag_Data：包含所有的标签数据。
Video_Tag：视频标签数据。
Tag_Header：视频标签的头部信息。
Tag_Data：视频标签的数据部分，包含帧类型、编码器标识等。

Audio_Tag：音频标签数据。
Tag_Header：音频标签的头部信息。
Tag_Data：音频标签的数据部分，包含声音格式、采样率等。
Script_Tag：脚本标签数据。

Tag_Header：脚本标签的头部信息。
Tag_Data：脚本标签的数据部分。





//HLS
HTTP Live Streaming(HLS) 是 Apple 提出的基于 HTTP 的流媒体传输协议，常用于点播和实时视频流的传输。
HLS 使用 m3u8 文件作为播放清单，流媒体内容被分成若干小的 MPEG - TS 或者其他支持的格式文件来传输。以下是 HLS 格式的结构解析：

{
	"HLS":
	{
		"Master_Playlist":
		{
			"File_Extension": ".m3u8",                // 文件扩展名为 .m3u8 的播放清单文件
			"EXTM3U" : "Header",                       // m3u8 文件头标识
			"EXT-X-VERSION" : "HLS 版本号",            // HLS 版本号，指示播放器支持的协议版本
			"EXT-X-STREAM-INF" :
			{
				"Bandwidth": "必要的带宽 (bps)",      // 指定每个分辨率流的带宽
				"Resolution" : "视频分辨率",           // 视频的分辨率，如 1920x1080
				"Codecs" : "编码信息",                 // 音视频的编码信息，如 avc1.4d001f, mp4a.40.2
				"URI" : "播放清单子文件 URI"          // 指向各个变体流的子播放清单文件的 URI
			},
			"EXT-X-MEDIA":
			{
				"Type": "媒体类型",                   // 媒体类型，通常是 AUDIO 或 SUBTITLES
				"Group_ID" : "组 ID",                  // 媒体组 ID，用于标识该媒体流组
				"Name" : "媒体名称",                   // 媒体流的名称
				"Language" : "语言代码",               // 媒体语言代码，如 en, es
				"Default" : "是否为默认流"            // 标记是否为默认流，YES 或 NO
			}
		},
		"Media_Playlist":
		{
			"File_Extension": ".m3u8",                // 媒体播放清单的文件扩展名
			"EXTM3U" : "Header",                       // m3u8 文件头标识
			"EXT-X-TARGETDURATION" : "最大分片时长",   // 指定分片的最大时长（秒）
			"EXT-X-MEDIA-SEQUENCE" : "序列号",         // 媒体序列号，指定第一个分片的序列号
			"EXT-X-PLAYLIST-TYPE" : "点播或直播",       // 点播 (VOD) 或直播 (LIVE) 类型
			"EXTINF" :
			{
				"Duration": "分片时长 (秒)",          // 每个分片的持续时间（秒）
				"URI" : "媒体分片文件 URI"             // 指向媒体分片的文件的 URI
			},
			"EXT-X-ENDLIST" : "End Marker"             // 结束标记，仅用于 VOD 表示播放清单结束
		},
		"Media_Segment":
		{
			"File_Extension": ".ts 或其他格式",        // 每个媒体分片的文件扩展名，如 .ts（MPEG-TS）
			"Codec" : "视频和音频编码格式",            // 如 H.264/AVC，AAC 等
			"Key_Frame_Alignment" : "关键帧对齐",       // 对于广告插入等用途，每个分片的开头通常为关键帧
			"Duration" : "分片时长",                   // 分片的时长，通常与 EXTINF 中的一致
			"URI" : "文件 URI"                        // 媒体分片的 URI，用于播放
		},
		"Encryption":
		{
			"EXT-X-KEY":
			{
				"Method": "加密方法",                  // 加密方式，如 AES-128, SAMPLE-AES
				"URI" : "密钥 URI",                     // 密钥的 URI，用于解密分片
				"IV" : "初始向量 (IV)"                 // 加密时的初始向量，提供额外的加密强度
			}
		}
	}
}

//解析说明
1、Master_Playlist：主播放清单，包含不同质量（带宽和分辨率）的变体流。播放器会根据网络条件选择适合的流。
EXT - X - STREAM - INF：定义一个变体流的信息，包括带宽、分辨率和编码。
EXT - X - MEDIA：用于描述音频或字幕流。
2、Media_Playlist：媒体播放清单，每个变体流对应一个媒体播放清单。包含分片文件的列表。
EXT - X - TARGETDURATION：分片的最大时长，播放器通常会使用此信息来设置缓冲区大小。
EXT - X - MEDIA - SEQUENCE：指定播放清单的开始序列号。
EXT - X - PLAYLIST - TYPE：指定播放类型，直播或点播。
EXTINF：每个分片的时长和 URI。
3、Media_Segment：媒体分片，通常为.ts 文件，包含实际的音视频数据。每个分片开头通常为关键帧，以便播放器可以从任意位置开始播放。
4、Encryption：加密信息，如果分片被加密。
EXT - X - KEY：包含加密方法和密钥 URI，用于解密相应的媒体分片。




//DASH

Dynamic Adaptive Streaming over HTTP(DASH) 是一种基于 HTTP 的自适应流媒体传输协议，适用于点播和直播。DASH 使用.mpd 文件作为清单，包含不同的媒体流（音频、视频、字幕等）的描述，并将媒体内容分成若干小的分片。以下是 DASH 格式结构的解析：

{
	"DASH":
	{
		"MPD (Media Presentation Description)":
		{
			"File_Extension": ".mpd",                     // DASH 的描述文件扩展名
			"Type" : "静态或动态",                          // 指示播放类型，静态 (VOD) 或动态 (LIVE)
			"MinimumUpdatePeriod" : "更新周期",            // 对于直播，指示播放清单的更新频率
			"MediaPresentationDuration" : "媒体总时长",     // 对于点播，指示媒体的总时长
			"BaseURL" : "基础 URL",                         // 可选，用于分片的基础 URI
			"Period" :
			{
				"Start": "起始时间",                       // 此 Period 的开始时间
				"Duration" : "时长",                        // Period 时长
				"AdaptationSet" :
				{
					"ID": "自适应集合 ID",                 // 唯一标识
					"ContentType" : "媒体类型",             // 媒体类型，如 video、audio
					"Lang" : "语言",                        // 音频或字幕的语言
					"MimeType" : "MIME 类型",               // 媒体的 MIME 类型，如 video/mp4, audio/mp4
					"Codecs" : "编码信息",                  // 编码格式，如 avc1.4d401e（H.264），mp4a.40.2（AAC）
					"FrameRate" : "帧率",                   // 视频帧率
					"SegmentAlignment" : "分片对齐",        // 指示分片是否对齐
					"Representation" :
					{
						"ID": "Representation ID",         // 表示不同码率或分辨率的流
						"Bandwidth" : "带宽 (bps)",          // 每个 Representation 的码率
						"Width" : "视频宽度",                // 视频分辨率宽度
						"Height" : "视频高度",               // 视频分辨率高度
						"AudioSamplingRate" : "音频采样率",   // 音频采样率
						"BaseURL" : "媒体片段的 URL",        // 此 Representation 的分片文件基准 URL
						"SegmentBase" :
						{
							"Initialization": "初始化片段 URI" // 初始化分片，包含解码所需的元数据
						},
						"SegmentTemplate" :
						{
							"Timescale": "时间刻度",          // 分片的时间刻度，通常为每秒的时间单位
							"Duration" : "分片时长",          // 分片的时长（单位与 Timescale 一致）
							"Media" : "分片 URI 模板",        // 分片 URI 模板
							"StartNumber" : "起始序列号"      // 分片序列号起点
						},
						"SegmentList":
						{
							"SegmentURL":
							{
								"Media": "分片文件 URI",     // 分片的 URI，指向具体媒体数据
								"Duration" : "分片时长"       // 分片时长（与 SegmentTemplate 对应）
							}
						}
					}
				}
			}
		},
		"Segment":
		{
			"Initialization Segment":
			{
				"Header": "包含解码信息的初始化片段"       // 包含媒体解码器所需的头信息
			},
			"Media Segment" :
			{
				"File_Extension": ".m4s 或 .mp4",          // 分片文件扩展名
				"Data" : "媒体数据",                         // 实际的音频或视频数据
				"Duration" : "分片的播放时长"                // 分片的播放时长
			}
		}
	}
}

//解析说明
1、MPD(Media Presentation Description)：DASH 播放清单文件，以.mpd 扩展名。它描述了媒体内容、不同码率和分辨率的流信息。
Type：指示播放的类型，可以是点播(VOD) 或直播(LIVE)。
Period：表示一个时间段，可以包含多个自适应集(AdaptationSet)，每个自适应集代表一种媒体类型（如音频或视频）。
2、AdaptationSet：自适应集合，包含不同的 Representation，每种 Representation 通常代表一种分辨率或码率。
ContentType：指示媒体类型，例如视频或音频。
Representation：表示特定码率、分辨率或音频采样率的流。
3、SegmentTemplate 和 SegmentList：提供媒体分片的结构化信息，用于动态生成每个分片的 URI 和序列号。
SegmentTemplate：定义分片的模板，适合直播流。
SegmentList：列出具体的分片 URI，适用于点播流。
4、Segment：媒体分片，包括初始化片段和实际的媒体分片。
Initialization Segment：初始化分片，包含媒体的编解码信息，用于解码后续的媒体分片。
Media Segment：实际的音频或视频数据，包含每个分片的媒体内容。





//GB28181
GB28181 是中国国家标准协议，主要用于视频监控和安防行业的视频、音频、控制等数据的传输。GB28181 基于 SIP（Session Initiation Protocol）协议，并结合了 RTP / RTCP 协议用于媒体流传输，实现设备之间的实时通信。以下是 GB28181 格式结构的解析：

{
	"GB28181_Protocol":
	{
		"SIP_Signal_Protocol":
		{
			"Method": "SIP 请求方法",                          // 如 REGISTER, INVITE, BYE, ACK 等
			"Headers" :
			{
				"From": "发送端地址",                         // 发送端标识符，例如设备 ID
				"To" : "接收端地址",                           // 接收端标识符
				"Call-ID" : "会话标识符",                      // 唯一标识一次通信会话
				"CSeq" : "命令序列号",                         // SIP 消息的序列号
				"Contact" : "联系地址",                        // 用于通信的 IP 地址和端口
				"Expires" : "有效期",                          // REGISTER 请求的有效期，单位为秒
				"User-Agent" : "用户代理",                      // 客户端设备的名称和版本
				"Content-Length" : "消息体长度",                // 指定消息体的字节长度
				"Content-Type" : "内容类型"                    // 指示消息体类型，通常为 `Application/MANSCDP+xml`
			},
			"Body":
			{
				"XML_Content": "消息体内容",                   // XML 格式的信令内容
				"MANSCDP_Message" :
				{
					"CommandType": "指令类型",                // 如 DeviceInfo, DeviceStatus, Catalog 等
					"SN" : "序列号",                           // 消息序列号
					"DeviceID" : "设备编码",                    // 设备的唯一标识符
					"Result" : "操作结果",                      // 响应时的操作结果，如 OK 或错误码
					"Status" : "设备状态信息",                  // 设备的工作状态等信息
					"Catalog" : "设备目录列表"                 // 当 CommandType 为 Catalog 时，包含设备子目录
				}
			}
		},
		"RTP_Media_Transmission":
		{
			"RTP_Header":
			{
				"Version": "2 位",                          // RTP 版本号，通常为 2
				"Padding" : "1 位",                          // 填充标识
				"Extension" : "1 位",                        // 扩展标识
				"CSRC_Count" : "4 位",                       // CSRC 标识符数量
				"Marker" : "1 位",                           // 标记位
				"Payload_Type" : "7 位",                     // 有效载荷类型
				"Sequence_Number" : "16 位",                 // 序列号
				"Timestamp" : "32 位",                       // 时间戳，用于同步媒体流
				"SSRC" : "32 位"                             // 同步源标识符
			},
			"RTP_Payload":
			{
				"Video_Audio_Data": "媒体数据",              // 视频或音频数据的实际内容
				"Payload_Format" : "H.264 或 G.711A/U"       // 常用的编码格式
			}
		},
		"RTCP_Control_Protocol":
		{
			"Sender_Report":
			{
				"SSRC": "32 位",                            // 发送端同步源标识符
				"Timestamp" : "发送时间戳",                   // 发送时的 RTP 时间戳
				"Packet_Count" : "发送的 RTP 包计数",          // 发送的 RTP 包数量
				"Octet_Count" : "发送的字节数"                // 发送的字节数
			},
			"Receiver_Report":
			{
				"SSRC": "32 位",                            // 接收端同步源标识符
				"Fraction_Lost" : "丢包比例",                 // 丢失的数据包比例
				"Cumulative_Number_Of_Packets_Lost" : "丢包总数", // 接收到的总丢包数量
				"Extended_Highest_Sequence_Number_Received" : "最高接收序列号" // 接收到的最高序列号
			}
		},
		"GB28181_Extensions":
		{
			"DeviceControl":
			{
				"PTZ_Command": "云台控制指令",              // 包括上下左右、放大缩小等控制命令
				"TeleBoot" : "远程重启指令",                 // 设备重启控制
				"AudioTransmissionControl" : "音频传输控制"   // 音频开关控制
			},
			"Alarm_Notifications":
			{
				"Alarm_Type": "报警类型",                   // 报警类型，如移动侦测等
				"Alarm_Priority" : "报警优先级",             // 报警的优先级
				"Description" : "报警描述",                  // 具体报警内容描述
				"Trigger_Time" : "报警触发时间"              // 报警事件的时间戳
			}
		}
	}
}

//解析说明
1、SIP 信令协议：用于设备注册、会话建立和控制信令。常用方法包括 REGISTER、INVITE、BYE、ACK 等，用于设备的注册、呼叫建立和关闭等。
Headers：包含基本的 SIP 信令头信息，包括设备标识、会话标识等。
Body：一般为 XML 格式，包含具体的控制命令和响应信息，如设备信息查询、状态更新等。
2、RTP 媒体传输：用于音视频数据的传输，通常采用 H.264 视频编码和 G.711 音频编码。
RTP Header：包含数据包的序列号、时间戳等，用于同步和解码媒体流。
RTP Payload：实际的媒体数据内容。
3、RTCP 控制协议：用于传输质量报告，如丢包信息、抖动等，以便监控传输的质量。
Sender Report 和 Receiver Report：用于发送端和接收端报告传输状态，帮助检测和调整网络状态。
4、GB28181 扩展：包括设备控制和报警通知等功能。
DeviceControl：控制设备的动作，包括 PTZ（云台）控制、远程重启和音频传输控制。
Alarm Notifications：用于传输报警事件，支持不同报警类型和优先级，如移动侦测等。

GB28181 提供了在复杂网络环境下的设备管理、实时控制、音视频传输和状态反馈的综合解决方案，广泛应用于安防监控领域。





//SRT
SRT（Secure Reliable Transport）是一种开放的流媒体传输协议，旨在提供在不可靠网络环境中的低延迟、可靠传输。
SRT 主要用于视频流媒体传输，支持端到端的加密、包恢复、时序同步等功能。

{
	"SRT_Protocol":
	{
		"Handshake":
		{
			"Type": "握手类型 (4字节)",                              // 握手阶段，包含 CONN、HSHAKE、KEMSG 等
			"Version" : "版本号 (4字节)",                             // SRT 协议版本
			"SRT_Socket_ID" : "连接唯一标识 (4字节)",                   // 用于标识 SRT 会话的 ID
			"Initial_Sequence_Number" : "初始序列号 (4字节)",           // 数据传输的初始序列号
			"Encryption" :
			{
				"Encryption_Type": "加密类型 (2字节)",                // 加密类型，如无加密、AES-128 等
				"Key_Length" : "密钥长度 (2字节)",                     // 密钥长度
				"Key_Data" : "密钥内容 (变长)"                         // 密钥数据
			}
		},
		"Data_Packet":
		{
			"Packet_Header":
			{
				"Packet_Type": "包类型 (4位)",                        // 包类型标识，0 表示数据包
				"Sequence_Number" : "序列号 (32位)",                   // 用于确认包顺序
				"Timestamp" : "时间戳 (32位)",                         // 包发送时的时间戳
				"Destination_Socket_ID" : "目的端 Socket ID (32位)"     // 接收端的 Socket ID
			},
			"Payload":
			{
				"Data": "实际数据内容 (变长)"                         // 音视频数据或其他负载数据
			}
		},
		"Control_Packet":
		{
			"Packet_Header":
			{
				"Packet_Type": "包类型 (4位)",                         // 包类型标识，1 表示控制包
				"Control_Type" : "控制指令类型 (16位)",                 // 控制指令的种类，如 ACK、NAK 等
				"Timestamp" : "时间戳 (32位)",                          // 包发送时的时间戳
				"Destination_Socket_ID" : "目的端 Socket ID (32位)"      // 接收端的 Socket ID
			},
			"Control_Message":
			{
				"ACK":
				{
					"Sequence_Number": "确认的序列号 (32位)"             // 确认接收的序列号
				},
				"NAK" :
				{
					"Lost_Sequence_Range": "丢包序列号范围 (变长)"       // 指定的丢失序列号范围
				},
				"KeepAlive" :
				{
					"Interval": "间隔时间 (32位)"                       // 保持连接的时间间隔
				}
			}
		},
		"Encryption":
		{
			"Method": "加密方法",                                       // 如 AES 加密
			"Key_Exchange" :
			{
				"Key_ID": "密钥 ID (4字节)",                           // 密钥标识
				"Public_Key" : "公钥 (变长)",                            // 公钥，用于密钥交换
				"Encryption_Algorithm" : "加密算法 (16位)"               // 如 RSA 等
			}
		},
		"Latency_Buffer":
		{
			"Size": "缓冲区大小 (32位)",                                // 延迟缓冲区的大小
			"Current_Fill_Level" : "当前缓冲区填充水平 (32位)"          // 用于流的平滑处理
		},
		"Stream_Control" :
		{
			"Flow_Control": "流量控制",                                // 控制数据传输速率
			"Retransmission" : "重传机制",                              // 丢包时的重传策略
			"Timestamp_Based_Pacing" : "基于时间戳的节流"              // 控制流的平滑度
		}
	}
}

//解析说明
1、握手(Handshake)：用于建立连接并初始化会话参数，包含加密类型、密钥交换等。
SRT_Socket_ID：用于标识唯一连接。
加密：提供密钥交换和加密支持。密钥可以变长，用于数据的加密。
2、数据包(Data Packet)：传输实际音视频等负载数据。
Packet_Header：包含序列号、时间戳等，用于接收端重排序和同步。
Payload：包含传输的音视频数据或其他内容。
3、控制包(Control Packet)：传输控制信息，如 ACK 确认包、NAK 丢包通知、KeepAlive 保持连接等。
Control_Message：具体的控制消息内容，包括确认（ACK）、丢包通知（NAK）以及保持连接等控制指令。
4、加密(Encryption)：SRT 支持端到端加密，主要使用 AES 加密，同时支持基于公钥的密钥交换机制。
5、延迟缓冲区(Latency Buffer)：缓冲区用于平滑传输，确保低延迟和流畅性。
Size 和 Current_Fill_Level：动态调节缓冲区，控制流的时延。
6、流控制(Stream Control)：用于控制数据流量和重传机制。
Flow Control：调节传输速率，确保稳定的流。
Retransmission：在数据丢失时触发数据包的重传，保证数据完整性。






//WebRTC
WebRTC（Web Real - Time Communication）是一种实时通信协议，允许通过点对点（P2P）连接直接在浏览器之间传输音视频、数据流等内容。WebRTC 的传输基于多种协议的组合，
主要包括 SRTP（Secure RTP）用于音视频流的传输，以及 SCTP（Stream Control Transmission Protocol）用于数据通道传输。

{
	"WebRTC":
	{
		"Signaling":
		{
			"SDP":
			{
				"Session_Description_Protocol": "包含会话协商的配置信息",  // 包括会话初始化、媒体类型、编码格式等
				"Media_Descriptions" :
				{
					"Audio":
					{
						"Codec": "音频编码格式 (如 Opus)",              // 音频编解码器
						"Sample_Rate" : "采样率 (如 48000 Hz)",          // 音频采样率
						"Channels" : "声道数 (如 2 代表立体声)"          // 音频通道配置
					},
					"Video":
					{
						"Codec": "视频编码格式 (如 VP8, H264)",         // 视频编解码器
						"Resolution" : "视频分辨率 (如 1280x720)",       // 视频分辨率
						"Frame_Rate" : "帧率 (如 30fps)"                // 视频帧率
					}
				},
				"ICE_Parameters":
				{
					"Candidate_Type": "候选者类型 (如 host, relay)",    // ICE 候选者类型
					"Network_Cost" : "网络代价",                         // 网络开销，优选连接
					"Transport" : "传输协议 (如 UDP, TCP)",              // 传输协议类型
					"Address" : "IP 地址",                               // IP 地址
					"Port" : "端口号"                                    // 端口号
				}
			},
			"ICE":
			{
				"Interactive_Connectivity_Establishment": "用于 NAT 穿透的协议",
				"Candidate_Discovery" :
				{
					"STUN":
					{
						"Server_IP": "STUN 服务器 IP",                   // 用于 NAT 穿透
						"Port" : "端口号"                                 // STUN 服务器端口
					},
					"TURN" :
					{
						"Server_IP": "TURN 服务器 IP",                   // 当 P2P 连接失败时使用中继服务器
						"Port" : "端口号",                                // TURN 服务器端口
						"Authentication" : "身份验证信息"                 // 用于认证的用户名和密码
					}
				}
			}
		},
		"Media_Transport":
		{
			"SRTP":
			{
				"Secure_Real-time_Transport_Protocol": "加密的 RTP 流传输",
				"Encryption" :
				{
					"Cipher": "加密算法 (如 AES)",                       // 加密算法
					"Key_Length" : "密钥长度 (如 128 位)",               // 密钥长度
					"Authentication" : "身份验证算法"                     // 身份验证算法
				},
				"Packet_Format":
				{
					"Header":
					{
						"Sequence_Number": "序列号 (16位)",              // RTP 包序列号
						"Timestamp" : "时间戳 (32位)",                    // 包的时间戳
						"SSRC" : "同步源标识符 (32位)"                    // 唯一的同步源标识符
					},
					"Payload":
					{
						"Data": "音视频数据"                            // 实际的音视频数据
					}
				}
			},
			"RTCP":
			{
				"Real-time_Transport_Control_Protocol": "提供传输质量报告",
				"Packet_Types" :
				{
					"Sender_Report": "发送方报告",                      // 报告发送方的统计数据
					"Receiver_Report" : "接收方报告",                    // 报告接收方的统计数据
					"Source_Description" : "源描述",                     // 包含媒体源信息
					"Goodbye" : "结束通知"                              // 终止流会话
				}
			}
		},
		"Data_Channel":
		{
			"SCTP":
			{
				"Stream_Control_Transmission_Protocol": "可靠的数据通道传输",
				"Channel_ID" : "通道唯一标识",
				"Reliability_Mode" : "传输模式 (如可靠传输、不可靠传输)", // 支持有序和无序、可靠和不可靠传输
				"Packet_Format" :
				{
					"Header":
					{
						"Message_ID": "消息标识符",                     // 用于标识数据包
						"Payload_Protocol_ID" : "负载协议 ID"            // 数据内容的协议类型
					},
					"Payload" :
					{
						"Data": "传输的数据内容"                        // 发送的数据内容
					}
				}
			}
		}
	}
}

//解析说明
1、信令(Signaling)：WebRTC 使用 SDP 和 ICE 来协商连接和媒体信息。
SDP(Session Description Protocol)：描述音视频会话的编解码器、采样率、分辨率、帧率等参数。
ICE(Interactive Connectivity Establishment)：用于 NAT 穿透，包含 STUN 和 TURN 服务器的信息，帮助连接到网络受限的用户。
2、媒体传输(Media Transport)：
SRTP(Secure RTP)：通过加密的 RTP 传输音视频数据，保障数据的安全性。
Header：包含序列号、时间戳等信息，用于包顺序和同步。
RTCP(Real - Time Control Protocol)：用于监控传输质量，包含发送方和接收方报告。
3、数据通道(Data Channel)：
SCTP(Stream Control Transmission Protocol)：用于传输非音视频数据，提供可靠和有序 / 无序传输。
Reliability_Mode：支持设置可靠模式或不可靠模式，使其可以适应不同的数据传输需求。

WebRTC 通过 SRTP、SCTP、RTCP 等协议的组合，实现低延迟和高可靠的数据传输。





