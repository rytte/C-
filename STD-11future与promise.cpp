/********************/std::future/************************************************************/
#include <future>

异步结果：std::future 提供了一个接口来获取异步任务的返回结果，或者在任务完成时返回一个状态。
获取结果：调用 get() 方法获取异步操作的结果。如果任务未完成，get() 会阻塞，直到任务完成。
同步与异步：std::future 提供了一种简洁的方式来实现异步操作的同步。
共享和线程安全：std::future 是线程安全的，但它的对象只能由一个线程调用 get() 方法。

//主要方法
get()				//获取异步操作的结果。如果异步操作还没有完成，get() 会阻塞并等待操作完成后返回结果。若异步操作抛出异常，get() 会重新抛出那个异常。
valid()				//检查 std::future 是否有效。尚未调用 get() 或 wait() 的 future 将会返回 true ,否则返回 false 。
wait()				//阻塞当前线程，直到异步操作完成。
wait_for()			//阻塞当前线程，直到异步操作完成或超时。如果超时，它会返回 std::future_status::timeout。
then()				//（C++20）用于连接未来的操作。通过该方法，可以在异步任务完成后继续执行后续操作。

std::future 对象调用过 get() 或 wait() 后就不再可用了。

//std::async
用于启动一个异步任务，是线程的封装：自动处理线程的创建、同步和资源管理。
std::future<T> std::async(std::launch policy, Func&& f, Args&&... args);
std::future<T> std::async(Func&& f, Args&&... args);

执行策略(std::launch)
std::launch::async      //（默认策略）强制异步执行，任务会在新的线程中运行。std::future 会在任务执行时返回一个新的线程。
std::launch::deferred   //延迟执行，任务只有在调用 get() 或 wait() 时才会执行，而不是在 std::async 调用时启动线程。


//std::future实例
#include <iostream>
#include <future>
#include <thread>

int compute_square(int x) 
{
    std::this_thread::sleep_for(std::chrono::seconds(2));  // 模拟长时间的计算
    return x * x;
}

int main() 
{
    // 创建一个异步任务
    std::future<int> result = std::async(std::launch::async, compute_square, 5);

    // 在等待异步操作的同时，主线程可以做其他事情
    std::cout << "Doing some work in the main thread...\n";

    // 获取异步操作的结果，这里会阻塞直到任务完成
    int square = result.get();

    // 输出结果
    std::cout << "The square of 5 is: " << square << std::endl;

    return 0;
}


//wait_for()实例
#include <iostream>
#include <future>
#include <thread>
#include <chrono>

int slow_task() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 42;
}

int main() {
    std::future<int> result = std::async(std::launch::async, slow_task);

    // 使用 wait_for() 设置超时
    if (result.wait_for(std::chrono::seconds(2)) == std::future_status::timeout) 
    {
        std::cout << "Task is still running, timing out.\n";
    }
    else 
    {
        std::cout << "Task completed in time.\n";
    }

    // 等待任务完成并获取结果
    int value = result.get();
    std::cout << "Result of task: " << value << std::endl;

    return 0;
}



/********************/std::promise/************************************************************/

承诺值：一个线程可以通过 std::promise 向另一个线程传递结果。
获取结果：另一个线程可以通过与该 std::promise 关联的 std::future 获取该结果，或者等待结果的计算完成。
异常传递：std::promise 也可以通过 set_exception() 来传递异常。


void set_value(const T& value);     //设置结果
void set_value(T&& value);          //设置异常



//std::promise实例
#include <iostream>
#include <future>
#include <thread>

// 用来计算平方的函数
int compute_square(int x)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));  // 模拟长时间的计算
    return x * x;
}

void compute_square_with_promise(std::promise<int>& prom, int x)
{
    // 执行计算并设置值
    int result = compute_square(x);
    prom.set_value(result);  // 通过 promise 设置结果
}

int main()
{
    // 创建一个 promise 和对应的 future
    std::promise<int> prom;
    std::future<int> result = prom.get_future();

    // 启动一个线程来执行任务，并将 promise 传递给线程
    std::thread t(compute_square_with_promise, std::ref(prom), 5);

    // 在等待异步操作的同时，主线程可以做其他事情
    std::cout << "Doing some work in the main thread...\n";

    // 获取异步操作的结果，这里会阻塞直到任务完成
    int square = result.get();

    // 输出结果
    std::cout << "The square of 5 is: " << square << std::endl;

    // 等待线程完成
    t.join();

    return 0;
}







