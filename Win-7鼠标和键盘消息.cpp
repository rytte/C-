/********************/键盘消息/************************************************************/
#include <windows.h>

//键盘消息
WM_KEYDOWN		键盘按键按下时产生。
WM_KEYUP		键盘按键弹起时产生。
WM_SYSKEYDOWN	系统按键按下时产生，如ALT、F10等等
WM_SYSKEYUP		系统放开时产生
WM_CHAR			字符消息

//消息参数
按键消息：
WPARAM —— 按键的虚拟键码(VirtualKey)
LPARAM —— 按键的参数，如按下的次数
WM_CHAR :
WPARAM —— 输入的字符(ASCII编码)
LPARAM —— 按键的相关参数

//消息的使用：
（1）KEYDOWN可以重复消息，KEYUP只能在按键松开时出现一次
（2）TranslateMessage在转换 WM_KEYDOWN 消息时，对于可见字符可以产生 WM_CHAR ，不可见字符无此消息。



/********************/鼠标消息/************************************************************/
//单击消息
WM_LBUTTONDOWN	鼠标左键按下
WM_LBUTTONUP	鼠标左键弹起
WM_RBUTTONDOWN	鼠标右键按下
WM_RBUTTONUP	鼠标右键弹起
WM_MOUSEMOVE	鼠标移动消息
*一般情况下鼠标按下 / 抬起成对出现，在鼠标移动过程中会根据移动速度产生一系列的 WM_MOUSEMOVE 消息。

//双击消息
WM_LBUTTONDBLCLK —— 鼠标左键双击
WM_RBUTTONDBLCLK —— 鼠标右键双击
使用时需要在注册窗口类的时候添加 CS_DBLCLS 风格，消息产生的顺序：
WM_LBUTTONDOWN
WM_LBUTTONUP
WM_LBUTTONDBLCLK
WM_LBUTTONUP

//滚轮消息
WM_MOUSEWHEEL —— 鼠标滚轮消息

//消息参数
WPARAM —— 其他按键的状态，例如Ctrl / Shift等
LRARAM —— 鼠标当前的位置，窗口客户区的坐标系：LOWORD(X坐标位置)，HIWORD(Y坐标位置)
HIWORD —— 滚轮的偏移量，是120的倍数，通过正负极表示滚动的方向：正(向前滚动)，负(向后滚动)