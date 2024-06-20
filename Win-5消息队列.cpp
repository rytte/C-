/********************/消息队列/************************************************************/
#include <windows.h>

//消息队列的类型
系统消息队列：由操作系统维护的消息队列，存放系统产生的消息，如鼠标、键盘消息等等。
程序消息队列：属于每一个应用程序（线程）的消息队列，用应用程序维护。

* 当产生鼠标、键盘等消息时，消息先存放到系统消息队列，然后操作系统根据存放的消息找到对应的窗口的消息队列，将消息投递到窗口的消息队列中。

//队列消息和非队列消息
队列消息：消息发出后，首先放入队列，然后通过消息循环获取。eg：键盘、鼠标、定时器消息等等。
非队列消息：消息发出后，直接找到窗口的消息处理函数，调用消息处理函数进行处理，无需经过消息队列。eg：WM_PAINT、WM_SIZE等等。



//消息循环
一般的消息循环如下;
void Message(HWND hWnd)
{
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, hWnd, 0, 0))	//GetMessage / PeekMessage：从程序的消息队列当中获取消息。
	{
		TranslateMessage(&nMsg);			//TranslateMessage：将键盘上的按键等消息翻译成字符消息。
		DispatchMessage(&nMsg);				//DispatchMessage：将翻译后的消息再次放入到程序的消息队列中。

		if (nMsg.message == WM_PAINT)
		{
			char buff[30] = {};
			sprintf(buff, "处理消息%d\n", nMsg.message);
			WriteConsole(hOutput, buff, sizeof(buff), NULL, NULL);
		}
	}
}

;
//GetMessage和PeekMessage
GetMessage(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)

lpMsg：指向MSG结构的指针，该结构从线程的消息队列里接收消息信息。
hWnd：取得其消息的窗口的句柄。当其值取NULL时，GetMessage为任何属于调用线程的窗口检索消息，线程消息通过PostThreadMessage寄送给调用线程。
wMsgFilterMin：指定被检索的最小消息值的整数。
wMsgFilterMax：指定被检索的最大消息值的整数。
返回值：如果函数取得WM_QUIT之外的其他消息，返回非零值。如果函数取得WM_QUIT消息，返回值是0。如果出现了错误，返回 - 1。例如，当hWnd是无效的窗口句柄或lpMsg是无效的指针时。若想获得更多的错误信息，请调用GetLastError函数;

BOOL PeekMessage( LPMSG IpMsg, HWND hWnd, UINT wMSGfilterMin, UINT wMsgFilterMax, UINT wRemoveMsg );

lpMsg：接收消息信息的MSG结构指针。
hWnd：其消息被检查的窗口句柄。
wMsgFilterMin：指定被检查的消息范围里的第一个消息。
wMsgFilterMax：指定被检查的消息范围里的最后一个消息。
wRemoveMsg：确定消息如何被处理。取值如下：
{
	PM_NOREMOVE		PeekMessage处理后，消息不从队列里除掉。
	PM_REMOVE		PeekMessage处理后，消息从队列里除掉。
	PM_NOYIELD		此标志使系统不释放等待调用程序空闲的线程。可将PM_NOYIELD随意组合到PM_NOREMOVE或PM_REMOVE。
}

区别：
GetMessage是阻塞函数，PeekMessage是非阻塞函数，
PeekMessage更多用来检测消息队里中是否有消息，它的最后一个参数可以用来指定获取到消息后要不要把消息从消息队列中移除，
通常情况下通过PeekMessage检测到消息队列有消息之后，再调用GetMessage区获取。


//GetMessage / PeekMessage获取消息的过程
1、先在程序的消息队列中查找消息，如果有队列消息，就取出消息。
2、如果程序的消息队列中没有消息，向系统的消息队列获取属于本程序的消息。如果系统的消息队列中有属于本程序的消息，系统的消息队列会将消息分发到本程序的消息队列中。
3、如果系统的消息队列也没有消息，检查窗口需要绘制的区域是否需要重绘，如果发现有需要重绘的区域，产生WM_PAINT消息。
4、如果没有重新绘制区域，检查是否具有到时的定时器，如果有产生WM_TIMER定时器消息。
5、如果没有到时的定时器，整理程序的资源、内存等等;


//SendMessage和PostMessage
LRESULT SendMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM IParam)

hWnd：其窗口程序将接收消息的窗口的句柄。如果此参数为HWND_BROADCAST，则消息将被发送到系统中所有顶层窗口，包括无效或不可见的非自身拥有的窗口、被覆盖的窗口和弹出式窗口，但消息不被发送到子窗口。
Msg：指定被发送的消息。
wParam：指定附加的消息特定信息。
IParam：指定附加的消息特定信息。
返回值：返回值指定消息处理的结果，依赖于所发送的消息;

BOOL WINAPI PostMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

hWnd：其窗口程序接收消息的窗口的句柄。可取有特定含义的两个值：
HWND_BROADCAST：消息被寄送到系统的所有顶层窗口，包括无效或不可见的非自身拥有的窗口、 被覆盖的窗口和弹出式窗口。消息不被寄送到子窗口
NULL：此函数的操作和调用参数dwThread设置为当前线程的标识符PostThreadMessage函数一样
Msg：指定被寄送的消息。
wParam：指定附加的消息特定的信息。
LParam：指定附加的消息特定的信息。
返回值：如果函数调用成功，返回非零，否则函数调用返回值为零

1、SendMessage
发送消息到指定的窗口，并等候对方将消息处理，为阻塞函数，获取消息的执行结果后返回。主要需要发送非队列消息，发送的消息不经过消息队列。
2、PostMessage
发送消息到程序的消息队列，不管消息有没有被处理都会立即返回，用于队列消息的发送。
