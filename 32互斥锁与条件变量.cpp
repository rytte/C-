/********************/互斥锁/************************************************************/
#include <mutex>

在多线程中往往需要访问临界资源，C++11为我们提供了mutex等相关类来保护临界资源，保证某一时刻只有一个线程可以访问临界资源。
即：防止其它线程修改目标变量（互斥量）。

//四种 Mutex 锁类型
mutex				//最基本的 Mutex 类。
time_mutex			//定时 Mutex 类。
recursive_mutex		//递归 Mutex 类，可以递归地对互斥量对象上锁。
recursive_timed_mutex	//定时递归 Mutex 类。

1、time_mutex拥有额外 try_lock_for() 和 try_lock_until() 两个函数。
2、recursive_mutex允许同一个线程对互斥量多次上锁（即递归上锁），来获得对互斥量对象的多层所有权多次lock，
释放互斥量时需要调用与该锁层次深度相同次数的 unlock()。若到达最大lock次数，lock方法会抛出异常（std::system_error），try_lock会返回false。
3、recursive_timed_mutex就是recursive_mutex和timed_mutex的结合体

//两种 Lock 类（RAII风格的Mutex Wrapper：构造时给 mutex 上锁，析构时解锁）（离开定义域时销毁）
lock_guard
unique_lock，支持mutex延迟上锁，尝试上锁等。unique_lock内部会维护一个锁的状态，所以在效率上会比lock_guard慢。

//其他类型
once_flag
adopt_lock_t
defer_lock_t
try_to_lock_t

//函数
try_lock			//尝试同时对多个互斥量上锁，没有获取到锁则不阻塞，返回false
lock				//尝试同时对多个互斥量上锁，没有获取到锁则阻塞
unlock			//解锁，释放对互斥量的所有权。
call_once			//如果多个线程需要同时调用某个函数，call_once 可以保证多个线程对该函数只调用一次。
try_lock_for		//尝试锁住互斥量在一段时间内，如果超过时长则失败。（timed_mutex）
try_lock_until		//尝试锁住互斥量到一个时间点，如果超过指定时间点则失败。（timed_mutex）



/********************/读写锁/************************************************************/
#include <share_mutex>


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