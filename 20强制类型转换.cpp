/********************/强制类型转换/************************************************************/

C++完全兼容C语言的类型转换语法，同时又新加了更合理的书写形式和更安全的新式类型转换，如下所示（目标类型以 char 为例）：

旧式转换
(char)a; // C语言风格类型转换
char(a); // C++风格类型转换

新式转换
（1） static_cast<char>(a);
主要用于数值之间的强制转换（与旧式转换相近，但提供了更易于查找的语法，并能有效识别不兼容类型。）
static 意味着静态转换，静态的含义是操作的过程只发生在编译阶段，而不是运行阶段，静态转换不涉及类型推理。

（2） const_cast<char>(a);
专用于去除指针或引用的 const (只读)属性
旨在去除标识符的cv限定属性（即 const 与 volatile），只能作用于指针或引用类型

（3） reinterpret_cast<char>(a);
主要用于基本数据类型的强制转换

（4） dynamic_cast<char>(a);
主要用于基类与派生类之间的强制转换（类类型的上下代际间的转换）
返回值为null，表示转换失败。
返回值为地址，表示转换成功，该地址为派生类首地址

必要条件 : 基类的析构函数必须是虚析构.

dynamic_cast 用于把指向派生类对象的基类指针或者引用，转换成派生类的指针或者引用。



案例:
有一个职工管理系统，有学生信息和老师信息，请创建对应类并输出。

假设有一个基类指针数组，是Person类的数组。Person类派生类出了
teacher类和student类，要求遍历数组，输出teacher类与student类的信息。



/********************/static_cast 实例/************************************************************/
#include <iostream>

using  namespace std;


int main()
{
	char ch = 'a';

	//在C++兼容C语言写法，所以这也是可以使用的,部分编译器会报警告
	int  num = ch;//发生隐式类型转换
	cout << num << endl;

	//C++的强制转换方式
	int data = static_cast<int>(ch);
	cout << data << endl;

	double m = 3.14;
	//num = m;报错---num是4字节，m是8字节，无法发生隐式类型转换

	data = static_cast<int>(m);
	cout << data << endl;

}



/********************/const_cast 实例/************************************************************/
#include <iostream>

using namespace std;


//外部内存num是没有只读的，函数参数中加入const，只是添加"只读"属性
void func(const int& a)
{
	//去掉只读属性
	int& n = const_cast<int&>(a);
	n = 200;
	cout << n << endl;
}

int main()
{
	int num = 100;
	func(num);

	cout << num << endl;
}



/********************/reinterpret_cast 实例/************************************************************/
#include <iostream>
#include <cstdlib>

using namespace std;

//在地址0x123456写入数值100

int main()
{
	//int *p = (int*)0x123456;
	int* p = reinterpret_cast<int*>(0x123456);
	*p = 100;


	//int *q = (int*)malloc(100);
	int* q = reinterpret_cast<int*>(malloc(100));
}



/********************/dynamic_cast 实例/************************************************************/
#include <iostream>

using namespace std;

class Base {
public:
	Base() {
	}
	//虚析构
	virtual ~Base() {

	}
};

class Data :public Base {
public:
	Data() {
	}
	void show() {
		cout << "Data::show()" << endl;
	}
};

class Num {

};

int main()
{
	Data P;
	Base* ptr = &P;//基类指针指向了派生类对象

	//转换成功
	Data* q = dynamic_cast<Data*>(ptr);
	if (q == NULL)
		cout << "转换失败" << endl;
	else
	{
		cout << "转换成功" << endl;
		q->show();
	}

	/* 	Num类与Data毫无关系，dynamic_cast会直接报错
		Num A;
		Num *m = &A;
		Data *q2 = dynamic_cast<Data*>(m);
		if(q2 == NULL)
			cout << "转换失败" << endl;
		else
		{
			cout << "转换成功" << endl;
			q2->show();
		} */

	Base m;
	ptr = &m;//基类指针指向基类对象

	//转换失败
	Data* q2 = dynamic_cast<Data*>(ptr);
	if (q2 == NULL)
		cout << "转换失败" << endl;
	else
	{
		cout << "转换成功" << endl;
		q2->show();
	}

}

