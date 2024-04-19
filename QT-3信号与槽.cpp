/********************/信号与槽/************************************************************/
//槽函数设置方法
private slots:
Connection connect(const QObject * sender, const char* signal, const QObject * receiver, const char* method, type = Qt::AutoConnection);
	//使用connect()函数连接已有函数，参数：（发送方，信号动作，接收方，连接函数，连接方式(默认为自动连接)）
	//例：connect(ui->stop_bt, &QPushButton::clicked, this, &MainWindow::myshow());

//connect 函数的第五个参数
enum ConnectionType {
	AutoConnection,		
	DirectConnection,
	QueuedConnection,
	BlockingQueuedConnection,
	UniqueConnection = 0x80
};

Qt::AutoConnection
默认值。根据 sender 和 receiver 所处线程在信号发出时作出判断。
如果在同一线程则使用 Qt::DirectConnection 连接，否则使用 Qt::QueuedConnection 连接。
判断的是发出信号这个动作所在的线程，和 sender 对象所处线程无关。

Qt::DirectConnection
槽函数会在信号发送的时候直接被调用，槽函数运行于信号发送者所在线程。
效果看上去就像是直接在信号发送位置调用了槽函数。在多线程环境下比较危险，可能会造成奔溃

Qt::QueuedConnection
槽函数在控制回到接收者所在线程的事件循环时被调用，槽函数运行于信号接收者所在线程。
发送信号之后，槽函数不会立刻被调用，等到接收者的当前函数执行完，进入事件循环之后，槽函数才会被调用。
多线程环境下一般用这个

Qt::BlockingQueuedConnection
槽函数的调用时机与 Qt::QueuedConnection 一致，不过发送完信号后发送者所在线程会阻塞，直到槽函数运行完，
在多线程间需要同步的场合可能需要这个。需要注意的是，接收者和发送者绝对不能在一个线程，否则程序会死锁

Qt::UniqueConnection
这个 flag 可以通过按位或（ | ）与以上四个结合在一起使用。
当这个flag设置时，当某个信号和槽已经连接时，再进行重复的连接就会失败，也就是避免了重复连接


//连接信号槽方式
Qt4 语法
connect(pb, SIGNAL(clicked()), this, SLOT(close()));

Qt5 语法
connect(pb, &QPushButton::clicked, this, &MainWindow::close)

函数指针
void(MainWindow:: * buttonClickSlot)() = &MainWindow::onButtonPushed;
connect(pb, &QPushButton::clicked, this, buttonClickSlot);

Lambda 表达式
connect(pb, &QPushButton::clicked, this, [=]() { this->close(); });


//sender
sender() 如果在由信号激活的插槽中调用该函数，返回指向发送信号的对象的指针，否则返回0，
该指针仅在从该对象的线程上下文调用此函数的槽执行期间有效。


//自动连接方式
1、槽函数需要设置为slots
2、定义控件，如QPushButton，并setObjectName
3、槽函数所属类的构造函数中使用 QMetaObject::connectSlotsByName(this);
4、定义槽函数 void on_对象名_信号名();


