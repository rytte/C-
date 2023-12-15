/******************************/解码流程/******************************************************************************************/
1、AVFormatContext * FormatContext = avformat_alloc_context()			// 创建AVFormatContext上下文
2、avformat_open_input(&FormatContext, 文件路径, nullptr, nullptr)			// 打开文件
3、avformat_find_stream_info(FormatContext, nullptr);						// AVFormatContext获取流信息
4、 int VideoIndex = -1;												// 获取音视频流索引号
int AudioIndex = -1;
for (int i = 0; i < FormatContext->nb_streams; i++)
{
	if (FormatContext->streams[i]->codecpar && FormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		VideoIndex = i;
	if (FormatContext->streams[i]->codecpar && FormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
		AudioIndex = i;
}
5、AVCodecContext * CodecContext = avcodec_alloc_context3(nullptr);							// 创建解码器上下文
6、avcodec_parameters_to_context(CodecContext, FormatContext->streams[VideoIndex]->codecpar);	// 解码器上下文获取视频流参数
7、AVCodec * Codec = avcodec_find_decoder(CodecContext->codec_id);		// 查找AVCodec解码器（解码器信息结构体）
8、avcodec_open2(CodecContext, Codec, nullptr)							// 打开AVCodec并关联到AVCodecContext上下文
9、AVPacket * Packet = (AVPacket *)av_malloc(sizeof(AVPacket));			// 初始化未解码包结构体
10、 AVFrame * Frame = av_frame_alloc();								// 初始化数据帧空间
AVFrame * FrameRGB = av_frame_alloc();
11、 unsigned char* buf = (unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_RGB32, CodecContext->width, CodecContext->height, 1));
// 创建图像数据存储缓冲区
av_image_fill_arrays(FrameRGB->data, FrameRGB->linesize, buf, AV_PIX_FMT_RGB32, CodecContext->width, CodecContext->height, 1);
// 缓冲区存储一帧像素数据
12、 struct SwsContext * SwsContext = sws_getContext(CodecContext->width, CodecContext->height, CodecContext->pix_fmt, CodecContext->width, CodecContext->height, AV_PIX_FMT_RGB32, SWS_BICUBIC, nullptr, nullptr, nullptr);
// 创建SwsContext图像转换上下文，获取CodecContext信息
13、// 循环读取一帧数据解码并显示
QLabel * Label_PlayWindow = new QLabel(this);
int gotPicture;
while (1)
{
	if (av_read_frame(FormatContext, Packet) >= 0)						// 读取一帧未解码的数据
	{
		if (Packet->stream_index == (int)VideoIndex)					// 如果是视频数据
		{
			int ret = avcodec_decode_video2(CodecContext, Frame, &gotPicture, Packet);		// 解码一帧视频数据
			if (ret < 0)															// 如果解码出错则跳过解下一帧
			{
				qDebug("Decode Error.\n");
				continue;
			}

			if (gotPicture)											// 不为0表示有图像可以解码
			{
				sws_scale(SwsContext, (const unsigned char* const*)Frame->data, Frame->linesize, 0, CodecContext->height, FrameRGB->data, FrameRGB->linesize);
				QImage img((uchar*)FrameRGB->data[0], CodecContext->width, CodecContext->height, QImage::Format_RGB32);
				Label_PlayWindow->setPixmap(QPixmap::fromImage(img));
				delay(100);										//播放延时
			}
		}
		av_packet_unref(pAVpkt);
	}
	else															// 读取完即跳出
		break;
}
14、// 释放资源
sws_freeContext(SwsContext);
av_frame_free(&FrameRGB);
av_frame_free(&Frame);
avcodec_close(CodecContext);
avformat_close_input(&FormatContext);


/******************************/编码流程/******************************************************************************************/


