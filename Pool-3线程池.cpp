/********************/线程池/************************************************************/


线程池（Thread Pool）是一种常用的并发编程技术，通过预先创建一组线程，并在需要执行任务时将任务分配给这些线程来处理，从而避免了频繁创建和销毁线程的开销。


#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>
#include <future>

class ThreadPool {
public:
    ThreadPool(size_t threads) : stop(false) {
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this] {
                            return this->stop || !this->tasks.empty();
                            });
                        if (this->stop && this->tasks.empty()) {
                            return;
                        }
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    task();
                }
                });
        }
    }

    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return res;
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& worker : workers) {
            worker.join();
        }
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

int main() {
    ThreadPool pool(4);

    auto result1 = pool.enqueue([] {
        std::cout << "Task 1 is running" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 1;
        });

    auto result2 = pool.enqueue([](int a, int b) {
        std::cout << "Task 2 is running" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return a + b;
        }, 2, 3);

    std::cout << "Result of task 1: " << result1.get() << std::endl;
    std::cout << "Result of task 2: " << result2.get() << std::endl;

    return 0;
}


//解释
1、线程池类 ThreadPool：
* ThreadPool(size_t threads) 构造函数创建指定数量的工作线程，每个线程在一个无限循环中等待任务队列中的任务。
* ~ThreadPool() 析构函数设置停止标志，并等待所有线程完成工作。
* enqueue(F&& f, Args&&... args) 方法将新任务添加到任务队列中，并通知一个等待线程开始工作。

2、任务队列：
* 使用 std::queue<std::function<void()>> 来存储任务。
* 任务通过 std::packaged_task 包装，允许获取任务结果。

3、同步机制：
* 使用 std::mutex 来保护任务队列的访问。
* 使用 std::condition_variable 来通知等待的线程有新任务到达。

4、主函数 main()：
* 创建一个包含 4 个线程的线程池。
* 添加两个任务到线程池并获取结果。
* 打印任务结果。

通过这种方式，线程池可以有效地管理并发任务，减少频繁创建和销毁线程的开销，提高系统性能。


