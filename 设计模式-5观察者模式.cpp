/********************/观察者模式/************************************************************/
观察者模式（Observer Pattern），也叫我们熟知的发布 - 订阅模式。

特点：定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。

//优点
1、观察者和被观察者是抽象耦合的；
2、建立了一套触发机制。

//缺点
1、如果一个被观察者对象有很多的直接和间接的观察者的话，通知所有的观察者需要花费很长的时间；
2、如果在观察者和被观察者目标之间有循环依赖的话，观察目标会触发他们之间的循环调用，可能会导致系统崩溃；
3、观察者模式没有相应的机制让观察者知道所观察的目标对象是怎么发生变化的，而仅仅是知道观察目标发生了变化。


//代码实现
场景说明
我们可以将观察者模式理解为，我们订阅一份报纸。
首先决定订阅报纸的时候，需要去报刊告诉相关工作人员，
填写自己订阅的信息，比如想要订阅什么类型的报纸（体育类、财经类等），之后留下自己的住址（这样就可以享受送报上门服务了）。

我们实现的话，可以简单的设置三个观察者，一个主题类（被观察者）。
这三个观察者可以设置自己喜欢的、感兴趣的消息类型（1、2、3）。
他们处理收到的消息就是打印一下自己收到了什么消息。


//实例
#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Observer Interface - 观察者接口
class Observer 
{
public:
    virtual void update(const std::string& message) = 0;
};

// Concrete Observer - 具体观察者
class ConcreteObserver : public Observer 
{
public:
    ConcreteObserver(const std::string& name) : name(name) {}

    void update(const std::string& message) override 
    {
        std::cout << "Observer " << name << " received message: " << message << std::endl;
    }

private:
    std::string name;
};

// Subject Interface - 主题接口
class Subject 
{
public:
    virtual void addObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void removeObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void notifyObservers() = 0;
};

// Concrete Subject - 具体主题
class ConcreteSubject : public Subject 
{
public:
    void addObserver(std::shared_ptr<Observer> observer) override 
    {
        observers.push_back(observer);
    }

    void removeObserver(std::shared_ptr<Observer> observer) override 
    {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers() override 
    {
        for (const auto& observer : observers) 
        {
            observer->update(message);
        }
    }

    // Set state and notify observers
    void setMessage(const std::string& msg) 
    {
        message = msg;
        notifyObservers();
    }

private:
    std::vector<std::shared_ptr<Observer>> observers;
    std::string message;
};

// Main function
int main() 
{
    // Create Subject
    ConcreteSubject subject;

    // Create Observers
    auto observer1 = std::make_shared<ConcreteObserver>("Observer1");
    auto observer2 = std::make_shared<ConcreteObserver>("Observer2");

    // Add Observers to Subject
    subject.addObserver(observer1);
    subject.addObserver(observer2);

    // Change Subject state and notify Observers
    subject.setMessage("Hello, Observers!");

    // Remove an observer and send another message
    subject.removeObserver(observer1);
    subject.setMessage("This is another message.");

    return 0;
}


解释
Subject 类（主题类）维护观察者列表并在状态变化时通知它们。
Observer 接口定义了观察者需要实现的 update 方法，用于接收通知。
ConcreteSubject 类实现了 addObserver、removeObserver 和 notifyObservers 方法。setMessage 方法用来修改状态并触发通知。
ConcreteObserver 类实现了 update 方法，在接收到消息时打印输出。

