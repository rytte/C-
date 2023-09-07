/********************/输入输出流/************************************************************/

std::cin     标准输入, 可以自动识别是输入的数据类型。
std::cout    标准输出，类似printf
std::endl    换行


使用流对象的优势在于，不需要关心操作数据的类型，流对象会自动识别不同的数据类型，也可以一次性快速处理，如下：
int a;
double f;
string s;

// 一次性输出多种不同类型的数据
cout << 100 << 3.14 << "abcd";
// 一次性输入多种不同类型的数据
cin >> a >> f >> s;

cerr的用法与cout是一样的，区别是cerr输出的时候不经过缓冲区直接输出，而cout需要经过行缓冲区。



/********************/实例/************************************************************/
#include <iostream>


int main()
{

	std::cout << "helloworld" << std::endl;

	//输入数值到变量a
	int a;
	std::cin >> a;						//标准输入流
	std::cout << a << std::endl;		//标准输出流（endl用于在行末添加一个换行符：end line）

	//输入字符串到变量buf
	char buf[32];
	std::cin >> buf;
	std::cout << buf << std::endl;

	return 0;
}
