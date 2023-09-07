/********************/纯虚函数/************************************************************/
纯虚函数：
您可能想要在基类中定义虚函数，以便在派生类中重新定义该函数更好地适用于对象，但在基类中又不能对虚函数给出有意义的实现，这个时候就会用到纯虚函数。

语法形式：
virtual 函数名() = 0;


若析构函数是纯虚函数，则称为纯虚析构。纯虚析构必须类外定义。

派生类中是无法对基类的析构函数进行重写的，因此需要将析构函数定义为虚析构或纯虚析构，并在函数外定义，由此可在派生类中重写析构函数。

/********************/抽象/************************************************************/
虚函数指向0的时候表示纯虚函数，带有至少一个纯虚函数的类被称为抽象类。

特点：
（1）抽象类无法创建实例化对象。
（2）抽象类的派生类也是抽象类，除非派生类中对纯虚函数进行重写并有执行的函数体。
（3）如果一个抽象类的子类需要被实例化，则必须实现每个纯虚函数，可用于实例化对象的类被称为具体类。
（4）抽象类一般用在不方便创建实例化对象的类中，例如算法类。
（5）第二种就是用在必须写派生类的情况，强调基类不可以创建对象。例如线程和线程池。


案例 : 算法类是 y = kx + 3;
依赖该算法类去运行。


/********************/虚继承与抽象类/************************************************************/
虚指针的创建

基类：抽象类编译时产生一个指向自己的虚表的虚指针（虚表中存放的是自己虚函数的内存地址）。

派生类①：继承抽象类会产生一个指向基类的虚表的虚指针（该虚指针是继承时复制的那个）。

派生类②：虚继承的类编译时也会产生一个虚指针指向自己的虚表的虚指针（虚表中存放的是虚基类的成员属性与成员方法的内存地址）。

派生类③：虚继承一个抽象类，会同时产生以上派生类①和派生类②所示的两个虚指针。


VS2022遵循以上规律
而在gcc编译器中，派生类③的情况下，若虚基类没有成员属性，则不会产生指向自己虚表的虚指针。


/************************************************************/
虚函数与纯虚函数：

1.定义一个函数为虚函数，不代表函数为不被实现的函数。

2.定义它为虚函数是为了允许用基类的指针来调用子类的这个函数。

3.定义一个函数为纯虚函数，才代表函数没有被实现。

4.定义纯虚函数是为了实现一个接口，起到一个规范的作用，规范继承这个类的程序员必须实现这个函数。


练习 :
应用抽象类，求圆, 圆内接正方形，和圆外切正方形的面积和周长



/********************/纯虚函数实例/************************************************************/
#include <iostream>

using namespace std;


class Base {
public:
	//纯虚函数---Base是一个抽象类
	virtual void show() = 0;
};

class Data :public Base {
public:
	virtual void show() {
		cout << "Data show()" << endl;
	}
};


int main()
{
	//Base P;		//错误，抽象类无法实例化
	Data P;

}



/********************/纯虚析构实例/************************************************************/
#include <iostream>

using namespace std;


class Base {
public:
	//纯虚析构
	virtual ~Base() = 0;
};

//纯虚析构必须类外定义
Base::~Base() {
	cout << "Base 析构" << endl;
}

class Data :public Base {
public:
	~Data() {
		cout << "Data 析构" << endl;
	}
};


int main()
{
	//Base P;
	Data P;
}



/********************/虚指针验证实例/************************************************************/
#include <iostream>

using namespace std;


class Base {
public:
	//纯虚函数---Base是一个抽象类
	virtual void show() = 0;
	//int a;
	//int b;
	//int c;
};

class Data :virtual public Base {
public:
	void show() {
		cout << "Data show()" << endl;
	}
};


int main()
{
	//Base P;		//错误，抽象类无法实例化

	cout << sizeof(Base) << endl;
	cout << sizeof(Data) << endl;

}



/********************/接口实例/************************************************************/
假设有栈和队列两种数据结构，要求使用同一个接口来调用它们。


#include <iostream>

using namespace std;

class base {
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
	void push(int n)//入栈
	{
		arr[size] = n;
		size++;
	}
	int pop()//出栈
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
	int front;//指向队首
	int last;//指向队尾
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

