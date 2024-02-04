/********************/C++标准库/************************************************************/
C++ 标准库可以分为两部分：

① 标准函数库：这个库是由通用的、独立的、不属于任何类的函数组成的。 函数库继承自 C 语言。
② 面向对象类库：这个库是类及其相关函数的集合。


//C++标准函数库
C++ 标准库包含了所有的 C 标准库，为了支持类型安全，做了一定的添加和修改。
具体来说，标准函数库分为以下几类：输入 / 输出 I / O、字符串和字符处理、数学、时间、日期和本地化、动态分配、其他、宽字符函数。


//C++面向对象类库
1. 容器（Containers）：
#include <vector> -动态数组
#include <list> -双向链表
#include <deque> -双端队列
#include <queue> -队列
#include <stack> -栈
#include <set> -集合
#include <map> -映射表
#include <unordered_set> -无序集合
#include <unordered_map> -无序映射表

2. 迭代器（Iterators）：
#include <iterator> -通用迭代器定义
#include <algorithm> -算法
#include <functional> -函数对象

3. 算法（Algorithms）：
#include <algorithm> -包含各种算法，如排序、查找等

4. 数值和数学（Numerics and Math）：
#include <numeric> -一些数值算法
#include <cmath> -C数学库的功能（位于C++标准库）

5. 输入输出（Input / Output）：
#include <iostream> -标准输入输出流
#include <fstream> -文件输入输出流
#include <iomanip> -控制输出格式的工具

6. 其他：
#include <string> -字符串
#include <sstream> -字符串流
#include <utility> -实用工具
#include <memory> -内存管理工具



