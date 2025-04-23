/********************/UI控件/************************************************************/
//常用窗口控件
QWidget：所有用户界面对象的基类，继承于QObject和QPaintDevice
QDialog：对话框窗口的基类，继承于QWidget
QMainWindow类提供一个有菜单条、工具栏、状态条的主应用程序窗口。继承于QWidget。

//QMainWindow
QMainWindow拥有自己的布局，我们可以使用QMenuBar（菜单栏）、QToolBar（工具栏）、QStatusBar（状态栏）
以及QDockWidget（悬浮窗体），布局有一个可由任何种类小窗口所占据的中心区域。


Q_OBJECT		宏定义，实现信号与槽的功能

this->CentralWidget()		//获取UI对象
ui->setupUi()				//UI界面的QMainWindow窗口框架和各种控件初始化。


//获取父控件的两种方式
MainWindow* myParent = (MainWindow*)topLevelWidget();			//顶层父控件
MainWindow* myParent = qobject_cast<MainWindow*>(parent());		//父控件



/********************/常用控件方法/************************************************************/
QObject类
void setObjectName(const QString& name)			//设置控件对象名称


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









