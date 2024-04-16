#include <iostream>
#include <map>
#include "ffmpeg.h"

//***** 不同于PCM音频数据，每一次读取后都存放于一块连续的内存中，ffmpge解码后的音频数据由于声道格式不同可能存放的数据不连续，
//***** 另外，SDL支持的音频格式比ffmpeg要少，因此需要使用swr_convert对解码音频数据重新采样以符合SDL要求。

using namespace std;

extern "C"
{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libswresample/swresample.h"
#include "SDL.h"
}


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

void fill_audio(void* udata, Uint8* stream, int len)
{
        SDL_memset(stream, 0, len);

        if (audioLen == 0)
                return;

        len = (len > audioLen ? audioLen : len);

        SDL_MixAudio(stream, audioPos, len, SDL_MIX_MAXVOLUME);

        audioPos += len;
        audioLen -= len;
}

#undef main
int main()
{
        const char* filename = "152.m4a";

        // 1 创建格式上下文和解码器
        AVFormatContext* pFormatCtx = avformat_alloc_context();
        const AVCodec* pCodec = NULL;
        int ret;

        // 2 打开文件
        if ((ret = avformat_open_input(&pFormatCtx, filename, NULL, NULL)) < 0)
        {
                av_log(NULL, AV_LOG_ERROR, "Cannot open input file\n");
                return ret;
        }

        // 3 上下文获取流信息
        if ((ret = avformat_find_stream_info(pFormatCtx, NULL)) < 0)
        {
                av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
                return ret;
        }

        // 4 找到音频流(不需要遍历)
        int audioIndex = -1;
        if ((audioIndex = av_find_best_stream(pFormatCtx, AVMEDIA_TYPE_AUDIO, -1, -1, &pCodec, 0)) < 0)
        {
                av_log(NULL, AV_LOG_ERROR, "Cannot find an audio stream in the input file\n");
                return audioIndex;
        }

        av_dump_format(pFormatCtx, audioIndex, NULL, 0);       // 输出所有流信息


        // 5 创建解码器上下文
        AVCodecContext* pCodecCtx = avcodec_alloc_context3(pCodec);
        if (!pCodecCtx)
        {
                av_log(NULL, AV_LOG_ERROR, "Could not allocate a decoding context\n");
                avformat_close_input(&pFormatCtx);
                return AVERROR(ENOMEM);
        }

        // 6 创建解码器参数
        AVCodecParameters* codecpar = pFormatCtx->streams[audioIndex]->codecpar;
        if ((ret = avcodec_parameters_to_context(pCodecCtx, codecpar)) < 0)
        {
                avformat_close_input(&pFormatCtx);
                avcodec_free_context(&pCodecCtx);
                return ret;
        }

        // 7 打开解码器并获取参数
        if ((ret = avcodec_open2(pCodecCtx, pCodec, NULL)) < 0)
        {
                avcodec_free_context(&pCodecCtx);
                avformat_close_input(&pFormatCtx);
                return ret;
        }

        ///重采样contex
        // 8 设置音频播放采样参数
        int out_sample_rate = pCodecCtx->sample_rate;           //采样率    48000
        int out_channels = pCodecCtx->ch_layout.nb_channels; //通道数    2
        int out_nb_samples = pCodecCtx->frame_size;            //单个通道中的样本数  1024
        enum AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_FLT; //声音格式  SDL仅支持部分音频格式

        // 9 依据参数计算输出缓冲区大小
        int out_buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, out_sample_fmt, 1);

        // 10 创建音频数据缓冲区
        unsigned char* outBuff = (unsigned char*)av_malloc(MAX_AUDIO_FRAME_SIZE * out_channels);

        // 11 创建重采样上下文
        SwrContext* swrCtx = swr_alloc();

        // 12 分配重采样的上下文信息
        swr_alloc_set_opts2(&swrCtx,
                &pCodecCtx->ch_layout,             /*out*/
                out_sample_fmt,                    /*out*///fltp->slt
                out_sample_rate,                   /*out*/
                &pCodecCtx->ch_layout,               /*in*/
                pCodecCtx->sample_fmt,               /*in*/
                pCodecCtx->sample_rate,              /*in*/
                0,
                NULL);


        // 13 swr上下文初始化
        swr_init(swrCtx);


        ///   SDL
        // 14 SDL初始化
        if (SDL_Init(SDL_INIT_AUDIO))
        {
                SDL_Log("init audio subsysytem failed.");
                return 0;
        }

        // 15 配置音频播放结构体SDL_AudioSpec，和SwrContext的音频重采样参数保持一致
        SDL_AudioSpec wantSpec;
        wantSpec.freq = out_sample_rate;        //48000/1024=46.875帧
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

        /// 开始解码
        // 18 创建Packet包和Frame帧
        AVPacket* packet = av_packet_alloc();
        AVFrame* frame = av_frame_alloc();


        while (1)
        {
                if ((av_read_frame(pFormatCtx, packet)) < 0)
                        break;

                if (packet->stream_index == audioIndex)
                {
                        ret = avcodec_send_packet(pCodecCtx, packet);      // 送一帧到解码器

                        while (ret >= 0)
                        {
                                ret = avcodec_receive_frame(pCodecCtx, frame);  // 从解码器取得解码后的数据

                                if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                                        break;
                                else if (ret < 0)
                                {
                                        av_log(NULL, AV_LOG_ERROR, "Error while sending a packet to the decoder\n");
                                        goto end;
                                }

                                //                static FILE *p = fopen("152m4a.pcm", "wb");
                                //                fwrite(frame->buf, 1, out_buffer_size, p);

                                ret = swr_convert(swrCtx, &outBuff, MAX_AUDIO_FRAME_SIZE, (const uint8_t**)frame->data, frame->nb_samples);
                                if (ret < 0)
                                {
                                        av_log(NULL, AV_LOG_ERROR, "Error while converting\n");
                                        goto end;
                                }

                                //                static FILE *outFile = fopen("xxx.pcm", "wb");
                                //                fwrite(outBuff, 1, out_buffer_size, outFile);

                                while (audioLen > 0)
                                        SDL_Delay(1);

                                audioChunk = (unsigned char*)outBuff;
                                audioPos = audioChunk;
                                audioLen = out_buffer_size;


                                av_frame_unref(frame);
                        }
                }
                av_packet_unref(packet);
        }

        // 音频不需要 flush ?

end:// 19 退出
        SDL_Quit();

        avcodec_free_context(&pCodecCtx);
        avformat_close_input(&pFormatCtx);
        av_frame_free(&frame);

        swr_free(&swrCtx);


        return 0;
}
