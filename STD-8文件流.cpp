/********************/文件流/************************************************************/
头文件：
#include <fstream>

创建文件对象：
fstream 对象名();
fstream 对象名(文件名);


Object.open() ：
open()函数是 fstream、ifstream 和 ofstream 对象的一个成员，下面是 open() 函数的标准语法。

void open(const char* filename, ios::openmode mode);
参数一：指定要打开的文件的名称和位置。
参数二：文件打开的模式。

<模式标志>	<描述>
ios::in		只读，不存在则报错，相当于"r"。
ios::out		只写，存在则清空，不存在则创建，相当于"w+"。
ios::app		追加，在文件末尾写入。
ios::ate		文件打开后定位到文件末尾。
ios::trunc		清空。（即如果该文件已经存在，其内容将在打开文件之前被截断，把文件长度设为 0）
ios::binary	二进制方式


/************************************************************/
fstream类方法

open()  			打开文件
is_open() 			判断是否打开成功，成功返回 true ，失败返回 false 。
close()			关闭文件

write()  			写入数据
<< 运算符重载		写入数据(自动识别类型)

read()  			读取数据
>> 运算符重载		读取数据(自动识别类型)
getline()			读取一行数据


/************************************************************/
文件位置指针：
istream 和 ostream 都提供了用于重新定位文件位置指针的成员函数。
这些成员函数包括关于 istream 的 seekg（"seek get"）和关于 ostream 的 seekp（"seek put"）。
seekg 和 seekp 的参数通常是一个长整型。第二个参数可以用于指定查找方向。

file.seekg(n);			// 定位到 file 的第 n 个字节（假设是 ios::beg）

file.seekg(n, ios::cur);      // 把文件的读指针从 fileObject 当前位置向后移 n 个字节

file.seekg(n, ios::end);     // 把文件的读指针从 fileObject 末尾往回移 n 个字节

file.seekg(0, ios::end);     // 定位到 fileObject 的末尾


/************************************************************/
练习 :
建立一个校园管理系统。有学生和教师之分。都有姓名和年龄的属性，学生有分数属性，教师有科目属性。
所有数据是保存在一个 1.txt文本中，当开启系统时，读取文本内的内容，创建对象。
有遍历，增加，删除操作。关闭系统时，把新的内容保存到文件中。



/********************/open 实例/************************************************************/
#include <iostream>
#include <fstream>

using namespace std;


int main()
{
	fstream A;

	//open() 打开的成员方法   ios::out相当于 "w+"
	//								  文件不存在则创建
	A.open("1.txt", ios::out);

	//is_open()  判断是否打开成功
	if (A.is_open())
		cout << "打开成功" << endl;
	else
		cout << "打开失败" << endl;

	//A.write("helloworld",10);
	//A.write("12345",5);

	//类fstream中有重载的<<运算符
	int num = 999;
	A << "helloworld" << "  " << num << endl;

	// fstream& operator<<(fstream &f, char *str);
	// fstream& operator<<(fstream &f, int num);


	A.close();

}



/********************/read 实例/************************************************************/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	fstream A;

	//open() 打开的成员方法   ios::in相当于 "r"
	//					 文件不存在则报错，文件存在则只读模式打开
	//A.open("1.txt",ios::in);

	//可读可写的方式打开---不会被清空
	//A.open("1.txt",ios::out | ios::in);

	//可读可写的方式打开---会被清空
	A.open("1.txt", ios::out | ios::in | ios::trunc);

	if (A.is_open())
		cout << "打开成功" << endl;
	else
		cout << "打开失败" << endl;

	char buf[32];


	//读取数据
	//A.read(buf,32); //---读取n-1个字节,或者读取到文件末尾结束
	//cout << buf << endl;

/* 	//判断是否到文件末尾，  到文件末尾时eof()返回真，否则返回假
	while( !A.eof())
	{
		A.getline(buf,32);//读取一行数据，最多读取n-1个字节
		cout << buf << endl;
	} */

	/* 	//读取单个字符
		for(int i=0;i<10;i++)
			cout << A.get() << "  ";
		cout << endl; */

	string str;
	string num;
	int num2;
	A >> str >> num >> num2;
	cout << "str=" << str << "  num=" << num << "  num2=" << num2 << endl;

	//很多库中没有 MFC和QT是一定有的
	//readAll一次性读取所有数据，最多读取 2^31-1个字节。
	//A.readAll();

	A.close();

}

