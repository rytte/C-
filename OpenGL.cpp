
OpenGL是一个规范而非语言，它定义了OpenGL函数的接口，以及OpenGL函数的参数和返回值。函数具体实现将由OpenGL库的开发者自行决定。

实际的OpenGL库的开发者通常是显卡的生产商。你购买的显卡所支持的OpenGL版本都为这个系列的显卡专门开发的。
这是因为OpenGL的实现和优化与显卡的硬件特性紧密相关，由显卡生产商来开发可以确保OpenGL库能够充分利用显卡的硬件能力。
由于OpenGL的大多数实现都是由显卡厂商编写的，当产生一个bug时通常可以通过升级显卡驱动来解决。这些驱动会包括你的显卡能支持的最新版本的OpenGL。


#include <glad/glad.h>		//glad需要在glfw之前被引入
#include <glfw3.h>


//双缓冲(Double Buffer)
前缓冲保存着最终输出的图像，它会在屏幕上显示；而所有的的渲染指令都会在后缓冲上绘制。
当所有的渲染指令执行完毕后，我们交换(Swap)前缓冲和后缓冲，这样图像就立即呈显出来，解决了单缓冲绘图时可能会存在图像闪烁的问题。


//VAO，VBO，EBO
VAO（Vertex Array Object，顶点数组对象），它存储了顶点数据的格式以及顶点数据所需的缓存对象的引用，任何随后的顶性调用都会储存在这个VAO中。
VBO（Vertex Buffer Object，顶点缓冲对象），它存储了顶点数据，它与顶点数组对象一起工作，它允许我们把顶点数据从CPU传到GPU，以减少CPU和GPU之间的数据传输。
EBO（Element Buffer Object，索引缓冲对象），专门储存索引，OpenGL调用这些顶点的索引来决定该绘制哪个顶点。

TB（Texture Obeject，纹理对象）
FBO（Frame Buffer Object，帧缓存对象）

一个VAO对应一个物体，一个VBO对应一个物品的所有属性 （顶点坐标、颜色等，除顶点索引外），而一个EBO仅对应一个物品的一种属性（顶点索引属性）。


//图形渲染管线
OpenGL的大部分工作都是关于把3D坐标转变为适应你屏幕的2D像素。
3D坐标转为2D坐标的处理过程是由OpenGL的图形渲染管线（Graphics Pipeline，大多译为管线，实际上指的是一堆原始图形数据途经一个输送管道，期间经过各种变化处理最终出现在屏幕的过程）管理的。
图形渲染管线可以被划分为两个主要部分：第一部分把你的3D坐标转换为2D坐标，第二部分是把2D坐标转变为实际的有颜色的像素。

//着色器
图形渲染管线具有并行执行的特性，当今大多数显卡都有成千上万的小处理核心，
它们在GPU上为每一个（渲染管线）阶段运行各自的小程序，从而在图形渲染管线中快速处理你的数据。这些小程序叫做着色器(Shader)。

//相关术语
顶点数据（Vertex Data）：顶点数据是从CPU传入到GPU的，传输是一个开销非常大的过程，因此应尽量减少传输的数据。
顶点着色器（Vertex Shader）：加工顶点数据，一般是指顶点数据的变换。这部分需要自己来实现代码，可以对顶点进行各种操作或修改数据，需要保证最终只有一个顶点坐标，并且将一些会在其他阶段使用的数据传递输出。
图元装配（Shape Assembly）：OpenGL支持四种基本图元类型：点，线，三角形，四边形，并提供了一些扩展图元供使用。
几何着色器（Geometry Shader）：生成新的顶点数据（输入一个顶点，能够生成新的顶点数据）；修改输出的图元类型（输入图元是点，能够输出线条图元或者三角形图元）
光栅化（rasterization）：将前两阶段处理之后的几何数据经过一系列变换转换为像素。
片段着色器（Fragment Shader）：计算光栅化中产生片段（“像素”）的颜色；带有一定的裁剪功能（discard）
测试（Tests）：筛选并处理从片段处理器中传递过来的像素。
混合（Blending）：混合技术常用于表现物体的透明度。
















//QOpenGL
在QOpenGLWidget的三个虚函数之外操作OpenGL对象必须要绑定当前OpenGL上下文，也就是要提前调用QOpenGLWidget::makeCurrent()方法。
使用OpenGL对象自身的一些方法也需调用bind()，才能正常使用，使用结束之后，最好习惯性的解除绑定（release方法）

避免以下问题：
1、未调用makeCurrent，直接创建OpenGL对象，导致创建失败。
2、未绑定VBO，调用VBO::allocate()，导致内存分配失败。
3、未绑定VBO，调用VBO::size()，获取到错误的数据，导致内存泄漏。
4、未解绑VAO，导致VBO混乱。
5、未绑定VAO，直接调用QOpenGLShaderProgram::setAttributeArray()，导致内存泄漏



//基本绘图操作
1.创建OpenGL窗口：创建窗口类，继承自QOpenGLWidget，需要实现三个虚函数。同时继承QOpenGLExtraFunctions，该类拥有大量gl函数。
initializeGL()—建立OpenGL的资源和状态。在第一次调用resizeGL()或paintGL()之前调用一次
resizeGL()—设置OpenGL视口，投影等。每当调整Widget的大小时（第一次显示窗口Widget时会调用它，因为所有新创建Widget都会自动获得调整大小的事件）。
paintGL()—渲染OpenGL场景，需要更新Widget时就会调用。

2.创建并编写着色器程序

3.为着色器程序装配顶点数据

4.启动渲染管线进行绘图


