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





/********************/自定义窗口界面/************************************************************/
//无边框：设置窗口标志为无边框
setWindowFlags(Qt::FramelessWindowHint | windowFlags());

关于WindowFlags枚举值很多，其中有一个WindowStaysOnTopHint，可以让窗体位于所有界面之上，
类似于QQ主面板，一打开就在所有软件之上 - 比较霸道。

//声明
QPoint windowPos;           //窗口位置
QPoint mousePos;            //鼠标位置
QPoint dPos;			 //窗口移动后位置

//关闭窗口
void ListWindow::slot_closebt_clicked()
{
	this->close();
}

//最小化窗口
void ListWindow::slot_minbt_clicked()
{
	this->showMinimized();
}

//通过鼠标点击事件，识别鼠标左键按下操作，并记录当前位置
void ListWindow::mousePressEvent(QMouseEvent* event)
{
	this->windowPos = this->pos();			// 获得部件当前位置
	this->mousePos = event->globalPos();		// 获得鼠标位置
	this->dPos = mousePos - windowPos;		// 移动后所在的位置
}

//通过鼠标移动事件，计算鼠标光标的坐标变化，并借助move事件使界面进行相同的移动。如果鼠标没有松开，需要判定鼠标一直在按钮内
void ListWindow::mouseMoveEvent(QMouseEvent* event)
{
	this->move(event->globalPos() - this->dPos);
}