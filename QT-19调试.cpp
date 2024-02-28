/********************/QDebug/************************************************************/
#include <QDebug>

//占位方式输出
使用方式完全和printf一样，因为内部实现就是printf，该方式无需头文件<QDebug>
qDebug("%s", "hello");

//流方式输出
QT中使用 qDebug() 函数代替 cout 进行输出调试。支持常见类型直接输出，还支持Qt内置的数据类型输出。
qDebug() << QString("Hello") << QPoint(10, 10);

我们可以通过友元函数的方式重载qDebug，来支持自定义类型输出。
并且还可以在结构体前后或中间随意的添加标记，诸如结构体前缀，成员变量标记，更明显的看出来这是哪个结构体的信息。

struct StInfo {
        int id;
        QString dev_id;

        friend inline QDebug operator<<(QDebug out, const StInfo& info)
        {
                out << " StInfo(" << info.id << info.dev_id << ") ";
                return out;
        }
};

StInfo info;
qDebug() << info;



/********************/Qt调试信息处理/************************************************************/
// 自定义消息处理回调函数
void myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg)     
{
        QByteArray localMsg = msg.toLocal8Bit();
        switch (type) {
        case QtDebugMsg:
                fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
                break;
        case QtInfoMsg:
                fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
                break;
        case QtWarningMsg:
                fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
                break;
        case QtCriticalMsg:
                fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
                break;
        case QtFatalMsg:
                fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
                abort();
        }
}

int main(int argc, char** argv)
{
        QApplication app(argc, argv);

        // 安装消息处理程序
        qInstallMessageHandler(myMessageOutput);

        // 打印信息
        qDebug("This is a debug message.");                  //调试消息
        qDebug("This is a info message.");                      //信息消息
        qWarning("This is a warning message.");            //警告消息和可恢复的错误
        qCritical("This is a critical message.");                 //关键错误和系统错误
        qFatal("This is a fatal message.");                        //致命错误

        return app.exec();
}

这时，我们不仅可以输出调试信息，而且可以很直观、很方便的得到输出代码所在的文件、函数、行号等信息。

注意：
1.该回调函数内的实现不可使用qDebug，否则会造成死递归，如需打印调试使用printf和std::out均可。
2.注意加锁以支持多线程qDebug();

输出如下：
Debug : This is a debug message. (…\MessageOutput\main.cpp:90, int __cdecl main(int, char* []))
Warning : This is a warning message. (…\MessageOutput\main.cpp:91, int __cdecl main(int, char* []))
Critical : This is a critical message. (…\MessageOutput\main.cpp:92, int __cdecl main(int, char* []))
Fatal : This is a fatal message. (…\MessageOutput\main.cpp:93, int __cdecl main(int, char* []))


//重定向qDebug的输出
调用qInstallMessageHandler，传入回调函数指针，qDebug最后的输出将会送入这个回调函数，因此可以在回调函数中打开文件并将信息输出到文件中。
QMessageLogContext中包含了文件名，函数名，行号等信息。msg则是输出的信息。数次实现写入文件即可。

为了调试方便，我们还可以将日志通过信号输出到窗口、文件、socket、控制台中等等。实现方式均可在回调函数中自定义。



/********************/Qt调试信息输出格式/************************************************************/
//qSetMessagePattern
占位符	                                描述
%{appname}	                        QCoreApplication::applicationName()
%{category}	                        日志类别
%{file}	                                原文件路径
%{function}	                        函数
%{line}	                                源文件所在行
%{message}	                        实际的消息
%{pid}	                                QCoreApplication::applicationPid()
%{threadid}	                        当前线程的系统范围ID（如果它可以获得）
%{type}	                                “debug”、“warning”、“critical"或"fatal”
%{time process}	                “debug”、“warning”、“critical"或"fatal”
%{time boot}	                        消息的时间，启动进程的秒数
%{time [format]}	                消息产生时,系统时间被格式化通过把格式传递至QDateTime::toString()。如果没有指定的格式，使用Qt::ISODate。
%{backtrace [depth=N] [separator=“…”]}	        很多平台不支持，暂略…

还可以使用条件类型，% { if - debug }, % { if - info }% {if - warning}, % { if - critical } 或% { if - fatal }后面跟着一个% { endif }。
如果类型匹配，% { if - * } 和% { endif }之间的内容会被打印。最后，如果类别不是默认的一个，% { if - category } ... %{endif}之间的内容将被打印。
例如：
QT_MESSAGE_PATTERN = "[%{time yyyyMMdd h:mm:ss.zzz t} %{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-critical}C%{endif}%{if-fatal}F%{endif}] %{file}:%{line} - %{message}"

默认的模式是：“% {if - category}% {category}:% {endif}% {message}”。
也可以在运行时改变模式，通过设置QT_MESSAGE_PATTERN环境变量。
如果既调用了 qSetMessagePattern()又设置了环境变量QT_MESSAGE_PATTERN，那么，环境变量优先。

//QT_MESSAGE_PATTERN环境变量
选择：项目->构建环境，添加环境变量：
QT_MESSAGE_PATTERN = [% {type}] % {appname} (% { file }:% {line}) - % {message}


/************************************************************/
//实例一
qSetMessagePattern("Message:%{message} File:%{file} Line:%{line} Function:%{function} DateTime:%{time [yyyy-MM-dd hh:mm:ss ddd]}");// 改变缺省消息处理程序的输出
qDebug("This is a debug message.");             // 打印信息
输出如下：
Message:This is a debug message.File : ..\MessagePattern\main.cpp Line : 138 Function : main DateTime : [2016 - 07 - 06 15:21 : 40 周三]

//实例二
#define LOG(X)	X
#define INFO	QMessagelogger(__FILE__, __LINE__, __FUNCTION__).info().nospace.noquote()
int main(int argc, char* argv[])
{
        QApplication a(argc, argv);
        qSetMessagePattern("%{time yyyy-MM-dd hh:mm:ss.zzz} (%{type}) %{file}:%{line}] %{message}");
        LOG(INFO) << "LANGUAGE: zh_CN";
        return a.exec();
}
输出如下：
2021 - 01 - 15 14:38 : 00.266 (info) .. / Capturer / main.cpp : 37] LANGUAGE: zh_CN


/************************************************************/
//注意的问题
1、环境变量中使用% { file }时，log打印unknown的报错
解决方法： 在pro文件的DEFINES中添加QT_MESSAGELOGCONTEXT, 即DEFINES += QT_MESSAGELOGCONTEXT

2、qt release模式下必须添加DEFINES += QT_MESSAGELOGCONTEXT，否则一些占位符无法使用。

3、环境变量和代码中使用qSetMessagePattern有差别。
比如，环境变量中不能带有空格，时间格式也无法输出，无论怎么限制格式，都是输出2016 - 03 - 17T22:20 : 22.729，
但是代码中使用qSetMessagePattern则可以输出时间的格式。（该问题后来发现使用颜色设置字符串的双引号包起来之后问题解决）

//输出带有颜色
如果想让输出带有颜色的话，可以使用ANSI非常规字符序列来实现。
比如下面的命令（shell 中使用的命令就是echo - e "\033[32m", 注意有双引号）

export QT_MESSAGE_PATTERN = "`echo -e "% {if - debug}\033[32m% {endif}% {if - critical}\033[31m% {endif}% {if - warning}\033[33m% {endif}% {if - info}\033[34m% {endif}[% {type}]\033[37mPid:% {pid} - Tid : % {threadid}--file : % {file} : % {line} - % {message} == DateTime : % {time hh : mm:ss}"`"

最终实现的效果就是critical是红色，debug是绿色，info是蓝色，warning是黄色，其他的是白色。
具体的参数网上可以查到，下面简单列一下：

//输出特效格式控制
\033[0m 关闭所有属性
\033[1m 设置高亮度
\03[4m 下划线
\033[5m 闪烁
\033[7m 反显
\033[8m 消隐
\033[30m – \033[37m 设置前景色
\033[40m – \033[47m 设置背景色

//字体背景颜色
30：黑
31：红
32：绿
33：黄
34：蓝色
35：紫色
36：深绿
37：白色

//字体背景颜色
40：黑
41：深红
42：绿
43：黄色
44：蓝色
45：紫色
46：深绿
47：白色

//Tips
qt time的时间表示：
yyyy：年
MM：月
dd：日
hh：小时
mm：分钟
ss：秒
zzz：毫秒
dddd：星期五（ddd：周五）

