/********************/QDateTime/************************************************************/
#include <QDateTime>
QDateTime类的基本知识，包括创建对象、访问和设置日期时间值、格式化、比较和计算日期时间，以及时区的处理等。
除了列举功能外，QDateTime类还提供了其他一些有用的函数，如添加时间间隔、判断是否为有效日期时间等。

//使用当前日期和时间创建对象：
QDateTime currentDateTime = QDateTime::currentDateTime();

//使用特定日期和时间创建对象：
QDateTime customDateTime(QDate(2023, 7, 15), QTime(10, 30, 0));

//访问日期和时间：
QDate date = dateTime.date();
QTime time = dateTime.time();

//设置日期和时间：
dateTime.setDate(QDate(2023, 7, 15));
dateTime.setTime(QTime(10, 30, 0));

//格式化日期时间：QDateTime类提供了功能强大的格式化函数，使您能够将日期时间以不同的格式显示出来。
//将日期时间转换为字符串：
QString formattedDateTime = dateTime.toString("yyyy-MM-dd hh:mm:ss");

//使用预定义的格式：
QString formattedDateTime = dateTime.toString(Qt::ISODate); // ISO 8601格式

//比较和计算日期时间：
QDateTime类提供了用于比较和计算日期时间的函数和操作符重载。以下是一些常用的比较函数和操作符：

//比较两个日期时间：
bool result = dateTime1 < dateTime2;

//计算日期时间的差值：
qint64 seconds = dateTime1.secsTo(dateTime2); // 计算两个日期时间之间的秒数差

//时区的处理：您可以将日期时间从一个时区转换到另一个时区，并获取特定时区的当前日期时间。
//转换时区：
QDateTime convertedDateTime = dateTime.toTimeZone(QTimeZone("America/New_York"));

//获取特定时区的当前日期时间：
QDateTime currentDateTime = QDateTime::currentDateTime().toTimeZone(QTimeZone("Asia/Tokyo"));



/********************/QDate/************************************************************/
#include <QDate>
QDate可以从系统时钟读取当前日期。它提供了比较日期和操作日期的功能。例如，可以在日期上加上和减去几天，几个月和几年。


//创建QDate
QDate date(2020, 3, 19);

//通过静态成员函数currentDate来创建QDate对象，该QDate自动包含当前系统日期。
QDate date = QDate::currentDate();

//通过静态成员函数fromString来创建QDate，fromString可以通过格式字符串在创建对象的同时指定日期
QDate date = QDate::fromString("20200319", "yyyyMMdd");	//对应关系：2020-yyyy;03-MM;19-dd;


QDate提供了一些标准的格式定义在Qt::DateFormat宏中。
表达式	输出
d		没有前导0的日期数字（1 - 31）
dd		带前导0的日期数字（01 - 31）
ddd		缩略的本地日期名（比如今天是19号，可以用周四代替）
dddd	完整的本地日期名（比如今天是19号，可以用星期四代替）
M		没有前导0的月份数字（1 - 12）
MM		带有前导0的月份数字（01 - 12）
MMM	缩略的本地月份名（比如是3月本来只显示3，但这里可以显示”3月“）
MMMM	完整的本地月份名（比如是3月本来只显示3，但这里可以显示”三月“）
yy		两位数字的年份
yyyy		四位数字的年份，如果年份是负的，一个负号会附加在上面。



返回值类型	函数名						说明
			QDate(int y, int m, int d)			日期类对象通过指定的年月日实现如: QDate date(2025, 1, 1)
QDate 		addDays(qint64 ndays) const		添加n天之后的日期, n可以为负数
QDate 		addMonths(int nmonths) const	添加n月之后的日期, n可以为负数
QDate 		addYears(int nyears) const		添加n年之后的日期, n可以为负数
qint64		daysTo(const QDate& d) const	返回两个日期的间隔天数; 小日期在前, 否则结果为负数
int 			day() const					返回日期为该月的第几天; 返回0:日期出错
int 			dayOfWeek() 	const			返回日期为该星期的第几天(星期几); 返回0:日期出错
int 			dayOfYear() const				返回日期为该年的第几天; 返回0:日期出错
int 			daysInMonth() const			返回该月的天数 28 - 31; 返回0:日期出错
int 			daysInYear() const				返回该年的天数 365 / 366; 返回0:日期出错
QDate		static currentDate()				获取当前的日期
QDate 		static fromJulianDay(qint64 jd)	从JulianDay的日期转为QDate
QDate		static fromString(const QString& string, const QString& format)	从字符串按照指定规则生成QDate
bool			static isLeapYear(int year)		判断是否为闰年
bool 		static isValid() const			判断日期是否正确
bool			static isValid(int year, int month, int day)	给定年月日, 判断日期是否正确



/********************/QTime/************************************************************/
#include <QTime>

//当前时间增加毫秒，ms可为负
QTime addMSecs(int ms) const

//当前时间增加秒，s可为负
QTime addSecs(int s) const

//返回自上次调用start()或restart()以来经过的毫秒数。
int elapsed() const

//返回小时数
int hour() const

//返回分钟数
int minute() const

//返回秒数
second() const

//返回毫秒数
int msec() const

//如果时间为空返回true
bool isNull() const

//判断当前时间对象是否有效，比如H的范围是0~23，M和S的范围是0~59
bool isValid() const

//返回从一天开始的秒数，即从00 : 00 : 00开始的秒数。
int msecsSinceStartOfDay() const

//返回从当前时间到t的秒数。如果t比这个时间早，返回的毫秒数为负。
int secsTo(const QTime & t) const

//返回从当前时间到t的毫秒数。如果t比这个时间早，返回的毫秒数为负。
int msecsTo(const QTime & t) const

//将此时间设置为当前时间，并返回自上次调用start()或restart()以来经过的毫秒数。
int restart()int

//将时间设置为小时h、分钟m、秒s和毫秒ms。
bool setHMS(int h, int m, int s, int ms = 0)

//将当前系统时间记录为当前时间
void start()

//将时间转化为特定的字符串格式
QString toString(const QString & format) const

//按照Qt::DateFormat的格式转化
QString toString(Qt::DateFormat format = Qt::TextDate) const

//获得系统当前时间
QTime currentTime()

//从Qt::DateFormat转化为QTime对象
QTime fromString(const QString & string, Qt::DateFormat format = Qt::TextDate)

//从特定的字符串格式转化为QTime对象
QTime fromString(const QString & string, const QString & format)


//时间字符串格式
h :		没有补零的小时(如果AM / PM显示，则为0到23或1到12)
hh :		位数不够需要补零的小时(00至23或01至12，如果是AM / PM显示)
m :		没有补零的分钟(0到59)
mm :	位数不够需要补零的分钟(00到59)
s :		没有补零的秒(0到59)
ss :		位数不够需要补零的秒(00到59)
z :		没有补零的毫秒(0到999)
zzz :		位数不够需要补零的毫秒(000到999)
ap / AP : 上午 / 下午，ap为am或pm，AP为AM或PM

例：
hh : mm:ss.zzz    08 : 18 : 68.138
h : m : s ap        8 : 18 : 68 am



/********************/QLocale/************************************************************/
#include <QLocale>

QLocale类用于在不同语言的数字及其字符串表示形式之间进行转换。


实用的类型成员
1、QLocale::Country。国家和地区。太长不列了。
2、QLocale::Language。语言。太长不列了。
3、QLocale::FormatType。此枚举描述将QDate和QTime对象转换为字符串时可以使用的格式类型。

LongFormat：长文本格式。
ShortFormat：短文本格式。
NarrowFormat：极短文本格式。





