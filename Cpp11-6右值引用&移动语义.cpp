/********************/右值引用/************************************************************/
左值引用符号："&"
右值引用符号："&&"

左值引用只能引用左值，如下;
int a = 10;
int& b = a;			//正确，左值引用可以引用左值
int& c = 20;			//报错，左值引用不能引用右值
const int& d = 20;		//正确，常量左值引用可以引用常量

右值引用只能引用右值，如下;
int&& e = 30;			//正确，右值引用可以引用右值
int&& f = a;			//错误，右值引用不能引用左值

右值引用可以延长右值的生命周期：即使原始右值表达式的生命周期结束，我们仍然可以通过右值引用访问和操作该对象的资源。
引用限定符：所谓引用限定符，就是在成员函数的后面添加 "&" 或者 "&&"，从而限制调用者的类型（左值还是右值）。(C++14)


/************************************************************/
左值：指那些在表达式执行结束后依然存在的数据，也就是持久性的数据；
右值：指那些在表达式执行结束后不再存在的数据，也就是临时性的数据。
有一种很简单的方法来区分左值和右值，对表达式取地址，如果编译器不报错就为左值，否则为右值。

右值被细分为纯右值（prvalue，Pure Rvalue）和将亡值（xvalue，eXpiring Value）。
纯右值：指的是临时变量值、不跟对象关联的字面量值。
将亡值：指的是在表达式结束就会销毁的值。

//左值转换为右值
1、使用 static_cast<>();
int i = 0;
int&& m = i;						//编译失败
int&& n = static_cast<int&&>(i);		//编译成功

2、使用 std::move()
int&& b = 20;
int a = std::move(b);



/********************/移动语义/************************************************************/

使用右值引用可以实现移动语义：例如拷贝构造时，当被拷贝的对象是一个右值（临时对象）时，能够将右值的资源直接移动到目标对象中，提高效率。

意义：移动语义主要用来解决大对象（如std容器）从函数返回时深拷贝代价过大的问题。

//std::move()
#include <utility>
作用：将左值引用转换为右值引用（将亡值）

template <typename T>
typename remove_reference<T>::type&& move(T&& t)
{
        //其中remove_reference<T>::type是去了引用，然后又加上&&使其变成右值引用，返回。（完美转发）
        return static_cast<typename remove_reference<T>::type&&>(t);    
}


//std::remove_reference<>::type
作用：移除引用。
例如：传入int&，那么T就是int，即type就是int。

template <typename T>
class remove_reference                          //当传入是非引用时则type为原类型
{
public:
        typedef T type;
};

template<typename T>
class remove_reference<T&>              //当传入是左值引用时则type为移除了引用的类型
{
public:
        typedef T type;
};

template<typename T>
class remove_reference<T&&>           //当传入是右值引用时则type为移除了引用的类型
{
public:
        typedef T type;
};


//正确理解移动语义
（一） “移动”操作实际上是一种请求，因为有些类型不存在移动操作，他们会通过其复制操作来实现“移动”。

（二）某些类型的移动操作未必比复制操作更快。如：
1. std::vector和std::array。
（1）std大部分容器类（如vector），内部是将其元素存放在堆上，然后用指针指向该堆内存。在进行移动操作时，只是进行指针的复制。
（2）而std::array对象其内容数据是直接存储对象上的。std::array提供移动操作，但其移动和复制的速度哪个更快，取决于元素的移动和复制速度的比较。
2. 许多std::string类型的实现采用了小型字符串优化（SSO）。
当使用SSO后，小型字符串（如不超过15个字符）会存储在std::string对象内的某个缓冲区内，即内容直接存储在对象上（而不是堆上）。
因此，此时是整个对象的移动，速度并比不复制更快。

（三）标准库一些容器操作提供了强异常安全保证，为了兼容C++98的遗留代码在升级到C++11时仍保证正确性。
库中用 std::move_if_noexcept 模板来替代 move 函数。
该函数在类的移动构造函数没有声明 noexcept 关键字时返回一个左值引用从而使变量通过拷贝语义，
而在移动构造函数有 noexcept 时返回一个右值引用，从而使变量可以使用移动语义。
移动操作未加 noexcept 时，编译器仍会强制调用一个复制操作。



/********************/移动构造函数/************************************************************/
移动构造函数是一种特殊的构造函数，用于将资源从临时对象或字面量“移动”到另一个对象中，而不是复制资源。

//优点
可以提高性能和资源利用率

//注意
对于移动构造函数来说，抛出异常是很危险的。因为移动语义还没完成，一个异常就抛出来，可能会造成悬挂指针。
因此，应尽量通过 noexcept 声明不抛出异常，而一旦出现异常就可以直接调用std::terminate终止程序。

class MyString {
public:
        MyString() : str_() {}                                                                  // 默认构造函数  
        
        MyString(const MyString& other) : str_(other.str_) {}             // 接受左值引用的构造函数  

        
        MyString(MyString&& other) noexcept : str_(std::move(other.str_))       // 移动构造函数（接受右值引用） 
        {              
                // 不执行任何初始化操作，直接移动资源  
        }
          
        MyString& operator=(MyString&& other) noexcept                  // 移动赋值运算符
        {                                    
                if (this != &other)
                        str_ = std::move(other.str_);                                         // 移动资源：赋值并清空
                return *this;
        }

        void print() const { std::cout << str_ << std::endl; }                    // 打印字符串

private:
        std::string str_;
};

int main() {
        MyString s1("Hello");
        MyString s2("World");
        s1.print(); // 输出：Hello  
        s2.print(); // 输出：World  
        s1 = std::move(s2); // 使用移动赋值运算符将s2的资源移动给s1  
        s1.print(); // 输出：World  
        s2.print(); // 输出：空字符串，资源已被移动出去  
}



/********************/万能引用/************************************************************/
在C++中，“引用的引用”是非法的。像 auto& &rx = x; （注意两个& 之间有空格）这种直接定义引用的引用是不合法的 ，
但是编译器在通过类型别名或模板参数推导等语境中，会间接定义出“引用的引用”，这时引用会形成“折叠”。

万能引用：当右值引用作为模板形参时，其既可以是一个左值引用，也可以是一个右值引用，因此称为万能引用。
void foo(int&& i)                    //i为右值引用

template<class T>
void bar(T&& t) {}			//t为万能引用

//折叠引用规则（不同引用类型叠加后的推导规则）
类模板型		T实际类型		最终类型
T&			R			R&
T&			R&			R&
T&			R&&		R&
T&&			R			R&&
T&&			R&			R&
T&&			R&&		R&&

万能引用可以实现 std::forward 的完美转发。


/************************************************************/
完美转发 std::forward()

普通转发：
template<class T>
void normal_forwarding1(T t)
{
        show_type(t);                           //会执行构造函数
}

template<class T>
void normal_forwarding1(T& t)
{
        show_type(t);                           //不能转发右值
}

template<class T>
void normal_forwarding1(const T& t)
{
        show_type(t);                           //会改变实参的常量性
}

完美转发：
template<class T>
void normal_forwarding1(T&& t)
{
        show_type(static_cast<T&&>(t));         // static_cast 函数中使用了 std::forward()
}

