/********************/QT基础/************************************************************/
QMainWindow类：是窗口的框架，包含：MenuBar菜单栏，ToolBar工具栏，StatusBar状态栏，CentralWidget中央控件。
头文件：#include<QMainWindow>
qmake： QT += widgets

UI底层界面就是CentralWidget对象。

Q_OBJECT		宏定义，实现信号与槽的功能

ui->setupUi		UI界面的QMainWindow窗口框架和各种控件初始化。

Ctrl + F		在帮助索引中搜索相关内容。

QString：string的派生类
1、方法fromUtf8()	将字符串转换为uft - 8格式。
2、格式化输出		QString str = QString("今天是%1年%2月%3日").arg(2023).arg(7).arg(5)

#include <QDebug>
QT中使用 qDebug() 函数代替 cout 进行输出调试。

QT工程编译后会生成一个build文件，程序在这里执行。


void setWindowTitle(const QString&)          //设置窗口标题
void setWindowIcon(Icon(":/资源图片名"))     //设置窗口图标




/********************/常用控件方法/************************************************************/
每种控件方法通常有两个或三个重载，以geometry()方法为例：

const QRect & geometry() const							//获取位置和尺寸，返回引用
void		 setGeometry(int x, int y, int w, int h)	//设置位置和尺寸（传入数字参数）
void		 setGeometry(const QRect&)					//设置位置和尺寸（传入已有对象）


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



/********************/样式表/************************************************************/

//资源
工程中添加 QT Resource File 文件。在该文件中添加资源路径。

样式设计：
color : "#00ff00";								//设置对象颜色
border-image:url(: / 1.jpg);					//设置背景图片，图片随控件大小缩放
background-image:url(: / 1.jpg);				//设置背景图片，图片不随控件大小缩放
QLineEdit{ border:10px solid#ff00ff };			//LineEdit设置边框颜色
QLineEdit{ border-radius:5px solid#ff00ff };	//LineEdit设置边框圆角

派生类对象：
类名#对象名{ 样式设计 }				//UI界面中，当前对象的派生类对象，使用此格式设置。

动作样式：
类名#对象名:动作名{ 样式设计 }		//动作名：例如要在按键按下时显示图片：QPushButton#login_bt:pressed{ border-image:url(:/1.jpg); }

代码实现：
ui->对象名->setStyleSheet("样式设计""样式设计"...)		//可以同时设计多个样式，也可以使用字符串拼接后传入一个字符串。


复选框样式表：
remember->setStyleSheet("QCheckBox{color:rgb(150,150,150);}"                                        //字体框
                        "QCheckBox::indicator::unchecked{ border:2px solid#dddddd;border-radius:3px; background-color:white; }"                  //未选中
                        "QCheckBox::indicator::checked{ border:2px solid#dddddd; border-radius:3px; background-image:url(:/png/tick.png); }");   //已选中


/********************/信号与槽/************************************************************/
//槽函数设置方法（二选一）
函数声明:
private slots:
1、	void on_对象名_动作名()				//使用默认名称定义槽函数
2、 Connection connect(const QObject * sender, const char* signal, const QObject * receiver, const char* method, type = Qt::AutoConnection)
				//使用connect()函数连接已有函数，参数：（发送方，信号动作，接收方，连接函数，连接方式(默认为自动连接)）
				//例：connect(ui->stop_bt, &QPushButton::clicked, this, &MainWindow::myshow());

	设计师界面类模版：
	MainWindow：继承QMainWindow，创建全新的窗口界面。
	Widget：	继承QWidget，覆盖原窗口上的UI，不会新建窗口。

窗口切换:
1、新建文件（设计师界面类）创建新窗口
2、包含新窗口头文件
3、设置槽函数
4、槽函数触发：创建新界面对象，同时传入旧界面指针this或引用，p->show()显示新窗口，使用this->hide()方法隐藏旧窗口。

旧窗口信息传入新窗口:
方法一: 在旧窗口的槽函数中利用新窗口对象指针p调用新窗口处理信息的成员函数，传入信息对象或字符串。
方法二: 重载新窗口的构造函数，在创建新窗口对象时传入信息对象或字符串。

销毁新窗口 :
this->parentWidget()->show()	返回上一级窗口
delete this						销毁窗口



/********************/对话框/************************************************************/
//1、消息盒子：消息窗口
头文件<QMessageBox>
information(父窗口指针，窗口标签，文本内容，按钮(给定枚举类型)，默认按钮(默认为无))		//返回值为点击的按钮
information(this, "消息盒子", "注册成功", QMessageBox::Yes, QMessageBox::No)

图标：参数都一样。
感叹号information，返回值为 StandardButton 类型
问号question，返回值为 int 类型
警告叹号warning，返回值为 int 类型


//2、文件对话框：选择文件
头文件<QFileDialog>
getOpenFileName(父窗口指针，窗口标签，打开的目录，文件类型过滤，过滤选项)		//返回值为文件名字符串
getOpenFileName(this, "文件对话框", "../", "*.cpp *.h")							//当前目录"./"为工程build文件目录
									//"*.cpp *.h"为同时过滤出*cpp和*h；"text(*.cpp);;file(*.h);;"为可选择其中一种。
getOpenFileNames()方法参数与上面相同，但返回的是一个含所有选择文件的字符串链表。


//3、字体对话框：设置字体大小和样式
头文件<QFontDialog>
getFont(传入bool类型参数(记录选择确认还是取消)，传入的Font对象(打开对话框时字体的默认选项)，父窗口指针，窗口标签)
QFont f = ui->label->font();
bool flag;
f = getFont(&flag, f, this, "字体对话框")


//4、颜色对话框：选择颜色获取颜色数据
头文件<QColorDialog>
getColor(颜色对象(打开对话框时的默认颜色默认为白色)，父窗口指针，窗口标签)		//返回QColor颜色对象
QColor color = getColor()
color.blue()		//获取蓝色数据0~255
color.grren()		//获取绿色数据0~255
color.red()			//获取红色数据0~255
color.name()		//获取全色数据"#000000"~"#ffffff"


//5、输入对话框
头文件<QInputDialog>
getText(父窗口指针，窗口标签，提示文本，设置输入模式(echomode默认普通模式)，文本，传入bool类型参数(记录选择确认还是取消))	//返回输入内容
QString str = getText(this, "输入对话框", "请输入账号")

//6、自定义对话框
头文件<QDialog>
自定义对话框是以Dialog类为基础直接设计对话框
QDialog的基类是QWidget

QDialog* d = new QDialog(this);
d->resize(400, 200);
QPushButton* bt = new QPushButton("ok", d);			//可以在对话框上创建按钮等控件
bt->setGeometry(100, 50, 100, 60);					//调整控件位置。自行设定控件槽函数
d->show();		//可替换为exec()方法。exec是进入到对话框的事件循环队列，无法点击其它窗口，直到退出。show是显示对话框，可以点击其它窗口。



/********************/文件/************************************************************/
QFile类方法
头文件<QFile>
virtual bool  open(QIODevice::OpenMode mode)
qint64 		  read(char* data, qint64 maxSize)
QByteArray 	  read(qint64 maxSize)
QByteArray 	  readAll()
qint64 		  readLine(char* data, qint64 maxSize)
qint64 		  rite(const char* data, qint64 maxSize)
qint64 		  rite(const char* data)
qint64 		  rite(const QByteArray& byteArray)
virtual void  close()
bool 		  isOpen() const

QFileinfo类方法
头文件<QFileInfo>
QString   fileName() const		//只有文件名
QString   filePath() const		//文件名+绝对路径
QString   path() const			//绝对路径
qint64    size() const			//文件大小


QFileInfo info(ui->filename_edit->text())	//定义文件信息对象，路径通过构造函数传入
QFile file									//定义无名文件对象
file.setFileName(info.filePath())			//设置文件名
file.open(QIODevice::ReadWrite)			    //读写方式打开文件


QPixmap类方法
头文件<QPixmap>
bool QPixmap::loadFromData(const QByteArray& data, const char* format = nullptr, Qt::ImageConversionFlags flags = Qt::AutoColor)
                //导入图片数据，参数一：数据     参数二：数据大小（若不是指针类型则不用填此参数）
QPixmap QPixmap::scaled(int width, int height) const  //设置图片大小，返回修改后的图片对象。例：对象名=对象名.scaled(ui->label->size())


/********************/布局管理器/************************************************************/
使用布局管理器后相关控件的geometry失效，只能通过策略模式来适应布局管理器。


1、水平布局管理器 QHBoxLayout		头文件 < QHBoxLayout>
2、垂直布局管理器 QVBoxLayout		头文件 < QVBoxLayout>
3、栅栏布局管理器 QGridLayout		头文件 < QGridLayout>
4、弹簧spacer						头文件 < QSpacerItem>

优先级：minimumSize / maximumSize > 弹簧spacer > 策略模式sizepolicy


布局管理器对象成员：
addWidget(控件对象)						//添加控件
addSpacer(弹簧对象)						//添加弹簧

//实例：
QSpacerItem * p = new QSpacerItem(40, 40, Expanding, Expanding);			//创建弹簧指针，构造函数传参
QHBoxLayout* hbox = new QHBoxLayout[2];
hbox[0]->addSpacer(p);								//向水平布局管理器中添加弹簧对象
hbox[0]->addWidget(&bt1);							//向水平布局管理器中添加控件对象
hbox[0]->addSpacer(p);
hbox[0]->addWidget(&bt2);
hbox[0]->addSpacer(p);
hbox[1]->addSpacer(p);
hbox[1]->addWidget(&bt3);
hbox[1]->addSpacer(p);
hbox[1]->addWidget(&bt4);
hbox[1]->addSpacer(p);
QVBoxLayout* vbox = new QVBoxLayout;
vbox->addLayout(&hbox[0]);							//将水平布局管理器添加到垂直布局管理器中
vbox->addLayout(&hbox[1]);
ui->centralwidget->setLayout(&vbox);				//将垂直布局管理器加入到当前窗口


void setSizePolicy(水平策略, 垂直策略)				//控件的策略模式设置方法
void serMaximumSize(最大长度，最大宽度)				//设置最大尺寸
void serMinimumSize(最小长度，最小宽度)				//设置最小尺寸


//栅栏布局管理器实例：
G = new QGridLayout;                    //创建栅栏布局管理器

for (int x = 0; x < 4; x++)             //加入到栅栏布局管理器中
{
    for (int y = 0; y < 4; y++)
    {
        G->addWidget(&bt[4 * y + x], y, x);
        bt[4 * y + x].setText(QString("%1").arg(4 * y + x));                            //设置按钮文本

        bt[4 * y + x].setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);        //设置按钮的策略模式
        bt[4 * y + x].setMaximumSize(100, 100);

        QFont f;                                //把文字字体设置
        f.setPointSize(16);
        bt[4 * y + x].setFont(f);

        connect(&bt[4 * y + x], &QPushButton::clicked, this, &MainWindow::myshow);      //设置关联的槽函数
    }
    ui->centralWidget->setLayout(G);            //把布局管理器加入到窗口
}

void MainWindow::myshow()                       //打印按钮对应的数字
{
    QPushButton* ptr = dynamic_cast<QPushButton*>(sender());        //获取信号发送对象的指针
    qDebug() << ptr->text();
}



