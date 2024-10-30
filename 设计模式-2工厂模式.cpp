/********************/工厂模式（Factory Pattern）/************************************************************/
//工厂模式分类
简单工厂：由"产品基类"派生出各种"产品"，由工厂函数根据"枚举"类型创建对应"产品"
工厂方法：由"产品基类"派生出各种"产品"，由"工厂基类"派生出各种"工厂"，每个工厂只能创建一种对应的"产品"
抽象工厂：由"产品基类"派生出各种"产品"，由"工厂基类"派生出各种"工厂"，由"组件基类"派生出各种"组件"，每个工厂负责创建一种对应的"产品"及其"组件"


//产品
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



/********************/简单工厂（Simple Factory）/************************************************************/
//优点
1、调用者想创建一个对象，只要知道其名称就可以了；
2、扩展性高，如果想增加一个产品，只要扩展一个工厂类就可以；
3、屏蔽产品的具体实现，调用者只关心产品的接口。

//缺点
每次增加一个产品时，都需要增加一个具体类和对象实现工厂，使得系统中类的个数成倍增加，
在一定程度上增加了系统的复杂度，同时也增加了系统具体类的依赖。


//工厂实例
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

每当我们想要扩展对象的时候（增加BENZ的对象）就需要在SimpleFactory类中添加代码，增加 switch 后面的 case 选项。
这样一来，就需要修改源代码。灵活性非常的差！！！



/********************/工厂方法（Factory Method）/************************************************************/
工厂方法的思想，就是在不同的工厂类里面创建不同的产品，能够对现有工厂以及产品的修改关闭。


//工厂实例
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
抽象工厂的思想，就是在工厂方法的基础上，把有关联关系的，同一系列的产品交由同一个工厂负责生产。


// 新增产品：车灯
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

//工厂实例：工厂方法 => 抽象工厂(对有一组关联关系的产品簇提供产品对象的统一创建)
class AbstractFactory
{
public:
	virtual Car* createCar(string name) = 0; // 工厂方法 创建汽车
	virtual Light* createCarLight() = 0;		// 工厂方法 创建汽车关联的产品，车灯
};

class BMWFactory : public AbstractFactory		// 宝马工厂
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

class AudiFactory : public AbstractFactory		// 奥迪工厂
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



/********************/工厂模板;/************************************************************/
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
