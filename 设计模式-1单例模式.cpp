/********************/单例模式（Singleton Pattern）/************************************************************/
//实现步骤
1、将该类的构造方法定义为私有方法（防止其他处的代码实例化该类的对象，只有通过该类提供的静态方法来得到该类的唯一实例）
2、在该类内提供一个静态方法，当我们调用这个方法时，如果类持有的引用不为空就返回这个引用，
如果类保持的引用为空就创建该类的实例并将实例的引用赋予该类保持的引用。



//模板单例模式实例
template <class T>
T& singleton() {
        static T instance;                      //该实现是线程安全的
        return instance;
}

在C++11中，静态局部变量的初始化在多线程环境下是线程安全的，即使在多个线程同时调用该函数时，静态局部变量也只会初始化一次。
因此，可以利用这一特性来实现懒汉式的单例模式，不再需要额外的同步机制来保证线程安全。

注意点：
static 初始化的对象在静态数据段，那个区域很小的，单例对象占用空间大的慎用。
而 new 出来的在堆空间不用担心空间不够，还可以控制禁止直接使用单例类的错误用法。



//饿汉式（Eager Initialization）
优点：
类加载时就完成了初始化，因此获取对象的速度快。
线程安全，因为实例在类加载时就已经创建，所以不存在多线程同步问题。
缺点：
如果类从未被使用，会造成资源的浪费，因为实例在类加载时就被创建。类加载较慢，因为实例的初始化可能在类加载时就很耗时。

“饿汉式”是在不管你用的用不上，一开始就建立这个单例对象：比如：有个单例对象
public class Singleton
{
public:
        Singleton() {}
private:
        static Singleton singleton = new Singleton()； //建立对象
public:
        static Singleton getInstance() {
                return singleton ；//直接返回单例对象 
        }
}


//懒汉式（Lazy Initialization）
优点：
实例在第一次使用时才初始化，因此如果类从未被使用，则不会造成资源浪费。
在某些情况下，可能可以提高类加载的速度。
缺点：
如果在多线程环境下没有正确的同步机制，可能会导致多次实例化，即不是单例。
需要额外的同步机制来保证线程安全，这可能会影响性能。

“懒汉式”是在你真正用到的时候才去建这个单例对象：
比如：有个单例对象
public class Singleton
{
private:
        Singleton() {}
private:
        static Singleton singleton = null； //不建立对象
public:
        static synchronized Singleton getInstance()
        {
                if (singleton == null)
                { //先判断是否为空
                        singleton = new Singleton(); //懒汉式做法
                }
                return singleton ；
        }
}


//总结
对于线程安全不敏感且性能要求高的场景，可以考虑使用饿汉式，因为它在类加载时就完成了初始化，获取对象的速度快。
对于线程安全敏感且资源利用要求高的场景，可以考虑使用懒汉式，但需要注意实现时的线程安全问题。



/********************/完整单例模式实例（懒汉式）/************************************************************/
#include <iostream>

class Singleton {
public:
        // 获取单例实例的静态方法
        static Singleton& getInstance() {
                static Singleton instance;
                return instance;
        }

        // 删除拷贝构造函数和赋值运算符重载，确保单例的唯一性
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        // 单例的其他成员函数
        void doSomething() {
                std::cout << "Singleton is doing something." << std::endl;
        }

private:
        // 将构造函数私有化，防止外部创建实例
        Singleton() {}
};

int main() {
        // 获取单例实例
        Singleton& instance = Singleton::getInstance();

        // 调用单例的成员函数
        instance.doSomething();

        return 0;
}


