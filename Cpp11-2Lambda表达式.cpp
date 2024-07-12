/********************/Lambda表达式/************************************************************/
lambda表达式
[捕获] (形参) mutable 异常说明->返回值类型 { 函数体 }

1、[捕获capture] :捕获列表
捕获列表能够捕捉上下文中的变量以供lambda函数使用，捕获列表由0个或者多个捕获项组成，多个捕获项中间用逗号隔开
捕获列表的形式：
[x]				表示值传递，只捕获变量x的值
[=]				表示值传递，捕获所有函数体涉及到的变量
[&x]			表示地址传递或引用传递，只捕获变量x的地址或引用
[&]				表示地址传递或引用传递
[=, &a, &b]		表示以引用传递的方式捕获变量a和b的值，其他的以值传递的方式进捕捉获取
[&, a, this]	表示值传递的方式捕获a和this
其他的以引用传递的方式进行捕捉获取（包含父作用域）//父作用域是指包含lambda语句块

2、(形参)参数列表		与普通的函数的参数列表是一致，如果不需要参数传递，可以连括号一起省略
3、 mutable			Lambda函数默认为 const 函数。 mutable 可以取消其常量性，使得Lamdba函数可以修改捕获变量的值。
4、->返回值类型		如果不需要返回值，可以将符号“->”一起省略
5、{ 函数体 }		函数体，内容和写法和普通函数一致
6、 异常说明			Exception attr异常属性，可选


//注意
1、[]是lambda标识，编译器根据该标识判断，接下来是否为lambda函数。
2、捕获列表[]和函数体{}是必要的，其他都是可选;


示例;
int x = 10;
auto a = [=] {return x};		//a为Lambda函数名，并非变量

示例：
int x = 5;
auto foo = [x](int y)->int { return x * y; };
std::cout << foo(8) << std::endl;


//其它用法
1、转化为函数指针
2、在stl函数中使用lambda表达式作为stl函数的函数指针参数



/********************/底层实现原理/************************************************************/
//编译器转换过程
编译器将Lambda表达式转换成C++代码时，通常会进行以下步骤：

1、创建闭包类型：编译器会根据Lambda表达式的捕获列表、参数列表、返回类型和函数体，自动生成一个唯一的类（闭包类型）。
这个类通常包含与捕获列表对应的成员变量（用于存储捕获的外部变量），一个重载的operator()成员函数（对应于Lambda表达式的函数体），
以及必要的构造函数和析构函数（如果有必要）。
2、实例化闭包对象：当Lambda表达式被评估时，会创建闭包类型的一个实例（即Lambda对象），并根据捕获列表初始化其成员变量。
3、调用Lambda对象：通过调用Lambda对象的operator()成员函数来执行Lambda表达式中的代码。


//示例
auto lambda = [](int x, int y) -> int { return x + y; };

编译器可能会将其转换成类似于以下的代码：
class __lambda_xxx 
{
public:
    int operator()(int x, int y) const 
    {
        return x + y;
    }
};

auto lambda = __lambda_xxx();

注意，实际的转换结果会更加复杂，特别是当涉及到捕获列表时，编译器会生成额外的成员变量和相应的构造函数。


//捕获列表的实现
按值捕获：捕获的变量会作为闭包类型的成员变量，按值传递。这意味着在Lambda表达式内部对捕获变量的修改不会影响到原始变量。
按引用捕获：捕获的变量会作为闭包类型的引用成员（或指针成员，取决于编译器实现），使得在Lambda表达式内部对捕获变量的修改能够反映到原始变量上。



/********************/Lambda表达式用于回调函数/************************************************************/

#include <iostream>  
 

//1、使用函数指针
typedef void (*CallbackFunc)(int);      // 定义一个函数指针类型 
  
void doSomething(CallbackFunc callback)     // 一个接受函数指针作为回调的函数
{
    std::cout << "Doing something..." << std::endl;
    callback(42);    // 调用回调函数 
}


//2、使用std::functional
#include <functional>  
void doSomething(std::function<void(int)> callback)
{
    std::cout << "Doing something..." << std::endl;
    callback(42);    // 调用回调函数  
}


//3、使用模板
template<typename Func>
void doSomething(Func callback)         // 使用模板来接受任何可调用对象
{
    std::cout << "Doing something..." << std::endl;
    callback(42);   // 调用回调函数  
}


int main()
{
    doSomething([](int value) {
        std::cout << "Callback called with value: " << value << std::endl;
    });

    return 0;
}


请注意，使用函数指针的代码实际上在C++标准中是不合法的，因为Lambda表达式不能直接转换为函数指针。
Lambda表达式是特殊的函数对象类型，它们有自己的类型，这些类型与任何函数指针类型都不兼容。
然而，在某些编译器（如GCC和Clang）中，如果Lambda表达式没有捕获任何外部变量，并且其签名与函数指针兼容，
编译器可能会提供一个非标准的扩展来允许这种转换。然而，这种做法并不是可移植的，也不是C++标准的一部分。






