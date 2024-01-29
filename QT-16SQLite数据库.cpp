/********************/SQLite数据库/************************************************************/
//编译sqlite中的工程文件
gcc  sqlite3.c  shell.c - o  main - lpthread - ldl

//运行
. / main + 数据库名（不存在则创建）

//退出
.exit

//创建表格
create table 表格名(第1列名 类型, 第2列名 类型, ...)；

//增加数据
insert into 表格名(列名, 列名, ...)values(值, 值, ...)；

//检索表格
select * from 表格名；						//打印整个表格信息
select * from 表格名 where 列名 = 值；		//打印值所在行的信息

//删除信息，删除一整行（sqlite的属性决定了它无法删除某一列）
delete * from 表格名 where 列名 = 值；

//修改某行信息
update 表格名 set 列名 = 修改值 where 列名 = 值；

//查看数据库中的表格
.table

*字符串记得加单引号。

实例：
$. / main school.db
sqlite > create table student(name text, age int, score double)；			//创建表
sqlite > insert into student(name, age, score)values('jack', 17, 98.5)；	//添加
sqlite > select * from student；									//查找
jack | 17 | 98.5
sqlite > delete * from student where name = 'jack' ；				//删除
sqlite > update student set score = 96 where name = 'jack' ；		//修改
sqlite > .table						//查看表格
student
sqlite > .exit						//退出


软件创建数据库表格:
1、右键数据库名称，点击"New Table"
2、在"table name"上输入新表格名称
3、点击"add"添加列名，设置列名"Name"、数据类型"Type"、大小"Size"、是否允许值为空"Not null"等。
4、点击"apply"完成创建
5、切换到"Data"栏添加数据，点击"+"等符号编辑值
6、切换到"SQL"栏，可以执行语句。


/************************************************************/
C/C++ 常用API接口：

官方API接口查询网站：	http ://www.sqlite3.org/
	
（1）打开数据库，不存在则创建
int sqlite3_open(const char* filename, sqlite3** ppDb)
参数一 : 数据库文件名
参数二 : 数据库句柄，传入数据库类型指针的地址

（2）执行数据库指令
int sqlite3_exec(sqlite3*, const char* sql, sqlite_callback, void* data ，char** errmsg)
参数一 : 数据库句柄
参数二 : 需要执行的数据库指令
参数三 : 数据库执行时的回调函数（处理函数），不需要可设为 NULL 
参数四 : 回调函数的参数
参数五 : 错误管理结构体

回调函数
int callback(void* data, int ncols, char** values, char** headers)
参数一:  传入的参数，sqlite3_exec函数的参数四
参数二:  列数
参数三:  这一列的数据
参数四:  这一列的头信息

（3）关闭数据库
sqlite3_close(sqlite3*)
参数一: 数据库句柄

//编译语句
gcc main.c sqlite3.c - o main - lpthread - ldl

关键字： unique 不允许重复数据，它可以在软件中添加，也可以在创建表格时添加。


/************************************************************/
//实例
#include <stdio.h>
#include "sqlite3.h"

int callback(void* data, int ncols, char** values, char** headers)		//将数据输出到ubuntu屏幕上
{
	int i;
	for (i = 0; i < ncols; i++)
		printf("%s:%s  ", headers[i], values[i]);
	printf("\n");

	return 0;//继续输出下一行
	//return 1;//停止输出下一行
}

int main()
{
	sqlite3* pdb;								//定义一个数据库指针

	int fd = sqlite3_open("car.db", &pdb);		//打开数据库
	if (fd == -1)
	{
		perror("open failed");
		return -1;
	}

	/*
	char *sql = "create table phone(name text not NULL unique,	\				//设置列名属性：not NULL非空；unique不可重复属性，但已经自带了这个属性
											size double not NULL,  \
											price double not NULL )";

	char *sql = "insert into phone(name,size,price)values('huawei',6,3999)";	//添加数据
	*/

	//添加数据
	char name[16];
	double size;
	double price;

	scanf("%s", name);
	scanf("%lf", &size);
	scanf("%lf", &price);

	char sql[64];
	sprintf(sql, "insert into phone(name,size,price) values('%s',%lf,%lf)", name, size, price);	//拼接

	sqlite3_exec(pdb, sql, NULL, NULL, NULL);		//执行该指令，不带回调函数

	//执行指令，带回调函数
	//char* sql = "select*from phone";
	char* sql = "update phone set size=8 where size=6";
	sqlite3_exec(pdb, sql, callback, NULL, NULL);

	sqlite3_close(pdb);								//关闭数据库

	return 0;
}



/********************/QT中的SQLite数据库/************************************************************/
QT += sql

头文件<QSqlDatabase>
static QSqlDatabase addDatabase(const QString& type, const QString& connectionName = QLatin1String(defaultConnection))		//添加数据库，返回数据库对象
			//参数一：添加的数据库种类，sqlite3填QSQLITE		参数二 : 为数据库创建一个名称，可以是默认名称

QSqlQuery exec(const QString& query = QString()) const			//执行sql语句，结果放入QSqlQuery请求对象中返回。
void setDatabaseName(const QString& name)						//设置数据库文本的名称
bool open()														//打开数据库


头文件<QSqlQuery>		sqlite请求类
QSqlQuery(const QString & query=QString(), QSqlDatabase db=QSqlDatabase())		//构造函数。query：要执行的sql语句	db ：默认的数据库，指向的QSqlDatabase名称为默认值的对象。
bool exec()				//执行sql语句。
bool next()				//将指针定位到下一条记录。Sql执行后，返回值是否存在。如果存在，则一行一行地读取。
bool QSqlQuery::first()	//将指针定位到第一条记录。
QVariant value(int index) const			//获取当前记录的第 index 列的数据（序号不算一列），返回值使用toInt()或toString()等方法转换。
QSqlError QSqlQuery::lastError() const	//显示最后一条错误信息。需要添加头文件<QSqlError>


头文件<QSqlTableModel>		数据库表格模型类：也就是副本，对副本进行操作后使用submit()方法覆盖到数据库中,该模型上的数据还可以在其它控件中显示
QSqlTableModel(QObject * parent = nullptr, QSqlDatabase db = QSqlDatabase())		//创建数据库表格模型对象，绑定数据库对象
bool insertRecord(int row, const QSqlRecord & record)					//在第row行添加一行数据库记录
QSqlRecord 	record(int row) const										//返回第row行的数据库记录
virtual void setTable(const QString & tableName)						//指定要操作数据库中的哪一个表格
virtual bool select()													//查询数据，默认是查询所有内容
virtual void setFilter(const QString & filter)							//设置过滤器，一般与select同时使用。默认过滤器为空""，即不过滤
virtual bool submit() override											//更新数据库到表格中
bool removeRow(int row, const QModelIndex & parent = QModelIndex())		//删除第row行
virtual bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex())		//从第row行开始，删除count行
virtual int rowCount(const QModelIndex & parent = QModelIndex()) const = 0					//获取当前行的数量

bool commit()				//QSqlDatabase类方法，当更新数据库内容到表格中后，还需要显示出来。这个是上传到数据库对象中。


头文件<QSqlRecord>		数据库记录类，表示一行数据库的内容
void setValue(int index, const QVariant & val)					//在第index列写入数据val
void setValue(const QString & name, const QVariant & val)		//在列头尾name的那一列添加val数据


头文件<QCryptographicHash>		加密模式类
QCryptographicHash(QCryptographicHash::Algorithm method)		//构造函数。为对象选择加密模式
void addData(const char* data, int length)						//把需要加密的数据，加入到对象中
void addData(const QByteArray& data)
bool addData(QIODevice* device)
QByteArray result() const				//获取加密结果


移植sqlite3到开发板上：交叉编译sqlite3程序，然后移动到开发板的 /bin 目录下


/************************************************************/
//实例：数据库读写图片

//创建数据库
QString dbName("myDatabase.db");
QFile::remove(dbName);                  //删除 SQLite 文件（如果它存在于以前的运行中）
QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
db.setDatabaseName(dbName);             //设置数据库名字
db.open();
QSqlQuery query = QSqlQuery(db);
query.exec("CREATE TABLE IF NOT EXISTS imgTable ( filename TEXT, image BLOB )");

//加载图片到缓冲区中
QFile file("./pic.png");
if (!file.open(QIODevice::ReadOnly)) return;
QByteArray ByteArr = file.readAll();

//将图片字节插入到数据库中
query.prepare("insert into imgTable (filename, image) VALUES ('pic.png', :imageData)");
query.bindValue(":imageData", ByteArr);         //自定义的:imageData绑定图片缓冲区
if (!query.exec())                              //执行
qDebug() << "插入图片失败\n" << query.lastError();

//从数据库获取图像数据
if (!query.exec("SELECT image from imgTable"))
qDebug() << "获取图片失败\n" << query.lastError();
query.first();
QByteArray outByteArray = query.value(0).toByteArray();     //获取图片数据到缓冲区
QPixmap outPic = QPixmap();
outPic.loadFromData(outByteArray);                          //加载图片
db.close(); //关闭数据库

// 显示图片
QLabel* myLabel = new QLabel(this);
myLabel->resize(600, 300);
myLabel->setPixmap(outPic);
myLabel->show();

 

