/********************/信号与槽/************************************************************/
//槽函数设置方法（二选一）
函数声明 :
private slots:
1、	void on_对象名_动作名()				//使用默认名称定义槽函数
2、 Connection connect(const QObject * sender, const char* signal, const QObject * receiver, const char* method, type = Qt::AutoConnection)
	//使用connect()函数连接已有函数，参数：（发送方，信号动作，接收方，连接函数，连接方式(默认为自动连接)）
	//例：connect(ui->stop_bt, &QPushButton::clicked, this, &MainWindow::myshow());

设计师界面类模版：
MainWindow：继承QMainWindow，创建全新的窗口界面。
Widget：	继承QWidget，覆盖原窗口上的UI，不会新建窗口。

窗口切换 :
1、新建文件（设计师界面类）创建新窗口
2、包含新窗口头文件
3、设置槽函数
4、槽函数触发：创建新界面对象，同时传入旧界面指针this或引用，p->show()显示新窗口，使用this->hide()方法隐藏旧窗口。

旧窗口信息传入新窗口 :
方法一 : 在旧窗口的槽函数中利用新窗口对象指针p调用新窗口处理信息的成员函数，传入信息对象或字符串。
方法二 : 重载新窗口的构造函数，在创建新窗口对象时传入信息对象或字符串。

销毁新窗口 :
this->parentWidget()->show()	返回上一级窗口
delete this						销毁窗口



sender() 如果在由信号激活的插槽中调用该函数，返回指向发送信号的对象的指针，否则返回0，
该指针仅在从该对象的线程上下文调用此函数的槽执行期间有效。


::write()
类中有和标准库函数同名的函数，
加上::使用标准库函数
不加::使用类中成员函数


