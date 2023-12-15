#include "SDL.h"

//图片视频渲染通用
SDL_Init						初始化SDL，成功返回 0						SDL_Init( SDL_INIT_VIDEO | SDL_INIT_VIDEO | SDL_INIT_TIMER );
SDL_CreateWindow				创建窗口，返回 SDL_Window*					SDL_CreateWindow(  )
SDL_CreateRenderer			创建渲染器，返回 SDL_Renderer*
SDL_CreateWindowAndRenderer	创建窗口和渲染器
SDL_RenderClear				清除当前渲染目标
SDL_RenderCopy				复制纹理到渲染目标
SDL_RenderPresent				显示画面

//通用其他
SDL_Log						输出消息
SDL_LogError					输出消息
SDL_GetError					输出报错原因
SDL_Delay					延时ms
SDL_CreateThread				创建线程
SDL_GetWindowSize			获取窗口大小
SDL_memset					清空缓冲区
SDL_SetWindowTitle			设置窗口标题

//绘制图形
SDL_SetRenderDrawColor		设置画笔颜色
SDL_RenderDrawPoint			绘制一个点
SDL_RenderDrawLine			绘制直线
SDL_RenderDrawRect			绘制矩形
SDL_RenderFillRect				填充矩形

//图片渲染
SDL_LoadBMP					加载BMP图片，返回 SDL_Surface*
SDL_CreateTextureFromSurface	从表面创建纹理，返回 SDL_Texture*

//视频渲染
SDL_CreateTexture				创建纹理，返回 SDL_Texture*
SDL_UpdateTexture				更新纹理数据
SDL_UpdateYUVTexture			更新YUV纹理数据

//音频渲染 SDL_AudioSpec
SDL_OpenAudio				打开音频设备，成功返回 0
SDL_PauseAudio				开始播放
SDL_MixAudio					叠加音频buffer

SDL_OpenAudioDevice			打开音频设备，成功返回音频设备ID号（非回调版）
SDL_PauseAudioDevice			开始播放（非回调版）
SDL_QueueAudio				在回调设备上填充音频数据，而不用回调函数（非回调版）

//事件 SDL_Event
SDL_WaitEvent				等待事件
SDL_PushEvent				发送事件

//清理资源
SDL_DestroyTexture			释放纹理
SDL_FreeSurface				释放表面
SDL_DestroyRenderer			释放渲染器
SDL_DestroyWindow			释放窗口
SDL_Quit						退出SDL
