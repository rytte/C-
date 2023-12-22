/********************/QML工程结构/************************************************************/
QML 与 QWidget 交互
由于QML引擎和Qt的元对象系统的集成，使得允许将QML、JavaScript、C++三者进行混合开发。
界面代码与逻辑代码分离，界面采用QML、JavaScript，逻辑采用C++。

只有QObject的子类才能将数据或函数提供给QML使用，也就是说C++中的类要想与QML交互需要继承QObject类。
由于QML引擎集成了Qt元对象系统，由QObject派生的所有子类的属性、方法和信号等都可以在QML中访问。



/********************/在QML文件中访问C++类/************************************************************/
* C++类可以注册为一个可实例化的QML类型，QML中直接使用这个QML类型
* C++类可以被注册为一个单例类型，QML中导入这个单例
* C++类的实例可以作为上下文属性或上下文对象嵌入到QML代码中


1.使用C++属性（Q_PROPERTY）
QObject子类的所有属性都能够被QML访问。QObject子类使用Q_PROPERTY宏定义一个属性，该宏的作用是向Qt元对象系统注册类的属性。
一个类型的属性就是类的数据成员，通常有一个读（READ）函数和写（WHITE）函数。
Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)

* 任何可写属性都应该关联一个NOTIFY信号
* 读函数是userName()，写函数是setUserName()
* 不仅可以有QString类型的属性，还可以是对象，也可以是对象数组。对象数组采用QQmlListProperty类型。
Q_PROPERTY(QQmlListProperty messages READ messages)

2.使用函数和槽
QML可以有条件的访问QObject子类的函数，条件是
* 使用 Q_INVOKABLE 宏标记的public函数；
* public槽函数
然后在从main.cpp中setContextProperty，这样就可以直接在QML中使用函数和槽

class Window : public QWidget
{
        Q_OBJECT

public:
        Window();
        Q_INVOKABLE void invokableMethod();
public slots:
        void refresh();
};


//QML中使用C++类：将自定义的C++类注册到QML文件中使用，可以注册为可实例化对象类型、不可实例化对象类型、单例类型。
步骤1：
1. 自定义的类继承自QObject
2. 自定义的类声明 Q_OBJECT 宏定义
3. 自定义的类声明 Q_PROPERTY 宏定义
4. 自定义的类中定义好对应的userName()方法、setuserName()方法、userNameChanged信号，以及供访问的对象m_userName
5. 在main.cpp主函数包含该类头文件#include "MyBackend.h"
6. 在main.cpp主函数中注册该类 qmlRegisterType <MyBackend>("io.mylibrary.backend", 1, 0, "MyBackend");//参数（自定义模块名，主版本号，副版本号，类名）
7. 在main.qml文件中导入该模块 import io.mylibrary.backend 1.0
8. 在main.qml文件中使用该类 MyBackend{ ... }

//********************//main.cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "MyBackend.h"

int main(int argc, char* argv[])
{
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QGuiApplication app(argc, argv);

        //MyBackend类被注册为一个QML类型，可以在QML中导入"io.mylibrary.backend"来访问该类型
        //参数（自定义模块名，主版本号，副版本号）
        qmlRegisterType <MyBackend>("io.mylibrary.backend", 1, 0, "MyBackend");

        QQmlApplicationEngine engine;
        const QUrl url(QStringLiteral("qrc:/main.qml"));
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                &app, [url](QObject* obj, const QUrl& objUrl) {
                        if (!obj && url == objUrl)
                                QCoreApplication::exit(-1);
                }, Qt::QueuedConnection);
        engine.load(url);

        return app.exec();
}

//********************//mybackend.h
#ifndef MYBACKEND_H
#define MYBACKEND_H

#include <QObject>

class MyBackend : public QObject
{
        Q_OBJECT
                //宏声明了一个可以从QML访问的属性
                Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
public:
        explicit MyBackend(QObject* parent = nullptr);

        QString userName()
        {
                return m_userName;
        }
        void setUserName(const QString& userName)
        {
                if (userName == m_userName) {
                        return;
                }
                m_userName = userName;
                emit userNameChanged();
        }

signals:
        void userNameChanged();

private:
        QString    m_userName;
};

#endif // MYBACKEND_H

//********************//main.qml
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import io.mylibrary.backend 1.0

Window{
        visible: true
        width : 640
        height : 480
        title : qsTr("Hello World")

        MyBackend {
                id: backend
                //调用MyBackend::userName()
                onUserNameChanged : console.log(backend.userName)
        }

        Column {
                spacing: 10
                anchors.centerIn : parent

                TextField {
                        placeholderText: qsTr("user name")
                        //调用MyBackend::setUserName()
                        onTextChanged : backend.userName = text
                }

                Label {
                        text: backend.userName
                        background : Rectangle {
                                color: "red"
                        }
                }
        }
}



/********************/在C++代码中访问QML对象/************************************************************/
//1.QQmlEngine与QQmlApplicationEngine
这个类提供了一个QML引擎，管理QML文档，引擎提供了一个默认的QML上下文。
创建Quick应用时，最常见的是QQmlApplicationEngine类，继承自QQmlEngine，它结合了QQmlEngine和QQmlComponent的功能。

实例：
QQmlApplicationEngine engine;
engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
if (engine.rootObjects().isEmpty()) {
        return -1;
}


//2.QQmlContext
QQmlContext主要是用于创建上下文环境，它暴露C++对象给QML文件使用，并允许在QML中直接访问这些对象的属性和方法。
但是，QQmlContext本身并不直接修改QML元素。

实例：
QQmlEngine engine;
QStringListModel modelData;
QQmlContext* context = engine.rootContext();                             
context->setContextProperty("stringModel", &modelData); //调用 setContextProperty() 函数将QStringListModel类设为QQmlContext的属性，可以在qml文件中作为属性调用它


//3.QQmlComponent
QML的对象类型可以在运行时使用QQmlCompontent类型进行实例化。
要修改QML中的一个元素，通常使用QQmlComponent来获取和修改该元素的相关属性和行为。

实例：
main.cpp
int main(int argc, char* argv[])
{
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QGuiApplication app(argc, argv);

        QQmlEngine engine;
        QQmlComponent component(&engine, QUrl::fromLocalFile(":/main.qml"));
        QObject* obj = component.create();
        QQuickItem* item = qobject_cast <QQuickItem*> (obj);
        qDebug() << item->width();

        return app.exec();
}
main.qml
Item{
    width: 640
    height : 480
}


//4.QQmlExpresssssion
动态执行表达式也是QML的核心概念之一。可以在C++中，利用特定的QML上下文执行JS表达式。
QQmlEngine * engine = new QQmlEngine();
QQmlComponent component(engine, QUrl::fromLocalFile(":/main.qml"));
QObject* obj = component.create();
QQmlExpression* expr = new QQmlExpression(engine->rootContext(), object, "width * 2");
int result = expr->evaluate().toInt();



//C++访问QML
QML对象类型也可以在C++中被实例化，从而使C++对象可以访问其属性、函数、及对象。
这是由于所有的QML对象类型，都是QObject子类，因此才能够允许QML引擎使用Qt元对象系统动态实例化任何QML对象类型。
不推荐在C++中操作QML对象，重构QML要比重构C++要容易的多，为减少后期维护成本，建议尽量减少C++端处理QML内容。


第一种：使用C++加载QML对象

第二种：使用对象名字objectName访问加载的QML对象
不建议使用，对象名字的属性值并不是唯一的。

第三种：使用C++访问QML对象成员
1.访问QML属性
QML对象声明属性，就可以在C++中访问这个属性，既可以通过QObject::setProperty()和QObject::property()两个函数，也可以通过QQmlProperty类来读写。
2.访问QML函数
因为QML函数都已经暴露给了Qt元对象系统了，所以可以使用QMetaObject::invokeMethod。QML函数参数和返回值的类型都被自动转换为对应的QVariant值。
3.访问QML信号
连接信号可以使用QObject::connect()函数进行连接，连接的方式只能采用Qt 4风格。因为Qt 5的信号和槽新语法要求一个静态的C++类。
而QML生成的是动态的，无法使用取地址运算符。要理解这一点，可以在C++代码中输出item的类型，就可以看到QML在元对象系统中的类名字（MyItem_QMLTYPE_0）

注意
当使用QML对象类型作为信号参数时，需要使用var作为参数类型，在C++中则应该使用QVariant。














QQmlApplicationEngine::rootObjects()      返回QList
返回由QQmlApplicationEngine实例化的所有根对象的列表。这将只包含通过Load()或方便的构造函数加载的对象。

QList::first()          返回QObject
返回对列表中第一项的引用。该列表不能为空。如果列表可以为空，则在调用此函数之前调用isEmpty()。


findchild()函数中
name指的是objectName，而不是id
Text{
        id: abcd
        x : 44
        y : 27
        text : qsTr("HelloWorld")
        font.pixelSize : 12
        objectName : "hello"
}