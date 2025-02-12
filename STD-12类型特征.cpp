/********************/类型特征/************************************************************/

#include <type_traits>

std::is_*_v<T> = std::is_*<T>::value	//Cpp17简化


//Cpp11
std::is_integral<T>::value			// 判断整型
std::is_floating_point<T>::value	// 判断浮点型
std::is_void<T>::value				// 判断空类型
std::is_pointer<T>::value			// 判断指针类型
std::is_reference<T>::value			// 判断引用类型
std::is_array<T>::value				// 判断数组类型
std::is_class<T>::value				// 判断类类型（包括结构体、联合体和类）
std::is_enum<T>::value				// 判断枚举类型
std::is_union<T>::value				// 判断联合类型
std::is_abstract<T>::value			// 判断抽象类类型

std::is_base_of<Base, Derived>::value	// 判断是否继承关系
std::is_convertible<T, U>::value		// 判断 T 类型是否可以隐式转换为 U 类型
std::is_same<T, U>::value				// 判断 T 和 U 是否是相同类型

std::is_signed<T>::value				// 判断是否为有符号类型
std::is_unsigned<T>::value				// 判断是否为无符号类型
std::is_literal_type<T>::value			// 判断是否为字面量类型，即是否可以用于常量表达式
std::is_trivially_copyable<T>::value	// 判断是否是可以直接拷贝的类型，即是否满足可以使用 memcpy 的条件
std::is_constructible<T, Args...>::value			// 判断是否可以通过指定的参数类型 Args... 构造 T 类型对象
std::is_move_constructible<T>::value				// 判断类型 T 是否支持移动构造
std::is_copy_constructible<T>::value				// 判断类型 T 是否支持拷贝构造

//Cpp14
std::is_trivially_constructible<T, Args...>::value	// 判断类型 T 是否可以平凡构造（无任何构造函数或只包含无参构造函数）
std::is_trivially_copy_constructible<T>::value		// 判断类型 T 是否可以平凡拷贝构造
std::is_trivially_assignable<T, U>::value			// 判断类型 T 是否支持平凡的赋值运算符
std::is_polymorphic<T>::value						// 判断类型 T 是否为多态类型（是否有虚函数）
std::is_empty<T>::value								// 判断类型 T 是否为空类类型（没有成员变量）
std::is_final<T>::value								// 判断类型 T 是否为最终类（不允许继承）

//Cpp17
std::is_aggregate<T>::value							// 判断类型 T 是否为聚合类型（没有用户定义的构造函数、拷贝构造函数、拷贝赋值操作符等）
std::is_nothrow_constructible<T, Args...>::value	// 判断类型 T 是否可以在没有抛出异常的情况下构造
std::is_nothrow_copy_constructible<T>::value		// 判断类型 T 是否可以在没有抛出异常的情况下进行拷贝构造
std::is_nothrow_move_constructible<T>::value		// 判断类型 T 是否可以在没有抛出异常的情况下进行移动构造
std::is_nothrow_assignable<T, U>::value				// 判断类型 T 是否可以在没有抛出异常的情况下进行赋值
std::is_nothrow_copy_assignable<T>::value			// 判断类型 T 是否可以在没有抛出异常的情况下进行拷贝赋值
std::is_nothrow_move_assignable<T>::value			// 判断类型 T 是否可以在没有抛出异常的情况下进行移动赋值

//Cpp20
std::is_constant_evaluated()						// 判断当前的表达式是否是在常量表达式上下文中求值


