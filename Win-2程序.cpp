/********************/创建程序/************************************************************/

//创建Windows界面程序步骤
（1）定义WinMain函数
（2）定义窗口处理函数。
（3）注册窗口
（4）创建窗口
（5）显示窗口
（6）编写消息循环函数
（7）处理消息;



#include <windows.h>

//定义WinMain函数
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
    //注册窗口类：窗口在创建之前需要先向操作系统进行注册
    WNDCLASSEX wce = { 0 };         //WNDCLASSEX窗口类：包含了菜单、图标、背景色等窗口信息。
    wce.cbSize = sizeof(wce);
    wce.cbClsExtra = 0;
    wce.cbWndExtra = 0;
    wce.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wce.hCursor = NULL;
    wce.hIcon = NULL;
    wce.hIconSm = NULL;
    wce.hInstance = hInstance;
    wce.lpfnWndProc = wndProc;
    wce.lpszClassName = "Main";     //lpszClassName：注册的类名称
    wce.lpszMenuName = NULL;
    wce.style = CS_HREDRAW | CS_VREDRAW;
    ATOM nAtom = RegisterClassEx(&wce);     //注册
    if (!nAtom)
    {
        MessageBox(NULL, "注册失败", "Infor", MB_OK);
        return 0;
    }

    //使用CreateWindowEx系统API创建窗口
    HWND hWnd = CreateWindowEx(0, "Main", "Window",    //参数二是注册的窗口类名称，参数三是窗口的标题名称，其他的是一些窗口显示的参数。
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, g_hInstance, NULL);

    //显示窗口。
    ShowWindow(hWnd, SW_SHOW);      //设置窗口显示属性
    UpdateWindow(hWnd);             //更新窗口属性
}

//定义窗口处理函数
窗口处理函数用来为系统回调函数，主要用来处理消息。比如窗口关闭、窗口最大化、拖动窗口时都会产生对应的消息。
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)    //hWnd:句柄   uMsg:传入的消息，本质是无符号整形的数字。
{                                                                               //wParam、lParam:消息附带的两个参数
    switch (uMsg)
    {
    case WM_DESTROY:       //关闭窗口时发送的消息
        PostQuitMessage(0);//调用系统的API PostQuitMessage(0), 使窗口退出并返回0
        break;
    default:
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//开启消息循环
所谓的消息循环，其实就是一个死循环，不断的通过GetMessage捕捉着窗口的消息，再通过TranslateMessage将虚拟键消息转换为字符消息,
然后通过DispatchMessage将消息分派给我们的窗口程序进行处理（所谓处理就是调用我们定义的窗口处理函数WinProc）：
void Message()
{
    MSG nMsg = { 0 };
    while (GetMessage(&nMsg, NULL, 0, 0))
    {
        TranslateMessage(&nMsg);
        DispatchMessage(&nMsg);
    }
}



/********************/完整封装/************************************************************/
#include <windows.h>

HINSTANCE g_hInstance = 0;

//窗口处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//可以使GetMessage返回0
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//消息循环
void Message()
{
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}
}

//注册窗口类
BOOL Register(LPSTR lpClassName, WNDPROC wndProc)
{
	WNDCLASSEX wce = { 0 };
	wce.cbSize = sizeof(wce);
	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wce.hCursor = NULL;
	wce.hIcon = NULL;
	wce.hIconSm = NULL;
	wce.hInstance = g_hInstance;
	wce.lpfnWndProc = wndProc;
	wce.lpszClassName = lpClassName;
	wce.lpszMenuName = NULL;
	wce.style = CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom = RegisterClassEx(&wce);
	if (nAtom == 0)
		return FALSE;
	return true;

}

//主函数
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// TODO: Place code here.

	g_hInstance = hInstance;
	BOOL nRet = Register(LPSTR("Main"), WndProc);					//注册窗口
	if (!nRet)
	{
		MessageBox(NULL, "注册失败", "Infor", MB_OK);
		return 0;
	}
	HWND hWnd = CreateWindowEx(0, "Main", "Window",					//创建窗口
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, g_hInstance, NULL);

	ShowWindow(hWnd, SW_SHOW);										//显示窗口
	UpdateWindow(hWnd);

	Message();														//消息循环
	return 0;
}

