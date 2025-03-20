/********************/信号与槽/************************************************************/
//槽函数设置方法
private slots:
Connection connect(const QObject * sender, const char* signal, const QObject * receiver, const char* method, type = Qt::AutoConnection);
	//使用connect()函数连接已有函数，参数：（发送方，信号动作，接收方，连接函数，连接方式(默认为自动连接)）
	//例：connect(ui->stop_bt, &QPushButton::clicked, this, &MainWindow::myshow());

//connect 函数的第五个参数
enum ConnectionType {
	AutoConnection,				//（默认值）如果信号和槽在同一线程，使用直接连接（Qt::DirectConnection）；如果不在同一线程，使用队列连接（Qt::QueuedConnection）。
	DirectConnection,			// 无论信号和槽是否在同一线程中，信号都会立即调用槽函数，这对于需要直接响应的情况很有用。多线程环境下可能会造成奔溃。
	QueuedConnection,			// 当信号和槽不在同一线程时，信号会被放入接收者的事件队列，直到接收者的事件循环处理它。适用于多线程，保证信号会在接收者的线程中执行槽函数。
	BlockingQueuedConnection,	// 与 QueuedConnection 类似，但发送信号的线程会被阻塞，直到槽函数执行完毕。需要注意的是，接收者和发送者绝对不能在一个线程，否则程序会死锁。
	UniqueConnection = 0x80		// 这个 flag 可以通过按位或（ | ）与以上四个结合在一起使用。当这个flag设置时，当某个信号和槽已经连接时，再进行重复的连接就会失败，也就是避免了重复连接
};



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


//自动连接（不使用connect）
1、槽函数需要设置为slots
2、定义控件，如QPushButton，并setObjectName
3、槽函数所属类的构造函数中使用 QMetaObject::connectSlotsByName(this);
4、定义槽函数 void on_对象名_信号名();


