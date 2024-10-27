/********************/线程/************************************************************/

C++11之后添加了新的标准线程库 std::thread。


//编译命令示例：
g++ test.cpp - o test - std = c++11


#include<thread>
using namespace std;


//构造函数
thread t(callable, args...);		

callable：可调用对象
①函数指针
②函数对象
③lambda 表达式

//注意
当线程的参数是引用时，必须通过 std::ref()来声明参数是一个引用。否则创建线程后该参数的传入对象会被销毁。


//方法
void join()						//等待线程结束并清理资源（会阻塞）
bool joinable()						//返回线程是否可以执行join函数
void detach()						//将线程与调用其的线程分离，彼此独立执行（此函数必须在线程创建时立即调用，且调用此函数会使其不能被join）
std::thread::id get_id()				//获取线程id
thread& operator=(thread&& rhs)		//见移动构造函数（如果对象是joinable的，那么会调用std::terminate()终止程序）


//C++的延时函数
std::this_thread::sleep_for(std::chrono::seconds(n))								//延时秒
std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(5))	//延时到指定时间

简化命名空间中的函数名
using + 新名称 = 命名空间中的函数名
using  SEC = std::chrono::seconds;


//类的成员函数做线程执行函数
1、类中static成员函数做线程执行函数，可以通过 类名::成员函数 的方式直接调用。thread t1(A::func, 5);
2、类中非static成员函数做线程执行函数，必须创建对象，使用对象的成员函数。thread t2(&A::test, &a, 3);



/********************/thread_local 关键字/************************************************************/
thread_local 关键字用于声明线程局部存储对象。被声明的变量类似于静态变量，但具有线程属性。
该关键字可以解决 全局变量和静态变量 在多线程程序中存在的问题：
例如： errno 原本是一个静态变量，当线程1出现错误时， errno 获取信息，此时线程2也出现错误信息，将也会修改 errno 的信息。因此难以准确获取错误信息。
而C++11之后errno改为线程局部存储变量，便无此问题。

线程局部变量只会被初始化一次，通常在线程销毁时被释放。
线程局部变量定义了变量的生命周期但没有限制访问，因此可以将该变量地址传递给其它线程，在该变量生命周期内可以访问。

static int sv;
thread_local int tv;

int main()
{
	constexpr int* sp = &sv;				//编译成功，sv的地址在编译时确定
	constexpr int* tp = &tv;				//编译失败，tv的地址在运行时确定
}

