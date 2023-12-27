#include <iostream>

using namespace std;

extern "C"
{
#include "SDL.h"
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
        SDL_Window* window = SDL_CreateWindow("ShowPicture", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 480, SDL_WINDOW_SHOWN);
        if (!window)
        {
                std::cout << "SDL_CreateWindow failed! SDL_Error: " << SDL_GetError() << std::endl;
                return -2;
        }

        //3.创建渲染器。参数：渲染的窗口、渲染设备索引-1表示默认、属性
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);


        //***************绘制图形***************
        //设置画笔颜色
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

        //绘制一个点
        SDL_RenderDrawPoint(renderer, 300, 200);

        //绘制直线
        SDL_RenderDrawLine(renderer, 100, 100, 400, 400);

        //绘制矩形
        SDL_Rect rect;
        rect.x = 200;
        rect.y = 100;
        rect.w = 200;
        rect.h = 200;
        SDL_RenderDrawRect(renderer, &rect);

        //填充矩形
        SDL_SetRenderDrawColor(renderer, 220, 180, 140, 0);
        SDL_RenderFillRect(renderer, &rect);
        //*************************************


    //    //4.创建图片数据。
    //    SDL_Surface *pic = SDL_LoadBMP("1.bmp");

    //    //5.创建纹理。参数：目标渲染器、纹理格式、变化频率、纹理宽、纹理高
    //    SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(renderer, pic);

    //    //6.复制纹理到渲染目标。参数：渲染目标、输入纹理、选择输入纹理的一块区域NULL为整个输入、选择输出渲染目标的一块矩形区域NULL为整个渲染目标
    //    SDL_RenderCopy(renderer, sdlTexture, nullptr, nullptr);

        //7.显示画面。参数：渲染器
        SDL_RenderPresent(renderer);

        //8.创建循环事件
        SDL_Event event;
        while (1)
        {
                SDL_WaitEvent(&event);              //当有事件时抛出事件，否则阻塞释放CPU
                if (event.type == SDL_QUIT)          //用户从菜单要求退出程序
                        break;
        }

        //9.清理资源
    //    SDL_DestroyTexture(sdlTexture);
    //    SDL_FreeSurface(pic);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        //10.退出SDL
        SDL_Quit();



        return 0;
}
