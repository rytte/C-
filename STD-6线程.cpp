/********************/线程/************************************************************/

C++11之后添加了新的标准线程库 std::thread。


//编译命令示例：
g++ test.cpp - o test - std = c++11


#include<thread>
using namespace std;


thread thread_object(callable);

callable：可调用对象
①函数指针
②函数对象
③lambda 表达式


thread :
explicit thread(Function && f, Args&&... args);
线程构造，创建出线程，并执行f函数，函数中传入参数arg


//C++的延时函数
std::this_thread::sleep_for()		//函数
std::chrono::seconds			//延时秒

简化命名空间中的函数名
using + 新名称 = 命名空间中的函数名
using  SEC = std::chrono::seconds;


//注意事项
当线程的参数是引用时，必须通过 std::ref()来声明参数是一个引用。

//原理 
线程创建需要分配资源，在分配资源时，默认是值传递。在创建完以后，再去调用线程执行函数。
此时如果线程执行参数的参数是引用，那么会引用到线程创建时值传递的变量。
线程创建完毕以后，该变量会被销毁，那么传入的参数也会被销毁。
所以必须声明传入的是引用，让编译器在创建线程时，进行引用传递。


//类的成员函数做线程执行函数

1、类中static成员函数做线程执行函数，可以通过 类名::成员函数 的方式直接调用。
thread t1(A::func, 5);

2、类中非static成员函数做线程执行函数，必须创建对象，使用对象的成员函数。
thread t2(&A::test, &a, 3);	//参数1：类的成员函数的地址		参数2：访问对象的地址		参数3：线程函数的参数




