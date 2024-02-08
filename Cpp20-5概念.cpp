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



/********************/requires 表达式/************************************************************/

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


//支持形参列表
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
 

//简单要求
不以 requires 关键字开始的要求，它只断言表达式的有效性，并不做表达式的求值操作。
template <typename T> concept C = requires (T a, T b)
{
	a + b;
}

//类型要求
以 typename 关键字开始的要求，紧跟 typename 的是一个类型名，通常可以用来检查嵌套类型、类模板以及别名模板特化的有效性。
template <typename T, typename T::type = 0> struct S; 
template <typename T> using Ref = T&;
template <typename T> concept C = requires
{
	typename T::inner;		//要求嵌套类型
	typename S<T>;		//要求类模板特化
	typename Ref<T>;		//要求别名模板特化
}

//复合要求
断言一个复合要求需要按照一下顺序：
1、替换模板实参到{E}中的表达式E，检测表达式的有效性。
2、如果使用了 noexcept ，则需要检查并确保{E}中的表达式E不会有抛出异常的可能。
3、如果使用了 -> 后的返回值类型约束，则需要将模板实参替换到返回值类型约束中，
并且确保表达式E的结果类型，即 decltype((E))，满足返回类型约束。

复合要求示例：
template <class T>
concept Check = requires(T a, T b)
{
	{a.clear()} noexcept;
	{a + b} noexcept -> std::same_as<int>;
}

//嵌套要求
以 requires 开始的要求，它通常是根据局部形参来指定其它额外要求。
template <class T>
concept Check = requires(T a, T b)
{
	requires std::same_as<decltype((a + b)), int>;
}


//约束可变参数模板
是将各个实参替换到概念的约束表达式后合取各个结果。
template <class T> concept C1 = true;
template <C1 ... T> struct s1 {};		//相当于（C1<T> && ...），也就是约束每一个参数。


*约束可以影响类模板特化的结果，在模板实例化的时候编译器会自动选择更满足约束条件的特化版本进行实例化。
*对 auto 和 decltype(auto) 的约束可以扩展到普遍情况。

