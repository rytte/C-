/********************/异常/************************************************************/


throw: 用于抛出异常。当问题出现时，程序会抛出一个异常。
catch : 用于捕获异常。在您想要处理问题的地方，通过异常处理程序捕获异常。
try : try 块中的代码标识将被激活的特定异常。它后面通常跟着一个或多个 catch 块。


//抛出异常
您可以使用 throw 语句在代码块中的任何地方抛出异常。throw 语句的操作数可以是任意的表达式，表达式的结果的类型决定了抛出的异常的类型。

以下是尝试除以零时抛出异常的实例：

double division(int a, int b)
{
        if (b == 0)
        {
                throw "Division by zero condition!";
        }
        return (a / b);
}


//捕获异常
如果有一个块抛出一个异常，捕获异常的方法会使用 try 和 catch 关键字。
如果 try 块在不同的情境下会抛出不同的异常，这个时候可以尝试罗列多个 catch 语句，用于捕获不同类型的异常。使用"..."能够匹配所有类型的因此。
try
{
        // 保护代码（可能抛出异常的代码）
}
catch (ExceptionName e1)
{
        // catch 块（处理ExceptionName e1异常的代码）
}
catch (ExceptionName e2)
{
        // catch 块（处理ExceptionName e2异常的代码）
}
catch (...)
{
        // 能处理任何异常的代码
}



/********************/异常处理实例/************************************************************/
下面是一个实例，抛出一个除以零的异常，并在 catch 块中捕获该异常。

#include <iostream>
using namespace std;

double division(int a, int b)
{
    if (b == 0)
    {
        throw "Division by zero condition!";
    }
    return (a / b);
}

int main()
{
    int x = 50;
    int y = 0;
    double z = 0;

    try 
    {
        z = division(x, y);
        cout << z << endl;
    }
    catch (const char* msg)             //由于我们抛出了一个类型为 const char* 的异常，因此，当捕获该异常时，我们必须在 catch 块中使用 const char* 。
    {
        cerr << msg << endl;
    }

    return 0;
}
当上面的代码被编译和执行时，它会产生下列结果：
Division by zero condition!

//////////////////////////////////////////////////////////////////////
异常	                                 描述

std::exception	                 最通用的异常类，只报告异常的发生而不提供任何额外的信息。该异常是所有标准 C++ 异常的父类。

std::bad_alloc	                 动态内存分配错误时抛出。

std::bad_cast	                 dynamic_cast 类型转换出错时抛出。

std::bad_typeid	         该异常可以通过 typeid 抛出。

std::bad_exception	         这在处理 C++ 程序中无法预期的异常时非常有用。

std::logic_error	                 程序逻辑错误（理论上可以通过读取代码来检测到的异常）

std::domain_error	         参数对应的结果值不存在

std::invalid_argument	 使用了无效的参数

std::length_error	         试图创建一个超出该类型最大长度的对象

std::out_of_range	         使用一个超出有效范围的值

std::runtime_error	         只有在运行时才能检测出的错误

std::overflow_error	         计算上溢

std::underflow_error	 计算下溢

std::range_error	         产生了超出有意义值域范围的结果


/********************/定义新的异常/************************************************************/
您可以通过继承和重载 exception 类来定义新的异常。下面的实例演示了如何使用 std::exception 类来实现自己的异常：

#include <iostream>
#include <exception>
using namespace std;

struct MyException : public exception
{
    const char* what() const throw ()
    {
        return "C++ Exception";
    }
};

int main()
{
    try
    {
        throw MyException();
    }
    catch (MyException& e)
    {
        std::cout << "MyException caught" << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch (std::exception& e)
    {
        //其他的错误
    }
}
这将产生以下结果：

MyException caught
C++ Exception
在这里，what() 是异常类提供的一个公共方法，它已被所有子异常类重载。这将返回异常产生的原因。



对于:
const char* what() const throw ()
{
    //函数体
}
做几点说明，从左到右看：

1. const char* 表示返回值类型
2. what 是函数名称
3. () 是参数列表
4. const 表示该成员函数不能修改成员变量
5. throw() 是异常规格说明符。括号内写该函数可抛出的异常类型


