#include <iostream>

//***** 将播放的声音发送给声卡，当声卡将要播放的声音输出到扬声器时，它首先会通过回调函数，向你要它一部分声频数据，然后拿着这部分音频数据去播放 *****//
//***** 等播放完了，它会再向你要下一部分，直到全部播放完毕 *****//

using namespace std;

extern "C"
{
#include "SDL.h"
}

#define SDL_MAIN_HANDLED

unsigned char* audioChunk = NULL;
unsigned int   audioLen = 0;
unsigned char* audioPos = NULL;

void fill_audio(void* udata, Uint8* stream, int len)
{
        //SDL 2.0
        SDL_memset(stream, 0, len);

        if (audioLen == 0)
                return;

        len = (len > audioLen ? audioLen : len);

        SDL_MixAudio(stream, audioPos, len, SDL_MIX_MAXVOLUME);

        audioPos += len;
        audioLen -= len;

        //cout << "buff use "<< len << endl;
}


#undef main
int main()
{
        //1.初始化SDL
        if (SDL_Init(SDL_INIT_AUDIO))
        {
                SDL_Log("init audio subsysytem failed.");
                return 0;
        }

        //2.配置音频播放结构体SDL_AudioSpec
        SDL_AudioSpec wantSpec;
        wantSpec.freq = 44100;
        wantSpec.format = AUDIO_F32SYS;
        wantSpec.channels = 2;
        wantSpec.silence = 0;
        wantSpec.samples = 1024;    // 512, 1024 均可  采样数据缓冲区 基准
        wantSpec.callback = fill_audio;

        //3.打开音频设备
        if (SDL_OpenAudio(&wantSpec, NULL) < 0) {
                cout << "can not open SDL!" << endl;
                return -1;
        }

        //4.打开音频文件
        FILE* fp = fopen("aki.pcm", "rb+");
        if (fp == NULL) {
                cout << "cannot open this file" << endl;
                return -1;
        }

        //5.创建音频数据缓冲区。pcm数据缓冲区大小 = 采样数据缓冲区基准 的 整数倍
        int pcm_buffer_size = wantSpec.samples * wantSpec.channels * SDL_AUDIO_BITSIZE(wantSpec.format) / 8;
        char* pcm_buffer = (char*)malloc(pcm_buffer_size);
        int data_count = 0;

        //6.开始播放
        SDL_PauseAudio(0);

        //7.循环读取播放
        int i = 0;
        while (1)
        {
                if (fread(pcm_buffer, 1, pcm_buffer_size, fp) != pcm_buffer_size)
                {
                        break;
                        //SDL_Delay(3000);
                        ///Loop
                        //fseek(fp, 0, SEEK_SET);
                        //fread(pcm_buffer, 1, pcm_buffer_size, fp);
                        //data_count = 0;
                }
                data_count += pcm_buffer_size;

                if (i % 100 == 0)
                        cout << "Now Playing " << data_count << " Bytes data." << endl;
                i++;

                audioChunk = (Uint8*)pcm_buffer;   //设置音频缓冲区（PCM数据）
                audioLen = pcm_buffer_size;         //音频缓冲区大小
                audioPos = audioChunk;

                while (audioLen > 0)                 //等待声卡将缓冲区数据读取完毕
                        SDL_Delay(1);
        }

        //8.释放音频数据缓冲区，退出SDL
        free(pcm_buffer);
        SDL_Quit();


        return 0;
}
