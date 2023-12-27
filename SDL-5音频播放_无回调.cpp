#include <iostream>

//***** 目前在windows上使用预编译的库，没有自己编译。在代码中数据推送都成功，但是没有声音。后经测试，树莓派官方Debian系统可用 *****//

using namespace std;

extern "C"
{
#include "SDL.h"
}

#define SDL_MAIN_HANDLED

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
        wantSpec.format = AUDIO_S16SYS;  // 2字节
        wantSpec.channels = 2;           // 2个声道
        wantSpec.silence = 0;            //
        wantSpec.samples = 1024;  // 多取值2^n，如512,1024。 采样数据缓冲区 基准
        wantSpec.callback = NULL;

        //3.打开音频设备
        SDL_AudioDeviceID deviceID;
        if ((deviceID = SDL_OpenAudioDevice(NULL, 0, &wantSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE)) < 2)
        {
                cout << "can not open SDL!" << endl;
                return -1;
        }

        //4.打开音频文件
        FILE* fp = fopen("ppccmm.pcm", "rb+");
        if (fp == NULL)
        {
                cout << "cannot open this file" << endl;
                return -1;
        }

        //5.创建音频数据缓冲区。pcm数据缓冲区大小 = 采样数据缓冲区基准 的 整数倍
        int pcm_buffer_size = wantSpec.samples * wantSpec.channels * SDL_AUDIO_BITSIZE(wantSpec.format) / 8;
        char* pcm_buffer = (char*)malloc(pcm_buffer_size);
        int data_count = 0;

        //6.开始播放
        SDL_PauseAudioDevice(deviceID, 0);

        //7.循环读取播放
        while (1)
        {
                if (fread(pcm_buffer, 1, pcm_buffer_size, fp) != pcm_buffer_size)
                {
                        break;
                        //SDL_Delay(3000);
                        //Loop
                        //fseek(fp, 0, SEEK_SET);
                        //fread(pcm_buffer, 1, pcm_buffer_size, fp);
                        //data_count = 0;
                }

                data_count += pcm_buffer_size;
                cout << "Now Playing " << data_count << "Bytes data." << endl;

                SDL_QueueAudio(deviceID, pcm_buffer, pcm_buffer_size);

                SDL_Delay(20); // 1024/44100 == 0.023 s
        }

        //8.释放音频数据缓冲区，退出SDL
        free(pcm_buffer);
        SDL_Quit();

        return 0;
}
