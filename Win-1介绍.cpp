/********************/Win32 API/************************************************************/

//内核对象
* 用户和内核模式
* 80386芯片的4个权限级别：0~3
* Windows系统所使用的两个权限级别：0，3
* 操作系统运行在0环
* 一阶段开发的程序运行在3环

//句柄
* 内核对象的唯一标识符，也就是目前程序所在的内存的位置

//消息机制
* 使用回调函数(函数指针) 来实现
* Windows是消息驱动的操作系统

//Console(DOS)程序与Windows程序区别
任务				入口函数		链接选项（"调试属性>>链接器>>系统>>子系统"）	预处理器（"调试属性>>C/C++>>预处理器>>预处理器定义"）
Windows		多任务(多线程)	窗口/SUBSYSTEM:WINDOWS						_CONSOLE
Console		单任务			控制台/SUBSYSTEM:CONSOLE						_WINDOWS


//随机基址
关闭随机基址：属性页->连接器->高级->随机基址
关闭掉随机基址后，hInstance也是指向0x00400000。


//虚拟内存
每个32位的程序都有自己独立的4GB虚拟空间，其中低2G为用户可以操作的空间。
0~64K为保留区，高2G为操作系统操作的空间。
用户空间：0x00000000~0x7FFFFFFF
系统空间：0x80000000~0xFFFFFFFF


//进程间的内存隔离
会将低2G的用户空间映射到物理内存条不同的位置，来实现内存中的每个程序的地址空间是互相隔离的。
磁盘映射：当物理内存不够用时，会将一部分内存放到磁盘空间中。
hInstance是EXE程序在进程中的首地址，即其从磁盘拷贝向虚拟内存实从0x400000开始拷贝的。



/********************/VC/************************************************************/
//VC下编译工具分类(相当于GCC)
编译器CL.exe			作用是将源代码翻译成目标代码(.obj)
连接器LINK.exe		作用是将目标代码、库连接生成最终文件。
资源编译器RC.exe		作用是将资源编译，最终通过连接器存入最终文件。

//常见的VC的库(C:\Windows\System32)
1、kernel32.dll		//提供了线程、进程、内存管理等核心的API
2、user32.dll		//提供了窗口、消息等API
3、gdi32.dll			//提供了绘图的API

//VC下标准的头文件
<windef.h>			//windows的数据类型
<winbase.h>			//包含kernel32.dll所有API的声明
<wingdi.h>			//包含所有gdi32.dll的API的声明
<winuser.h>			//包含所有user32.dll的API的声明
<winnt.h>			//包含对UNICODE字符集的支持
<windows.h>			//所有windows头文件的集合



/********************/mian与字符集/************************************************************/
//main函数
WinMain用于ANSI字符集，而wWinMain(推荐使用)用于Unicode(宽字符)字符集。

#include <windows.h>

int WINAPI WinMain(
	HINSTANCE hInstance,      // handle to current instance，实例句柄，代表应用层本身，实际上是可执行文件在内存中的首地址
	HINSTANCE hPrevInstance,  // handle to previous instance
	LPSTR lpCmdLine,          // command line
	int nCmdShow)             // show state
{
	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	return 0;
}


APIENTRY : __stdcall 调用约定
_In_ : 说明性宏，表示输入参数
_Out_: 说明性宏，表示输出参数
HINSTANCE hInstance : 实例句柄，代表应用程序本身
HINSTANCE hPrevInstance : 已弃用，为了兼容老的入口函数
LPWSTR lpCmdLine : 命令行参数
int nCmdShow : 控制显示
{
	SW_HIDE				隐藏窗口并激活另一个窗口。
	SW_MAXIMIZE			最大化指定的窗口。
	SW_MINIMIZE			最小化指定的窗口并按Z顺序激活下一个顶级窗口。
	SW_RESTORE			激活并显示窗口。如果窗口被最小化或最大化，系统会将其恢复到原来的大小和位置。应用程序应该在恢复最小化窗口时指定此标志。
	SW_SHOW				激活窗口并显示其当前大小和位置。
	SW_SHOWMAXIMIZED	激活窗口并将其显示为最大化窗口。
	SW_SHOWMINIMIZED	激活窗口并将其显示为最小化窗口。
	SW_SHOWMINNOACTIVE	不激活窗口，将窗口显示为最小化窗口。类似于sw_show。
	SW_SHOWNA			不激活窗口，显示窗口的当前大小和位置。类似于SW_SHOW，。
	SW_SHOWNOACTIVATE	不激活窗口，显示窗口的最新大小和位置。类似于SW_SHOWNORMAL，。
	SW_SHOWNORMAL		激活并显示窗口。如果窗口被最小化或最大化，系统会将其恢复到原来的大小和位置。应用程序应该在第一次显示窗口时指定此标志。
}

Windows.h头文件中，将基础类型进行了重新定义，为了提高可读性和方便升级。
HINSTANCE（Handle Instance）
HWN（Handle Window）
LPWSTR（Long Pointer Wide Str）


//MessageBox
int MessageBox(
	HWND hWnd,          //窗口句柄
	LPCTSTR lpText,     //弹窗内容
	LPCTSTR lpCaption,  //弹窗标题
	UINT uType          //弹窗类型
);

MessageBox是宏定义，采用条件编译，在UNICODE和非UNICODE之间，切换。
当用ASCII时会调用MeaageBoxA，使用UNICODE的会调用MessageBoxW。

当Windows中涉及字符串的都会有两个版本。

在编译选项中，字符集位置来定义是否是UNICODE字符集。
多字节字符集是ASCII码(GBK编码，中文占两个字节，英文占一个字节)。


//TEXT()和_T()
<tchar.h>中的_T()依附于条件编译宏_UNICODE。
Windows提供了一个类似于_T()的宏，TEXT()。
MessageBox(NULL, TEXT("Hello World!"), TEXT("标题"), MB_OKCANCEL);

平台			头文件			条件			兼容宏
C语言		tchar.h			_UNICODE	_T
Windows		windows.h		UNICODE		_TEXT

_T 的意思是通知编译器，自行进行字符串的ASCII / Unicode转换。
而L表示，该字符串为Unicode版本。

//UNICODE宏条件的三个定义位置
1、头文件之前定义 #define UNICODE;
2、可以用属性->高级->字符集 来定义;
3、可以用 属性->C / C++->预处理器->预处理器定义 来定义。


//不同于Windows和Console的Dll程序
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
) {}

