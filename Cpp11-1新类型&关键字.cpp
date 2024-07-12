/********************/新基础类型/************************************************************/
//long long
long long	    8字节							       //C99中已有该类型，而C++中到C++11才加入该类型
（值后缀LL）

long long myLongLong = 9223372036854775807LL;  // LL后缀用于明确表示为 long long 类型


//UTF编码类型
char16_t	  2字节
char32_t	  4字节
（值前缀u或U）

char16_t myChar = u'A';						// 声明一个char16_t变量
char16_t myString[] = u"Hello, char16_t!";		// 声明一个char16_t字符串



/********************/nullptr/************************************************************/
NULL在C语言中是(void*)0。 void 类型的指针都可以被转化为其他任何指针类型
#define NULL (void*)0

而在C++中是0。由于函数重载的存在，因此不支持如C语言般的隐式转换将 void* 转为其它类型指针
// lmcons.h中定义NULL的源码  
#ifndef NULL  
#ifdef __cplusplus  
#define NULL    0  
#else  
#define NULL    ((void *)0)  
#endif  
#endif


//模拟nullptr的实现
const
class nullptr_t
{
public:
	template<class T>           operator T* () const { return 0; }
	template<class C, class T>  operator T C::* () const { return 0; }
private:
	void operator& () const;
} nullptr_t = {};
#undef NULL  
#define NULL nullptr_t 


/************************************************************/
nullptr 是一个纯右值，而创建的对象是一个左值
std::nullptr_t null1;
cout << &null1 << endl;				//可取地址，是一个左值



/********************/auto && decltype 关键字/************************************************************/
auto 关键字
C语言的 auto 关键字在定义时需要指定类型，可不赋值。
C++的 auto 关键字在定义时类型由编译器自动判断，但必须赋初值。


在作为函数返回值类型时，还需要指定返回值类型，如：
auto someFunc(int i, double j) -> std::string;				//等价于 std::string someFunc(int i, double j);


在函数模板中，返回类型取决于参数类型，上边这种写法就会有很大作用，因为你很有可能并不知道进行某种操作后自己会得到什么类型，请看下例：
template<typename T, typename V>
auto addWithTwoTypes(T t, V v) -> decltype(t + v)
{
	return t + v;
}


在C++14中，编译器可以直接推断出函数的返回值类型：
auto someFunc(int i, double j)		//自动推断返回类型为std::string
{
	return std::to_string(i + j);
}


auto 的限制
1、 auto 不能用于定义数组
2、 auto 不能在函数的参数中使用		 //C++20中 auto 可用于函数形参
3、 auto 不能用于模板调用时的传入参数
4、 auto 不能作用于类的非静态成员变量（也就是没有 static 关键字修饰的成员变量）中。


auto 其它用法
1、 用于定义迭代器，减少冗长的代码
2、 用于泛型编程，可以在模板的定义或 Lambda 表达式中使用 auto 关键字



/************************************************************/
decltype 关键字
decltype 关键字可以用于求表达式的类型.是"declare type"的缩写，译为“声明类型”
decltype(exp) 会推导exp（表达式）的类型并替换掉整个"decltype(exp)"
例如：decltype(10.8) x = 5.5;		//x 被推导成了 double

注意： exp推导结果不能为 void

总结：
1.	auto 忽略顶层 const ， decltype 保留顶层的 const
2.	对引用操作， auto 推出原有类型， decltype 推出引用类型
3.	对解引用操作， auto 推出原有类型， decltype 推出引用类型
4.	auto 推断会实际执行， decltype 不会执行，只做分析



/********************/override && final 关键字/************************************************************/
重载(overload)
重写(override)
隐藏(overwrite)	派生类出现基类同名函数时，参数不同时，基类函数会被隐藏；参数相同时，若为虚函数则是重写，否则也会隐藏。

在重写函数后面加上 override 能使编译器检查函数重写，避免重写函数时在派生类中打错函数名、参数等却难以察觉的问题。

final 关键字：
1、与 override 相反，在虚函数后面加上 final 表明该虚函数不允许被重写。
2、 final 声明类，在类定义的类名后面加上 final 表明该类不允许被继承。



/********************/noexcept 关键字/************************************************************/

当语义移动时发生异常，容器可能只移动了一部分，此时新旧两个容器对象都不完整。C++11中引入 noexcept 关键字解决该问题。

noexcept 作为说明符，添加在函数末尾，可以将函数声明为不应抛出异常的函数。若是抛出异常，将自动调用 terminate 函数终止函数。

noexcept 作为运算符，语法: noexcept(表达式)。将返回 true 或 false 表示该表达式是否可以抛出异常。


/********************/default && delete 关键字/************************************************************/
default 关键字
default 关键字，用于使编译器自动生成相应的特殊成员函数的默认实现。
可用于 构造函数、析构函数、拷贝构造函数、拷贝赋值运算符和移动构造函数等。

ClassName() = default;		//即使定义了有参构造，编译器仍将生成无参构造函数。


/************************************************************/
delete 关键字
delete 关键字，用于删除类的特殊成员函数或禁用某个函数。
通常， delete 用于阻止某些默认生成的特殊成员函数的生成，或者禁用某个特定的函数，以防止其被调用。

~ClassName() = delete;								//使编译器不生成默认析构函数。
ClassName(const ClassName&) = delete;				//删除拷贝构造函数。
ClassName& operator=(const ClassName&) = delete;		//删除拷贝赋值运算符。



/********************/ static_assert 静态断言/************************************************************/
#include <assert.h>
void assert(int expression);
assert断言一般在debug时使用，触发时会报错并终止程序，一般用在正确的位置如除数不等于零，保证严格部分的合法性。


static_assert 静态断言可在运行前（即编译时）进行指定的语法检查。断言失败会显示丰富的诊断信息，可以在命名空间，类，或代码块中使用。
static_assert(常量表达式，"自定义字符串");		//C++17标准支持单参数static_assert，省略第二参数



/********************/alignof&& alignas 关键字/************************************************************/
alignof 关键字
用于获取类型的对齐长度（而不能使用对象）

auto x = alignof(int);
auto y = alignof(void(*)());


/************************************************************/
alignas 关键字
用于控制数据对齐的长度

struct alignas(8) test			//这3个alignas定义的字节数哪个长听哪个的
{
	alignas(16) char a;
	alignas(double) int b;
	double c;
};


/************************************************************/
另外标准库中对齐字节长度的支持

std::alignment_of			//获取类型的对齐字节长度
std::aligned_storage		//分配一块指定对齐字节长度的大小和内存
std::aligned_union			//获取参数类型中对齐字节长度最大的作为分配内层的对齐字节长度


使用 new 分配指定对齐字节长度的对象（C++17）
void* operator new (std::size_t, std::align_val_t);			//align_val_t参数用于指定对齐字节长度
void* operator new[] (std::size_t, std::align_val_t);


