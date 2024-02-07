/********************/概念/************************************************************/

概念是对C++核心语言特性中模板功能的扩展。
他是编译时进行评估，对类模板、函数模板以及类模板的成员函数进行约束：它限制了能被接受为模板形参的实参集。

//使用std::enable_if约束模板
template <class T, class U = std::enable_if_t<std::is_intergral_v<T>>>
struct X{};
X<int> x1;			//编译成功
X<std:::string> x2;		//编译失败


//concept 关键字
concept 关键字，用于定义类型约束。
template <class C>
concept IntegerType = std::is_integral_v<C>;
template <IntegerType T>
struct X {};

约束表达式还支持一般的逻辑操作，包括合取和析取。
合取：
template <class C>
concept SignedIntegerType = std::is_integral_v<C> && std::is_signed_v<C>;
析取：
template <class C>
concept SignedFloatingType = std::is_integral_v<C> || std::is_floating_point_v<C>;


//requires关键字
requires 关键字
在 C++20 中， requires 关键字用于函数模板或类模板的参数约束。
它允许开发者指定模板参数必须满足的特定条件，类似于类型特性（type trait）或静态断言（static_assert）。
这些条件可以是类型检查、成员存在性检查等。
template <class T>
requires std::is_integral_v<T>;
struct X {};

约束表达式定义 :
requires 子句必须是一个类型为 bool 的常量表达式，除此之外还有一些额外要求：
* 是一个初等表达式，或者带括号的任意表达式。
* 使用&& 或者 || 运算符连接的上述表达式。



约束模板实参的方法很多，当一个模板同时具备多种约束时，如何确定优先级？
* 模板形参列表中的约束表达式，其中检查顺序就是按照形参出现顺序。
* 模板形参列表之后的 requires 子句中的约束表达式。
* 简写函数模板声明中每个拥有约束 auto 占位符类型的形参所引入的约束表达式。
* 函数模板声明尾部 requires 子句中的约束表达式。


//原子约束
原子约束是表达式和表达式中模板形参到模板实参映射的组合（简称为形参映射）。
template <int N> constexpr bool Atomic = true;
template <int N> concept C = Atomic<N>;
template <int N> concept Add1 = C<N + 1>;
template <int N> concept AddOne = C<N + 1>;
template <int M> void f()
	requires Add1<2 * M> {};
template <int M> void f()
	requires AddOne<2 * M> && true{};

f<0>();	//编译成功


//requires 表达式
该表达式同样是一个纯右值表达式，表达式为 true 时表示满足约束条件，反之 false 表示不满足约束条件。
template <class T>
concept Check = requires
{
	T().clear();
};
template <Check T>
struct G {};

G<std::vector<char>> x;		//编译成功
G<std::string> y;			//编译成功
G<std::array<char, 10>> z;	//编译失败


支持形参列表：
a.clear()  和 a+b是要求序列
template <class T>
concept Check = requires(T a, T b)
{
	a.clear();
	a + b;
}

4种要求序列：
简单要求
类型要求
复合要求
嵌套要求
 




