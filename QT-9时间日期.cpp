

//QTime类方法
头文件<QTime>
QTime currentTime()				//获取当前时间
QTime QTime::fromString(const QString& string, Qt::DateFormat format = Qt::TextDate)	//获取格式化时间
QString QTime::toString(const QString& format) const			//将时间转换为字符串

String T = mtime.currentTime().toString("hh-mm-ss");


//QDate类方法
头文件<QDate>
QDate currentDate();			//获取当前日期
QString toString(const QString& format)const					//将日期转换为字符串

String D = mdate.currentDate().toString("20yy-MM-dd	  dddd");