/********************/ consteval && constinit 关键字/************************************************************/
consteval ：声明函数必须在编译期就执行计算，否则将会报错。



constinit ：检查常量初始化
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


