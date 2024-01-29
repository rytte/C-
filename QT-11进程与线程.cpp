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
void QObject::moveToThread(QThread * targetThread)

moveToThread()方法可以将QObject的派生类对象添加到线程循环队列中
使用connect关联started信号触发槽函数func()时，槽函数将在线程的事件循环队列中运行

创建线程：		//创建QObject的派生类作为任务类，将其对象放入QThread线程类对象中执行。
1、新建文件C++ Class任务类，继承QObject类
2、在新任务类中定义任务执行函数
3、在主文件中创建任务类对象以及QThread线程类对象
4、调用任务类的moveToThread()方法，将其移动到QThread线程类对象中：任务类对象->moveToThread(线程类对象)
5、使用connect关联任务执行函数：connect(线程类对象， & QThread::started，任务类对象， & 任务函数)
6、线程类对象调用start()方法开启线程


//（3）直接调用QT线程池
头文件<QThreadPool>
int activeThreadCount() const			//获取当前运行的线程数
void clear()							//清空线程池，销毁所有线程的任务队列，销毁所有线程
int maxThreadCount() const				//获取最大线程数
void start(QRunnable * runnable, int priority = 0)		//开始执行QRunnable派生类任务对象
static QThreadPool * globalInstance()	//返回全局线程池。一般情况下不会创建新的线程池，而是使用全局线程池中的线程

QRunnable类中有一个纯虚函数 virtual void run() = 0，需要在派生类中重写该函数作为任务。

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

	手动关闭线程 :
1、退出死循环
2、退出循环队列（调用quit()方法）
3、等待线程结束（调用wait()方法）