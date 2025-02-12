/********************/std::string_view/************************************************************/
#include <string_view>

提供了对字符串的只读访问，避免不必要的字符串复制，提高性能。

//从 C 风格字符串创建
const char* str = "Hello, World!";
std::string_view sv(str);

//从 std::string 创建
std::string str = "Hello, World!";
std::string_view sv(str);

//从字符数组创建
char arr[] = "Hello, World!";
std::string_view sv(arr);


//常用方法
size()				//返回视图中字符的数量（长度）。
data()				//返回一个指向字符数据的指针，可以用来访问底层的字符数组。
empty()				//检查视图是否为空。
substr()			//返回从视图中指定位置开始的子字符串视图。
remove_prefix()		//移除视图前缀。
remove_suffix()		//移除视图后缀
find()				//在视图中查找子字符串，返回找到的第一个位置。





