/********************/数据封装与抽象/************************************************************/
C++ 三大特性 : 封装，继承，多态

封装：即隐藏对象的属性和实现方法，只对外部提供接口。控制程序在运行过程中访问范围和修改的权限。

数据封装是一种把数据和操作数据的函数捆绑在一起的机制(即类)。
数据抽象是一种仅向用户暴露接口而把具体的实现细节（函数源码）隐藏起来，仅仅提供接口的机制。


数据抽象有两个重要的优势：
类的内部受到保护，不会因无意的用户级错误导致对象状态受损。
类实现可能随着时间的推移而发生变化，以便应对不断变化的需求，或者应对那些要求不改变用户级代码的错误报告。


//定义类，若不指定权限，则默认为private
class 类名
{
访问权限:
	成员属性
	成员方法
};

//定义对象
类名 + 对象名



/********************/实例/************************************************************/
#include <iostream>

using namespace std;


//创建人的类
class Person
{
public:
	int height;		//身高

	void setage(int _age)//在类的里面称为方法，在类外称为函数
	{
		age = _age;
	}
	void show() {
		eating();
		running();
	}

protected:
	int age;//年龄

	void eating() {
		cout << "吃饭" << endl;
	}

private:
	void running() {
		cout << "跑步" << endl;
	}
};

int main()
{
	Person jack;			//创建实体对象

	jack.height = 170;
	//jack.age = 18;		//受到保护，无法赋值
	jack.setage(18);

	//jack.eating();		//受到保护，无法调用
	jack.show();



	Person* rose = new Person();	

	rose->height = 160;
	rose->setage(14);		//通过类的公有函数对类的私有成员进行操作
	rose->show();
}



