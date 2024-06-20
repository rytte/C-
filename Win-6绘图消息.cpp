/********************/WM_PAINT/************************************************************/
#include <windows.h>

#define WM_PAINT  0x000F

携带参数：WPARAM和LPARAM两个参数为空，没有携带消息。
触发时机：绘制窗口、调整窗口大小、最小化还原(最小化时不触发)、最大化、窗口拉回屏幕(拉出时不触发)、调用InvalidateRect函数


//InvalidateRect函数
BOOL InvalidateRect(HWND hWnd, CONST RECT* lpRect, BOOL bErase);

hWnd：要更新的客户区所在的窗体的句柄。如果为 NULL, 则默认重绘所有的窗口, 然后发送 WM_ERASEBKGND 和 WM_PAINT 给窗口过程处理函数。
lpRect：无效区域的矩形代表，它是一个结构体指针，存放着矩形的大小。如果为 NULL, 全部的窗口客户区域将被增加到更新区域中。
bErase：无效矩形是否重画, true 为需要重画，重画时用预先定义好的画刷。
返回值：成功返回非零值，失败返回0。


//处理WM_PAINT消息，并在窗口上绘制一个矩形
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)	//窗口处理函数  
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);						//可以使GetMessage返回0  
		break;
	case  WM_PAINT:
	{
		PAINTSTRUCT pt;
		HDC hdc;
		hdc = BeginPaint(hWnd, &pt);			//我们利用BeginPaint获取绘图设备的句柄---一个HDC对象，然后在改绘图设备上进行绘制。
		Rectangle(hdc, 0, 0, 100, 100);
		EndPaint(hWnd, &pt);					//结束绘图处理
	}
	case WM_LBUTTONDOWN:
	{
		//InvalidateRect(hWnd,NULL,true);
	}
	break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


