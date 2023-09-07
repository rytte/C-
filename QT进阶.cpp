/********************/定时器和时间日期/************************************************************/
定时器到达时间触发时会产生一个QTimer::timeout信号。
//QTimer类方法
头文件<QTimer>
void start(毫秒数)				//开启定时器，达到给定时间则产生timeout信号
void stop()						//关闭定时器
void isActive()const			//判断定时器是否开启


//QTime类方法
头文件<QTime>
QTime currentTime()				//获取当前时间
QTime QTime::fromString(const QString& string, Qt::DateFormat format = Qt::TextDate)	//获取格式化时间
QString QTime::toString(const QString& format) const			//将时间转换为字符串

String T = mtime.currentTime().toString("hh-mm-ss");


//QDate类方法
头文件<QDate>
QDate currentDate();			//获取当前日期
QString toString(const QString &format)const					//将日期转换为字符串

String D = mdate.currentDate().toString("20yy-MM-dd	  dddd");



/********************/列表/************************************************************/
//QListView类
头文件<QListView>
virtual void setModel(QAbstractItemModel* model);		//在QListView列表中添加模型，模型的基类是QAbstractItemModel。

QAbstractItemModel是 QAbstractListModel, QAbstractProxyModel, QAbstractTableModel 这三个类的基类
					 QAbstractListModel 是 QStringListModel 的基类
	   所以向QListView添加模型时，可以添加 QStringListModel 的对象。这个对象保存的是 QStringList 字符串链表的对象。

void QStringListModel::setStringList(const QStringList& strings)	//向QListView列表中添加字符串列表


//QListWidget类
头文件<QListWidget>
void addItem(const QString& label)				//添加字符串
void addItem(QListWidgetItem* item)				//添加另一对象
void addItems(const QStringList& labels)		//添加字符串列表

实例：添加按钮到窗口中
QPushButton* bt = new QPushButton("按钮")		//创建新按钮
QListWidgetItem* item = new QListWidgetItem()	//创建一个模型
ui->listWidget->addItem(item)					//把模型加入到窗口中
ui->listWidget->setItemWidget(item, bt) 		//把按钮放入到窗口中

实例：添加新窗口到窗口中
form* ptr = new form							//创建自定义窗口
QListWidgetItem* item = new QListWidgetItem()	//创建一个模型
ui->listWidget->addItem(item)					//把模型放入窗口
item->setSizeHint(ptr->sizeHint())  			//把模型设置为和窗口一样的大小
ui->listWidget->setItemWidget(item, ptr)		//把按钮加入到窗口中



/********************/进程/************************************************************/
//C语言进程
fork()				//创建一个进程，复制父进程的大部分资源。
vfork()				//创建一个空进程，可以调用 exec() 函数使其执行指定程序。

//QProcess类
头文件<QProcess>
void start(调用的程序, 传入参数(字符串列表), QIODevice::OpenMode mode = ReadWrite)	//创建进程。指定程序，并传入参数。
void start(字符串命令, QIODevice::OpenMode mode = ReadWrite)						//创建进程。指定程序。
void start(QIODevice::OpenMode mode = ReadWrite)									//创建进程。已指定程序。

void kill()			//杀死进程，相当于kill -9
void terminate()	//终止进程，相当于Ctrl + C

void setProcessChannelMode(ProcessChannelMode mode)	  //进程输出端口重定向，参数是枚举类型
QProcess::ProcessState 	state() const				  //获取当前进程状态 enum ProcessState{ NotRunning, Starting, Running }



/********************/mplayer/************************************************************/
//格式
mplayer - slave - quiet - zoom - x 800 - y 480 - wid + 窗口ID  1.avi

- slave  :利用从模式打开mplayer 播放器    （只有在从模式下，才可以接受用户的命令）
- quiet  ：去除杂项信息
- zoom - x 800 - y 480   指定播放窗体的大小
- wid : 指定播放的窗口ID

//成员函数
get_time_length()  		//返回值是播放文件的长度，以秒为单位。
seek value()   			//向前查找到文件的位置播放 参数value为秒数。
get_percent_pos()		//返回文件的百分比（0--100）
get_time_pos() 			//打印出在文件的当前位置用秒表示，采用浮点数
volume <value>[abs] 	//增大 / 减小音量，或将其设置为<value>，如果[abs]不为零
例 : volume 100 1  	设置音量为100 中间的为音量的大小。



/********************/线程/************************************************************/
定时器仍然是在当前事件循环中执行，若执行时间太长，有可能造成窗口无响应。而线程是一个独立的任务，不会影响到前台的主窗口界面。

QT中创建线程有3种方法：
//（1）基于 QThread 类派生线程对象，该方法因为只有一个run()函数，因此一个线程只能执行一个任务。
头文件<QThread>
void start(QThread::Priority priority = InheritPriority)		//开启线程，默认执行虚函数run()，因此要提前重写run()函数
void quit()									//线程退出事件循环队列
void terminate()							//关闭线程（有内存泄露风险）
bool wait(unsigned long time = ULONG_MAX)	//等待线程结束-
void sleep(unsigned long secs)				//线程延时。参数：秒数

创建线程：		//使用QTread的派生类，重写其run()任务函数以执行新线程。
1、新建文件C++ Class线程类，继承QTread类
2、将新线程类的构造函数替换为QThread的构造函数
3、重写run()函数，写入你要执行的任务
4、在主文件中创建新线程类对象，并使该对象调用成员函数start()开启线程。


//（2）通过 moveToThread 来执行线程，该方法可以在一个线程中执行多个任务，可以节省资源。
头文件<QObject>
void QObject::moveToThread(QThread* targetThread)

moveToThread()方法可以将QObject的派生类对象添加到线程循环队列中
使用connect关联started信号触发槽函数func()时，槽函数将在线程的事件循环队列中运行

创建线程：		//创建QObject的派生类作为任务类，将其对象放入QThread线程类对象中执行。
1、新建文件C++ Class任务类，继承QObject类
2、在新任务类中定义任务执行函数
3、在主文件中创建任务类对象以及QThread线程类对象
4、调用任务类的moveToThread()方法，将其移动到QThread线程类对象中：任务类对象->moveToThread(线程类对象)
5、使用connect关联任务执行函数：connect(线程类对象，&QThread::started，任务类对象，&任务函数)
6、线程类对象调用start()方法开启线程


//（3）直接调用QT线程池
头文件<QThreadPool>
int activeThreadCount() const			//获取当前运行的线程数
void clear()							//清空线程池，销毁所有线程的任务队列，销毁所有线程
int maxThreadCount() const				//获取最大线程数
void start(QRunnable* runnable, int priority = 0)		//开始执行QRunnable派生类任务对象
static QThreadPool* globalInstance()	//返回全局线程池。一般情况下不会创建新的线程池，而是使用全局线程池中的线程

QRunnable类中有一个纯虚函数 virtual void run()=0，需要在派生类中重写该函数作为任务。

创建任务在线程池中执行：
1、新建文件C++ Class任务类，继承QRunnable类
2、重写run()函数，写入你要执行的任务
3、创建线程池对象，创建任务类对象
4、线程池对象调用start()方法执行任务：线程池对象->start(任务类对象)



/************************************************************/
在新类中创建自定义信号:
1、包含宏定义：在新类中添加 Q_OBJECT 宏定义，重新构建工程，若重构失败则删除build文件重新编译。
2、定义信号：使用 signals: 关键字声明发送信号的函数，该函数名就是信号名
3、发送信号：使用 emit 关键字调用 signals 声明的函数在线程任务中发送信号，该信号会发送给整个QT进程
4、接收信号：在主程序中使用connect关联信号，自定义槽函数的参数需要与 signals 声明的函数完全一致

手动关闭线程:
1、退出死循环
2、退出循环队列（调用quit()方法）
3、等待线程结束（调用wait()方法）



/********************/TCP/************************************************************/
qmake : QT += network

头文件<QTcpServer>		TCP服务器类
头文件<QTcpSocket>		TCP套接字类
bool listen(const QHostAddress& address = QHostAddress::Any, quint16 port = 0)	//绑定服务器IP地址并监听

参数：QHostAddress：主机地址类		
	  头文件<QHostAddress>
	  QHostAddress(const QString& address)

virtual QTcpSocket* nextPendingConnection()		//获取新客户端套接字
												//取出后就从QTcpServer客户端队列中删除，因此每次获取的都是最新的套接字。

qint64 	read(char* data, qint64 maxSize)
QByteArray 	read(qint64 maxSize)
QByteArray 	readAll()
qint64 	write(const char* data, qint64 maxSize)
qint64 	write(const char* data)
qint64 	write(const QByteArray& byteArray)


新客户端连接信号：signals:newConnection()
准备读取数据信号：readyRead()

void disconnectFromHost()				//客户端断开连接方法
客户端断开信号：disconnected()


服务器创建：
1、绑定监听：qmake : QT += network。创建服务器类对象，调用listen()方法绑定并监听
2、获取套接字：关联新客户端连接信号"newConnection"到槽函数，在槽函数中使用获取通信套接字
3、接收数据：关联"readyRead"信号，到自定义槽函数中使用套接字的read()方法接收。
4、发送数据：发送信息按钮设置为槽函数，使用套接字的write()方法发送数据。

virtual void connectToHost(const QString& hostName, quint16 port, QIODevice::OpenMode openMode = ReadWrite, QAbstractSocket::NetworkLayerProtocol protocol = AnyIPProtocol)
virtual void connectToHost(const QHostAddress& address, quint16 port, QIODevice::OpenMode openMode = ReadWrite)
						//发送连接请求
QHostAddress peerAddress() const		//获取当前的IP地址
quint16 peerPort() const				//获取当前的端口号


客户端创建：
1、创建套接字：qmake : QT += network。创建套接字对象。
2、连接服务器：使用套接字的方法向服务器发送连接请求。
3、接收数据：关联"readyRead"信号，到自定义槽函数中使用套接字的read()方法接收。
4、发送数据：发送信息按钮设置为槽函数，使用套接字的write()方法发送数据。


/************************************************************/
//文件传输
	发送端					  接收端
1	发送文件名和文件大小	  接收文件名，创建空文件；创建变量接收文件大小		  
2	循环读取并发送文件内容	  循环接收数据并写入文件
3	关闭文件				  关闭文件

QDataStream：数据流类。它可以关联多个字符串，组合成一个QByteArray的对象。并在移动过程中不打乱次序与属性。

//发送步骤
创建QFileinfo类对象info
info.fileName()	获取文件名
info.size()		获取文件大小

创建QFile类对象file
file.setFileName()	绑定文件
file.open()			打开文件

创建QByteArray类对象arr								//QByteArray arr
创建QDataStream类对象stream，同时传入arr			//QDataStream stream(&arr)
将文件名和文件大小写入stream						//stream << 文件名 << 文件大小
通过套接字对象的write()方法发送文件名和文件大小		//socket.write(arr)

//接收步骤
创建QByteArray类对象arr
创建QDataStream类对象stream，同时传入arr
使用套接字的readAll()方法接受数据，赋给arr			//arr = socket.readAll()
定义文件名和文件大小变量							//QString filename;		int filesize;
通过stream接收文件名和文件大小						//stream << filename << file

//可选协议
发送文件名和文件大小时，在最前面加入0x01
发送文件内容时，在前面加上0x02
发送文件结束后，发送0x03
每次接收到文件后，发送0x1000。发送方若没接收到该标志则重发
接收时校对第一段数据，选择处理程序



/********************/UDP/************************************************************/
头文件<QUdpSocket>
qint64 	writeDatagram(const char* data, qint64 size, const QHostAddress& address, quint16 port)	//发送数据
qint64 	writeDatagram(const QNetworkDatagram& datagram)
qint64 	writeDatagram(const QByteArray& datagram, const QHostAddress& host, quint16 port)

qint64 	readDatagram(char* data, qint64 maxSize, QHostAddress* address = nullptr, quint16* port = nullptr)	//接收数据

广播：直接调用writeDatagram()方法，写入广播地址。QUdpSocket类默认具有广播属性。

组播：
bool joinMulticastGroup(const QHostAddress& groupAddress)		//加入组播
bool joinMulticastGroup(const QHostAddress& groupAddress, const QNetworkInterface& iface)

bool leaveMulticastGroup(const QHostAddress& groupAddress)		//退出组播
bool leaveMulticastGroup(const QHostAddress& groupAddress, const QNetworkInterface& iface)

bool bind(const QHostAddress& address, quint16 port, QAbstractSocket::BindMode mode)	//绑定端口号



/********************/HTTP协议/************************************************************/
QT += network
头文件<QNetworkAccessManager>		网络访问管理器类：管理http的发送请求和接收响应
头文件<QNetworkRequest>				网络请求类：用于放入请求内容
头文件<QNetWorkReply>				网络响应类：用于存放响应信息

QNetworkRequest(const QUrl& url = QUrl())				//构造函数，传入参数为url网址
QNetworkReply* get(const QNetworkRequest& request)		//参数为请求内容
结束响应信号：void finished(QNetworkReply* reply)

http通信流程：
1、创建http的管理类对象QNetworkAccessManager
2、创建请求对象QNetworkRequest：url:是www网络上信息资源的唯一地址。
3、管理类对象调用get()方法发起http请求。
4、通过finished信号关联上槽函数，在槽函数中获取http的内容



/********************/JSON/************************************************************/
头文件<QJsonDocument>		json文本类。
static QJsonDocument QJsonDocument::fromJson(const QByteArray& json, QJsonParseError* error = nullptr)
				//用于检查数据是否符合json格式	  参数一：传入数据		参数二：错误管理类对象，是一个枚举类型
QJsonObject object()const		//将json数据转换成json对象返回。
QByteArray toJson()const		//把文本内容转换成字符串返回。


头文件<QJsonObject>			json对象类。
QJsonValue value(const QString& key) const			//通过键查找json值返回。
QJsonObject::iterator 	insert(const QString& key, const QJsonValue& value)		//加入一组键值对

头文件<QJsonValue>			json数据类型。
QJsonObject toObject() const						//转换为json对象返回
QString toString() const							//转换为字符串
QJsonArray toArray() const							//转换为json数组

头文件<QJsonArray>			json数组类
QJonValue at(int i)const							//下标索引对应元素
int count()const									//获取数组的成员数
void insert(int i, const QJsonValue& value)			//在下标i的位置插入元素


/************************************************************/
//实例
QByteArray arr = reply->readAll();

QJsonDocument doc;						//创建Json文本类对象

QJsonParseError err;					//创建Json错误管理结构体

doc = QJsonDocument::fromJson(arr, &err);		//向文本对象中导入数据,需要赋值
if (err.error != QJsonParseError::NoError)		//判断数据是否符合json格式
{
    ui->textBrowser->setText("json数据不匹配");
    return;
}

//具体解析转换的格式，必须与你所直到的格式是相同的
//在Json数据匹配的情况下，开始解析。先文本转换成Json对象
QJsonObject obj = doc.object();

//已知键值"time",获取它所在的对组
QJsonValue time_value = obj.value("time");
ui->textBrowser->append(time_value.toString());


//已知键值"cityInfo"对应的是多个对组，那么实值应该是一个Json对象
QJsonValue cityInfo_value = obj.value("cityInfo");			//先拿到实值
QJsonObject cityInfo_obj = cityInfo_value.toObject();		//把实值转换成一个对象
QJsonValue  city_value = cityInfo_obj.value("city");		//再在对象中通过键值获取数值
ui->textBrowser->append(city_value.toString());

//QJsonValue  parent_value = cityInfo_obj.value("parent");
ui->textBrowser->append(cityInfo_obj.value("parent").toString());

//已知data键值下有forecast键值，再往下是一个数组，每个数组又是一个对象

//拿到data键值下的对象
QJsonObject data_obj = obj.value("data").toObject();
//再拿到forecast键值下的数组
QJsonArray  forecast_arr = data_obj.value("forecast").toArray();

//遍历数组
int i;
QJsonObject  temp;
QString high, low;
//====for循环====
//    for(i = 0; i < forecast_arr.count(); i++)
//    {
//        temp = forecast_arr.at(i).toObject();

//        high = temp.value("high").toString();
//        low  = temp.value("low").toString();

//        ui->textBrowser->append(high + low);
//    }

//=====迭代器====
for (QJsonArray::const_iterator it = forecast_arr.begin(); it != forecast_arr.end(); it++)
{
    temp = it->toObject();

    high = temp.value("high").toString();
    low = temp.value("low").toString();

    ui->textBrowser->append(high + low);
}







