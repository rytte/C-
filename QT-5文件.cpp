/********************/文件/************************************************************/
QFile类方法
头文件<QFile>
virtual bool  open(QIODevice::OpenMode mode)
qint64 		  read(char* data, qint64 maxSize)
QByteArray 	  read(qint64 maxSize)
QByteArray 	  readAll()
qint64 		  readLine(char* data, qint64 maxSize)
qint64 		  rite(const char* data, qint64 maxSize)
qint64 		  rite(const char* data)
qint64 		  rite(const QByteArray& byteArray)
virtual void  close()
bool 		  isOpen() const

QFileinfo类方法
头文件<QFileInfo>
QString   fileName() const		//只有文件名
QString   filePath() const		//文件名+绝对路径
QString   path() const			//绝对路径
qint64    size() const			//文件大小


QFileInfo info(ui->filename_edit->text())	//定义文件信息对象，路径通过构造函数传入
QFile file									//定义无名文件对象
file.setFileName(info.filePath())			//设置文件名
file.open(QIODevice::ReadWrite)			    //读写方式打开文件