/********************/组件/************************************************************/
QML 可以用基本元素组合成一个复杂的元素，方便以后我们的重用。这种组合元素就被称为组件。
QML 提供了很多方法来创建组件。不过，这里我们只介绍一种方式：基于文件的组件。
基于文件的组件将 QML 元素放置在一个单独的文件中，然后给这个文件一个名字。以后我们就可以通过这个名字来使用这个组件。
例如，如果有一个文件名为 Button.qml，那么，我们就可以在 QML 中使用 Button { … }这种形式。 
下面我们通过一个例子来演示这种方法。我们要创建一个带有文本说明的 Rectangle，这个矩形将成为一个按钮。用户可以点击矩形来响应事件。

import QtQuick 2.0 

Rectangle { 
        id: root 
        
        property alias text: label.text 
        signal clicked 
        
        width: 116; height: 26 
        color: "lightsteelblue" 
        border.color: "slategrey" 
        
        Text { 
                id: label 
                anchors.centerIn: parent 
                text: "Start" 
        } 
        MouseArea { 
                anchors.fill: parent 
                onClicked: { 
                        root.clicked() 
                } 
        } 
}

我们将这个文件命名为 Button.qml，放在 main.qml 同一目录下。这里的 main.qml 就是 IDE 帮我们生成的 QML 文件。此时，我们已经创建了一个 QML 组件。
这个组件其实就是一个预定义好的 Rectangle。这是一个按钮，有一个 Text 用于显示按钮的文本；有一个MouseArea 用于接收鼠标事件。
用户可以定义按钮的文本，这是通过设置 Text 的 text 属性实现的。为了不对外暴露 Text 元素，我们给了它的 text 属性一个别名。signal clicked给这个 Button一个信号。
由于这个信号是无参数的，我们也可以写成 signal clicked()，二者是等价的。
注意，这个信号会在 MouseArea 的 clicked 信号后被发出，具体就是在MouseArea 的 onClicked 属性中调用个这个信号。
下面我们需要修改 main.qml 来使用这个组件：

import QtQuick 2.0 

Rectangle { 
    width: 360 
    height: 360 
    Button { 
        id: button 
        x: 12; y: 12 
        text: "Start" 
        onClicked: { 
            status.text = "Button clicked!" 
        } 
    } 

    Text { 
        id: status 
        x: 12; y: 76 
        width: 116; height: 26 
        text: "waiting ..." 
        horizontalAlignment: Text.AlignHCenter 
    } 
} 

在 main.qml 中，我们直接使用了 Button这个组件，就像 QML 其它元素一样。由于Button.qml 与 main.qml 位于同一目录下，所以不需要额外的操作。但是，如果我们将Button.qml 放在不同目录，如：
app
|- QML
| |- main.qml
|- components
|- Button.qml
那么，我们就需要在 main.qml 的 import 部分增加一行 import ../components 才能够找到Button组件。 有时候，选择一个组件的根元素很重要。比如我们的 Button组件。
我们使用 Rectangle 作为其根元素。Rectangle 元素可以设置背景色等。但是，有时候我们并不允许用户设置背景色。所以，我们可以选择使用 Item 元素作为根。事实上，Item 元素作为根元素会更常见一些



/********************/QML工程结构/************************************************************/
QML 与 QWidget 交互
由于QML引擎和Qt的元对象系统的集成，使得允许将QML、JavaScript、C++三者进行混合开发。界面代码与逻辑代码分离，界面采用QML、JavaScript，逻辑采用C++。
只有QObject的子类才能将数据或函数提供给QML使用，由于QML引擎集成了Qt元对象系统，由QObject派生的所有子类的属性、方法和信号等都可以在QML中访问。QObject的子类可以有多种方式将功能暴露给QML。
* C++类可以注册为一个可实例化的QML类型，QML中直接使用这个QML类型
* C++类可以被注册为一个单例类型，QML中导入这个单例
* C++类的实例可以作为上下文属性或上下文对象嵌入到QML代码中
除了从QML中访问C++的功能，QML模块中也提供了多种方式从C++代码中操作QML对象。

1.QQmlEngine
这个类提供了一个QML引擎，管理QML文档，引擎提供了一个默认的QML上下文。创建Quick应用时，最常见的是QQmlApplicationEngine类，它是QQmlEngine的子类，它结合了QQmlEngine和QQmlComponent的功能。

2.QQmlContext
提供了对象实例化和表达式执行所需的运行时上下文，允许数据暴露给由QML引擎实例化的QML组件。
QQmlEngine engine;
QStringListModel modelData;
QQmlContext* context = engine.rootContext();
context->setContextProperty("stringModel", &modelData);

3.QQmlComponent
QML的对象类型可以在运行时使用QQmlCompontent类型进行实例化。QQmlCompontent实例既可以使用C++直接创建，也可以通过在QML代码中创建。
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

4.QQmlExpresssssion
动态执行表达式也是QML的核心概念之一。可以在C++中，利用特定的QML上下文执行JS表达式。
QQmlEngine * engine = new QQmlEngine();
QQmlComponent component(engine, QUrl::fromLocalFile(":/main.qml"));
QObject* obj = component.create();
QQmlExpresssssion* expr = new QQmlExpresssssion(engine->rootContext(), object, "width * 2");
int result = expr->evaluate().toInt();



/********************/QML 与 QWidget 交互/************************************************************/
//其它
1.使用C++属性（Q_PROPERTY）
QObject子类的所有属性都能够被QML访问。QObject子类使用Q_PROPERTY宏定义一个属性，该宏的作用是向Qt元对象系统注册类的属性。一个类型的属性就是类的数据成员，通常有一个读（READ）函数和写（WHITE）函数。
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


//QML访问C++
C++类注册到QML类型系统
QObject子类都可以注册为QML对象类型，注册成功之后，这个类就可以在QML代码中像其他对象类型一样声明和初始化。可以注册为可实例化对象类型、不可实例化对象类型、单例类型。


//C++访问QML
QML对象类型也可以在C++中被实例化，从而使C++对象可以访问其属性、函数、及对象。这是由于所有的QML对象类型，都是QObject子类，因此才能够允许QML引擎使用Qt元对象系统动态实例化任何QML对象类型。
虽然在C++中可以操作QML对象，但是不推荐，重构QML要比重构C++要容易的多，为减少后期维护成本，建议尽量减少C++端处理QML内容。
不建议使用

第一种：使用C++加载QML对象

第二种：使用对象名字访问加载的QML对象
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
