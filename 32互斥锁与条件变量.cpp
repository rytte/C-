/********************/互斥锁/************************************************************/
#include <mutex>

线程在定义lock_guard的地方会调用构造函数加锁，在离开定义域的话lock_guard就会被销毁
unique_lock<mutex> unique(mt);
这个会在构造函数加锁，然后可以利用unique.unlock()来解锁，所以当你觉得锁的粒度太多的时候，可以利用这个来解锁，而析构的时候会判断当前锁的状态来决定是否解锁
方便肯定是有代价的，unique_lock内部会维护一个锁的状态，所以在效率上肯定会比lock_guard慢



/********************/条件变量/************************************************************/
条件变量是利用线程间共享的全局变量进行同步的一种机制，主要包括两个动作：
一个线程等待条件变量的条件成立而挂起; 另一个线程使条件成立（给出条件成立信号）。
为了防止竞争，条件变量的使用总是和一个互斥量结合在一起。

#include <condition_variable>

std::condition_variable		//仅限于与 std::mutex 一起工作
​std::condition_variable_any	//可以和任何满足最低标准的互斥量一起工作，从而加上了_any的后缀。会产生额外开销。

*条件变量在阻塞时释放锁，在被唤醒时会重新上锁。

void notify_one();		//唤醒一条等待中的线程
void notify_all();		//唤醒所有等待中的线程

void wait(std::unique_lock<mutex>& _Lck);					//阻塞等待。
void wait(std::unique_lock<mutex>& _Lck, _Predicate _Pred);	//阻塞等待。执行或被唤醒时若Pred为真则继续执行。（Predicate是lambda表达式）。

//以下函数说明
Pred：只有当 Pred 条件为 false 时调用 wait() 才会阻塞当前线程，并且在收到其他线程的通知后只有当 Pred 为 true 时才会被解除阻塞。
双参数：超时后自动唤醒并继续执行线程。
三参数：超时后自动唤醒并继续执行线程，执行或被唤醒时若Pred为真则继续执行线程。
双参数返回值：超时返回1，不超时返回0。
三参数返回值：返回 Pred 值。

wait_for()：达到指定时长。其内部实现为转化成wait_until()。
wait_until()：抵达指定时间点。其内部会执行两次Pred。

bool wait_for(std::unique_lock<mutex>& _Lck, const chrono::duration<_Rep, _Period>& _Rel_time);
bool wait_for(std::unique_lock<mutex>& _Lck, const chrono::duration<_Rep, _Period>& _Rel_time, _Predicate _Pred);

bool wait_until(std::unique_lock<mutex>& _Lck, const chrono::time_point<_Clock, _Duration>& _Abs_time);
bool wait_until(std::unique_lock<mutex>& _Lck, const chrono::time_point<_Clock, _Duration>& _Abs_time, _Predicate _Pred);

//native_handle_type native_handle()
native_handle_type native_handle();	//返回条件变量句柄

//虚假唤醒

https://blog.csdn.net/TwoTon/article/details/123752423
https://blog.csdn.net/luohaha66/article/details/134251052



//condition_variable_any
用法与condition_variable基本相同，只有condition_variable_any的wait阻塞函数与condition_variable的wait阻塞函数不同，
将第一个参数unique_lock＜mutex＞替换为mutex即可，其他都使用方法一样。
//程序将每秒输出一个点号，直到输入整数并回车即退出程序
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <chrono>             // std::chrono::seconds
#include <mutex>              // std::mutex
#include <condition_variable> // std::condition_variable_any, std::cv_status

std::condition_variable_any cv;

int value;

void read_value() {
	std::cin >> value;
	cv.notify_one();
}

int main()
{
	std::cout << "Please, enter an integer (I'll be printing dots): ";
	std::thread th(read_value);

	std::mutex mtx;
	mtx.lock();
	while (cv.wait_for(mtx, std::chrono::seconds(1)) == std::cv_status::timeout) {
		std::cout << '.';
	}
	std::cout << "You entered: " << value << '\n';
	mtx.unlock();

	th.join();

	return 0;
}