/********************/线程/************************************************************/
C++中的基本网络接口是与C语言一致的，都是使用套接字,如：bind, socket, accpet, select, recv, send等。

在MFC, QT, WINUI其他的图形框架中，才有自己专门的网络通信库。


C++11之后添加了新的标准线程库 std::thread，std::thread 在 <thread> 头文件中声明，因此使用 std::thread 时需要包含 在 <thread> 头文件。

之前一些编译器使用 C++ 11 的编译参数是 - std = c++11：

	g++ test.cpp - o test - std = c++11

std::thread 默认构造函数，创建一个空的 std::thread 执行对象。


#include<thread>
std::thread thread_object(callable)
一个可调用对象可以是以下三个中的任何一个：

函数指针
函数对象
lambda 表达式


thread :
explicit thread(Function && f, Args&&... args);
线程构造，创建出线程，并执行f函数，函数中传入参数arg

C++的延时函数在std命名空间中
std::this_thread::sleep_for()  函数
std::chrono::seconds           延时秒

简化命名空间中的函数名
using + 新名称 = 命名空间中的函数名
using  SEC = std::chrono::seconds;


注意事项：
当线程的参数是引用时，必须通过 std::ref()来声明参数是一个引用。

原理 :
线程创建需要分配资源，在分配资源时，默认是值传递。在创建完以后，再去调用线程执行函数。
此时如果线程执行参数的参数是引用，那么会引用到线程创建时值传递的变量。
线程创建完毕以后，该变量会被销毁，那么传入的参数也会被销毁。
所以必须声明传入的是引用，让编译器在创建线程时，进行引用传递。


类的成员函数做线程执行函数：

1.类中static成员函数做线程执行函数，可以通过 类名::成员函数 的方式直接调用。
thread t1(A::func, 5);

2.类中非static成员函数做线程执行函数，必须创建对象，使用对象的成员函数。
thread t2(&A::test, &a, 3);

参数一 : 类中成员函数的地址, 通过类名 + 作用域方式访问
参数二 : 访问对象的地址
参数三 : 线程函数的参数


/********************/互斥锁 mutex/************************************************************/

m.lock();//加锁
{
	if ()
		return;//发生了死锁
	...
}
m.unlock();//解锁


为了解决这个问题，也有一个类似于智能指针的独占性的锁 unique_lock;

explicit unique_lock(mutex_type& m);

unique_lock<mutex> lm(a, defer_lock);;//lm绑定了互斥锁m
//defer_lock表示绑定的是未加锁的锁资源

lm.lock();//加锁
{
	if ()
		return;//销毁当前函数栈中的对象，也就是销毁lm
	//lm通过调用析构函数，来解除锁
}

lm.unlock();//解锁

