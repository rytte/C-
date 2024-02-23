/********************/static 关键字/************************************************************/

static 修饰的成员属性和成员方法是这个类所有对象公有的。

当 static 修饰成员属性时，该成员属性不在对象的内存空间，其数据位于数据段的静态存储区中。该成员变量必须在类外定义赋值，而不是在构造函数中。
当 static 修饰成员方法时，该函数中不能够使用 this 指针，也不能够调用非 static 成员。
static 修饰的成员，无法通过 this 指针定位，但可以通过 类名 + 作用域 的形式直接访问。



/********************/const 关键字/************************************************************/

C语言中, const 是修饰只读属性，数据本质仍为变量，存在于栈空间，可以通过指针改变变量值。
C++中, const 是修饰常量，数据存在于常量区，其值不可改变。


使用：
（1） const 修饰的成员不可修改。
（2）当 const 修饰成员属性时，必须参数列表初始化。
（3）当 const 修饰成员方法时， const 加到函数末尾，并且整个函数中不可发生数据修改。
（4）当 const 修饰成员对象时，必须参数列表初始化，并且对象的成员都不可被修改



/********************/static 实例/************************************************************/
#include <iostream>

using namespace std;


class Person {
public:
	Person() {}

	static void show() 
	{	
		//cout << "this->a" <<  this->a << endl;		//错误，因为static的成员是所有类对象公有，this指针无法定位到具体对象,且无法调用非static成员。
		cout << "static show() num=" << num << endl;
	}

	int a;
	static int num;//属于Person类所有对象公有
};


int Person::num = 0;			//因为num不仅属于当前对象,创建构造函数时不会定义num的内存空间，所以num需要在类外定义赋值。


int main()
{
	Person A;
	A.num = 100;

	Person B;
	cout << "B.num=" << B.num << endl;				//输出B.num=100

	//num所表示的是同一块内存空间，输出相同地址
	cout << "&A.num=" << &A.num << endl;
	cout << "&B.num=" << &B.num << endl;

	cout << "sizeof(A)=" << sizeof(A) << endl;			//输出sizeof(A)=4

	A.show();


	cout << "-------------------" << endl;
	cout << Person::num << "   " << &Person::num << endl;		//直接通过类名调用静态成员属性
	Person::show();												//直接通过类名调用静态成员方法

}



/********************/const 实例/************************************************************/
#include <iostream>

using namespace std;


class data {
public:
	int m;
};

class Person {
public:
	Person() :a(100), P()				//const修饰的成员属性和成员对象需要使用参数列表初始化
	{			
		num = 99;
	}

	void show() const				//const修饰成员方法时，const放后面
	{
		cout << num << endl;
		cout << a << endl;
	}

	const int a;					//const修饰成员属性
	int num;

	const data P;					//const修饰的成员对象
};



int main()
{
	Person  A;
	A.show();

	//A.P.m=1;						//const修饰的成员对象，其对象的成员不可被修改
}

