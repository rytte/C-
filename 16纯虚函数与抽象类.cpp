/********************/纯虚函数/************************************************************/
纯虚函数：
您可能想要在基类中定义虚函数，以便在派生类中重新定义该函数更好地适用于对象，但在基类中又不能对虚函数给出有意义的实现，这个时候就会用到纯虚函数。

语法形式：
virtual 函数名() = 0;


//纯虚析构
若析构函数是纯虚函数，则称为纯虚析构。纯虚析构必须类外定义，也可以不定义。
纯虚析构函数的主要作用是强制派生类提供自己的析构函数实现，并确保在基类指针指向派生类对象时，能够正确调用派生类的析构函数。



/********************/抽象/************************************************************/
虚函数指向0的时候表示纯虚函数，带有至少一个纯虚函数的类被称为抽象类。抽象类是 C++ 的接口。

//特点
（1）抽象类无法创建实例化对象。
（2）抽象类的派生类也是抽象类，除非派生类中对纯虚函数进行重写并有执行的函数体。
（3）如果一个抽象类的子类需要被实例化，则必须实现每个纯虚函数，可用于实例化对象的类被称为具体类。
（4）抽象类一般用在不方便创建实例化对象的类中，例如算法类。
（5）第二种就是用在必须写派生类的情况，强调基类不可以创建对象。例如线程和线程池。


案例 : 算法类是 y = kx + 3;
依赖该算法类去运行。



/********************/接口实例/************************************************************/
假设有栈和队列两种数据结构，要求使用同一个接口来调用它们。


#include <iostream>

using namespace std;

class base {				//接口
public:
	virtual int pop() = 0;
	virtual void push(int n) = 0;
	virtual void show() = 0;
};

class stack :public base {
public:
	stack(int _size = 100) {
		arr = new int[100];
		size = 0;
	}
	void push(int n)		//入栈
	{
		arr[size] = n;
		size++;
	}
	int pop()				//出栈
	{
		int temp = arr[size - 1];
		arr[size - 1] = 0;
		size--;

		return temp;
	}
	void show() {
		for (int i = 0; i < size; i++)
			cout << arr[i] << "  ";
		cout << endl;
	}

	int* arr;
	int size;
};

class queue :public base {
public:
	queue(int num = 100) {
		arr = new int[num];
		front = 0;
		last = 0;
	}

	void push(int n) {
		arr[last] = n;
		last++;
	}
	int pop() {
		if (front == last)
		{
			cout << "空队" << endl;
			return -1;
		}
		else
		{
			int temp = arr[front];
			front++;
			return temp;
		}
	}
	void show() {
		for (int i = front; i < last; i++)
			cout << arr[i] << "  ";
		cout << endl;
	}


	int* arr;
	int front;		//指向队首
	int last;		//指向队尾
};

void func(base* p)
{
	for (int i = 0; i < 10; i++)
		p->push(i * 10);
	p->show();

	cout << p->pop() << endl;
	cout << p->pop() << endl;

	p->show();
}

int main()
{
	stack  A;
	queue  B;

	func(&A);//调用栈的成员方法
	//func(&B);//调用队列的成员方法
}

