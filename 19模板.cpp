/********************/模板和泛型编程/************************************************************/
模板是静态多态的一种表现形式，分为模板函数和模板类。

模板是泛型编程的基础。
泛型编程是一种编程风格，其中算法以尽可能抽象的方式编写，而不依赖于将在其上执行这些算法的数据形式。
泛型：指兼容各种数据类型，如：模板函数在调用时候才通过传参指定参数的数据类型。

模板是创建泛型类或泛型函数的蓝图或公式。库容器，比如迭代器和算法，都是泛型编程的例子，它们都使用了模板的概念。
每个容器都有一个单一的定义，比如 向量，我们可以定义许多不同类型的向量，比如 vector <int> 或 vector <string>。


/********************/模板函数/************************************************************/
模板函数：参数个数固定，参数类型在使用时指定的函数。


模板函数定义：

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


模板函数调用：
func<类型传参>(数据传参)        //可以不给定类型，由编译器自行推断


作用：模板函数本质上是为了解决相同参数个数的重载函数过多时，定义繁琐的情况。

模板函数中的数据类型，取决于函数调用时，传入参数的数据类型。
在有多个模板未知类型情况下，可以设置多种不同类型的参数，也可以全部设置相同数据类型。


模板函数的局限性 :
（1）在调用时，必须明确各个未知数据类型的参数，否则无法编译通过。
（2）在调用时，只有基本数据类型才可以直接使用。如果是类或者结构体，其结构更加复杂，必须重载运算符说明其中的运算方式。


模板函数和普通函数的调用机制：
（1）完全符合条件的情况下，优先调用普通函数;
（2）在不完全符合条件的情况下，调用模板函数（即普通函数需要发生隐式类型转换的情况下，优先调用模板函数）。
（3）使用<>时强制调用模板函数


模板函数和普通函数的区别 :
（1）普通函数会发生隐式类型转换，模板函数不会发生隐式类型转换。
（2）调用模板函数时，一定要数据类型匹配，能多不能少。


练习 :
1.假设有一个冒泡排序的模板函数, 设计它并实现字符串,整型与浮点型的排序。
2.假设有一个快速排序的模板函数，设计它并实现字符串整型与浮点型的排序。
3.冒泡, 插入, 选择, 快排, 归并, 希尔


/********************/模板类/************************************************************/
模板类定义：

template <class T> 
class 类名
{
    //类主体
}

template : 关键字，表示声明了模板
class    : 修饰未知数据类型。非类关键字，仅表示此模板是类模板。
T        : 自定义变量，代表一种数据类型或已有定义的类名，在调用时以传参方式确定，可以在返回值、参数列表、类主体中使用


*通过未知的数据类型T进行占位，调用时将需要使用的数据类型进行传参替换，以实现多种不同情况下的类的定义，构成模板。

* 模板类可以设置默认参数，要求与函数默认参数一致，即从右往左连续。
    template <class T1 = 数据类型/类名, class T2 = 数据类型/类名>   //即使设置了默认参数，创建对象时也必须加<>，表示使用的是模板。


注意事项：
（1）模板类无法根据传入参数的类型自动判断模板类的数据类型，必须通过<数据类型>进行数据传参来创建对象
（2）模板类调用时传入的数据类型不同，则创建的对象属于不同的类。
（3）这些对象的类是不同的，因此类中的运算符重载是无效的，每一个都要单独编写。


/********************/模板类对象的传参/************************************************************/
使用情景：
(1)传入的参数为具体类的对象（已确定数据类型的模板类），只能够调用符合要求的类的对象
(2)传入的参数为模板类的对象（未确定数据类型的模板类），可以调用模板类创建的任意类的对象
(3)模板函数的参数为模板类的对象，可以调用任意的模板类对象      //需要注意该函数中使用时的运算符的重载情况

注意事项 :
(1)模板类的成员的调用机制
在编译时确定调用的函数接口。一个标准模板类, 理论上是所有成员函数都可以调用。但也有可能存在无法直接调用的接口。

(2)模板类的成员函数在类外定义
成员函数类外定义时，必须写成模板。
static 修饰的成员，不能够作为模板类的成员属性。

(3)友元函数
友元函数并非类的成员，所以类中的未知数据类型不会影响到友元函数，友元函数必须定义成模板函数。且未知数据类型不能够与模板类的未知数据类型同名。

(4)继承
继承时，如果基类有设置默认参数，那么派生类就不是模板类；
        如果基类没有设置默认参数，那么派生类要写成模板类。


总结 : 当使用模板类时，只要加了类名的地方，就一定有<>+数据类型



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



/********************/模板类对象的传参实例/************************************************************/
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



