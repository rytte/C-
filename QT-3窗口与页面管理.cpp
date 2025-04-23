/********************/自定义窗口界面/************************************************************/

void setWindowTitle(const QString&)          //设置窗口标题
void setWindowIcon(Icon(":/资源图片名"))      //设置窗口图标


//无边框：设置窗口标志为无边框
setWindowFlags(Qt::FramelessWindowHint | windowFlags());

关于WindowFlags枚举值很多，例如其中有一个WindowStaysOnTopHint，可以让窗体位于所有界面之上，

//声明
bool m_isDragging;
QPoint m_lastMousePos;

//关闭窗口
void MainWindow::slot_closebt_clicked()
{
	this->close();
}

//最小化窗口
void MainWindow::slot_minbt_clicked()
{
	this->showMinimized();
}

//鼠标点击事件，识别鼠标左键按下操作，并记录当前位置
void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_lastMousePos = event->pos();
        m_isDragging = true;
    }
}

//鼠标移动事件，计算鼠标光标的坐标变化，并借助move事件使界面进行相同的移动。如果鼠标没有松开，需要判定鼠标一直在按钮内
void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (m_isDragging && (event->buttons() & Qt::LeftButton))
        move(pos() + event->pos() - m_lastMousePos);        // 计算窗口的新位置并移动窗口
}

//鼠标释放事件
void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        m_isDragging = false;               // 鼠标释放，停止拖动
}



/********************/页面切换/************************************************************/
设计师界面类模版：
MainWindow：继承QMainWindow，创建全新的窗口界面。
Widget：	继承QWidget，覆盖原窗口上的UI，不会新建窗口。

//窗口切换
1、新建文件（设计师界面类）创建新窗口
2、包含新窗口头文件
3、设置槽函数
4、槽函数触发：创建新界面对象，同时传入旧界面指针this或引用，p->show()显示新窗口，使用this->hide()方法隐藏旧窗口。

//旧窗口信息传入新窗口
方法一: 在旧窗口的槽函数中利用新窗口对象指针p调用新窗口处理信息的成员函数，传入信息对象或字符串。
方法二: 重载新窗口的构造函数，在创建新窗口对象时传入信息对象或字符串。

//销毁新窗口
this->parentWidget()->show()	//返回上一级窗口
delete this						//销毁窗口

