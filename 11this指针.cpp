/********************/this 指针/************************************************************/

this 指针：用来访问当前对象的地址

this 指针是所有成员函数的隐含参数。在成员函数内部，用来指向当前的对象。每一个成员方法都有 this 指针。

特点：
（1）在构造函数中，当形参与成员属性同名，通过 this 指针进行分辨。
（2）在需要返回当前类对象的成员函数，使用 return *this 来实现。
（3） this 指针不占内存空间。



/********************/实例/************************************************************/
#include <iostream>

using namespace std;


class Person {
public:
	Person(int a) {
		this->a = a;
		//左侧加上this指针，强调使用的是当前对象的成员
		//右边没有任何前缀，优先调用局部变量，即形参a
	}

	int a;
	void func() 
	{
		cout << "a=" << this->a << endl;
	}

	Person& test() 
	{
		a += 20;
		return *this;
	}

};


int main()
{
	Person A(20);
	A.func();

	A.test().func();

}






