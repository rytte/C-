/********************/ if 和 switch 初始化（C++17）/************************************************************/
if (init; condition)				//init部分可以进行变量的定义和赋值
{
	//代码块
}

switch (init; condition)
{
	//代码块
}



/********************/结构化绑定（C++17）/************************************************************/
1、返回多个值（元组）
auto return_multiple_values()
{
	return std::make_tuple(11, 7);
}

int main()
{
	auto [x, y] = return_multiple_values();
	std::cout << "x=" << x << "y=" << y << std::endl;
}

2、绑定到结构体
3、绑定到元组和类元组对象



/********************/inline 扩展（C++17）/************************************************************/
内联静态成员变量
class X
{
public:
	static const int num{ 5 };				//常量静态成员变量可以在声明时定义赋值
	static int a;						//非常量静态成员变量需要在类外赋值，且赋值语句不能写在头文件中，否则可能被重复包含调用
	inline static int b = 20;				//inline 声明的静态成员变量无上述问题
};

int a = 10;



/********************/三向比较（C++20）/************************************************************/
bool b = 7 <= > 11 < 0;					//b == true
bool b = 7 <= > 11 < 100;				//编译失败，<=>的返回值只能与0和自身类型比较

返回三种结果:
strong_ordering：表示两个操作数（类型等）相同，可以相互替换
weak_ordering：表示两个操作数（类型等）不同，无法相互替换
partial_ordering

std::strong_ordering::less：如果 a 小于 b，则返回该值；
std::strong_ordering::equal：如果 a 等于 b，则返回该值；
std::strong_ordering::greater：如果 a 大于 b，则返回该值。

std::weak_ordering::less
std::weak_ordering::equal
std::weak_ordering:::greater

std::partial_ordering::less
std::partial_ordering::equal
std::partial_ordering::greater
std::partial_ordering::unordered：表示两个操作数没有任何关系


int main()
{
	int a = 1;
	int b = 2;

	std::strong_ordering result = a <= > b;

	if (result == std::strong_ordering::less)
	{
		std::cout << "a < b" << std::endl;
	}
	else if (result == std::strong_ordering::equal)
	{
		std::cout << "a == b" << std::endl;
	}
	else if (result == std::strong_ordering::greater)
	{
		std::cout << "a > b" << std::endl;
	}
}


/********************/ consteval&& constinit 关键字（C++20）/************************************************************/
consteval：声明函数必须在编译期就执行计算，否则将会报错。


constinit：检查常量初始化
1、对于具有静态存储持续时间的变量声明上，它要求变量具有常量初始化程序
constinit int x = 11;							//编译成功，全局变量具有静态存储持续
int main()
{
	constinit static int y = 42;				//编译成功，静态变量具有静态存储持续
	constinit static int z = 7;					//编译失败，局部变量是动态分配的
}

2、要求变量具有常量初始化程序
const char* f() { return "hello"; }
constexpr const char* g() { return "cpp"; }
constinit const char* str1 = f();				//编译错误，f()不是一个常量初始化程序
constinit const char* str2 = g();				//编译成功


