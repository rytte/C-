/********************/auto 关键字/************************************************************/
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



/********************/decltype 关键字/************************************************************/
decltype 关键字可以用于求表达式的类型.是"declare type"的缩写，译为"声明类型"
decltype(exp) 会推导exp（表达式）的类型并替换掉整个"decltype(exp)"
例如：decltype(10.8) x = 5.5;		//x 被推导成了 double

注意： exp推导结果不能为 void

总结：
1.	auto 忽略顶层 const ， decltype 保留顶层的 const
2.	对引用操作， auto 推出原有类型， decltype 推出引用类型
3.	对解引用操作， auto 推出原有类型， decltype 推出引用类型
4.	auto 推断会实际执行， decltype 不会执行，只做分析
