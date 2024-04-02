/******************************/SDL核心API/******************************************************************************************/
基本的SDL的使用思路，基本分为三部分：初始化--->循环渲染--->销毁释放资源。

//SDL 初始化相关方法 ：
SDL_Init() : 初始化SDL
SDL_CreateWindow() : 创建窗口（Window）
SDL_CreateRenderer() : 基于窗口创建渲染器（Render）
SDL_CreateTexture() : 创建纹理（Texture）

//SDL 渲染数据相关方法：
SDL_UpdateTexture() : 设置纹理的数据。
SDL_RenderCopy() : 纹理复制给渲染器。
SDL_RenderPresent() : 显示。

//SDL 销毁释放资源相关方法：
SDL_DestroyTexture(tex) : 释放纹理资源
SDL_DestroyRenderer(ren) : 释放渲染器
SDL_DestroyWindow(win) : 释放窗口
SDL_Quit() : 关闭所有SDL子系统


//SDL 核心 API 使用流程
初始化：SDL_Init()
创建SDL_Window：SDL_CreateWindow()
创建SDL_Render：SDL_CreateRenderer()
创建SDL_Texture：SDL_CreateTexture()
更新SDL_Texture：SDL_UpdateTexture()
渲染SDL_Texture：SDL_RenderCopy()
显示：SDL_RenderPresent()
返回步骤4（创建Texture）继续执行


//SDL_Texture 与 SDL_Surface
SDL_Render对象中有一个视频缓冲区，该缓冲区我们称之为SDL_Surface，它是按照像素存放图像的。
SDL_Texture 与 SDL_Surface 相似，也是一种缓冲区。只不过它存放的不是真正的像素数据，而是存放的图像的描述信息。
这些描述信息通过OpenGL、D3D 或 Metal等技术操作GPU，从而绘制出与SDL_Surface一样的图形，且效率更高。



/******************************/函数详解/******************************************************************************************/
//一、初始化函数 SDL_Init()
int SDL_Init(Uint32 flags)				//该初始化函数可以确定希望激活的子系统

Uint32 flags参数为要启动的子系统的flag值，具体可以传入的内容如下：

SDL_INIT_TIMER：定时器
SDL_INIT_AUDIO：音频
SDL_INIT_VIDEO：视频
SDL_INIT_JOYSTICK：摇杆
SDL_INIT_HAPTIC：触摸屏
SDL_INIT_GAMECONTROLLER：游戏控制器
SDL_INIT_EVENTS：事件
SDL_INIT_NOPARACHUTE：不捕获关键信号（这个不理解）
SDL_INIT_EVERYTHING：包含上述所有选项


//二、创建窗口 SDL_CreateWindow()
SDL_Window* SDL_CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags);

title ：窗口标题
x ：窗口位置x坐标。也可以设置为SDL_WINDOWPOS_CENTERED或SDL_WINDOWPOS_UNDEFINED。
y ：窗口位置y坐标。同上。
w ：窗口的宽
h ：窗口的高
flags ：支持窗口的状态属性的标识。包括了窗口的是否最大化、最小化，能否调整边界等等属性。默认则设为0。
SDL_WINDOW_FULLSCREEN
SDL_WINDOW_FULLSCREEN_DESKTOP
SDL_WINDOW_OPENGL
SDL_WINDOW_VULKAN
SDL_WINDOW_METAL
SDL_WINDOW_HIDDEN
SDL_WINDOW_BORDERLESS
SDL_WINDOW_RESIZABLE
SDL_WINDOW_MINIMIZED
SDL_WINDOW_MAXIMIZED
SDL_WINDOW_INPUT_GRABBED
SDL_WINDOW_ALLOW_HIGHDPI
返回创建完成的窗口的ID。如果创建失败则返回0。


//三、创建渲染器 SDL_CreateRenderer()
SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags);

window ： 渲染的目标窗口。
index ：打算初始化的渲染设备的索引。设置“ - 1”则初始化默认的渲染设备。
flags ：支持以下值（位于SDL_RendererFlags定义中），默认则设为0。
	SDL_RENDERER_SOFTWARE->使用软件渲染；
	SDL_RENDERER_ACCELERATED->使用硬件加速；
	SDL_RENDERER_PRESENTVSYNC->和显示器的刷新率同步
返回创建完成的渲染器的ID。如果创建失败则返回NULL。


//四、创建纹理 SDL_CreateTexture()
SDL_Texture* SDL_CreateTexture(SDL_Renderer* renderer, Uint32 format, int access, int w, int h);

renderer：目标渲染器。
format ：纹理的像素格式。SDL_PixelFormatEnum枚举值，见附录。
access ：可以取以下值（定义位于SDL_TextureAccess中） 
SDL_TEXTUREACCESS_STATIC			//纹理几乎不会改变，不可被锁定
SDL_TEXTUREACCESS_STREAMING	//纹理经常会改变，可以被锁定
SDL_TEXTUREACCESS_TARGET		//纹理可以作为渲染目标
w ：纹理的宽
h ：纹理的高
这个函数创建成功则返回纹理的ID，失败返回0。


//五、更新纹理 SDL_UpdateTexture()
int SDL_UpdateTexture(SDL_Texture* texture, const SDL_Rect* rect, const void* pixels, int pitch);

texture：目标纹理。
rect：更新像素的矩形区域。设置为NULL的时候更新整个区域。
pixels：像素数据。
pitch：一行像素数据的字节数。
这个函数更新纹理成功的话返回0，失败的话返回 - 1。


//六、复制纹理到渲染目标 SDL_RenderCopy()
int SDL_RenderCopy(SDL_Renderer * renderer, SDL_Texture * texture, const SDL_Rect * srcrect, const SDL_Rect * dstrect);

renderer：渲染目标。
texture：输入纹理。
srcrect：选择输入纹理的一块矩形区域作为输入。设置为NULL的时候整个纹理作为输入。
dstrect：选择渲染目标的一块矩形区域作为输出。设置为NULL的时候整个渲染目标作为输出。
这个函数执行成功的话返回0，失败的话返回 - 1。


//七、显示画面 SDL_RenderPresent()
void SDL_RenderPresent(SDL_Renderer * renderer);

其中参数 renderer 用于指定渲染器。



/******************************/附录/******************************************************************************************/
//SDL_PixelFormatEnum
SDL_PIXELFORMAT_UNKNOWN
SDL_PIXELFORMAT_INDEX1LSB
SDL_PIXELFORMAT_INDEX1MSB
SDL_PIXELFORMAT_INDEX4LSB
SDL_PIXELFORMAT_INDEX4MSB
SDL_PIXELFORMAT_INDEX8
SDL_PIXELFORMAT_RGB332
SDL_PIXELFORMAT_RGB444
SDL_PIXELFORMAT_RGB555
SDL_PIXELFORMAT_BGR555
SDL_PIXELFORMAT_ARGB4444
SDL_PIXELFORMAT_RGBA4444
SDL_PIXELFORMAT_ABGR4444
SDL_PIXELFORMAT_BGRA4444
SDL_PIXELFORMAT_ARGB1555
SDL_PIXELFORMAT_RGBA5551
SDL_PIXELFORMAT_ABGR1555
SDL_PIXELFORMAT_BGRA5551
SDL_PIXELFORMAT_RGB565
SDL_PIXELFORMAT_BGR565
SDL_PIXELFORMAT_RGB24
SDL_PIXELFORMAT_BGR24
SDL_PIXELFORMAT_RGB888
SDL_PIXELFORMAT_RGBX8888
SDL_PIXELFORMAT_BGR888
SDL_PIXELFORMAT_BGRX8888
SDL_PIXELFORMAT_ARGB8888
SDL_PIXELFORMAT_RGBA8888
SDL_PIXELFORMAT_ABGR8888
SDL_PIXELFORMAT_BGRA8888
SDL_PIXELFORMAT_ARGB2101010
SDL_PIXELFORMAT_RGBA32	alias for RGBA byte array of color data, for the current platform(>= SDL 2.0.5)
SDL_PIXELFORMAT_ARGB32	alias for ARGB byte array of color data, for the current platform(>= SDL 2.0.5)
SDL_PIXELFORMAT_BGRA32	alias for BGRA byte array of color data, for the current platform(>= SDL 2.0.5)
SDL_PIXELFORMAT_ABGR32	alias for ABGR byte array of color data, for the current platform(>= SDL 2.0.5)
SDL_PIXELFORMAT_YV12	planar mode : Y + V + U(3 planes)
SDL_PIXELFORMAT_IYUV	planar mode : Y + U + V(3 planes)
SDL_PIXELFORMAT_YUY2	packed mode : Y0 + U0 + Y1 + V0(1 plane)
SDL_PIXELFORMAT_UYVY	packed mode : U0 + Y0 + V0 + Y1(1 plane)
SDL_PIXELFORMAT_YVYU	packed mode : Y0 + V0 + Y1 + U0(1 plane)
SDL_PIXELFORMAT_NV12	planar mode : Y + U / V interleaved(2 planes) (>= SDL 2.0.4)
SDL_PIXELFORMAT_NV21	planar mode : Y + V / U interleaved(2 planes) (>= SDL 2.0.4)