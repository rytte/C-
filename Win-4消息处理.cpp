/********************/消息/************************************************************/
#include <windows.h>

消息：就是QT中的事件;

//Windows的消息结构体
typedef struct tagMSG {
	HWND hwnd;				//触发消息的窗口的句柄。
	UINT message;			//消息ID。操作系统为每个消息都分配了一个唯一的消息ID。如:WM_CREATE本质就是一个整数，就是消息ID。
	WPARAM wParam;			//消息可附带的参数。
	LPARAM lParam;			//消息可附带的参数。
	DWORD time;				//发生消息的时刻。
	POINT pt;				//发生消息时鼠标所在的位置。
} MSG;


//消息队列
消息队列分为两种，一种是系统消息队列，另外一种是进程消息队列。
我们在触发消息后，消息先进入系统消息队列。
操作系统处理后会根据消息的的窗口句柄hwnd值将消息分配到我们程序自己的消息队列，然后在我们程序内部进行消息的处理。


//消息循环
见消息循环函数;
void Message()
{
    MSG nMsg = { 0 };
    while (GetMessage(&nMsg, NULL, 0, 0))		//GetMessage()不断获取消息队列中的消息
    {
        TranslateMessage(&nMsg);				//将虚拟键消息转成字符消息WM_CHAR、WM_SYSCHAR等等
        DispatchMessage(&nMsg);					//将消息分派到定义好的窗口处理函数中进行处理
    }
}

GetMessage（LPMSG lpMsg，HWND hWnd，UINT wMsgFilterMin，UINT wMsgFilterMax)
lpMsg —— 用来存放消息的MSG类型的指针。
hWnd —— 指定取得其消息的窗口的句柄。当其值取NULL时，GetMessage为任何属于调用线程的窗口检索消息。
wMsgFilterMin —— 指定被检索的最小消息值的整数。
wMsgFilterMax —— 指定被检索的最大消息值的整数。

GetMessage()获取到消息后，TranslateMessage会将消息进行翻译，主要是把虚拟键消息转换为字符消息。
字符消息被寄送到调用线程的消息队列里，当下一次线程调用函数GetMessage或PeekMessage时被读出。
Windows中每一个键盘按键，都对应了一个宏，这个键盘按键发出的消息就是虚拟键消息。



/********************/消息处理;/************************************************************/

//WM_CREATE 
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);								//可以使GetMessage返回0  
		break;
	case  WM_CREATE:
	{
		CREATESTRUCT crt = *((CREATESTRUCT*)lParam);	//lParam参数的使用
		char buf[256] = { 0 };
		sprintf(buf, "创建的窗口类名称是%s，窗口名称是%s", crt.lpszClass, crt.lpszName);
		MessageBox(NULL, buf, "消息处理", MB_OK);
	}

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//WM_QUIT
WM_QUIT是我们使用PostQuitMessage(0)发送的一个消息，用来结束程序进程，它的WMPARAM是PostQuitMessage中传递的参数，LPARAM参数未被使用。
通常情况下我们发送了WM_QUIT后，会引起消息循环中的GetMessage函数返回，从而使得进程退出。
WM_QUIT消息是无法传递到我们自己的窗口处理函数中的。但是我们可以从侧面验证有这么一个消息：我们先在代码中增加对WM_QUIT消息的处理;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//可以使GetMessage返回0  
		break;
	case  WM_CREATE:
	{
		CREATESTRUCT crt = *((CREATESTRUCT*)lParam);
		char buf[256] = { 0 };
		sprintf(buf, "创建的窗口类名称是%s，窗口名称是%s", crt.lpszClass, crt.lpszName);
		MessageBox(NULL, buf, "消息处理", MB_OK);
	}
	case WM_QUIT:
	{
		int param = (int)wParam;
		char buf[256];
		sprintf(buf, "进程退出，退出码:%d", param);
		MessageBox(NULL, buf, "消息处理", MB_OK);
	}
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
运行程序，在关闭处理WM_CREATE消息的对话框后，发现弹出了我们验证WM_QUIT消息的对话框。
这是因为，弹出的处理WM_CREATE消息MessageBox也是一个窗口，但它属于我们的进程。
每个窗口都有一个消息循环，但是消息队列一个进程却只有一个，
当MessageBox的窗口关闭时，它的窗口处理函数也调用PostQuitMessage(0)发送了一个WM_QUIT消息。
它的消息循环中GetMessage接收到WM_QUIT消息后返回并退出。
而这个消息又会被我们的消息循环捕获到，但是由于它不是我们的窗口发出的消息，所以不会导致我们的GetMessage返回结束循环，
反而被传给我们的窗口处理函数汇总进行处理，所以出现了上面截图显示的对话框。


//WM_SYSCOMMAND消息
系统命令消息，点击最大化、最小化和关闭命令时会触发这个消息（这么说来点击关闭按钮时会同时触发WM_DESTROY和WM_SYSCOMMAND两个消息哦）。
它的wParam参数携带了具体的窗口操作：
SC_CLOSE		关闭
SC_MAXIMIZE		最大化
SC_MINIMIZE		最小化
...
lParam参数携带的是产生该消息的鼠标的位置，位置的X和Y坐标分别被存放在lParam的低位和高位字中。
case WM_SYSCOMMAND:
{
	if (wParam == SC_MAXIMIZE)
	{
		short x = LOWORD(lParam);
		short y = HIWORD(lParam);
		char buf[256];
		sprintf(buf, "窗口最大化，x坐标:%d，y坐标:%d", x, y);
		MessageBox(NULL, buf, "消息处理", MB_OK);
	}
}


//WM_SIZE
调整窗口的大小时触发WM_SIZE消息。wParam参数携带该消息产生的原因：
SIZE_RESTORED —— 重新调整窗口大小
SIZE_MAXIMIZED —— 最大化显示
SIZE_MINIMIZED —— 最小化显示
...
lParam参数携带的是重新调整大小后的窗口的高和宽，其中低字节代表宽，高字节代表高。
case WM_SIZE:
{
	if (wParam == SIZE_MAXIMIZED)
	{
		short width = LOWORD(lParam);
		short hight = HIWORD(lParam);
		char buf[256];
		sprintf(buf, "窗口最大化，高度:%d，宽度:%d", hight, width);
		MessageBox(NULL, buf, "消息处理", MB_OK);
	}
}