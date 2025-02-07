/********************/标准属性/************************************************************/
//属性声明基本语法
[[attr]] [[attr1, attr2, attr3(args)]] [[namespace::attr(args)]];

//例子
[[attr1]] class [[attr2]] X { int i; } a, b [[attr3]];


//使用using打开属性的命名空间
[[using gnu: always_inline, hot, const]] [[nodiscard]]
	inline int f()


//标准属性
noreturn				//声明属性不会返回（与返回空是不同的）
carries_dependency		//允许跨函数传递内存依赖项，它通常用于弱内存顺序架构平台上多线程程序的优化，避免编译器生成不必要的内存栅栏指令。
deprecated			//带有此属性的实体被声明为弃用的
fallthrough			//在switch语句的上下文中提示编译器直落行为是有意的
nodiscard				//声明函数的返回值不应该被舍弃
maybe_unused		//声明实体可能不会被使用
likely && unlikely		//属性允许编译器对该属性所在的执行路径相对于其它执行路径更可能/不可能地进行优化
no_unique_address		//指示编译器该数据成员不需要唯一地址


