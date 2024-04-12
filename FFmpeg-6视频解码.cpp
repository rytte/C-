/*************************/基本解码流程/***************************************************************************/
//1.创建上下文
AVFormatContext* pFormatCtx = avformat_alloc_context();

//2.打开文件
avformat_open_input(&pFormatCtx, "aki.mp4", nullptr, nullptr);

//3.上下文获取流信息
avformat_find_stream_info(pFormatCtx, nullptr);

//4.查找流
int videoIndex = av_find_best_stream(pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);

//5.创建音视频解码器上下文
AVCodecContext* pCodecCtx = avcodec_alloc_context3(nullptr);

//6.解码器上下文获取参数
avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[videoIndex]->codecpar);

//7.查找解码器
const AVCodec* pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

//8.打开解码器并绑定上下文
avcodec_open2(pCodecCtx, pCodec, nullptr);

//9.获取视频数据
av_dump_format(pFormatCtx, -1, nullptr, 0);

// 10.创建帧和包
AVFrame* frame = av_frame_alloc();
AVPacket* packet = av_packet_alloc();

//解码部分
while (1)
{
	//读取一个包数据
	if (av_read_frame(pFormatCtx, packet) < 0)
		break;

	if (packet->stream_index == videoIndex)
	{
		//发送一个包数据
		avcodec_send_packet(pCodecCtx, packet);

		while (1)
		{
			//获取解码后的帧数据
			ret = avcodec_receive_frame(pCodecCtx, frame);
			if (ret < 0) break;
			else if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) break;

			//>>解码后的数据处理<<
			......

			//释放帧内存
			av_frame_unref(frame);
		}
	}
	av_packet_unref(packet);
}


//11.释放资源
avcodec_free_context(&pCodecCtx);
avformat_close_input(&pFormatCtx);
av_frame_free(&frame);



/*************************/解码保存为文件/***************************************************************************/
FILE* output_file = fopen("output.raw", "wb");

//>>数据处理部分<<
fwrite(frame->data[0], 1, frame->linesize[0] * codec_ctx->height, output_file);		//此处保存为原始数据



/*************************/解码使用SDL显示/***************************************************************************/
//SDL初始化
SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
SDL_Window* window = SDL_CreateWindow("SDL2.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, heigth, SDL_WINDOW_RESIZABLE);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, 0, width, heigth);
if (!texture) return -1;
SDL_Rect rect = SDL_Rect{ 0, 0, width, heigth };

//获取初始时间
int64_t start_time = av_gettime();              //获取从公元1970年1月1日0时0分0秒开始的微秒值

//>>数据处理部分<<
//显示数据
SDL_UpdateYUVTexture(texture, &rect,
	frame->data[0], frame->linesize[0],
	frame->data[1], frame->linesize[1],
	frame->data[2], frame->linesize[2]);
SDL_RenderClear(renderer);
SDL_RenderCopy(renderer, texture, nullptr, &rect);
SDL_RenderPresent(renderer);

//延时控制
AVRational time_base_q = { 1,AV_TIME_BASE };          // 1/1000000秒，即1us
int64_t pts_time = av_rescale_q(frame->pkt_dts, pFormatCtx->streams[videoIndex]->time_base, time_base_q);  //该函数将<参数二>时基中的<参数一>时间戳转换<参数三>时基下的<返回值>时间戳
int64_t now_time = av_gettime() - start_time;       // 计算当前程序已开始时间
if (pts_time > now_time)                             // 若应帧解码时间>当前时间对比，延时到应解码的时间再开始解下一帧(若无此延时则计算机将会很快解码显示完)
	av_usleep(pts_time - now_time);



/*************************/解码使用SDL线程/***************************************************************************/
//SDL 线程参数
struct FFmpegData
{
	AVFormatContext* pFormatCtx;
	AVCodecContext* pCodecCtx;
	int videoIndex;
	AVFrame* frame;
};

//创建SDL线程参数
FFmpegData data;
data.pFormatCtx = pFormatCtx;
data.pCodecCtx = pCodecCtx;
data.frame = frame;
data.videoIndex = videoIndex;

//创建SDL线程，并传入参数
SDL_CreateThread(thread_video_decode, NULL, &data);

//定义事件
SDL_Event event;

// Event loop
while (1)
{
	SDL_WaitEvent(&event);
	if (event.type == SDL_QUIT)                         //程序退出
	{
		thread_quit = 1;
		break;
	}
	else if (event.type == SDL_KEYDOWN)                  //空格键暂停
	{
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			thread_pause = !thread_pause;
		}
	}
}

//>>视频解码线程<<
int thread_video_decode(void* data)
{
	int64_t start_time = av_gettime();              //获取从公元1970年1月1日0时0分0秒开始的微秒值
	int ret;
	AVPacket* packet = av_packet_alloc();
	AVFrame* frame = av_frame_alloc();
	//获取传入的参数
	AVFormatContext* pFormatCtx = ((FFmpegData*)data)->pFormatCtx;
	AVCodecContext* pCodecCtx = ((FFmpegData*)data)->pCodecCtx;
	int videoIndex = ((FFmpegData*)data)->videoIndex;

	//解码
	while (!thread_quit)
	{
		if (thread_pause)
		{
			SDL_Delay(10);
			start_time += 10 * 1000;
			continue;
		}

		//读取一个包数据
		if (av_read_frame(pFormatCtx, packet) < 0)
			break;

		if (packet->stream_index == videoIndex)
		{
			//发送一个包数据
			avcodec_send_packet(pCodecCtx, packet);

			while (1)
			{
				ret = avcodec_receive_frame(pCodecCtx, frame);
				if (ret < 0) break;
				else if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) break;

				//显示数据
				SDL_UpdateYUVTexture(texture, &rect,
					frame->data[0], frame->linesize[0],
					frame->data[1], frame->linesize[1],
					frame->data[2], frame->linesize[2]);
				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, texture, nullptr, &rect);
				SDL_RenderPresent(renderer);

				//延时控制
				AVRational time_base_q = { 1,AV_TIME_BASE };          // 1/1000000秒，即1us
				int64_t pts_time = av_rescale_q(frame->pkt_dts, pFormatCtx->streams[videoIndex]->time_base, time_base_q);  //该函数将<参数二>时基中的<参数一>时间戳转换<参数三>时基下的<返回值>时间戳
				int64_t now_time = av_gettime() - start_time;       // 计算当前程序已开始时间
				if (pts_time > now_time)                             // 若应帧解码时间>当前时间对比，延时到应解码的时间再开始解下一帧(若无此延时则计算机将会很快解码显示完)
					av_usleep(pts_time - now_time);

				av_frame_unref(frame);
			}
		}
		av_packet_unref(packet);
	}
	thread_quit = 1;

	av_frame_free(&frame);
	return 0;
}




/*************************/解码使用QImage显示，sws_scale转换/***************************************************************************/
//延时函数
void delay(int ms)
{
	QTime stopTime;
	stopTime.start();
	qDebug() << "start:" << QTime::currentTime().toString("HH:mm:ss.zzz");
	while (stopTime.elapsed() < ms)//stopTime.elapsed()返回从start开始到现在的毫秒数
	{
		QCoreApplication::processEvents();
	}
	qDebug() << "stop :" << QTime::currentTime().toString("HH:mm:ss.zzz");
}

// 创建QLabel
QLabel* Label_PlayWindow = new QLabel(this);
label_PlayWindow->resize(800, 480);

//转换后的帧
AVFrame* frameRGB = av_frame_alloc();

//创建图像数据存储缓冲区。av_image_get_buffer_size传入参数获取一帧frameRGB大小。av_image_fill_arrays主要用于填充其前两个参数
unsigned char* buf = (unsigned char*)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_RGB32, 800, 480, 1));
av_image_fill_arrays(frameRGB->data, frameRGB->linesize, buf, AV_PIX_FMT_RGB32, 800, 480, 1);

// 创建SwsContext图像转换上下文，获取CodecContext信息
struct SwsContext* pSwsCtx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, 800, 480, AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);

//>>数据处理部分<<
//显示
sws_scale(pSwsCtx, (const unsigned char* const*)frame->data, frame->linesize, 0, pCodecCtx->height, frameRGB->data, frameRGB->linesize);
QImage img((uchar*)frameRGB->data[0], 800, 480, QImage::Format_RGB32);
label_PlayWindow->setPixmap(QPixmap::fromImage(img));
delay(40);//播放延时：1000/延时=帧率



/*************************/其它方式/***************************************************************************/
//1、创建上下文时可以
AVFormatContext* pFormatCtx = nullptr;
那么
avformat_open_input()函数将会自动调用avformat_alloc_context()

//2、查找流。有另一种方式
int VideoIndex = -1;												// 获取音视频流索引号
int AudioIndex = -1;
for (int i = 0; i < pFormatCtx->nb_streams; i++)
{
	if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		VideoIndex = i;
	if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
		AudioIndex = i;
}

//3、查找解码器。在 av_find_best_stream() 第五参数传入AVCodec，可省略 avcodec_find_decoder() 查找解码器
const AVCodec* pCodec = nullptr;
int videoIndex = av_find_best_stream(pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, &pCodec, -1);

//4、Flush decoder 冲刷缓冲区，即发送空包
while (1)
{
	ret = avcodec_send_packet(pCodecCtx, nullptr);		//此处发送空包nullptr
	if (ret < 0)
		break;

	while (1)
	{
		ret = avcodec_receive_frame(pCodecCtx, frame);
		if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
			break;
		else if (ret < 0)
			goto end;

		// 解码的视频数据处理
		printf("\rSucceed to decode frame %d\n", frameCnt++);

		av_frame_unref(frame);  // 释放frame缓冲区数据
	}
}
