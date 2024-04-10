/*************************/基本解码流程/***************************************************************************/
//1.创建上下文
AVFormatContext* pFormatCtx = avformat_alloc_context();

//2.打开文件
avformat_open_input(&pFormatCtx, "aki.mp4", nullptr, nullptr);

//3.上下文获取流信息
avformat_find_stream_info(pFormatCtx, nullptr);

//4.查找流
int audioIndex = av_find_best_stream(pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);

//5.创建音视频解码器上下文
AVCodecContext* pCodecCtx = avcodec_alloc_context3(nullptr);

//6.解码器上下文获取参数
avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[audioIndex]->codecpar);

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

	if (packet->stream_index == audioIndex)
		continue;

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

	av_packet_unref(packet);
}


//11.释放资源
avcodec_free_context(&pCodecCtx);
avformat_close_input(&pFormatCtx);
av_frame_free(&frame);



/*************************/SDL音频播放/***************************************************************************/
//  audio sample rates map from FFMPEG to SDL (only non planar)
static std::map<int, int> AUDIO_FORMAT_MAP = {
	// AV_SAMPLE_FMT_NONE = -1,
	 {AV_SAMPLE_FMT_U8,  AUDIO_U8    },
	 {AV_SAMPLE_FMT_S16, AUDIO_S16SYS},
	 {AV_SAMPLE_FMT_S32, AUDIO_S32SYS},
	 {AV_SAMPLE_FMT_FLT, AUDIO_F32SYS}
};


#define MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio    //48000 * (32/8)

unsigned int audioLen = 0;
unsigned char* audioChunk = NULL;
unsigned char* audioPos = NULL;

void fill_audio(void* udata, Uint8 * stream, int len)
{
	SDL_memset(stream, 0, len);

	if (audioLen == 0)
		return;

	len = (len > audioLen ? audioLen : len);

	SDL_MixAudio(stream, audioPos, len, SDL_MIX_MAXVOLUME);

	audioPos += len;
	audioLen -= len;
}

//重采样
// 8 设置音频播放采样参数
int out_sample_rate = pCodecCtx->sample_rate;           //采样率    48000
int out_channels = pCodecCtx->channels;              //通道数    2
int out_nb_samples = pCodecCtx->frame_size;            //单个通道中的样本数  1024
enum AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_FLT; //声音格式  SDL仅支持部分音频格式

// 9 依据参数计算缓冲区大小
int out_buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, out_sample_fmt, 1);   //输出buffer

// 10 创建音频数据缓冲区
unsigned char* outBuff = (unsigned char*)av_malloc(MAX_AUDIO_FRAME_SIZE * out_channels);

// 11 获取当前声道布局中的声道数目
uint64_t out_chn_layout = av_get_default_channel_layout(pCodecCtx->channels);  //AV_CH_LAYOUT_STEREO;  //通道布局 输出双声道

// 12 分配重采样的上下文，返回音频信息上下文结构体SwrContext
SwrContext* au_convert_ctx = swr_alloc_set_opts(NULL,
	out_chn_layout,                    /*out*/
	out_sample_fmt,                    /*out*///fltp->slt
	out_sample_rate,                   /*out*/
	pCodecCtx->channel_layout,           /*in*/
	pCodecCtx->sample_fmt,               /*in*/
	pCodecCtx->sample_rate,              /*in*/
	0,
	NULL);


// 13 swr上下文初始化
swr_init(au_convert_ctx);


///   SDL
// 14 SDL初始化
if (SDL_Init(SDL_INIT_AUDIO))
{
	SDL_Log("init audio subsysytem failed.");
	return 0;
}

// 15 配置音频播放结构体SDL_AudioSpec，和SwrContext的音频重采样参数保持一致
SDL_AudioSpec wantSpec;
wantSpec.freq = 45000;//out_sample_rate; 极限帧数44帧左右
wantSpec.format = AUDIO_FORMAT_MAP[out_sample_fmt];
wantSpec.channels = out_channels;
wantSpec.silence = 0;
wantSpec.samples = out_nb_samples;
wantSpec.callback = fill_audio;                 //回调函数
wantSpec.userdata = pCodecCtx;

// 16 打开音频设备
if (SDL_OpenAudio(&wantSpec, NULL) < 0)
{
	printf("can not open SDL!\n");
	return -1;
}

// 17 开始播放
SDL_PauseAudio(0);



//>>解码处理部分<<
ret = swr_convert(au_convert_ctx, &outBuff, MAX_AUDIO_FRAME_SIZE, (const uint8_t**)frame->data, frame->nb_samples);
if (ret < 0)
{
	av_log(NULL, AV_LOG_ERROR, "Error while converting\n");
	goto end;
}

while (audioLen > 0)
SDL_Delay(1);

audioChunk = (unsigned char*)outBuff;
audioPos = audioChunk;
audioLen = out_buffer_size;

