/********************/TCP/************************************************************/
qmake : QT += network

头文件<QTcpServer>		TCP服务器类
头文件<QTcpSocket>		TCP套接字类
bool listen(const QHostAddress & address = QHostAddress::Any, quint16 port = 0)	//绑定服务器IP地址并监听

参数：QHostAddress：主机地址类
头文件<QHostAddress>
QHostAddress(const QString & address)

virtual QTcpSocket * nextPendingConnection()		//获取新客户端套接字
//取出后就从QTcpServer客户端队列中删除，因此每次获取的都是最新的套接字。

qint64 	read(char* data, qint64 maxSize)
QByteArray 	read(qint64 maxSize)
QByteArray 	readAll()
qint64 	write(const char* data, qint64 maxSize)
qint64 	write(const char* data)
qint64 	write(const QByteArray & byteArray)


新客户端连接信号：signals:newConnection()
准备读取数据信号：readyRead()

void disconnectFromHost()				//客户端断开连接方法
客户端断开信号：disconnected()


服务器创建：
1、绑定监听：qmake : QT += network。创建服务器类对象，调用listen()方法绑定并监听
2、获取套接字：关联新客户端连接信号"newConnection"到槽函数，在槽函数中使用获取通信套接字
3、接收数据：关联"readyRead"信号，到自定义槽函数中使用套接字的read()方法接收。
4、发送数据：发送信息按钮设置为槽函数，使用套接字的write()方法发送数据。

virtual void connectToHost(const QString & hostName, quint16 port, QIODevice::OpenMode openMode = ReadWrite, QAbstractSocket::NetworkLayerProtocol protocol = AnyIPProtocol)
virtual void connectToHost(const QHostAddress & address, quint16 port, QIODevice::OpenMode openMode = ReadWrite)
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
qint64 	writeDatagram(const char* data, qint64 size, const QHostAddress & address, quint16 port)	//发送数据
qint64 	writeDatagram(const QNetworkDatagram & datagram)
qint64 	writeDatagram(const QByteArray & datagram, const QHostAddress & host, quint16 port)

qint64 	readDatagram(char* data, qint64 maxSize, QHostAddress * address = nullptr, quint16 * port = nullptr)	//接收数据

广播：直接调用writeDatagram()方法，写入广播地址。QUdpSocket类默认具有广播属性。

组播：
bool joinMulticastGroup(const QHostAddress & groupAddress)		//加入组播
bool joinMulticastGroup(const QHostAddress & groupAddress, const QNetworkInterface & iface)

bool leaveMulticastGroup(const QHostAddress & groupAddress)		//退出组播
bool leaveMulticastGroup(const QHostAddress & groupAddress, const QNetworkInterface & iface)

bool bind(const QHostAddress & address, quint16 port, QAbstractSocket::BindMode mode)	//绑定端口号



/********************/HTTP协议/************************************************************/
QT += network
头文件<QNetworkAccessManager>		网络访问管理器类：管理http的发送请求和接收响应
头文件<QNetworkRequest>				网络请求类：用于放入请求内容
头文件<QNetWorkReply>				网络响应类：用于存放响应信息

QNetworkRequest(const QUrl & url = QUrl())				//构造函数，传入参数为url网址
QNetworkReply * get(const QNetworkRequest & request)		//参数为请求内容
结束响应信号：void finished(QNetworkReply * reply)

http通信流程：
1、创建http的管理类对象QNetworkAccessManager
2、创建请求对象QNetworkRequest：url:是www网络上信息资源的唯一地址。
3、管理类对象调用get()方法发起http请求。
4、通过finished信号关联上槽函数，在槽函数中获取http的内容