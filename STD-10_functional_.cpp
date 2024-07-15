/********************/std::function/************************************************************/
#include <functional>

std::function 提供了一种通用的方式来存储、复制和调用任何可调用的目标（Callable Target），包括函数、Lambda 表达式、函数对象、绑定表达式以及其他函数指针等。
std::function 的设计目的是为了提供一种类型安全的、多态的方式来回调任何可调用实体。

使用 std::function 时需要注意性能开销。


//简单使用实例
#include <functional>  
#include <iostream>  

int add(int a, int b) {
	return a + b;
}

int main() {
	std::function<int(int, int)> func = add;
	std::cout << "func(5, 3) = " << func(5, 3) << std::endl; // 输出 8  

	// 使用 Lambda 表达式  
	std::function<int(int, int)> funcLambda = [](int a, int b) { return a * b; };
	std::cout << "funcLambda(5, 3) = " << funcLambda(5, 3) << std::endl; // 输出 15  

	return 0;
}

//实现多态
//通过函数指针实现多态
#include<iostream>
#include <functional>

typedef int (*func)();

int print1() {
	printf("hello, print1 \n");
	return 0;
}

int print2() {
	printf("hello, print2 \n");
	return 0;
}

int main(int argc, char* argv[]) {
	func fp = print1;
	fp();

	fp = print2;
	fp();

	return 0;
}


//C++中只使用 std::function 替代函数指针
void print1() {
	std::cout << "hello, print1" << std::endl;
}

void print2() {
	std::cout << "hello, print2" << std::endl;
}

int main(int argc, char* argv[])
{
	std::function<void()> func(&print1);
	func();

	func = &print2;
	func();

	return 0;
}


//通过重载对象的()操作符，调用对象
你可以将一个重载了()操作符的对象赋值给它，这样就可以像调用函数一样使用该对象了。

struct A 
{
	void operator()() 
	{
		std::cout << "This is A Object" << std::endl;
	}
};

int main()
{
	A a;
	func = a;
	func();
}




/********************/std::bind/************************************************************/
#include <functional>


//两大作用：
1、将可调用对象（如函数、成员函数、
函数对象、lambda 表达式等）与其参数绑定起来，形成一个新的可调用对象。
2、将n元可调用对象转成m(m < n)元可调用对象，绑定一部分参数，不绑定的参数使用std::placeholders占位符。


//绑定普通函数
double callableFunc(double x, double y) { return x / y; }
auto NewCallable = std::bind(callableFunc, std::placeholders::_1, 2);
std::cout << NewCallable(10) << '\n';

参数1：函数名，普通函数做实参时，会隐式转换成函数指针。因此std::bind(callableFunc, _1, 2)等价于std::bind(&callableFunc, _1, 2)；
参数2：_1表示占位符，位于<functional>中，std::placeholders::_1；
第一个参数被占位符占用，表示这个参数以调用时传入的参数为准，在这里调用NewCallable时，给它传入了10，其实就想到于调用callableFunc(10, 2);
参数3：绑定(固定)的参数。


//绑定一个成员函数
class Base
{
public:
	void display_sum(int a1, int a2)
	{
		std::cout << a1 + a2 << '\n';
	}

	int m_data = 30;
};
int main()
{
	Base base;
	auto newiFunc = std::bind(&Base::display_sum, &base, 100, std::placeholders::_1);
	f(20); // should out put 120. 
}

1、bind绑定类成员函数时，第一个参数表示对象的成员函数的指针，第二个参数表示对象的地址。
2、必须显式地指定& Base::diplay_sum，因为编译器不会将对象的成员函数隐式转换成函数指针，所以必须在Base::display_sum前添加& ；
3、使用对象成员函数的指针时，必须要知道该指针属于哪个对象，因此第二个参数为对象的地址& base；


//绑定一个引用参数
默认情况下，bind的那些不是占位符的参数被拷贝到bind返回的可调用对象中。
但是，与lambda类似，有时对有些绑定的参数希望以引用的方式传递，或是要绑定参数的类型无法拷贝。

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std::placeholders;
using namespace std;

ostream& printInfo(ostream& os, const string& s, char c)
{
	os << s << c;
	return os;
}

int main()
{
	vector<string> words{ "welcome", "to", "C++11" };
	ostringstream os;
	char c = ' ';
	for_each(words.begin(), words.end(),
		[&os, c](const string& s) {os << s << c; });
	cout << os.str() << endl;

	ostringstream os1;
	// ostream不能拷贝，若希望传递给bind一个对象，
	// 而不拷贝它，就必须使用标准库提供的ref函数
	for_each(words.begin(), words.end(),
		bind(printInfo, ref(os1), _1, c));
	cout << os1.str() << endl;
}




