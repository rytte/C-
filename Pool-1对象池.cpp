/********************/对象池/************************************************************/


对象池（Object Pool）是一种设计模式，用于管理和重用对象的实例。
通过对象池，可以减少创建和销毁对象的开销，提高系统的性能，尤其是在需要频繁创建和销毁对象的场景下。


#include <iostream>
#include <vector>
#include <memory>

template <typename T>
class ObjectPool {
public:
    // 获取对象
    std::shared_ptr<T> acquire() {
        if (!available.empty()) {
            auto obj = available.back();
            available.pop_back();
            return obj;
        }
        else {
            return std::make_shared<T>();
        }
    }

    // 释放对象
    void release(std::shared_ptr<T> obj) {
        available.push_back(obj);
    }

private:
    std::vector<std::shared_ptr<T>> available; // 可用对象池
};

class MyObject {
public:
    MyObject() {
        std::cout << "MyObject created" << std::endl;
    }

    ~MyObject() {
        std::cout << "MyObject destroyed" << std::endl;
    }

    void doSomething() {
        std::cout << "MyObject is doing something" << std::endl;
    }
};

int main() {
    ObjectPool<MyObject> pool;

    {
        auto obj1 = pool.acquire();
        obj1->doSomething();

        auto obj2 = pool.acquire();
        obj2->doSomething();

        pool.release(obj1);
        pool.release(obj2);
    }

    // 再次获取对象，将复用之前释放的对象
    auto obj3 = pool.acquire();
    obj3->doSomething();

    return 0;
}



//解释
1、对象池类 ObjectPool：
* 模板类 ObjectPool 可以适用于任何类型的对象。
* 使用一个 std::vector<std::shared_ptr<T>> 作为可用对象池，存储已经创建并且可供复用的对象。
* acquire() 方法从池中获取一个对象，如果池中没有可用对象，则创建一个新的对象。
* release() 方法将对象释放回池中，以便将来复用。

2、示例类 MyObject：
* MyObject 类用于演示对象池的使用，包含构造函数、析构函数和一个成员函数 doSomething()。

3、主函数 main()：
* 创建一个 ObjectPool<MyObject> 对象池。
* 获取两个对象并调用其方法，然后将其释放回池中。
* 再次获取一个对象，观察对象是否被复用。

通过对象池，可以有效地减少对象的创建和销毁次数，从而提升系统性能。这种模式特别适用于对象创建和销毁成本较高的场景。
