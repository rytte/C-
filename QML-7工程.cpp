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


//1.使用C++属性（Q_PROPERTY）
QObject子类的所有属性都能够被QML访问。QObject子类使用Q_PROPERTY宏定义一个属性，该宏的作用是向Qt元对象系统注册类的属性。
一个类型的属性就是类的数据成员，通常有一个读（READ）函数和写（WHITE）函数。
Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)

* 任何可写属性都应该关联一个NOTIFY信号
* 读函数是userName()，写函数是setUserName()
* 不仅可以有QString类型的属性，还可以是对象，也可以是对象数组。对象数组采用QQmlListProperty类型。
Q_PROPERTY(QQmlListProperty messages READ messages)

//2.使用函数和槽
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
步骤：
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
                Q_PROPERTY(QString userName READ getUserName WRITE setUserName NOTIFY userNameChanged)
public:
        explicit MyBackend(QObject* parent = nullptr);

        QString getUserName()
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
                //userName属性改变时，调用MyBackend::getUserName()
                onUserNameChanged : console.log(backend.userName)
        }

        Column {
                spacing: 10
                anchors.centerIn : parent

                TextField {
                        placeholderText: qsTr("user name")
                        //当文本框内容改变时，调用MyBackend::setUserName()
                        onTextChanged : backend.userName = text
                }

                Label {
                        //调用MyBackend::getUserName()
                        text: backend.userName
                        background : Rectangle {
                                color: "red"
                        }
                }
        }
}



/********************/QML相关的C++类/************************************************************/
//QML对象获取方法
QObject * obj = engine.rootObjects().first();
QObject* obj = component.create();


//0.常用的继承自QObject的函数
查找子对象：T findChild(const QString & name = QString(), Qt::FindChildOptions options = Qt::FindChildrenRecursively) const
设置属性：bool setProperty(const char* name, const QVariant & value)
获取属性：QVariant property(const char* name) const
设置父对象：void setParent(QObject * parent)
获取父对象：QObject * parent() const
设置对象名：void setObjectName(const QString & name)
获取对象名：QString objectName() const


//1.QQmlEngine与QQmlApplicationEngine
这个类提供了一个QML引擎，管理QML文档，引擎提供了一个默认的QML上下文。
创建Quick应用时，最常见的是QQmlApplicationEngine类，继承自QQmlEngine，它结合了QQmlEngine和QQmlComponent的功能。
实例：
        QQmlApplicationEngine engine;
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
        if (engine.rootObjects().isEmpty()) {
                return -1;
        }

<常用函数>
获取engine上下文：QQmlContext* rootContext() const
获取engine对象列表：QList<QObject*> rootObjects() const
返回对列表中第一项的引用：T& QList::first()
<Public Slots>
读取url文件：void load(const QUrl& url)
读取qml文件：void load(const QString& filePath)
<Signals>
对象被创建时产生的信号：void objectCreated(QObject* object, const QUrl& url)


//2.QQmlContext，调用 setContextProperty() 函数将C++类设为QQmlContext的属性，可以在qml文件中作为属性调用它
QQmlContext主要是用于创建上下文环境，它暴露C++对象给QML文件使用，并允许在QML中直接访问这些对象的属性和方法。
但是，QQmlContext本身并不直接修改QML元素。
实例：
        QQmlApplicationEngine engine;
        QStringListModel modelData;
        QQmlContext* context = engine.rootContext();                             
        context->setContextProperty("stringModel", &modelData); 

<常用函数>
获取上下文对象：QObject* contextObject() const
获取上下文属性：QVariant contextProperty(const QString& name) const
获取engine：QQmlEngine* engine() const
判断有效性：bool isValid() const
获取对象名：QString nameForObject(QObject* object) const
获取父对象上下文：QQmlContext* parentContext() const
设置上下文对象：void setContextObject(QObject* object)
设置上下文属性：void setContextProperties(const QVector<QQmlContext::PropertyPair>& properties)
设置上下文属性：void setContextProperty(const QString& name, QObject* value)
设置上下文属性：void setContextProperty(const QString& name, const QVariant& value)


//3.QQmlComponent
QML的对象类型可以在运行时使用QQmlCompontent类型进行实例化。
要修改QML中的一个元素，通常使用QQmlComponent来获取和修改该元素的相关属性和行为。
实例：
        QQmlEngine engine;
        QQmlComponent component(&engine, QUrl::fromLocalFile(":/main.qml"));
        QObject* obj = component.create();


//4.QQmlExpresssssion
动态执行表达式也是QML的核心概念之一。可以在C++中，利用特定的QML上下文执行JS表达式。
实例：
        QQmlEngine * engine = new QQmlEngine();
        QQmlComponent component(engine, QUrl::fromLocalFile(":/main.qml"));
        QObject* obj = component.create();
        QQmlExpression* expr = new QQmlExpression(engine->rootContext(), obj, "width * 2");
        int result = expr->evaluate().toInt();


//5.QQuickItem
*只能读取Item类型组件
提供一种轻量级的可视化解决方案，它占用的资源较少，性能更高
具有很强的可定制性，开发者可以通过继承QQuickItem类创建自定义的元素，并实现自定义的绘制、动画和交互功能
实例：
        QQuickItem* item = qobject_cast <QQuickItem*> (obj);
        item->setWidth(300);
        qDebug() << item->width();

        Item{
                width: 640
                height : 480
        }


//6.QQuickWindow
为了在窗口中显示一个图形化的QML场景，可以使用QQuickWindow类
QQuickWindow始终有一个不可见的根项目。若要将项目添加到此窗口，请将这些项目重新设置为场景中根项目或现有项目的父对象。
实例：
        QQuickWindow* window = qobject_cast <QQuickWindow*> (obj);
        window->show();
        window->setProperty("width", 200);                                                          //可以设置主窗口属性


//7.QQuickView
QQuickView是QQuickWindow的一个子类，它管理显示来自QML文件的场景，并且可以很容易地使用
实例：
        QQuickView* view = new QQuickView;
        view->setSource(QUrl::fromLocalFile("myqmlfile.qml"));
        view->show();


//8.QQuickWidget
在qml中和QQuickView差不多
在qtwidget中，QQuickWidget直接就是个QWidget子类，你可以直接添加到用QtWidgets写的界面里去，可以加载qml相关东西。
QQuickView得转换下才能添加到QtWidgets写的界面里。这是最主要的区别。
class Q_QUICKWIDGETS_EXPORT QQuickWidget : public QWidget
{
}



/********************/在C++代码中访问QML对象/************************************************************/
//C++访问QML
QML对象类型也可以在C++中被实例化，从而使C++对象可以访问其属性、函数、及对象。
这是由于所有的QML对象类型，都是QObject子类，因此才能够允许QML引擎使用Qt元对象系统动态实例化任何QML对象类型。
不推荐在C++中操作QML对象，重构QML要比重构C++要容易的多，为减少后期维护成本，建议尽量减少C++端处理QML内容。


/////////////////////////使用C++访问QML对象//////////////////////////
//1.创建QQmlApplicationEngine
        QQmlApplicationEngine engine;
//2.获取QML对象QObject的方法
<方法一>
engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
QObject* obj = engine.rootObjects().value(0);                                       //等价于QObject* obj = engine.rootObjects().first();
<方法二>
QQmlComponent component(engine, QUrl::fromLocalFile(":/main.qml"));
QObject* obj = component.create();
//3.可以使用setProperty()设置属性，property()读取属性。也可以通过QQmlProperty类来读写。
obj->setProperty("color", "blue");
qDebug() << QQmlProperty::read(obj, "width").toInt();
QQmlProperty::write(obj, "width", 400);
//4.使用findchild()获取子对象，再访问子对象属性
QObject* child = obj->findChild<QObject*>("objectName");               //"对象名"指的是qml对象的objectName属性，而非id，且该属性不唯一
child->setProperty("color", "red");
//5.使用QMetaObject::invokeMethod访问QML函数。QML函数参数和返回值的类型都被自动转换为对应的QVariant值。
QVariant returnValue;
QVariant msgw = "i am cpp";
QMetaObject::invokeMethod(obj, "legalName",
        Q_RETURN_ARG(QVariant, returnValue),
        Q_ARG(QVariant, msgw));
qDebug() << returnValue.toString();

Item{
        //函数名必须是合法的
        function legalName(msg) {
                console.log("cpp send:", msg);
                return "i am qml";
        }
}
//6.访问QML信号
1.定义信号：signal qmlSignal(string str)
2.发射信号：onClicked : item.qmlSignal("大大泡泡糖")
3.连接信号：QObject::connect(item, SIGNAL(qmlSignal(QString)), myClass, SLOT(cppSlot(QString)));

可以使用QObject::connect()函数连接信号，连接的方式只能采用Qt 4风格。如：connect(btn, SIGNAL(clicked()), this, SLOT(close()));
因为Qt 5的信号和槽新语法要求一个静态的C++类。而QML生成的是动态的，无法使用取地址运算符。
要理解这一点，可以在C++代码中输出item的类型，就可以看到QML在元对象系统中的类名字（MyItem_QMLTYPE_0）

//********************//main.qml
Item{
        id: item
        width : 400; height: 400
        signal qmlSignal(string str)

        MouseArea {
                anchors.fill: parent
                onClicked : item.qmlSignal("大大泡泡糖")
        }
}

//********************//main.cpp
class MyBackend : public QObject
{
        Q_OBJECT
public slots:
        void cppSlot(const QString& msg) {
                qDebug() << "QML send signal" << msg;
        }
};

int main(int argc, char* argv[])
{
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QGuiApplication app(argc, argv);

        QQuickView view(QUrl(QStringLiteral("qrc:/main.qml")));
        QQuickItem* item = view.rootObject();

        MyBackend* myClass = new MyBackend();
        QObject::connect(item, SIGNAL(qmlSignal(QString)), myClass, SLOT(cppSlot(QString)));
        view.show();

        return app.exec();
}


*注意：当使用QML对象类型作为信号参数时，需要使用var作为参数类型，在C++中则应该使用QVariant。
//main.qml中
Item{
        id: item
        width : 400; height: 400
        signal qmlSignal(var item)
        MouseArea {
                anchors.fill: parent
                onClicked : item.qmlSignal(item)
        }
}

//MyBackend.h中
public slots:
        void cppSlot(const QVariant& msg) {
                qDebug() << "QML send signal" << msg;
        }
 


