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



/********************/页面切换/************************************************************/
设计师界面类模版：
MainWindow：继承QMainWindow，创建全新的窗口界面。
Widget：	继承QWidget，覆盖原窗口上的UI，不会新建窗口。

窗口切换 :
1、新建文件（设计师界面类）创建新窗口
2、包含新窗口头文件
3、设置槽函数
4、槽函数触发：创建新界面对象，同时传入旧界面指针this或引用，p->show()显示新窗口，使用this->hide()方法隐藏旧窗口。

旧窗口信息传入新窗口 :
方法一: 在旧窗口的槽函数中利用新窗口对象指针p调用新窗口处理信息的成员函数，传入信息对象或字符串。
方法二 : 重载新窗口的构造函数，在创建新窗口对象时传入信息对象或字符串。

销毁新窗口 :
this->parentWidget()->show()	返回上一级窗口
delete this						销毁窗口

