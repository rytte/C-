/********************/模板和泛型编程/************************************************************/
模板是静态多态的一种表现形式，分为模板函数和模板类。

//模板是泛型编程的基础
泛型编程是一种编程风格，其中算法以尽可能抽象的方式编写，而不依赖于将在其上执行这些算法的数据形式。
泛型：指兼容各种数据类型，如：模板函数在调用时候才通过传参指定参数的数据类型。模板是创建泛型类或泛型函数的蓝图或公式。



/********************/模板函数/************************************************************/
模板函数：参数个数固定，参数类型在使用时指定的函数。
作用：模板函数本质上是为了解决相同参数个数的重载函数过多时，定义繁琐的情况。


//定义
template <typename T> 
type func(参数列表)
{
    // 模板函数的主体
}

template : 关键字，表示声明了模板
typename : 关键字，表示后面是数据类型
T        : 自定义变量，代表一种数据类型，在调用时以传参方式确定，可以在返回值、参数列表、函数主体中使用
type     : 返回值类型
func     : 函数名
参数列表 : 参数个数不限


//调用
func<类型传参>(数据传参)        //可以不给定类型，由编译器自行推断


//调用机制
（1）完全符合条件的情况下，优先调用普通函数;
（2）在不完全符合条件的情况下，调用模板函数（即普通函数需要发生隐式类型转换的情况下，优先调用模板函数）。
（3）使用<>时强制调用模板函数


//局限性
（1）在调用时，必须明确各个未知数据类型的参数，否则无法编译通过。
（2）在调用时，只有基本数据类型才可以直接使用。如果是类或者结构体，其结构更加复杂，必须重载运算符说明其中的运算方式。
（3）普通函数会发生隐式类型转换，模板函数不会发生隐式类型转换。
（4）调用模板函数时，一定要数据类型匹配，能多不能少。


* 通过未知的数据类型T进行占位，调用时将需要使用的数据类型进行传参替换，以实现多种不同情况下的类的定义，构成模板。

* 模板函数可以设置默认参数，且不必遵循从右往左连续的规则。（C++11）
    template <typename T1 = 数据类型, typename T2 = 数据类型>


练习 :
1.假设有一个冒泡排序的模板函数, 设计它并实现字符串,整型与浮点型的排序。
2.假设有一个快速排序的模板函数，设计它并实现字符串整型与浮点型的排序。
3.冒泡, 插入, 选择, 快排, 归并, 希尔



/********************/模板类/************************************************************/

//定义
template <class T> 
class 类名
{
    //类主体
}

template : 关键字，表示声明了模板
class    : 修饰未知数据类型。非类关键字，仅表示此模板是类模板。
T        : 自定义变量，代表一种数据类型或已有定义的类名，在调用时以传参方式确定，可以在返回值、参数列表、类主体中使用


* 模板类可以设置默认参数，要求从右往左连续。
    template <class T1 = 数据类型/类名, class T2 = 数据类型/类名>   //即使设置了默认参数，创建对象时也必须加<>，表示使用的是模板。


//注意事项
（1）模板类无法根据传入参数的类型自动判断模板类的数据类型，必须通过<数据类型>进行数据传参来创建对象
（2）模板类调用时传入的数据类型不同，则创建的对象属于不同的类。
（3）这些对象的类是不同的，因此类中的运算符重载是无效的，每一个都要单独编写。
（4）外部模板：使用 extern 解决模板重复实例化。（C++11）


/********************/模板类对象的传参/************************************************************/
//使用情景
（1）传入的参数为具体类的对象（已确定数据类型的模板类），只能够调用符合要求的类的对象
（2）传入的参数为模板类的对象（未确定数据类型的模板类），可以调用模板类创建的任意类的对象
（3）模板函数的参数为模板类的对象，可以调用任意的模板类对象      //需要注意该函数中使用时的运算符的重载情况


//注意事项
（1）模板类的成员的调用机制
在编译时确定调用的函数接口。一个标准模板类, 理论上是所有成员函数都可以调用。但也有可能存在无法直接调用的接口。

（2）模板类的成员函数在类外定义
成员函数类外定义时，必须写成模板。
static 修饰的成员，不能够作为模板类的成员属性。

（3）友元函数
友元函数并非类的成员，所以类中的未知数据类型不会影响到友元函数，友元函数必须定义成模板函数。且未知数据类型不能够与模板类的未知数据类型同名。

（4）继承
继承时，如果基类有设置默认参数，那么派生类就不是模板类；
如果基类没有设置默认参数，那么派生类要写成模板类。


总结 : 当使用模板类时，只要加了类名的地方，就一定有<>+数据类型


//模板的模板形参优化
模板的模板形参可以是模板别名。（C++11）
模板的模板形参中，可以使用 typename 替换 class ，效果不变。（C++17）
对于未决类型的内嵌类型需要用到 typename （C++20）
template <class T> void f(T::R);        //编译错误
template <class T> void f(typename T::R);


//可变参数模板（C++11）
可变参数模板的语法和可变函数有一点相似之处，就是都使用到了省略号...
template <class ...Args>                //class ...Args 类型模板形参包
class bar
{
public:
        bar(Args ...args)                     //Args ...args 函数形参包
        {
                foo(args...);                    //args... 形参包展开
        }
};


//折叠表达式（C++17）
template <class ...Args>
auto sum(Args ...args)
{
        return (args + ...);
}

int main()
{
        cout << sum(1, 5.0, 11.7) << endl;
}

展开规则（op是二元运算符）：
表达式
(args op ...)                           //展开为：(arg0 op (arg1 op ... (argN-1 op argN)))
(... op args)                           //展开为：((((arg0 op arg1) op arg2) op ...) op argN)))
(args op ... op init)                //展开为：(arg0 op (arg1 op ... (argN-1 op argN op init)))
(init op ... op args)                //展开为：((((init op arg0) op arg1) op ...) op argN)))

一元折叠表达式中空参数包的特殊处理
编译器很难确定折叠表达式最终的求值类型
特殊规则：
1、只有 &&、|| 和 ，运算符能够在空参数包的一元折叠表达式中使用。
2、其中 && 的求值结果一定为 true
3、|| 的求值结果一定为 false
4、而 ，的求值结果为void()
5、其它运算符都是非法的

//using 声明中的包展开（C++17）。
在派生类中引用基类成员。

//Lambda表达式初始化捕获的包展开
template <class F, class... Args>
auto delay_invoke(F f, Args... args)
{
        return [f = std::move(f), ...args = std::move(args)]() -> decltype(auto) { return std::invoke(f, args...) };
}



/********************/类模板实参推导/************************************************************/

//通过初始化构造函数推导类模板的模板实参（C++17）
std::tuple<int, double, const char*> v{ 5, 11.7, "hello" };     //显示指定参数类型
auto v = std::make_tuple(5, 11.7, "hello");                           //使用 auto 关键字
std::tuple v{ 5, 11.7, "hello" };                                               //C++17标准能够自动推导类型


//别名模板的类模板实参推导（C++20）
template <class T, class U> struct C
{
        C(T, U) {}
};

template <class V>
using A = C<V*, V*>;

int i{};
double d{};
A a1(&i, &i);           //编译成功，可以推导为A<int>
A a2(i, i);                 //编译失败，i 无法推导为V*
A a3(&i, &d);          //编译失败，(int *, double *)无法推导为(V*, V*)


//聚合类型的类模板实参推导（C++20）
template <class T>
struct S
{
        T x;
        T y;
};
S s1{ 1, 2 };           //编译成功 S<int>
S s2{ 1, 2u };         //编译失败


//用户自定义推导指引
template <typename T1, typename T2>
struct Mypair
{
        MyPair(const T1& x, const T2& y) : first(x), sencond(y) {}
        T1 first;
        T2 second;
};
MyPair p(5, "hello");           //报错，若是std的pair的话可以正确推导

template <typename _T1, typename _T2> pair(_T1, _T2) -> pair(_T1, _T2);         //std的pair模板，使用到了自定义推导指引

用户自定义推导指引不必一定要有模板参数
MyPair(int, const char*)->MyPair<long long, std::string>;
MyPair p(5, "hello");


//SFINAE（C++11）
SFINAE全称Substitution Failure Is Not An Error，即“替换失败不是错误”。
指在函数模板重载的时候，当模板形参替换为指定的实参，或者由指定的函数实参推导出模板形参的过程中，
出现了失败，就应该放弃这个重载，而不是直接编译失败。



/********************/变量模板（C++14）/************************************************************/
从C++14开始，通过模板不仅能实例化类和函数，还可以实例化变量了：
template <class T>
constexpr T PI = static_cast<T>(3.1415926)
cout << PI<float> << endl;


template<class T, int N>
T PI = static_cast<T>(3.1415926)*N
int main()
{
        PI<float, 2> *= 5;
        std::cout << PI<float, 2> << std::endl;
}



/********************/模板函数实例/************************************************************/
#include <iostream>

using namespace std;


//模板函数
template <typename T, typename T2>
T2 add(T a, T b)
{
    cout << "T1 add(T1 a, T2 b)" << endl;
    return a + b;
}

template <typename T1, typename T2>
void func(T1 a, T2 b)
{
    T2 x = a + b;
    cout << "void func(T1 a,T2 b )" << endl;
    cout << x << endl;
}


int main()
{
    //识别T为int，但是T2的类型未知，编译报错
    //cout << add(1,3) << endl;


    //<>对应模板函数的<> 参数一int对象T,参数二int对象T2
    cout << add<int, int>(1, 3) << endl;


    func<double, int>(3.14, 3.99);

}



/********************/模板函数实例（参数为类或结构体）/************************************************************/
#include <iostream>

using namespace std;

//模板函数
template <typename T>
void func(T a, T b)
{
    T x = a + b;
    cout << "void func(T a,T b )" << endl;
    cout << x << endl;
}

class book {
public:
    book(int page, double price) {
        this->page = page;
        this->price = price;
    }
    book operator+(book& p)
    {
        book temp(0, 0);
        temp.page = this->page + p.page;
        temp.price = this->price + p.price;

        return temp;//这里的return会调用拷贝构造
    }
    int page;
    double price;
};

class Pen {
public:
    Pen(int size, double price) {
        this->size = size;
        this->price = price;
    }
    Pen operator+(Pen& p)
    {
        Pen temp(0, 0);
        temp.size = this->size + p.size;
        temp.price = this->price + p.price;

        return temp;//这里的return会调用拷贝构造
    }

    int size;
    double price;
};

ostream& operator<<(ostream& out, book& p)
{
    out << p.page << "  " << p.price << endl;
    return out;
}

ostream& operator<<(ostream& out, Pen& p)
{
    out << p.size << "  " << p.price << endl;
    return out;
}


int main()
{
    book A(100, 99.9);
    book B(200, 170.9);

    func(A, B);

    func(1, 2);

    Pen C(1, 33.5);
    Pen D(2, 23.5);

    func(C, D);

}



/********************/模板类实例/************************************************************/
#include <iostream>

using namespace std;

//创建模板类
template <class T1, class T2>
class Person {
public:
    Person(T1 _a, T2 _b) {
        this->a = _a;
        this->b = _b;
    }
    T1 a;
    T2 b;
};

//创建模板类---设置默认数据类型
template <class T1 = string, class T2 = int>
class student {
public:
    student(T1 _a, T2 _b) {
        this->a = _a;
        this->b = _b;
    }
    T1 a;
    T2 b;
};

int main()
{
    Person<string, int> A("jack", 14);
    Person<int, string> B(15, "rose");
    Person<int, int>  C(18, 29);

    //Person D("1",1);		错误，未进行传参

    //当只使用<>时，表示使用默认的数据类型
    student <>D("ben", 17);

    //默认类型不匹配
    //student<> E(19,"Tom");

    student<int, string> E(19, "Tom");

    //模板类创建对象必须加<>
    //student F("wang",19);
}



/********************/模板类对象作参数 实例/************************************************************/
#include <iostream>

using namespace std;


//创建模板类
template <class T1, class T2>
class Person {
public:
    Person(T1 _a, T2 _b) {
        this->a = _a;
        this->b = _b;
    }
    T1 a;
    T2 b;
};


//把参数设置为具体的类的对象---仅仅只能够调用符合要求的类的对象
void func1(Person<string, int>& P)
{
    cout << "a=" << P.a << "  b=" << P.b << endl;
}

//把参数设置为模板类的对象---可以调用模板类创建的任意类的对象
template<class T3, class T4>				//关键字为class，但实际为模板函数，class可以替换成typename
void func2(Person<T3, T4>& P)			//T3、T4的传参来自于模板类Person的T1，T2
{
    cout << "a=" << P.a << "  b=" << P.b << endl;
}

//把函数设置为模板---可以调用任意类型的对象
//				  ---需要注意该函数中使用时的运算符的重载情况
template<typename T>
void func3(T& P)
{
    //cout << "a=" << P.a << "  b=" << P.b << endl;
    cout << P << endl;
}

//为实现func3进行运算符<<的重载
template <class T1, class T2>
ostream& operator<<(ostream& out, Person<T1, T2>& P)
{
    out << "a=" << P.a << " b=" << P.b;
    return out;
}


int main()
{
    Person<string, int> A("jack", 18);
    func1(A);

    Person<int, string> B(20, "rose");
    //func1(B); 形参与实参是不同的数据类型

    func2(A);
    func2(B);
    cout << "-----------" << endl;

    func3(A);
    func3(B);

    int num = 100;
    func3(num);
}



