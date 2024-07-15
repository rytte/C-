/********************/重载/************************************************************/
C++ 允许在同一作用域中的某个函数和运算符指定多个定义，分别称为函数重载和运算符重载。


重载声明：指一个与之前已经在该作用域内声明过的函数或方法具有相同名称的声明，但是它们的参数列表和定义（实现）不相同。
重载决策：当您调用一个重载函数或重载运算符时，编译器将传入参数的类型与定义中的参数类型进行比较，决定选用最合适的定义的过程。



/********************/函数重载/************************************************************/
函数重载：在同一个作用域下，函数名相同，参数类型、参数个数、参数顺序任意一个不同的函数。

函数重载要求在同一个作用域下调用函数，有且仅有一个符合条件，如果有多个符合条件，则发生歧义。

//注意事项
1、返回值不能够作为重载条件。
2、引用不发生重载，而是作为函数调用时的判断条件（类似占位参数）。

//实例
void func(int) { ; }          //定义一个函数
void func(int&) { ; }      //错误，引用不发生重载
int  func(int) { ; }          //错误，返回值不能作为重载条件



/********************/运算符重载/************************************************************/

在C / C++中，运算符都只能默认支持基本数据单位。在C++中，对于复杂的复合结构，需要重载运算符后才可以支持。

operator 关键字

运算符重载，本质上仍然是基本数据类型的运算。所以我们不可以改变运算符的语义，也不可改变运算符的优先级。


// 双目运算符：+ -*/ %
双目运算符既可以做全局重载，也可以做成员函数重载


// 左移运算符：<<
只能够做全局重载
cout << 变量;    因为cout不会是 this 的对象。连续使用时返回值需要为out。


// 赋值运算符：=
赋值运算符也是拷贝构造中的一种。但调用时有区别:

数据类型 对象a = 对象b;          //调用拷贝构造

数据类型 对象名a;
对象a = 对象b;                        //调用赋值运算符重载

* 默认情况下，赋值运算符也是浅拷贝。当构造函数有申请堆空间，或析构函数有释放堆空间时，必须自定义深拷贝的赋值运算符重载。
* 赋值运算符重载的返回值是引用，如果是数值，则会再次调用拷贝构造函数。


// 自加自减运算符：++ / --
前缀 : 先运算，后使用
后缀 : 先使用，后运算

通过占位参数来分别前缀和后缀。
operator++()        //前缀
operator++(int)     //后缀

后缀++ / --单独使用时，可以不考虑返回值是引用还是变量的问题。
但如果类中有拷贝构造函数，且外部有 << 运算符的重载，那么必须把临时变量写成堆空间或者静态数据或者全局数据，防止函数结束时被销毁。


/************************************************************/
&& ||  == > < >=  <= 等等都可以进行运算符重载

        下列运算符是完全无法做重载的：

        条件运算符 ? :
        作用域运算符   ::
        成员运算符     .
        长度运算符     sizeof
        成员指针运算符 ->*   ->.  .*
        预处理符号     #


作业:
根据string类的构造，拷贝构造，析构，运算符重载，
成员函数，自定义mystring类(字符串类)


/********************/函数对象(仿函数)/************************************************************/
函数对象：本质上是()运算符的重载，在C++的大部分算法库中，都是使用的函数对象。

假设有多个类的成员函数使用到了相同的公有函数，那么我们可以把公有函数写成仿函数。



/********************/ +/ -运算符重载实例/************************************************************/
#include <iostream>

using namespace std;


class Book {
public:
        Book(int _price, int _page) :price(_price), page(_page)
        {

        }

        //成员函数重载---运算符左侧变量是this 当前对象
        //				 参数有且仅有一个，表示运算符右侧变量
        Book operator-(Book& P)
        {
                Book C(0, 0);
                C.price = this->price - P.price;
                C.page = this->page - P.page;

                return C;
        }

        int price;
        int page;
};

//全局函数重载---第一个参数是运算符左侧变量
//			  ---第二个参数是运算符右侧变量
Book operator+(Book& A, Book& B)
{
        Book C(0, 0);
        C.price = A.price + B.price;
        C.page = A.page + B.page;

        return C;
}


int main()
{
        Book A(100, 200);
        Book B(50, 100);

        Book C = A + B;
        cout << "price=" << C.price << "  page=" << C.page << endl;

        Book D = A - B;
        cout << "price=" << D.price << "  page=" << D.page << endl;

}



/********************/ << 运算符重载实例/************************************************************/
#include <iostream>

using namespace std;


class Book {
public:
        Book(int _price, int _page) :price(_price), page(_page)
        {

        }
        int price;
        int page;
};

//全局函数重载左移运算符。ostream标准输出类，包含 cout
ostream& operator<<(ostream& out, Book& P)
{
        out << P.price << "  " << P.page << endl;
        return out;
}

int main()
{
        Book A(100, 200);
        cout << A;              //打印A的价格和页数

        Book B(30, 50);
        cout << A << B;         //打印A和B的价格和页数

}



/********************/ = 运算符重载实例/************************************************************/
#include <iostream>

using namespace std;


class Book {
public:
        Book() {                                            //无参构造
                page = new int;
        }
        Book(int _price, int _page) :price(_price) {        //有参构造
                page = new int(_page);
        }
        Book(Book& p) {                                     //拷贝构造
                cout << "拷贝构造" << endl;
                this->price = p.price;
                this->page = new int(*p.page);
        }
        //赋值运算符重载
        Book& operator=(Book& p)
        {
                cout << "赋值运算符重载" << endl;
                this->price = p.price;
                this->page = new int(*p.page);

                return *this;
        }

        ~Book() {
                cout << "析构" << endl;
                delete this->page;
        }

        int price;
        int* page;
};


ostream& operator<<(ostream& out, Book& P)
{
        out << P.price << "  " << P.page << "  " << *P.page << endl;
        return out;
}

void func(Book& a)
{
        //先定义再赋值，调用赋值运算符的重载
        Book C;
        C = a;

        cout << C;
}

int main()
{
        Book A(100, 200);

        //Book B = A;//定义时赋值，调用拷贝构造函数

        func(A);
        cout << "----";
        cout << A;
}



/********************/ ++运算符重载实例/************************************************************/
#include <iostream>

using namespace std;


class Time
{
private:
        int hours;             // 0 到 23
        int minutes;           // 0 到 59
public:
        // 所需的构造函数
        Time() {
                hours = 0;
                minutes = 0;
        }
        Time(int h, int m) {
                hours = h;
                minutes = m;
        }
        // 显示时间的方法
        void displayTime()
        {
                cout << "H: " << hours << " M:" << minutes << endl;
        }
        // 重载前缀递增运算符（ ++ ）
        Time operator++ ()
        {
                ++minutes;          // 对象加 1
                if (minutes >= 60)
                {
                        ++hours;
                        minutes -= 60;
                }
                return Time(hours, minutes);
        }
        // 重载后缀递增运算符（ ++ ）
        Time operator++(int)
        {
                // 保存原始值
                Time T(hours, minutes);
                // 对象加 1
                ++minutes;
                if (minutes >= 60)
                {
                        ++hours;
                        minutes -= 60;
                }
                // 返回旧的原始值
                return T;
        }
};
int main()
{
        Time T1(11, 59), T2(10, 40);

        ++T1;                    // T1 加 1
        T1.displayTime();        // 显示 T1
        ++T1;                    // T1 再加 1
        T1.displayTime();        // 显示 T1

        T2++;                    // T2 加 1
        T2.displayTime();        // 显示 T2
        T2++;                    // T2 再加 1
        T2.displayTime();        // 显示 T2
        return 0;
}
//当上面的代码被编译和执行时，它会产生下列结果：
//
//H : 12 M : 0
//H : 12 M : 1
//H : 10 M : 41
//H : 10 M : 42



/********************/函数对象实例/************************************************************/
#include <iostream>

using namespace std;

class Fun {
public:
    //求2个数值的和
    int operator()(int a, int b)
    {
        return a + b;
    }

    //要求写 y=kx+3的算法函数
    int operator()(int x)
    {
        return k * x + 3;
    }
    //要求写 y=a*x*x+b*x+c
    int operator()(int x, int, int)
    {
        return a * x * x + b * x + c;
    }

private:
    int k;

    int a;
    int b;
    int c;
};

class Test {
public:
    int add(int a, int b)
    {
        return a + b;
    }
};

int main()
{
    Fun f;
    cout << f(1, 2) << endl;
    cout << f(3) << endl;//-----y = k*3+3;

    cout << f(4, 0, 0) << endl;//-----y=a*4*4+b*4+c;

    Test A;
    cout << A.add(1, 2) << endl;
}

