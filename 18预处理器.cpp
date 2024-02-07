/********************/预处理器/************************************************************/

# 和 ## 预处理运算符在 C++ 和 ANSI / ISO C 中都是可用的。


//# 运算符会把参数转换为用引号引起来的字符串。

实例
#include <iostream>
using namespace std;

#define MKSTR( x ) #x

int main()
{
    cout << MKSTR(HELLO C++) << endl;		//输出：HELLO C++

    return 0;
}



//## 运算符用于连接两个参数。下面是一个实例：

#define CONCAT( x, y )  x ## y
当 CONCAT 出现在程序中时，它的参数会被连接起来，并用来取代宏。例如，程序中 CONCAT(HELLO, C++) 会被替换为 "HELLO C++"，如下面实例所示。

实例
#include <iostream>
using namespace std;

#define concat(a, b) a ## b
int main()
{
    int xy = 100;

    cout << concat(x, y);			//输出：100
    return 0;
}



/********************/预定义宏/************************************************************/
C++ 提供了下表所示的一些预定义宏：

宏	        描述
__LINE__	这会在程序编译时包含当前行号。
__FILE__	这会在程序编译时包含当前文件名。
__DATE__	这会包含一个形式为 month / day / year 的字符串，它表示把源文件转换为目标代码的日期。
__TIME__	这会包含一个形式为 hour : minute : second 的字符串，它表示程序被编译的时间。

实例
#include <iostream>
using namespace std;

int main()
{
    cout << "Value of __LINE__ : " << __LINE__ << endl;
    cout << "Value of __FILE__ : " << __FILE__ << endl;
    cout << "Value of __DATE__ : " << __DATE__ << endl;
    cout << "Value of __TIME__ : " << __TIME__ << endl;

    return 0;
}
当上面的代码被编译和执行时，它会产生下列结果：

Value of __LINE__ : 6
Value of __FILE__ : test.cpp
Value of __DATE__ : Feb 28 2011
Value of __TIME__ : 18 : 52 : 48



/********************/新增预处理器功能和预定义宏/************************************************************/

__has_include		//判断某个头文件是否能够被包含进来（C++17）

#if __has_include(<optional>)
#include <optional>
#endif



__has_cpp_attribute()	//属性测试运算符，可以指示编译环境是否支持某种属性（C++20）

对于标准属性，将被展开成为属性被添加到标准时的年份和月份；
而对于编译器厂商特有的属性，将被展开为一个非零的值。

cout << __has_cpp_attribute(deprecated) << endl;



__VA_OPT__()			//当可变参数宏的可变参数不为空时，展开宏里的内容（C++20）

#define LOG(msg, ...) printf("[" __FILE__ ":%d]" msg, __LINE__, __VA_ARGS__)
LOG("HELLO")
展开后
printf("[" __FILE__ ":%d]" "HELLO", __LINE__, );	//因为内有可变参数，展开后结尾多了个逗号，会导致编译失败。

#define LOG(msg, ...) printf("[" __FILE__ ":%d]" msg, __LINE__ __VA_OPT__(,) __VA_ARGS__)		//可变参数不为空时才展开