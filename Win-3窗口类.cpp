/********************/窗口类/************************************************************/
#include <windows.h>

//窗口类分类
（1）系统窗口类：“Button”等系统窗口无需注册，可直接创建
（2）全局窗口类
（3）局部窗口类：凡是未在wce的style中添加CS_GLOBALCLASS，而注册的窗口类都是局部窗口类

【全局窗口类】
指注册之后可以在应用程序全局范围内（可以跨项目）使用的窗口类。
比如，我们可以在dll中对全局窗口类进行注册，那么引入该dll的所有程序都可以使用该类。
注册全局使用的窗口类时，我们只需要在注册时对wec的结构体的style成员添加CS_GLOBALCLASS属性
wce.style = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS;


//查找窗口类是否注册
每种窗口类在操作系统中的作用域不同，而且每个作用域内注册的窗口类名称是不能重复的。

创建窗口时，操作系统根据传入的窗口类名称，依次在已注册的 局部、全局、系统 窗口类中进行查找，
比较局部窗口类和创建窗口时传入的HINSTANCE变量，如果发现相等，则使用找到的窗口类的信息创建窗口返回。如果都没找到，则创建窗口失败;


//注册窗口类的API：RegisterClass()和RegisterClassEx()
二者的区别主要在于接收的参数上，这个参数就是我们需要注册的窗口类。
ATOM WINAPI RegisterClass( _In_ const WNDCLASS* lpWndClass );
ATOM WINAPI RegisterClassEx( _In_ const WNDCLASSEX* lpwcx );

typedef struct tagWNDCLASS {
	UINT      style;
	WNDPROC   lpfnWndProc;
	int       cbClsExtra;
	int       cbWndExtra;
	HINSTANCE hInstance;
	HICON     hIcon;
	HCURSOR   hCursor;
	HBRUSH    hbrBackground;
	LPCTSTR   lpszMenuName;
	LPCTSTR   lpszClassName;
} WNDCLASS, * PWNDCLASS;

typedef struct tagWNDCLASSEX {
	UINT      cbSize;				//(ex)窗口的结构体大小
	UINT      style;
	WNDPROC   lpfnWndProc;
	int       cbClsExtra;
	int       cbWndExtra;
	HINSTANCE hInstance;
	HICON     hIcon;
	HCURSOR   hCursor;
	HBRUSH    hbrBackground;
	LPCTSTR   lpszMenuName;
	LPCTSTR   lpszClassName;
	HICON     hIconSm;				//(ex)窗口的小图标句柄
} WNDCLASSEX, * PWNDCLASSEX;


//获取已注册的窗口信息 GetClassInfo()
BOOL WINAPI GetClassInfo(
	_In_opt_ HINSTANCE  hInstance,			//查找的作用域，如果设为NULL，会从系统、全局和局部三个作用域查找。
	_In_     LPCTSTR    lpClassName,		//查找的窗口类名称
	_Out_    LPWNDCLASS lpWndClass);		//传入的WndClass结构体变量的地址，用于接收窗口类信息

实例：
WNDCLASS wc;
if (GetClassInfo(NULL, "Button", &wc) == false)
MessageBox(NULL, "GetClassInfo Faile", NULL, NULL);


//卸载窗口类 UnregisterClass()
BOOL WINAPI UnregisterClass(
	_In_     LPCTSTR   lpClassName,			//窗口类名称
	_In_opt_ HINSTANCE hInstance);			//作用域


//创建子窗口 CreateWindow()或者CreateWindowEx() 
HWND WINAPI CreateWindow(
	_In_opt_ LPCTSTR lpClassName,
	_In_opt_ LPCTSTR lpWindowName,
	_In_ DWORD dwStyle,					//创建子窗口:WS_CHILD  显示:WS_VISIBLE  弹出的方式显示(类似关闭确认的对话框):WS_POPUP
	_In_ int x,
	_In_ int y,
	_In_ int nWidth,
	_In_ int nHeight,
	_In_opt_ HWND hWndParent,
	_In_opt_ HMENU hMenu,
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ LPVOID lpParam
);

实例：
g_hInstance = hInstance;
BOOL nRet = Register("Main", WndProc);
if (!nRet)
{
	MessageBox(NULL, "注册失败", "Infor", MB_OK);
	return 0;
}
HWND hWnd = CreateMain("Main", "window");
CreateWindow("Main", "子窗口",
	WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE | WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, 400, 200,
	hWnd, NULL, g_hInstance, NULL);


