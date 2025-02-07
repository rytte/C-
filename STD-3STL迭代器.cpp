/********************/STL标准模板库/************************************************************/
标准模板库 STL（Standard Template Library），是 C++ 标准库的一部分，不需要单独安装，只需要#include 头文件。

//C++标准模板库
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <algorithm>
#include <numeric>
#include <memory>
#include <iterator>
#include <functional>
#include <utility>



STL标准模板库包括以下六个组件：

组件	                        描述

容器（Containers）	容器就是一些常用的数据结构体的模板类。如vector、list、queue、stack。
算法（Algorithms）	算法作用于容器。就是容器类的方法，如clear()、swap()、find()、begin()、erase()。
迭代器（Iterators）	迭代器的本质也是一个模板类，用于遍历容器。相当于指针用于遍历数据结构。迭代器就是包装过的指针。

函数对象	            如果一个类将() 运算符重载为成员函数，这个类就称为函数对象类，这个类的对象就是函数对象（又称仿函数）。
适配器	            可以使一个类的接口（模板的参数）适配成用户指定的形式，从而让原本不能在一起工作的两个类工作在一起。值得一提的是，容器、迭代器和函数都有适配器。
内存分配器	        为容器类模板提供自定义的内存申请和释放功能，由于往往只有高级用户才有改变内存分配策略的需求，因此内存分配器对于一般用户来说，并不常用。



/********************/迭代器 iterator/************************************************************/
<容器>						     <对应的迭代器类型>
array							随机访问迭代器
vector							随机访问迭代器
deque							随机访问迭代器
list								双向迭代器
set / multiset						双向迭代器
map / multimap					双向迭代器
forward_list						前向迭代器
unordered_set / unordered_multiset	前向迭代器
unordered_map / unordered_multimap	前向迭代器
stack							不支持迭代器
queue							不支持迭代器

//（1）前向迭代器（forward iterator）
假设 p 是一个前向迭代器，则 p 支持 ++p，p++， * p 操作，还可以被复制或赋值，可以用 == 和 != 运算符进行比较。

//（2）双向迭代器（bidirectional iterator）
双向迭代器具有正向迭代器的全部功能，除此之外，假设 p 是一个双向迭代器，则还可以进行 --p 或者 p-- 操作（即一次向后移动一个位置）。

//（3）随机访问迭代器（random access iterator）
随机访问迭代器具有双向迭代器的全部功能。除此之外，假设 p 是一个随机访问迭代器，i 是一个整型变量或常量，则 p 还支持以下操作：
p += i：使得 p 往后移动 i 个元素。
p -= i：使得 p 往前移动 i 个元素。
p + i：返回 p 后面第 i 个元素的迭代器。
p - i：返回 p 前面第 i 个元素的迭代器。
p[i]：返回 p 后面第 i 个元素的引用。

此外，两个随机访问迭代器 p1、p2 还可以用 <、>、 <= 、 >= 运算符进行比较。
另外，表达式 p2 - p1 也是有定义的，其返回值表示 p2 所指向元素和 p1 所指向元素的序号之差（也可以说是 p2 和 p1 之间的元素个数减一）。


//迭代器定义格式
正向迭代器			容器类名::iterator  迭代器名;
常量正向迭代器			容器类名::const_iterator  迭代器名;
反向迭代器			容器类名::reverse_iterator  迭代器名;
常量反向迭代器			容器类名::const_reverse_iterator  迭代器名;

正向迭代器：进行 ++ 操作时，迭代器会指向容器中的后一个元素；
反向迭代器：进行 ++ 操作时，迭代器会指向容器中的前一个元素。
常量迭代器：无法修改其指向的元素。
非常量迭代器：可以修改其指向的元素。



