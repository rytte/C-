/*************************/ffmpeg介绍/***************************************************************************/
FFmpeg 是一套可以用来记录、转换数字音频、视频，并能将其转化为流的开源计算机程序。采用 LGPL 或 GPL 许可证。


//相关概念
容器 / 文件(Conainer / File)	      ：指特定格式的多媒体文件，比如mp4、flv、mov等视频格式。
媒体流(Stream)				      ：一个容器（如mp4文件）中可存在多个流，可以是视频流、音频流、字幕流。
数据帧 / 数据包（Frame / Packet）：一个流媒体是由大量的数据帧构成的，对于压缩数据，帧对应着编解码器的最小处理单元，分属于不同媒体流的数据帧交错存储于容器之中。
编码器 / 解码器				      ：编解码器是以帧为单位进行压缩数据和复原数据的，对原始数据和压缩的数据进行转换。

复用器：把多路原始流按一定的规则组成成一个新的音视频文件（例如：把一个纯视频流、一个纯音频流和一个纯字幕流组合成一个mp4文件）；
解复用器：把一个新的音视频文件按一定的规则拆分成多路原始流（例如：把一个mp4文件，拆分成纯视频流、纯音频流和纯字幕流）。


//ffmpeg代码组成
ffmpeg.exe 的代码实际上不算多，加起来只有1万多行代码，相关的代码文件如下：

ffmpeg.c，ffmpeg.exe 的主要逻辑就放在 ffmpeg.c 里面。
ffmpeg_opt.c，主要是负责解析跟处理命令行参数的，里面也有一些打开输出文件，打开编码器的逻辑。
ffmpeg_filter.c，主要是负责滤镜配置的逻辑，命令行的语法可以配置很复杂的滤镜逻辑的。
ffmpeg_hw.c，硬件加速相关。
ffmpeg_qsv.c，硬件加速相关，qsv 是 intel 的硬件加速。
ffmpeg_videotoolbox.c，videotoolbox 是 MacOS，IOS 系统上访问硬件编解码器的一个框架。



/*************************/字幕/***************************************************************************/
字幕分为硬字幕和软字幕
软字幕如SRT、ASS为，可以编辑修改；硬字幕是画面的一部分，不可修改。

使用：
- vf "ass = 字幕文件名.ass"
- vf "subtitles = 字幕文件名.srt"

字幕样式：						字体名 = 思源字体				字体大小		字体颜色					边框颜色					边框粗细	 字幕与底边的距离
- vf "ass = 字幕文件名.ass:force_style='FontName=SourceHanSansCN-Bold, FontSize=20, PrimaryColour=&H0000FFFF, OutlineColour=&H00222222, Outline=1, MarginV=20'"
其它属性：
BackColour = &H00222222	阴影颜色
Shadow = 1				阴影深度
BorderStyle = 3				字幕背景色

HTML颜色代码：RGB：#FFFFFF
ASS颜色代码：ABGR：#00FFFFFF



/*************************/ffmpeg命令行/***************************************************************************/
ffmpeg - i  输入文件名  参数选项  输出文件名

//参数选项
- f			输出格式，当文件名没有扩展名, 或者文件格式与扩展名不匹配, 此时就需要使用 - f 参数来手动指定格式;
- an			去掉音频
- vn			去掉视频
- sn			去掉字幕
- ss			起始时间（裁剪）
- to			终止时间（裁剪）
- t			视频长度（裁剪）
- r			帧率（默认为25）
- s			帧大小（W * H）
- b			设定视频码率
- b:v			视频码率
- b:a			音频码率（为保证音质，每声道码率不低于64kbps）
- c:a			指定音频编码器
- c:v			指定视频编码器
- map		选择轨道
- af			音频滤镜
- vf			视频滤镜
- ac			设置音频通道数。1单声道，2立体声。
- ar			设置音频采样率
- aspect		横纵比（4:3，16:9，1.3333等）
- acodec		指定音频编解码器。copy拷贝，libmp3lame用于mp3格式音频编码，aac，用于 AAC 格式音频编码。
- vcodec		指定视频编解码器。copy拷贝
- crf			只能在编码器为x264或x265时使用，取值范围0~51，值越低画质越好（码率越高），默认为23
- filter_complex		复杂滤镜
- pix_fmt		格式转换
- aframes		要输出的音频帧数
- encoders	查询当前 ffmpeg 中的 编码器
- findstr		搜索文本字符串
- formats		获取ffmpeg支持的音视频格式

//常用-f参数值
h264：表示输出的是h264的视频裸流
mp4：表示 输入或输出 的 文件格式是 mp4 格式;
avi：表示 输入或输出 的文件格式是 avi 格式;
flv：表示 输入或输出 的文件格式是 flv 格式;
mov：表示 输入或输出 的文件格式是 mov 格式;
mkv：表示 输入或输出 的文件格式是 mkv 格式;
wav：表示 输入或输出 的文件格式是 wav 格式;
rawvideo：表示 原始视频 数据流格式, 通常用于一些专业的音视频处理;
null：特殊的格式, 用于不产生任何输出文件, 通常用于测试或性能分析;
image2：处理图像序列, 将 视频帧 保存为一系列的 图片或将图片序列编码成视频;
image2pipe：用于通过管道传输图像数据的格式, 通过标准输入 / 输出(stdin / stdout) 或其他管道机制将图像数据传递给 FFmpeg 或从 FFmpeg 接收图像数据;
mpegts：表示 MPEG 传输流格式（ts视频流），常用于流媒体传输


//实例
ffmpeg - i input.mp4 output.avi					//视频格式转换
ffmpeg - i input.mp4 - b:a 128k output.mp3			//设置音频码率
ffmpeg - i input.mp4 - ar 44100 output.mp3			//设置音频采样率
ffmpeg - i input.mp4 - af "volume=0.25,atempo=2.0" output.mp3	//输出文件音量是输入文件的 0.25 倍 , 播放速度是输入文件的 2 倍。

ffmpeg - encoders | findstr mp3					//查找 mp3 格式相关的编码器
ffmpeg - encoders > output.txt					//将命令行内容输出到文本文件中

//实例
ffmpeg - i "concat:test1.h264|test2.h264" out12.h264	//视频拼接

ffmpeg - i test.mp4 - t 0.001 - s 352x240 1.jpg		// 视频截图，在test.mp4中截图
ffmpeg - i test.mp4 - vframes 30 - y - f gif 1.gif		// 视频截图，将test.py前30帧做成gif动图
ffmpeg - i test.mp4 - t 10 - r 1 pic - % 03d.jpg		// 视频截图，从视频前10s中取图像，1s提取一帧

ffmpeg - i test_1280x720.mp4 - acodec copy - vn audio.mp4			//提取音频 - acodec copy 直接拷贝音频编码数据
ffmpeg - i test_1280x720.mp4 - vcodec libx264 - an test_lpf.h264		//提取视频，强制格式

ffmpeg - i test_1280x720.mp4 - t 3 - pix_fmt yuv420p yuv420p_orig.yuv	//提取yuv数据。提取3秒数据，分辨率和源视频一致
ffmpeg - i test_1280x720.mp4 - t 3 - pix_fmt yuv420p - s  640 * 480 yuv420p_320x240.yuv//提取3秒数据，分辨率转为320x240

ffmpeg - i test.mp4 - t 3 - pix_fmt rgb24 - s 320x240 rgb24_320x240.rgb	//提取3秒数据，分辨率转为320x240
ffmpeg - s 640 * 480 - i yuv420p_640x480.yuv - pix_fmt yuv420p - pix_fmt rgb24 - s 640 * 480 rgb24_640x480.rgb//RGB和YUV之间的转换

ffmpeg - i test_1280x720.mp4 - codec copy test_copy2.ts				//更改封装格式
ffmpeg - i test_1280x720.mp4 - vcodec libx265 - acodec libmp3lame out_h265_mp3.mkv	//改变编码格式	
ffmpeg - i test_1280x720.mp4 - r 15 output2.mp4					//改变帧率
ffmpeg - i test.mp4 - b 400k output_b.mkv							//修改音视频码率
ffmpeg - i test.mp4 - b:v 400k output_bv.mkv						//修改视频码率
ffmpeg - i test.mp4 - b:a 192k output_ba.mp4			//修改音频码率： 如果不想重新编码video，需要加上 - vcodec copy
ffmpeg - i test.mp4 - b:v 400k - b : a 192k output_bva.mp4	//修改音视频码率
ffmpeg - i test.mp4 - s 480x270 output_480x270.mp4		//修改视频分辨率
ffmpeg - i test.mp4 - ar 44100 output_44100hz.mp4		//修改音频采样率

#双宫格
ffmpeg - i 1.mp4 - i 2.mp4 - i 3.mp4 - i 4.mp4 - filter_complex "nullsrc=size=640x480[base];[0:v]setpts=PTS-STARTPTS,scale=320x240[upperleft];[1:v]setpts=PTS-STARTPTS,scale=320x240[upperright];[base][upperleft]overlay=shortest=1[tmp1];[tmp1][upperright]overlay=shortest=1:x=320" out2.mp4
#四宫格
ffmpeg - i 1.mp4 - i 2.mp4 - i 3.mp4 - i 4.mp4 - filter_complex "nullsrc=size=640x480[base];[0:v] setpts=PTS-STARTPTS,scale=320x240[upperleft];[1:v]setpts=PTS-STARTPTS,scale=320x240[upperright];[2:v]setpts=PTS-STARTPTS, scale=320x240[lowerleft];[3:v]setpts=PTS-STARTPTS,scale=320x240[lowerright];[base][upperleft]overlay=shortest=1[tmp1];[tmp1][upperright]overlay=shortest=1:x=320[tmp2];[tmp2][lowerleft]overlay=shortest=1:y=240[tmp3];[tmp3][lowerright]overlay=shortest=1:x=320:y=240" out3.mp4



//压片技巧
1、使用高画质片源
2、选择高效编码器，如x265、NVENC
3、使用类似CRF的码率控制方式，并设置合适的质量值
4、尝试提高Preset的值（值越高速度越慢）
5、如果片源有大量噪点，先降噪处理（噪点非常消耗码率）

delogo滤镜去logo（复杂场景使用boxblur）
-vf delogo=60:50:200:80				前两值为logo的xy坐标，后两值为logo宽高


文件拖拽：在bat文件中使用"%~1"可自动识别替换为拖拽进bat文件的第一个文件，需指定路径和输出文件名。
批量转换：略





