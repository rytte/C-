/********************/QMainWindow/************************************************************/
常用的窗口 - QWidget、QDialog、QMainWindow
QWidget继承于QObject和QPaintDevice，QDialog和QMainWindow则继承于QWidget

QWidget类是所有用户界面对象的基类。
QDialog类是对话框窗口的基类。
QMainWindow类提供一个有菜单条、工具栏、状态条的主应用程序窗口。

QMainWindow拥有自己的布局，我们可以使用QMenuBar（菜单栏）、QToolBar（工具栏）、QStatusBar（状态栏）
以及QDockWidget（悬浮窗体），布局有一个可由任何种类小窗口所占据的中心区域。


#include<QMainWindow>
qmake： QT += widgets



UI底层界面就是CentralWidget对象。

Q_OBJECT		宏定义，实现信号与槽的功能

ui->setupUi		UI界面的QMainWindow窗口框架和各种控件初始化。

Ctrl + F		在帮助索引中搜索相关内容。


QT工程编译后会生成一个build文件，程序在这里执行。


void setWindowTitle(const QString&)          //设置窗口标题
void setWindowIcon(Icon(":/资源图片名"))     //设置窗口图标



/********************/常用控件方法/************************************************************/
每种控件方法通常有多个重载，以geometry()方法为例：

const QRect& geometry() const				//获取位置和尺寸，返回引用
void	setGeometry(int x, int y, int w, int h)		//设置位置和尺寸（传入数字参数）
void	setGeometry(const QRect&)				//设置位置和尺寸（传入已有对象）


/************************************************************/
QObject类
void setObjectName(const QString& name)			//设置控件对象名称


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
String str = qstr.toStdString();	  //QString转换为String
String str = qstr.toUtf8.constData(); //QString转换为String
String->QString
String str;
QString qstr = QString::fromStdString(str); //String转换为QString
QString转换为String中文输出乱码解决
QString path;
//QString转String 乱码解决
String cstr = String((const char*)path.toLocal8Bit());


//字符编码
UTF8(UTF8)
Local8Bits(本地系统的编码:GBK、ISO - 8859 - 1等)
Latin1(ANSI)








//命名冲突
::write()
类中有和标准库函数同名的函数，
加上::使用标准库函数
不加::使用类中成员函数


//获取父控件的两种方式
MainWindow * myParent = (MainWindow*)topLevelWidget();			//顶层父控件
MainWindow* myParent = qobject_cast<MainWindow*>(parent());		//父控件


//QT 使用全局缩放进行全分辨率适配
qputenv("QT_SCALE_FACTOR", "2.0");
注意：
1、这句代码需要放在QApplication实例初始化之前。
2、缩放系数必须大于等于1.0，不然会出现一些奇怪的问题。而且必须是小数形式的字符串。


全局缩放引发了两个问题：
1、图片放大的时候有锯齿。
2、字体在缩放的时候质量不太好。

解决方法：
调整图片缩放质量
QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

文字质量
这需要使用另外一个东西”qt.conf“。
内容如下。
[Platforms]
WindowsArguments = fontengine = freetype

将这个文件放入程序的资源中。路径为":/qt/etc/qt.conf"