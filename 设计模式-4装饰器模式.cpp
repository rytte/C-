/********************/装饰器模式（Decorator Pattern）/************************************************************/
装饰器模式（Decorator Pattern）允许向一个现有的对象添加新的功能，同时又不改变其结构。

//实现方法
设计一个新类，继承自原有类，并将原有类（或其父类）作为类成员在构造函数中传入赋值。
重写需要装饰的函数，通过成员指针调用原方法，然后添加其它操作。

//优点
1、在不派生子类的情况下扩展原有类的功能。装饰器模式是继承的一个替代模式。
2、装饰类和被装饰类可以独立发展，不会相互耦合。
3、它是作为现有的类的一个包装，相比生成子类更为灵活。

//缺点
多层装饰比较复杂。


//简单版实例
class Car
{
public:
	void show()
	{
		cout << "这是一辆宝马汽车，配置有：基本配置";
	}
};
class Decorator01: Car
{
public:
	Decorator01(Car* p) :pCar(p) {}
	void show()
	{
		pCar->show();
		cout << "，定速巡航";
	}
private:
	Car* pCar;
};



////扩展版实例////
class Car
{
public:
	virtual void show() = 0;
};

// 三个实体的汽车类
class Bmw :public Car
{
public:
	void show()
	{
		cout << "这是一辆宝马汽车，配置有：基本配置";
	}
};
class Audi :public Car
{
public:
	void show()
	{
		cout << "这是一辆奥迪汽车，配置有：基本配置";
	}
};

// 装饰器1 定速巡航
class Decorator01 :public Car
{
public:
	Decorator01(Car* p) :pCar(p) {}
	void show()
	{
		pCar->show();
		cout << "，定速巡航";
	}
private:
	Car* pCar;
};
// 装饰器2 自动刹车
class Decorator02 :public Car
{
public:
	Decorator02(Car* p) :pCar(p) {}
	void show()
	{
		pCar->show();
		cout << "，自动刹车";
	}
private:
	Car* pCar;
};


int main()
{
	Car* p1 = new Decorator01(new Bmw());		//宝马汽车增加了Decorator01（定速巡航）配置
	p1 = new Decorator02(p1);					//宝马汽车增加了Decorator02（自动刹车）配置
	p1->show();
	cout << endl;

	Car* p2 = new Decorator02(new Audi());		//给奥迪汽车增加了Decorator02（自动刹车）配置；
	p2->show();
	cout << endl;

	return 0;
}






