/********************/QT基础/************************************************************/
QMainWindow类：是窗口的框架，包含：MenuBar菜单栏，ToolBar工具栏，StatusBar状态栏，CentralWidget中央控件。
头文件：#include<QMainWindow>
qmake： QT += widgets

UI底层界面就是CentralWidget对象。

Q_OBJECT		宏定义，实现信号与槽的功能

ui->setupUi		UI界面的QMainWindow窗口框架和各种控件初始化。

Ctrl + F		在帮助索引中搜索相关内容。


QT工程编译后会生成一个build文件，程序在这里执行。


void setWindowTitle(const QString&)          //设置窗口标题
void setWindowIcon(Icon(":/资源图片名"))     //设置窗口图标




Qt Designer被称为Qt设计师，用于设计和构建图形用户界面（Qt Widgets）。也就是可视化图形设计界面。
Qt Linguist被称为Qt语言家。主要任务是读取翻译文件、为翻译人员提供友好的翻译界面，是用于界面国际化的重要工具。它能帮助你很容易读懂C++语言。
Qt Assistant被称为Qt助手，是Qt自带的一款可定制、可重新发行的帮助文件浏览器。它支持HTML文件，用户可以利用其定制自己的功能强大的帮助文档浏览器。


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
void setSizePolicy()			//设置策略模式
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


