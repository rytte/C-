#include <iostream>
#include <map>

using namespace std;

extern "C"
{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libswresample/swresample.h"
#include "libavutil/time.h"
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

//最大音频帧
#define MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio    //48000 * (32/8)

//音频变量
unsigned int audioLen = 0;
unsigned char* audioChunk = NULL;
unsigned char* audioPos = NULL;

//回调函数
void fill_audio(void* udata, Uint8* stream, int len)
{
        SDL_memset(stream, 0, len);
        if (audioLen == 0)return;

        len = (len > audioLen ? audioLen : len);

        SDL_MixAudio(stream, audioPos, len, SDL_MIX_MAXVOLUME);

        audioPos += len;
        audioLen -= len;
}




//线程变量
int thread_quit = 0;
int thread_pause = 0;

//SDL 变量
SDL_Window* window;





//视频解码线程
//int thread_video_decode(void *data)
//{
//    AVFormatContext* pFormatCtx = (AVFormatContext*) data;

//    //1.查找流
//    int videoIndex = av_find_best_stream(pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, -1);
//    if(videoIndex < 0) return videoIndex;

//    //2.创建音视频解码器上下文
//    AVCodecContext* pCodecCtx = avcodec_alloc_context3(nullptr);

//    //3.解码器上下文获取参数
//    int ret = avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[videoIndex]->codecpar);
//    if(ret < 0) return ret;

//    //4.查找解码器
//    const AVCodec* pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
//    if(!pCodec) return -1;

//    //5.打开解码器并绑定上下文
//    ret = avcodec_open2(pCodecCtx, pCodec, nullptr);
//    if(ret < 0) return ret;

//    //初始化SDL
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
//    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, 0, pCodecCtx->width, pCodecCtx->height);
//    if(!texture) return -2;
//    SDL_Rect rect = SDL_Rect{0, 0, pCodecCtx->width, pCodecCtx->height};

//    //7.创建包和帧
//    int64_t start_time = av_gettime();              //获取从公元1970年1月1日0时0分0秒开始的微秒值
//    AVPacket* packet = av_packet_alloc();
//    AVFrame* frame = av_frame_alloc();

//    //解码
//    while(!thread_quit)
//    {
//        if(thread_pause)
//        {
//            SDL_Delay(10);
//            start_time += 10*1000;
//            continue;
//        }

//        //读取一个包数据
//        if(av_read_frame(pFormatCtx, packet) < 0)
//            break;

//        if(packet->stream_index == videoIndex)
//        {
//            //发送一个包数据
//            avcodec_send_packet(pCodecCtx, packet);

//            //显示数据
//            while(1)
//            {
//                ret = avcodec_receive_frame(pCodecCtx, frame);
//                if(ret < 0) break;
//                else if(ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) break;

//                SDL_UpdateYUVTexture(texture, &rect,
//                                     frame->data[0], frame->linesize[0],
//                                     frame->data[1], frame->linesize[1],
//                                     frame->data[2], frame->linesize[2]);
//                SDL_RenderClear(renderer);
//                SDL_RenderCopy(renderer, texture, nullptr, &rect);
//                SDL_RenderPresent(renderer);

//                //延时控制
//                AVRational time_base_q = {1,AV_TIME_BASE};          // 1/1000000秒，即1us
//                int64_t pts_time = av_rescale_q(frame->pkt_dts, pFormatCtx->streams[videoIndex]->time_base, time_base_q);  //该函数将<参数二>时基中的<参数一>时间戳转换<参数三>时基下的<返回值>时间戳
//                int64_t now_time = av_gettime() - start_time;       // 计算当前程序已开始时间
//                if(pts_time > now_time)                             // 若应帧解码时间>当前时间对比，延时到应解码的时间再开始解下一帧(若无此延时则计算机将会很快解码显示完)
//                    av_usleep(pts_time - now_time);

//                av_frame_unref(frame);
//            }
//        }
//        av_packet_unref(packet);
//    }

//    av_frame_free(&frame);
//    return 0;
//}



//音频解码线程
int thread_audio_decode(void* data)
{
        AVFormatContext* pFormatCtx = (AVFormatContext*)data;

        //1.查找流
        int audioIndex = av_find_best_stream(pFormatCtx, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
        if (audioIndex < 0) return audioIndex;

        //2.创建音视频解码器上下文
        AVCodecContext* pCodecCtx = avcodec_alloc_context3(nullptr);

        //3.解码器上下文获取参数
        int ret = avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[audioIndex]->codecpar);
        if (ret < 0) return ret;

        //4.查找解码器
        const AVCodec* pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
        if (!pCodec) return -1;

        //5.打开解码器并绑定上下文
        ret = avcodec_open2(pCodecCtx, pCodec, nullptr);
        if (ret < 0) return ret;

        //6.设置音频播放采样参数
        int out_sample_rate = pCodecCtx->sample_rate;           //采样率    48000
        int out_channels = pCodecCtx->ch_layout.nb_channels; //通道数    2
        int out_nb_samples = pCodecCtx->frame_size;            //单个通道中的样本数  1024
        enum AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_FLT; //声音格式  SDL仅支持部分音频格式

        //7.依据参数计算输出缓冲区大小
        int out_buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, out_sample_fmt, 1);

        //8.创建音频数据缓冲区
        unsigned char* outBuff = (unsigned char*)av_malloc(MAX_AUDIO_FRAME_SIZE * out_channels);

        //9.创建重采样上下文
        SwrContext* swrCtx = swr_alloc();

        //10.分配重采样的上下文信息
        swr_alloc_set_opts2(&swrCtx,
                &pCodecCtx->ch_layout,             /*out*/
                out_sample_fmt,                    /*out*///fltp->slt
                out_sample_rate,                   /*out*/
                &pCodecCtx->ch_layout,               /*in*/
                pCodecCtx->sample_fmt,               /*in*/
                pCodecCtx->sample_rate,              /*in*/
                0,
                NULL);


        //11.swr上下文初始化
        swr_init(swrCtx);


        ///   SDL
        //12.配置音频播放结构体SDL_AudioSpec，和SwrContext的音频重采样参数保持一致
        SDL_AudioSpec wantSpec;
        wantSpec.freq = out_sample_rate;        //48000/1024=46.875帧
        wantSpec.format = AUDIO_FORMAT_MAP[out_sample_fmt];
        wantSpec.channels = out_channels;
        wantSpec.silence = 0;
        wantSpec.samples = out_nb_samples;
        wantSpec.callback = fill_audio;                 //回调函数
        wantSpec.userdata = pCodecCtx;

        //14.打开音频设备
        if (SDL_OpenAudio(&wantSpec, NULL) < 0)
        {
                printf("can not open SDL!\n");
                return -1;
        }

        //15.开始播放
        SDL_PauseAudio(0);

        //16.创建帧和包
        AVPacket* packet = av_packet_alloc();
        AVFrame* frame = av_frame_alloc();

        //解码
        while (!thread_quit)
        {
                if (thread_pause)
                {
                        SDL_Delay(10);
                        continue;
                }

                //读取一个包数据
                if (av_read_frame(pFormatCtx, packet) < 0)
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
                                        break;
                                }

                                ret = swr_convert(swrCtx, &outBuff, MAX_AUDIO_FRAME_SIZE, (const uint8_t**)frame->data, frame->nb_samples);
                                if (ret < 0)
                                {
                                        av_log(NULL, AV_LOG_ERROR, "Error while converting\n");
                                        break;
                                }

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


        av_frame_free(&frame);
        return 0;
}




#undef main
int main()
{
        cout << "avformat_version : " << avformat_version() << endl;


        //1.创建上下文
        AVFormatContext* pFormatCtx = avformat_alloc_context();

        //2.打开文件
        int ret = avformat_open_input(&pFormatCtx, "aki.mp4", nullptr, nullptr);
        if (ret < 0) return ret;

        //3.上下文获取流信息
        ret = avformat_find_stream_info(pFormatCtx, nullptr);
        if (ret < 0) return ret;

        //4.查找视频流
        int videoIndex = av_find_best_stream(pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
        if (videoIndex < 0) return videoIndex;

        //5.获取视频数据
        av_dump_format(pFormatCtx, -1, nullptr, 0);


        //SDL_Window在主线程创建才可以运行时移动
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
        int videoWidth = pFormatCtx->streams[videoIndex]->codecpar->width;
        int videoHeight = pFormatCtx->streams[videoIndex]->codecpar->height;
        window = SDL_CreateWindow("SDL2.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, videoWidth, videoHeight, SDL_WINDOW_RESIZABLE);

        //创建SDL音视频解码线程，并传入参数
    //    SDL_Thread *thread_video = SDL_CreateThread(thread_video_decode, NULL, pFormatCtx);
        SDL_Thread* thread_audio = SDL_CreateThread(thread_audio_decode, NULL, pFormatCtx);
        SDL_Event event;                    //定义事件


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



        //结束
        SDL_Quit();
        avformat_close_input(&pFormatCtx);


        return 0;
}
