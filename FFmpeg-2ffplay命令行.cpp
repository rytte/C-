/*************************/ffmplay命令行/***************************************************************************/
ffplay - i  输入文件名  参数选项				//-i 可省略

//参数选项
- x				窗口宽度
- y				窗口高度
- volume			音量，取值范围[0,100]
- framerate		指定帧率
- fs				全屏播放
- an				禁用音频
- vn				禁用视频
- sn				禁用字幕
- ss   			根据设置的秒进行定位
- t				指定播放的时长
- ast				执行音频流索引
- vst				执行视频流索引，这个只有在视频包含多个流才会生效
- af				音频滤镜，多个滤镜之间使用逗号隔开，可不使用引号
- vf				视频滤镜，多个滤镜之间使用逗号隔开，可不使用引号
- acodec			指定音频解码器
- vcodec			指定视频解码器
- scodec			指定字幕解码器
- loop			设置循环播放次数
- nostats			不输出视频相关信息，通过这个可以查看 ffplay 如何收集的这些信息，自己写播放器可以借鉴
- nodisp			无图形窗口播放视频
- noborder		无边框窗口播放视频
- window_title  	设置播放窗口标题
- autorotate		自动旋转视频。1打开，0关闭。默认是打开的
- autoexit			播放完毕自动退出
- exitonkeydown	键盘按下任意键退出，默认情况是按下Esc才退出
- exitonmousedown鼠标按下任意键退出
- video_size		设置视频帧，YUV视频中没有包含 视频帧 的大小，需要使用该参数指定。
- pixel_format		像素格式，RGB和YUV视频通常需要指定
- bytes			按字节定位拖动的功能。1开启，0关闭，-1自动选择。开启后, 可以使用左右方向键控制该功能。mp4视频不支持该功能，flv可以。
- seek_interval		按时间定位拖动，单位秒，可以使用左右方向键控制该功能。
- showmode		显示模式。0显示视频（默认），1显示音频波形（时域信号），2显示音频带宽（音频频谱）
- sync			设置同步时钟。audio音频流时钟作为主时钟，video视频流时钟作为主时钟，ext外部时钟作为主时钟。
- framedrop		设置丢弃失去同步的视频帧。
- noframedrop		设置不丢弃失去同步的视频帧。
- infbuf			设置输入缓冲区。经常 与 - probesize 和 - analyzeduration 等参数一起使用
- probesize		指定 ffplay 在尝试确定 输入流格式 时应该读取的 数据量
- analyzeduration	限制输入流的分析时长，单位微秒

- codec:media_specifier		设置多媒体解码器。media_specifier替换为a音频，v视频，s字幕。
a: 音频, -codec : a 用于 设置 音频解码器;
v: 视频, -codec : v 用于 设置 视频解码器;
s: 字幕, -codec : s 用于 设置 字幕解码器;


//常用视频滤镜参数
transpose = direction 滤镜 : 用于旋转视频; direction 参数取值如下 :
0 : 逆时针旋转90度并翻转;
1 : 顺时针旋转90度;
2 : 逆时针旋转90度;
3 : 顺时针旋转90度 并翻转;
scale = width:height 滤镜 : 调整视频的尺寸; 如 scale = 640:480 会将视频 分辨率设置为 640x480 的分辨率;
pad = width:height:x:y:color 滤镜 : 为 视频添加边框, x 和 y 指定了边框的偏移量, color 指定了边框的颜色;
crop = width:height:x:y 滤镜 : 裁剪视频, x 和 y 指定了裁剪的起始坐标, width 和 height 指定了裁剪区域的尺寸;
framestep = number 滤镜 : 快进播放效果, 每隔 number 帧进行播放;
setpts = PTS / factor 滤镜 : 改变视频的播放速度; factor 大于 1 时视频变慢, 小于 1 时视频变快;


//常用音频滤镜参数
volume = volume : 设置 音频音量, volume 是一个 乘数, 可以设置一个 小数 或 整数,
volume = 0.5 就是将音量降低一半,
volume = 2 是 将音量 提高为原来的 2 倍;

atempo = tempo : 设置 音频播放速度, 参数值是一个浮点数, tempo 参数值 > 1 时 音频播放速度加快, 小于 1 时音频播放速度减慢;
atempo = 0.5 设置 0.5 倍速度播放;
atempo = 2.0 设置 2 倍速度播放;

aresample = resampler_options : 设置音频重采样; 该 音频滤镜 可以用来改变音频的 采样率 / 格式 / 声道布局;
aresample = 44100 可以将 音频的采样率 从 原始值 改变为 44100 Hz;

aformat = sample_fmts : 强制转换音频样本格式, 如 : 修改 位深度 和 编码方式;
aformat = sample_fmts = s16 将 播放的音频 转为 16 位 有符号整数 编码;

achannelmap = channel_layout : 重新映射音频声道;
bass = gain : 调整低音增益;
treble = gain : 调整高音增益;


//实例
ffplay test.mp4					//播放视频
ffplay - x 800 - y 600 test.mp4		//强制设置播放分辨率
ffplay - bytes 1 test.flv				//打开字节定位拖动
ffplay - seek_interval 2 test.mp4		//打开时间定位拖动
ffplay - pixel_format yuv420p - video_size 320x240 test.yuv		//播放yuv视频，指定像素格式和帧大小
ffplay - pixel_format rgb24 - video_size 320x240 test.rgb		//播放rgb视频，指定像素格式和帧大小
ffplay - ss 00:00:05 - t 00:00:10 test.mp4					//播放视频，从5秒开始，播放10秒钟
ffplay - vf "transpose=1,scale=640:480" test.mp4				//视频旋转90度并将视频窗口设置为 640x480 像素
ffplay - af "volume=0.25,atempo=2.0" fengjing.mp4			//播放音量设置为 0.25 倍 , 播放速度设置为 2 倍
ffplay - sync video test.mp4								//播放视频，以视频流时钟作为主时钟进行同步。
ffplay - codec:v h264 test.mp4							//使用 h264 解码器 解码视频播放
ffplay - codec:a libfdk_aac test.mp4						//使用 libfdk_aac 解码器来解码音频播放
ffplay - infbuf - probesize 50M - analyzeduration 100000 test.mp4	//设置 初始读取 50MB 的数据 , 分析时长 0.1 秒
ffplay - vst 4 - ast 3	test.mp4 									//这个是执行视频流索引是4  音频索引是3
ffplay - window_title "cctv1" - x 640 - y 480 rtmp:	//media3.scctv.net/live/scctv_800	//播放rtmp 流媒体
ffplay - ar 48000 - ac 2 - f f32le test.pcm					//播放pcm - ar 执行采样率 - ac指定通道数 - f 指定位深



/*************************/ffmplay简单的滤镜实例/***************************************************************************/
//视频反转
ffplay test.mp4 - vf hflip
ffplay test.mp4 - vf vflip

//音频变速播放
ffplay - i test.mp4 - af atempo = 2

//视频变速播放
ffplay - i test.mp4 - vf setpts = PTS / 2

//画中画 副视频停下之后默认显示最后一帧图像
ffplay test.mp4 - vf "movie=sub_320x240.mp4[sub];[in][sub]overlay=x=20:y=20[out]"

//eof_action = 1 表示短的视频停止之后都会停止
ffplay test.mp4 - vf "movie=sub_320x240.mp4[sub];[in][sub]overlay=x=20:y=20:eof_action=1[out]"

//短的视频结束了 画面直接结束
ffplay test.mp4 - vf "movie=sub_320x240.mp4[sub];[in][sub]overlay=x=20:y=20:eof_action=2[out]"

//shortest = 1 表示短的视频停止之后都会停止
ffplay test.mp4 - vf "movie=sub_320x240.mp4[sub];[in][sub]overlay=x=20:y=20:shortest =1[out]"

//对副视频视频进行缩放
ffplay test.mp4 - vf "movie=sub_320x240.mp4,scale=640x480[sub];[in][sub]overlay=x=20:y=20[out]"

//跑马灯
ffplay test_60_1280x720.mp4 - vf "movie=test_60_1280x720.mp4,scale=320x270[test];[in][test]overlay=x=mod(50*t\,main_w):y=abs(sin(t))*main_h*0.7[out]"



/*************************/ffmpeg常用解码器选项/***************************************************************************/
//常用音频解码器选项
aac:
Advanced Audio Coding, 高级音频编码,
广泛用于 音频编码 和 传输, 尤其是流媒体 和 网络广播, 音质比 MP3 更高, 文件相对较小;

mp2:
MPEG - 1 / 2 Audio Layer II, MPEG - 1 / 2 音频层 II,
MP2 是 MPEG - 1 和 MPEG - 2 标准中的 音频编码格式之一, 是较早的音频压缩格式之一, 曾经广泛用于数字音频广播和视频文件中, 现在不是主流编码格式;

mp3:
MPEG - 1 / 2 Audio Layer III, MPEG - 1 / 2 音频层 III,
MP3 是一种非常流行的音频编码格式, 该编码 提供 高效的压缩率 和 可接受的音质损失, 该格式 也是 MPEG - 1 和 MPEG - 2 标准中的音频编码格式之一,
该解码器 通常与 libmp3lame 一起进行编解码操作;

ac3:
Dolby Digital AC - 3, 杜比数字 AC - 3,
AC - 3 是由 杜比实验室 开发的一种音频编码格式, 广泛用于 电影院 / 数字电视 / DVD, 该编码格式 提供了 高质量的音频压缩, 支持多声道音频, 如 : 5.1 环绕声;

vorbis:
Ogg Vorbis,
Vorbis 是一种 开放 和 免费 的音频编码格式, 通常与 Ogg 容器格式一起使用, 它可以提供比 MP3 更高的音质, 同时保持较小的文件大小;

opus:
Ogg Opus,
Opus 是一种高效的音频编码格式, 特别适合用于互联网流媒体和实时通信, 它提供了出色的音质和非常低的延迟, 同时保持了较小的文件大小;

flac:
Free Lossless Audio Codec, 免费无损音频编码,
该音频格式 可以在压缩过程中不损失任何原始音频数据, 这使得 FLAC 文件比有损压缩格式的文件要大, 但音质完全等同于原始音频,
FLAC 广泛用于音频存档和高质量音频播放;


//常用视频解码器选项
h264:
H.264 / AVC / MPEG - 4 AVC / MPEG - 4 part 10, H.264 编码, 又称为 高级视频编码(AVC, Advanced Video Coding), 是 MPEG - 4 标准的 第 10 部分;
最广泛使用的 视频压缩标准, 压缩效率高, 视频质量好, 应用于 高清电视广播 / 视频会议 / 网络流媒体 / 蓝光光盘;

hevc:
H.265 / HEVC, 高效视频编码(HEVC, High Efficiency Video Coding), 比H.264 编码的 压缩效率 更高, 支持 更高的分辨率 和 更高的帧率, 文件大小较小, 被广泛用于 4K 视频编码 和 超高清视频编码;

vp9:
VP9 是 由 Google 开发的开源视频压缩格式, 广泛 应用于 Web 视频流 和 在线视频平台;

mpeg4:
MPEG - 4 part 2, MPEG - 4 标准的 第 2 部分,
该编码标准, 定义了 MPEG - 4 的 视觉对象编码标准, 包括视频编码和压缩, 该编码 逐渐被 H.264 和 HEVC 替代, 不是主流;

mpeg2video:
MPEG - 2 video, MPEG - 2 视频,
MPEG - 2 视频编码标准 被广泛用于 数字电视广播 / DVD / 视频编辑等领域;

theora:
Theora 视频编码, Theora 是一种开放和免费的视频编码格式, 该编码基于 Ogg 容器格式的, 被广泛用于开源和免费软件社区;

vp8:
VP8 是 开放 免费 的 编码格式, 广泛用于WebM多媒体容器格式中;


//常用字幕解码器选项
srt:
SubRip(.srt), SubRip 字幕格式, 字幕文件 是.srt 文件扩展名,
SRT 是一种简单的纯文本字幕格式, 用于 电影 / 电视节目 等的字幕显示; 它支持基本的字幕样式, 如时间戳 / 文本内容 / 简单格式设置;

ass:
Advanced SubStation Alpha(.ass) / SSA(.ssa), 高级 SubStation Alpha 字幕格式 也就是.ass 文件扩展名 或 SSA.ssa 文件扩展名 的 字幕文件;
ASS 是一种高级的字幕格式, 支持更多的字幕样式和特效, 包括 复杂的布局 / 字体样式 / 颜色 / 阴影 / 边框 等;

dvbsub:
DVB subtitles, Digital Video Broadcasting 数字视频广播 字幕;
DVBSub 是 数字视频广播 DVB 标准中定义的字幕格式; 它通常嵌入在视频流中, 用于电视节目的字幕显示, DVBSub 支持多种语言和字幕样式, 但通常不支持像 ASS 那样复杂的特效;

hdmv_pgs_subtitle:
HDMV Presentation Graphic Stream subtitles, 高清多媒体视频演示图形流字幕, 常用于 蓝光光盘;
该字幕格式, 支持高质量的字幕渲染, 包括矢量图形, 图像 和 文本;


