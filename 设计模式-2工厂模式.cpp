/********************/简单工厂（Simple Factory）/************************************************************/
//优点
1、一个调用者想创建一个对象，只要知道其名称就可以了；
2、扩展性高，如果想增加一个产品，只要扩展一个工厂类就可以；
3、屏蔽产品的具体实现，调用者只关心产品的接口。

//缺点
每次增加一个产品时，都需要增加一个具体类和对象实现工厂，使得系统中类的个数成倍增加，
在一定程度上增加了系统的复杂度，同时也增加了系统具体类的依赖。

//实例
class Car
{
public:
	Car(string name) :_name(name) {}
	virtual void show() = 0;
protected:
	string _name;
};
class Bmw :public Car
{
public:
	Bmw(string name) :Car(name) {}
	void show()
	{
		cout << "获取了一辆宝马汽车：" << _name << endl;
	}
};
class Audi :public Car
{
public:
	Audi(string name) :Car(name) {}
	void show()
	{
		cout << "获取了一辆奥迪汽车：" << _name << endl;
	}
};


enum Cartype
{
	BMW, AUDI
};

class SimpleFactory
{
public:
	// 用户想要创建一个对象，只需要知道名称就可以了
	Car* createCar(Cartype ct)
	{
		switch (ct)
		{
		case BMW:
			return new Bmw("x6");
		case AUDI:
			return new Audi("a8");
		default:
			cerr << "传入参数错误：" << ct << endl;
		}
		return nullptr;
	}
};


void main()
{
	SimpleFactory* fac = new SimpleFactory();
	Car* p1 = fac->createCar(BMW);
	Car* p2 = fac->createCar(AUDI);

	p1->show();
	p2->show();

	delete fac;
	delete p1;
	delete p2;

}

每当我们想要扩展对象的时候（增加BENZ的对象）就需要在SimpleFactory类中添加代码，增加switch后面的case选项。
这样一来，就需要修改源代码。灵活性非常的差！！！



/********************/工厂方法（Factory Method）/************************************************************/
工厂方法的思想就是定义一个Factory基类，基类中定义了一个纯虚函数（创建产品）；
之后定义派生类（具体产品的工厂）负责创建对应的产品。
可以做到不同的产品在不同的工厂里面创建，能够对现有工厂以及产品的修改关闭。


//实例
class Car
{
public:
	Car(string name) :_name(name) {}
	virtual void show() = 0;
protected:
	string _name;
};
class Bmw :public Car
{
public:
	Bmw(string name) :Car(name) {}
	void show()
	{
		cout << "获取了一辆宝马汽车：" << _name << endl;
	}
};
class Audi :public Car
{
public:
	Audi(string name) :Car(name) {}
	void show()
	{
		cout << "获取了一辆奥迪汽车：" << _name << endl;
	}
};


class Factory					// 基类（包含纯虚函数，不能实例化对象）
{
public:
	virtual Car* createCar(string name) = 0;
};

class BmwFac : public Factory		// 宝马汽车工厂，负责生产宝马汽车
{
public:
	Car* createCar(string name)
	{
		return new Bmw(name);
	}
};

class AudiFac :public Factory		// 奥迪汽车工厂，负责生产奥迪汽车
{
public:
	Car* createCar(string name)
	{
		return new Audi(name);
	}
};

int main()
{
	unique_ptr<Factory> bmwfty(new BmwFac());
	unique_ptr<Factory> audifty(new AudiFac());
	unique_ptr<Car> p1(bmwfty->createCar("X6"));
	unique_ptr<Car> p2(audifty->createCar("A8"));

	p1->show();
	p2->show();

	return 0;
}



/********************/抽象工厂（Abstract Factory）/************************************************************/
//抽象工厂的思想是：
把有关联关系的，属于一个产品簇的所有产品创建的接口函数，放在一个抽象工厂里面AbstractFactory，
派生类（具体产品的工厂）应该负责创建该产品簇里面所有的产品。


//接口与类的数量：
工厂方法模式中，通常只有一个抽象产品类，而具体工厂类只能创建一个具体产品类的实例。
抽象工厂模式中，由于需要处理整个产品族，因此会有多个抽象产品类和多个具体产品类。
//扩展性：
工厂方法模式在增加新产品时，只需增加产品类和生成产品实例的工厂类，而不需要修改已有的工厂类和客户端代码，符合“开放 - 封闭”原则。
抽象工厂模式在增加新的产品族时，需要增加新的具体工厂类和对应的具体产品类，但它不需要修改已有产品族的工厂类和客户端代码。


//实例
// 系列产品1：汽车
class Car
{
public:
	Car(string name) :_name(name) {}
	virtual void show() = 0;
protected:
	string _name;
};
class Bmw :public Car
{
public:
	Bmw(string name) :Car(name) {}
	void show()
	{
		cout << "获取了一辆宝马汽车：" << _name << endl;
	}
};
class Audi :public Car
{
public:
	Audi(string name) :Car(name) {}
	void show()
	{
		cout << "获取了一辆奥迪汽车：" << _name << endl;
	}
};
// 系列产品2：车灯
class Light
{
public:
	virtual void show() = 0;
};
class BmwLight : public Light
{
public:
	void show() { cout << "BMW light!" << endl; }
};
class AudiLight : public Light
{
public:
	void show() { cout << "Audi light!" << endl; }
};


// 工厂方法 => 抽象工厂(对有一组关联关系的产品簇提供产品对象的统一创建)
class AbstractFactory
{
public:
	virtual Car* createCar(string name) = 0; // 工厂方法 创建汽车
	virtual Light* createCarLight() = 0; // 工厂方法 创建汽车关联的产品，车灯
};
// 宝马工厂
class BMWFactory : public AbstractFactory
{
public:
	Car* createCar(string name)
	{
		return new Bmw(name);
	}
	Light* createCarLight()
	{
		return new BmwLight();
	}
};
// 奥迪工厂
class AudiFactory : public AbstractFactory
{
public:
	Car* createCar(string name)
	{
		return new Audi(name);
	}
	Light* createCarLight()
	{
		return new AudiLight();
	}
};


int main()
{
	unique_ptr<AbstractFactory> bmwfty(new BMWFactory());
	unique_ptr<AbstractFactory> audifty(new AudiFactory());
	unique_ptr<Car> p1(bmwfty->createCar("X6"));
	unique_ptr<Car> p2(audifty->createCar("A8"));
	unique_ptr<Light> l1(bmwfty->createCarLight());
	unique_ptr<Light> l2(audifty->createCarLight());

	p1->show();
	l1->show();

	p2->show();
	l2->show();

	return 0;
}



/********************/工厂模板/************************************************************/
//实例
// 抽象模板工厂类
// 模板参数：AbstractProduct_t 产品抽象类
template <class AbstractProduct_t>
class AbstractFactory
{
public:
	virtual AbstractProduct_t* CreateProduct() = 0;
	virtual ~AbstractFactory() {}
};

// 具体模板工厂类
// 模板参数：AbstractProduct_t 产品抽象类，ConcreteProduct_t 产品具体类
template <class AbstractProduct_t, class ConcreteProduct_t>
class ConcreteFactory : public AbstractFactory<AbstractProduct_t>
{
public:
	AbstractProduct_t* CreateProduct()
	{
		return new ConcreteProduct_t();
	}
};