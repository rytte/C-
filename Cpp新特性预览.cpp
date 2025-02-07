//Cpp11
基础类型： long long 、 char16_t 、 char32_t
空指针： nullptr
关键字： override && final
关键字： noexcept
关键字： default && delete
关键字： using
静态断言： static_assert
关键字： alignof && alignas
Lambda表达式：[捕获](形参) mutable 异常说明->返回值类型 { 函数体 }
列表初始化： std::initializer_list
委托构造： Myclass() : Myclass(0, 'c');
继承构造： using Base::Base;
右值引用
移动语义：std::move、std::forward、std::swap
常量表达式： constexpr
范围for循环： for(auto i: list){}
强枚举类型： enum class
聚合类
非受限联合体
字面量优化： 0x1.7p + 2(十六进制)
自定义字面量： return_type operator "" identifier(params)
原生字符串： R"()"
标准属性： [[attr]] [[attr1, attr2, attr3(args)]] [[namespace::attr(args)]];
返回值优化： RVO、NRVO
智能指针：std::unique_ptr、std::shared_ptr、std::weak_ptr
强制类型转换：static_cast、dynamic_cast、reinterpret_cast、const_cast
多线程：std::thread
原子操作：std::atomic、std::atomic_flag
同步原语：std::shared_timed_mutex、std::shared_lock、std::condition_variable
容器：std::tuple、std::get、std::make_tuple、std::array、std::unordered_map、std::unordered_set
函数对象：std::bind、std::function
类型推导： auto && decltype
时间库：std::chrono
异步操作：std::future、std::promise
正则表达式：std::regex
判断算法：std::is_same、std::is_move_constructible、std::is_move_assignable、std::is_base_of
算法改进：std::copy、std::transform
随机数生成库：std::random


//Cpp14
Lambda表达式运行参数可以使用 auto 类型： auto add = [](auto a, auto b) { return a + b; };
Lambda表达式可以在捕获列表中直接初始化捕获的变量： auto lambda = [x = x + 1]() { std::cout << x << std::endl; };
二进制字面量：0b11001101(二进制)
数字分隔符：123'456(单引号分隔符)
智能指针创建：std::make_unique
decltype允许使用 auto ： decltype(auto)
锁函数：std::shared_timed_mutex、std::unique_lock
算法：std::exchange（交换两个值，避免了中间变量）、std::integer_sequence、std::is_final（判断是否为不能被继承的类）
算法：std::as_const（标记为常量，避免被const_cast）
算法改进：std::result_of、std::transform_reduce
常量表达式增强
std::get增强：支持更多容器类型


//Cpp17
文件系统库：std::filesystem
字符串视图：std::string_view
constexpr 改进
任意类型容器：std::any
并行算法：std::parallel
inline 变量
统一的可调用对象接口：std::invoke
算法：std::erase_if（删除容器中符合条件的元素）、std::ranges（范围操作）、std::clamp（限定值的范围）
算法：std::sample、std::byte、std::invoke_result、std::is_invocable、std::is_invocable_v
模板类：std::optional、std::nullopt


