/********************/constexpr 常量表达式/************************************************************/
int x1 = 42;
const int x2 = x1;				//定义和初始化成功

int x3 = 42;
constexpr int x4 = x3;			//编译失败，x4无法用x3初始化

//常量表达式使用场景
1、定义数组长度
2、定义 case 标签的值
3、静态存储变量初始化

 //优点
编译时计算、优化代码、提高类型安全性、简化模板元编程、改善编译时错误消息、提高代码可读性以及支持constexpr函数

//常量表达式函数
constexpr int add(int x, int y)		//constexpr 声明的函数称为常量表达式函数。
{
	return x + y;
}

//常量表达式函数条件
1、必须在编译时就能计算出结果。
2、必须在任何给定相同输入的情况下都能产生相同的输出。

这使得 constexpr 函数非常适合用于模板元编程和常量表达式的计算。

//常量表达式函数的规则（C++11）
1、函数必须返回一个值，所以它的返回值类型不能是 void
2、函数体必须只有一条语句:  return expr，其中expr必须也是一个常量表达式
3、函数必须使用 constexpr 声明

//常量表达式函数的新规则（C++14）
1、函数的返回值可以声明为 void
2、函数允许出现 if  和 switch 语句，不能使用 go 语句
3、函数允许所有的循环语句，包括 for 、 while 、 do - while
4、函数可以修改生命周期和常量表达式相同的对象
5、函数体允许声明变量，除了没有初始化的变量、 static 变量和 thread_local 变量
6、 constexpr 修饰的成员函数不再具有 const 属性

//常量表达式函数的新规则（C++17）
1、Lambda表达式在条件允许的情况下都会隐式声明为 constexpr
2、 if constexpr (常量表达式)，条件结果一旦确定，编译器将只编译符合条件的代码块，
否则编译器就会试图执行 if 语句里的所有代码，例如在模板编程中可能编译不会通过。
3、字符串视图：引入了字符串视图类型，用于高效地处理字符串的查看而不进行复制操作，提高性能。

//常量表达式函数的新规则（C++20）
1、允许常量表达式中使用虚函数 : constexpr virtual int f() const { return 1; }
2、允许在 constexpr 函数中出现 try - catch
3、允许在 constexpr 中更改联合类型的有效成员
4、允许 dynamic_cast 和 typeid 出现在常量表达式中


//常量表达式构造函数的规则
1、构造函数必须使用 constexpr 修饰
2、构造函数初始化列表里必须是常量表达式
3、构造函数的函数体必须为空;

class X
{
public:
	constexpr X() : x1(5) {}
	constexpr X(int i) : x1(i) {}
	constexpr int get() const
	{
		return x1;
	}
private:
	int x1;
};

constexpr X x;
char buffer[x.get()] = { 0 };

