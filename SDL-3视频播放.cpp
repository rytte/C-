#include <iostream>

using namespace std;

extern "C"
{
#include "SDL.h"
}


int screen_w = 500;
int screen_h = 500;

// 根据不同的YUV视频，来设置不同的 宽 * 高 数据
const int pixel_w = 352;
const int pixel_h = 288;

const int bpp = 12;                                 //每个像素的bit
unsigned char buffer[pixel_w * pixel_h * bpp / 8];

#define REFRESH_EVENT  (SDL_USEREVENT + 1)          //刷新事件

int thread_exit = 0;

int refresh_video(void* opaque)
{
        while (thread_exit == 0)
        {
                SDL_Event event;
                event.type = REFRESH_EVENT;
                SDL_PushEvent(&event);
                SDL_Delay(40);
        }
        return 0;
}


#undef main
int main()
{
        cout << "Hello World!" << endl;


        //1.初始化SDL。成功返回0
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
                cout << "SDL_Init failed! SDL_Error: " << SDL_GetError() << endl;
                return -1;
        }

        //2.创建窗口。参数：标题、x坐标、y坐标、宽、高、属性
        SDL_Window* window = SDL_CreateWindow("Simplest Video Play SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                screen_w, screen_h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (!window)
        {
                std::cout << "SDL_CreateWindow failed! SDL_Error: " << SDL_GetError() << std::endl;
                return -2;
        }

        //3.创建渲染器。参数：渲染的窗口、渲染设备索引-1表示默认、属性
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);


        // IYUV: Y + U + V  (3 planes)
        // YV12: Y + V + U  (3 planes)
        // I420也叫IYUV, 也叫YUV420

        // 按照YUV视频的宽高创建SDL纹理对象
        SDL_Texture* sdlTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, pixel_w, pixel_h);

        FILE* fp = NULL;

        fp = fopen("qiu.mp4", "rb+");
        if (fp == NULL)
        {
                cout << "cannot open this file" << endl;
                return -1;
        }

        SDL_Rect sdlRect;

        SDL_Thread* refresh_thread = SDL_CreateThread(refresh_video, NULL, NULL);
        SDL_Event event;
        while (1)
        {
                SDL_WaitEvent(&event);                                  //Wait
                if (event.type == REFRESH_EVENT)
                {
                        if (fread(buffer, 1, pixel_w * pixel_h * bpp / 8, fp) != pixel_w * pixel_h * bpp / 8)     // 读取一帧数数据到缓冲区
                        {
                                fseek(fp, 0, SEEK_SET);
                                fread(buffer, 1, pixel_w * pixel_h * bpp / 8, fp);
                        }
                        SDL_UpdateTexture(sdlTexture, NULL, buffer, pixel_w);       // 将数据更新到纹理

                        sdlRect.x = 0;                                              // 窗口大小
                        sdlRect.y = 0;
                        sdlRect.w = screen_w;
                        sdlRect.h = screen_h;

                        SDL_RenderClear(renderer);                                  // 清除当前渲染目标
                        SDL_RenderCopy(renderer, sdlTexture, NULL, &sdlRect);       // 将更新后的纹理拷贝到渲染器
                        SDL_RenderPresent(renderer);                                // 渲染器显示画面
                        SDL_Delay(40);                                              // Dealy时常根据帧率进行调整
                }
                else if (event.type == SDL_WINDOWEVENT)                         //调整大小
                {
                        SDL_GetWindowSize(window, &screen_w, &screen_h);
                }
                else if (event.type == SDL_QUIT)                                //关闭窗口
                {
                        break;
                }
        }

        //9.清理资源
        SDL_DestroyTexture(sdlTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        //10.退出SDL
        SDL_Quit();


        return 0;
}
