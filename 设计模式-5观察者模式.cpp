/********************/观察者模式/************************************************************/
模式简介
观察者模式（Observer Pattern），也叫我们熟知的发布 - 订阅模式。
它是一种行为型模式。

介绍
观察者模式主要关注的是对象的一对多的关系，
也就是多个对象依赖于一个对象，当该对象的状态发生改变时，其他对象都能够收到相应的通知。

意图：
定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。
主要解决：
一个对象状态改变给其他对象通知的问题，而且要考虑到易用和低耦合，保证高度的协作。
如何解决：
使用面向对象技术，可以将这种关系弱化。

//优点
1、观察者和被观察者是抽象耦合的；
2、建立了一套触发机制。
//缺点
1、如果一个被观察者对象有很多的直接和间接的观察者的话，通知所有的观察者需要花费很长的时间；
2、如果在观察者和被观察者目标之间有循环依赖的话，观察目标会触发他们之间的循环调用，可能会导致系统崩溃；
3、观察者模式没有相应的机制让观察者知道所观察的目标对象是怎么发生变化的，而仅仅是知道观察目标发生了变化。


代码实现
场景说明
我们可以将观察者模式理解为，我们订阅一份报纸。
首先决定订阅报纸的时候，需要去报刊告诉相关工作人员；填写自己订阅的信息，比如想要订阅什么类型的报纸（体育类、财经类等），之后留下自己的住址（这样就可以享受送报上门服务了）。

我们实现的话，可以简单的设置三个观察者，一个主题类（被观察者）。
这三个观察者可以设置自己喜欢的、感兴趣的消息类型（1、2、3）。
他们处理收到的消息就是打印一下自己收到了什么消息。


//实例
#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
using namespace std;

class Observer
{
public:
	// 处理消息的接口
	virtual void handle(int msgid) = 0;
};
// 第一个观察者实例
class Observer1 :public Observer
{
public:
	void handle(int msgid)
	{
		switch (msgid)
		{
		case 1:
			cout << "Observer1 recv 1 msg!" << endl;
			break;
		case 2:
			cout << "Observer1 recv 2 msg!" << endl;
			break;
		default:
			cout << "Observer1 recv unkown msg!" << endl;
			break;
		}
	}
};
// 第二个观察者实例
class Observer2 :public Observer
{
public:
	void handle(int msgid)
	{
		switch (msgid)
		{
		case 2:
			cout << "Observer2 recv 2 msg!" << endl;
			break;
		default:
			cout << "Observer2 recv unkown msg!" << endl;
			break;
		}
	}
};
// 第三个观察者实例
class Observer3 :public Observer
{
public:
	void handle(int msgid)
	{
		switch (msgid)
		{
		case 1:
			cout << "Observer3 recv 1 msg!" << endl;
			break;
		case 3:
			cout << "Observer3 recv 3 msg!" << endl;
			break;
		default:
			cout << "Observer3 recv unkown msg!" << endl;
			break;
		}
	}
};

// 主题类
class Subject
{
public:
	// 给主题对象增加观察者对象
	void addObserver(Observer* obser, int msgid)
	{
		_subMap[msgid].push_back(obser);
	}
	// 主题发生改变，通知相应的观察者处理事件
	void dispatch(int msgid)
	{
		auto it = _subMap.find(msgid);
		if (it != _subMap.end())
		{
			for (Observer* obs : it->second)
			{
				obs->handle(msgid);
			}
		}
	}
private:
	unordered_map<int, list<Observer*>> _subMap;
};


auto it = _subMap.find(msgid);
if (it != _subMap.end())
{
	it->second.push_back(obser);
}
else
{
	list<Observer*> lis;
	lis.push_back(obser);
	_subMap.insert({ msgid, lis });
}


int main()
{
	Subject sub;
	Observer* p1 = new Observer1();
	Observer* p2 = new Observer2();
	Observer* p3 = new Observer3();

	sub.addObserver(p1, 1);
	sub.addObserver(p1, 2);
	sub.addObserver(p2, 2);
	sub.addObserver(p3, 1);
	sub.addObserver(p3, 3);

	int msgid = 0;
	for (;;)
	{
		cout << "请输入消息id：";
		cin >> msgid;
		if (msgid == -1)
			break;
		sub.dispatch(msgid);
	}

	return 0;
}


