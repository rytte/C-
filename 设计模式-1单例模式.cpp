/********************/单例模式（Singleton Pattern）/************************************************************/
//实现步骤
1、将该类的构造方法定义为私有方法（防止其他处的代码实例化该类的对象）
2、在该类内提供一个静态方法，当我们调用这个方法时，返回该类的实例（没有就创建后再返回）的引用



//模板单例模式实例
template <class T>
T& singleton() 
{
    static T instance;      //在C++11后，静态局部变量的初始化是线程安全的，无需上锁也不会多次初始化
    return instance;
}


注意点：
static 初始化的对象在静态数据段，那个区域很小的，单例对象占用空间大的慎用。
而 new 出来的在堆空间不用担心空间不够，但需要注意线程安全。



//饿汉式（Eager Initialization）
"饿汉式"是在程序初始化时就创建的
class Singleton 
{
public:
    static Singleton& getInstance() 
    {
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符，防止拷贝和赋值
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // 单例的其他成员函数
    void doSomething()
    {
        std::cout << "Singleton is doing something." << std::endl;
    }

private:
    // 私有构造函数，防止外部直接创建对象
    Singleton() {}

    // 静态实例，类加载时即初始化
    static Singleton instance;
};

int main() 
{
    // 获取单例实例
    Singleton& instance = Singleton::getInstance();

    // 调用单例的成员函数
    instance.doSomething();

    return 0;
}



//懒汉式（Lazy Initialization）
"懒汉式"是在使用时才创建的
class Singleton 
{
public:
    // 静态方法获取单例实例
    static Singleton* getInstance() 
    {
        // 双重检查锁定
        if (instance == nullptr) 
        {
            std::lock_guard<std::mutex> lock(mutex); // 锁定
            if (instance == nullptr) 
            {
                instance = new Singleton(); // 创建实例
            }
        }
        return instance;
    }
private:
    // 私有构造函数，禁止外部创建实例
    Singleton() {}

    // 禁止拷贝构造和赋值运算符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* instance;
    static std::mutex mutex;
};

// 静态成员初始化
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;


