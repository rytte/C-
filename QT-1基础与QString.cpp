/********************/QT基础/************************************************************/
Qt Designer被称为Qt设计师，用于设计和构建图形用户界面（Qt Widgets）。也就是可视化图形设计界面。
Qt Linguist被称为Qt语言家。主要任务是读取翻译文件、为翻译人员提供友好的翻译界面，是用于界面国际化的重要工具。它能帮助你很容易读懂C++语言。
Qt Assistant被称为Qt助手（也就是帮助模式），是Qt自带的一款可定制、可重新发行的帮助文件浏览器。它支持HTML文件，用户可以利用其定制自己的功能强大的帮助文档浏览器。



//文本编辑宏
当你在代码编辑器中打开一个文件，可以记录键盘序列作为宏。然后，你可以运行重复序列的宏。可以保存最新的宏并分配快捷键运行，或从定位器运行。


//QT库主要分为以下模块
Qt Core模块：这是Qt库的核心部分，提供了许多基础的功能，如事件循环、文件处理、数据流、字符串处理、线程管理、正则表达式等。这些都是任何Qt应用程序都会使用到的基本功能。
Qt GUI模块：这个模块提供了图形用户界面（GUI）相关的功能，包括绘制、事件处理、窗口管理、控件等。这个模块是构建图形用户界面应用程序的基础。
Qt Widgets模块：这个模块提供了一系列预制的UI控件，如按钮、文本框、列表框等，使得开发者可以快速地构建出用户界面。
Qt Network模块：这个模块提供了网络编程的功能，包括TCP / IP和UDP套接字、HTTP、SSL / TLS等。这使得开发者可以使用Qt库来开发网络应用程序。
Qt SQL模块：这个模块提供了数据库操作的功能，包括SQL查询、数据库连接管理等。这使得开发者可以使用Qt库来开发数据库应用程序。
Qt Multimedia模块：这个模块提供了处理多媒体内容的功能，如音频、视频、图像等。
Qt Quick模块：这个模块提供了用于开发动态和流畅的用户界面的功能，特别是使用QML（Qt Modeling Language）编写的界面。





/********************/QT元对象系统/************************************************************/
QObject 类不仅是所有 Qt 对象的基类，还是“Qt 中的对象模型（Object Model）”的核心类。
我们知道元对象模型最重要的功能就是“信号 - 槽”机制，该机制使 Qt 对象之间可以进行无缝的交互。
那么只要是 QObject 及其子类，都可以使用信号 - 槽机制。

//QObject特性
1、QObject如果有对象，必须在同一线程中
2、QObject类的成员变量是否为其子对象问题
3、禁用拷贝构造函数，禁用赋值运算符


QObject 对象是具有线程亲和性（Thread Affinity）的。什么意思呢？
就是这个类创建的对象收到信号或者事件的时候，处理信号的槽函数以及处理事件的某某函数也是和这个对象在一个线程中运行。

Qt对标准C++增加了一些功能：signals, slots, object properties, events, event filters, string translation, timers, object trees, guarded pointers, dynamic cast.

我们知道在各种容器中能以value方式存放的类型，必须有默认的构造函数，拷贝构造函数和赋值操作。
由于QObject及所有继承自它的子类都没有提供拷贝构造和赋值操作，当我们使用QList<QObject>时，编译器就会报错。
如果我们要在容器中存储这中类型的对象，我们就要使用它们的指针。如QList<QObject*>


https://zhuanlan.zhihu.com/p/43598693
https://blog.csdn.net/dengjin20104042056/article/details/115272771


/********************/常用控件方法/************************************************************/
每种控件方法通常有多个重载，以geometry()方法为例：

const QRect & geometry() const				//获取位置和尺寸，返回引用
void	setGeometry(int x, int y, int w, int h)		//设置位置和尺寸（传入数字参数）
void	setGeometry(const QRect&)				//设置位置和尺寸（传入已有对象）


/************************************************************/
QObject类
void setObjectName(const QString & name)			//设置控件对象名称


QWidget类
void setGeometry()				//设置位置和尺寸
void setSizePolicy()				//设置策略模式
void setMinimumSize()			//设置最小尺寸
void setMaximumSize()			//设置最大尺寸
void setFont()					//设置字体。需要另外定义字体类QFont，设置好进行传入。


/************************************************************/
标签QLabel：
#include<QLabel>
void setText()					//设置标题文本
void setAlignment()				//设置对齐，多个参数需要使用"|"符号隔开。


编辑行QLineEdit：
#include<QLineEdit>
void setEchoMode()				//设置输出模式
void setPlaceholderText()		//设置提示词


按钮QPushButton：
#include<QPushButton>



/********************/QString/************************************************************/
QString：string的派生类
1、方法fromUtf8()	将字符串转换为uft - 8格式。
2、格式化输出		QString str = QString("今天是%1年%2月%3日").arg(2023).arg(7).arg(5)



QString->String
QString qstr;
String str = qstr.toStdString(); //QString转换为String
String->QString
String str;
QString qstr = QString::fromStdString(str); //String转换为QString
QString转换为String中文输出乱码解决
QString path;
//QString转String 乱码解决
String cstr = String((const char*)path.toLocal8Bit());



/********************/QLabel/************************************************************/

setPixmap()
clear();


