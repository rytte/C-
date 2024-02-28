/********************/定时器/************************************************************/
//在Qt中使用定时器一般有三种方式
1、直接使用QObject类提供的定时器
2、使用QTimer类
3、仅调用一次溢出的定时器


//三种方式都可以用到的一些函数
1. 判断定时器是否正在运行：bool QTimer::isActive() const
2. 改变定时器的时间间隔：void QTimer::changeInterval(int msec)	//如果该定时器正在运行，他将被停止并重新开始，否则将会被开始。



/********************/一、直接使用QObject类提供的定时器/************************************************************/
//在需要开启定时器的地方直接调用QObject::startTimer();
int startTimer(int interval, Qt::TimerType timerType = Qt::CoarseTimer);	//该函数开启一个定时器

返回值：定时器的编号；
参数一：时间间隔，单位毫秒；
参数二：定时器的精确度：
Qt::PreciseTimer（精确的定时器，尽量保持毫秒精度，试图保持精确度在1毫秒）；
Qt::CoarseTimer（粗略的定时器，尽量保持精度在所需的时间间隔5% 范围内）；
Qt::VeryCoarseTimer（很粗略的定时器，只保留完整的第二精度，大约为500毫秒）；


//重载void QObject::timerEvent(QTimerEvent * event);
当定时器溢出时，会自动响应timerEvent()函数。
在timerEvent()函数中，通过event->timerId()来确定是哪个定时器触发的；

QTimerEvent 常用成员函数：

timerId()		//返回定时器的唯一标识符。
timerType()	//返回定时器的类型，如 Qt::CoarseTimer 或 Qt::PreciseTimer。
accept()		//标记该事件为已接受，阻止事件进一步传递。
ignore()		//忽略该事件，允许事件继续传递。


//在需要关闭定时器的地方调用killTimer();
void killTimer(int Id);	//该函数关闭一个定时器，参数为定时器的编号



/********************/二、使用QTimer类/************************************************************/
#include <QTimer>
void start(int msec)				//开启定时器，达到给定时间则产生timeout信号，参数单位为毫秒。
void stop()					//关闭定时器
void isActive()const				//判断定时器是否开启
void setInterval(int msec);		//设置定时器时间间隔

//1.用new的方式创建一个QTimer对象。
QTimer * timer = new QTimer(this);
//2.将定时器的溢出信号连接到自定义的槽函数。定时器到达时间触发时会产生一个QTimer::timeout信号。
connect(timer, &QTimer::timeout, this, &Myself::update);
//3.启动定时器。
timer->start(1000);
或者
timer->setInterval(1000); + timer->start();



/********************/三、仅调用一次溢出的定时器/************************************************************/
QTimer::singleShot(1000, this, SLOT(OnSendBreath()));

//函数原型

1.static void singleShot(int msec, const QObject * receiver, const char* member);
参数一：时间间隔，单位毫秒；
参数二：接收溢出信号的对象；
参数三：溢出信号的槽函数；

2.static void singleShot(int msec, Qt::TimerType timerType, const QObject * receiver, const char* member);
参数一：时间间隔，单位毫秒；
参数二：定时器的精确度（同上文）；
参数三：接收溢出信号的对象；
参数四：溢出信号的槽函数。



