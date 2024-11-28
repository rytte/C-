

//Linux图形系统: 从上层到底层

Internationalization(I18N)（国际化）：涉及到文本翻译、区域设置、时间格式、货币符号等的处理

Desktop Environment（桌面环境）：如 KDE（基于Qt）、GNOME（基于GTK）、LXDE

Window Manager（窗口管理器）：窗口管理器负责管理显示屏上的窗口布局，包括窗口的打开、关闭、最大化、最小化、移动等。

Toolkits（工具包）：如Qt、GTK+，也就是GUI控件库。

Graphic Library（图形库）：如OpenGL，提供了底层绘制函数，是对下层API的封装。

Graphic Server（图形服务器）：如：X11、Wayland。最底层的组件，是图形系统的核心。它负责管理屏幕显示、输入设备（如键盘、鼠标）和窗口的基本交互。

---硬件渲染涉及以下更加底层的组件---

Direct Rendering Manager（DRM）：负责 framebuffer（帧缓冲区）管理和图形输出

硬件层（图形硬件、GPU）



//渲染开发简化结构
Qt

OpenGL

X11（EGL）

DRM

GPU


//X11
X Window System又名X11，即第11个版本。
X Window System包括X Server和X Client，他们使用X Protocol协议通信
X Server：每个需要显示图形界面的主机都要运行一个X Server，它负责主机中各个与图形界面有关硬件设备的管理，如在显示器中显示输出，从鼠标、键盘接受输入等；
X Client：X Client指那些需要图形界面的应用程序，如浏览器、终端、视频播放器等。
逐渐被 Wayland(更高效的现代窗口系统) 所取代。


//EGL
EGL 提供 OpenGL(ES) 与 DRM / KMS 之间的接口，允许直接在 DRM 上使用 OpenGL(ES)。
EGL 允许 OpenGL(ES) 创建一个 显示表面，该表面可以直接与 DRM 提供的帧缓冲区交互，用于渲染内容。


//mesa
Mesa 是一个开源图形库，实现了多个图形 API，包括 OpenGL、OpenGL ES、Vulkan 等。（即依照OpenGL标准进行API的实现）


//离屏渲染
传统渲染：直接渲染到屏幕帧缓冲区上，最终显示在用户屏幕中。
离屏渲染：渲染在一个非屏幕的缓冲区（如纹理Texture、帧缓冲对象FBO或临时缓冲区）中。渲染结果不会直接显示，而是保存在内存中供后续使用。



/********************/DRM/************************************************************/
1、DRM 驱动 由每个 GPU 硬件厂商（如 Intel、AMD、NVIDIA、Arm Mali）各自实现
2、DRM 驱动 程序负责管理 GPU 和显示硬件的具体功能，包括内存管理、缓冲区分配、模式设置等

//功能
GEM（Graphics Execution Manager）：负责 GPU 内存的管理，包括分配、释放、共享和映射，是 GPU 缓冲区管理的标准机制。
KMS（Kernel Mode Setting）：管理帧缓冲区（Framebuffer），控制显示模式设置（分辨率、刷新率）和显示管道。
DMA - BUF：提供缓冲区共享机制，允许不同设备（如 GPU、视频解码器、显示引擎）高效地共享帧缓冲区。

//下层管理（图形硬件设备）
GPU：提供图形渲染功能，包括 3D 图形、纹理处理和计算着色器。DRM 管理 GPU 的命令队列、内存分配和渲染任务。
显示引擎：负责将帧缓冲区中的图像输出到显示设备。包括 CRTC（光栅转换器）、Plane（平面）和 Encoder（编码器）。
显示设备：例如LCD、LED 显示屏、HDMI 显示器。


//核心概念
Framebuffer
指一个内存缓冲区，存储要显示的像素数据。
可以通过 KMS 将帧缓冲区绑定到显示设备。

CRTC（光栅扫描转换器）
负责将帧缓冲区中的数据转换为显示设备可识别的信号。
一个系统可以有多个 CRTC，支持多显示器。

Plane
代表一个可叠加的图像层，多个 Plane 可以组合在一起形成最终显示。
常见的 Plane 包括主 Plane（Primary Plane）和覆盖层（Overlay Plane）。

Connector
表示物理显示设备（如 HDMI、DisplayPort、VGA）。
DRM 管理连接器的状态（连接、断开、支持的分辨率等）。


//Plane
Plane 是直接由显示引擎管理的硬件层，绕过了传统的窗口系统（如 X11 或 Wayland），直接将内容提交到显示硬件。
每个 GPU 或显示引擎（Display Engine）在硬件设计时定义了支持的 Plane 数量。
Primary Plane：1 个，负责显示主内容。
Overlay Plane：一般支持多个，主要用于视频或叠加图层。
Cursor Plane：1 或 2 个，用于渲染鼠标指针或硬件加速的光标。

X11 使用 GPU 或 CPU 将所有窗口内容合成到一个帧缓冲区（framebuffer），然后通过 Primary Plane 提交给显示硬件。


//Plane次序控制
* 使用 zpos（Z - position）属性来设置 Plane 的叠加顺序。
* 通过 drm_info 或 libdrm 检查和设置 Plane 的 zpos 值。
