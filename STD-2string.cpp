/********************/string类/************************************************************/

头文件及命名空间：
#include <string>
using namespace std;


//编码
string		//二进制数据（不确定编码）
wstring		//不跨平台，Window:UTF16 Linux:UTF32
u8string	//utf8编码
u16string	//utf16编码


//注意
string 和C语言字符串一样会被'\0'截断
解决方法：std::string str("hello\0world", 11);  //指定长度


//实例
string s1 = "abdc";				// 字符串的赋值

string s2;						//字符串的复制
s2 = s1;

//计算str类型所占的大小 以及 所占实际长度
string s;
cin >> s;
cout << s.capacity() << endl;  //所占总字节数
cout << s.length() << endl;    //实际内容长度

//字符串的拼接
s2 = "xyz" + s1;
s2 += "123";

//字符串的比对,可对比相等,也可以对比大于 小于 ...
if (s1 == s2)
{
	cout << "相等" << endl;
}

// 字符串中的元素引用
s1[1] = 'B'; // 将s1修改为"aBcd"



作业:
根据string类的构造，拷贝构造，析构，运算符重载，
成员函数，自定义mystring类(字符串类)



/********************/实例/************************************************************/
#include <iostream>
#include <cstring>

extern "C" {
#include <stdio.h>
}
using namespace std;


int main()
{
	string A;			//调用无参构造函数
	A = "helloworld";	//赋值运算符重载
	cout << A << endl;	//左移运算符重载

	string B("nihao");	//调用带参构造函数
	cout << B << endl;

	string C = A;		//调用拷贝构造函数
	cout << C << endl;

	//调用成员函数 size()  length():获取字符串长度
	cout << C.size() << endl;
	cout << C.length() << endl;

	//调用成员函数 c_str():转换成char*类型
	char buf[32];
	strcpy(buf, C.c_str());
	cout << buf << endl;

	//调用成员函数 at()：获取对应下标的字符
	cout << C.at(4) << endl;
	//重载[]运算符，获取对应下标的字符
	cout << C[4] << endl;

	//调用构造函数，赋值为 "aaaaa"
	string D(5, 'a');
	cout << D << endl;

	//调用成员函数 assign():拷贝字符串
	string E;
	E.assign(D);
	cout << E << endl;

	//调用成员函数 append():追加字符串
	E.append("123");
	cout << E << endl;

	//获取空间大小
	cout << E.capacity() << endl;
	char* p1 = &E[0];
	printf("%p\n", p1);

	//string类本质上是char*ptr申请了堆空间存入字符数据
	//当堆空间不够时，会申请新的堆空间，把原数据拷贝进去后
	//释放掉原堆空间，使指针ptr指向新的堆空间
	E.append("1234567890");
	cout << E << endl;
	cout << E.capacity() << endl;//整个堆空间大小
	char* p2 = &E[0];
	printf("%p\n", p2);
}



/********************/作业/************************************************************/
#include <iostream>

extern "C" {
#include <string.h>
#include <stdio.h>
}
using namespace std;


class mystring {
public:
	mystring() {
		this->ptr = NULL;
		this->lenth = 0;
	}
	mystring(const char* str) {
		int size = strlen(str);

		this->lenth = size;
		this->ptr = new char[size + 1];

		strcpy(this->ptr, str);
	}
	mystring(mystring& P) {
		lenth = P.lenth;
		this->ptr = new char[lenth];
		strcpy(this->ptr, P.c_str());
	}
	mystring(int n, char ch) {
		this->lenth = n;
		this->ptr = new char[n];
		for (int i = 0; i < n; i++)
			ptr[i] = ch;
	}
	~mystring() {
		if (this->ptr != NULL)
			delete[]ptr;
	}

	char* operator=(const char* str)
	{
		if (ptr != NULL)
			delete[]ptr;

		int size = strlen(str);

		this->lenth = size;
		this->ptr = new char[size + 1];
		strcpy(this->ptr, str);

		return this->ptr;
	}

	int size() {
		return this->lenth;
	}
	int length() {
		return this->lenth;
	}

	char* c_str() {
		return this->ptr;
	}

	char& at(int n)
	{
		if (n >= 0 && n < lenth)
			return ptr[n];
		else
			return ptr[0];
	}

	char& operator[](int n)
	{
		if (n >= 0 && n < lenth)
			return ptr[n];
		else
			//这里实际上会写try cath的抛异常，不是直接返回
			return ptr[0];
	}

	void assign(mystring& P)
	{
		this->lenth = P.lenth;

		if (ptr != NULL)
			delete[]ptr;

		ptr = new char[this->lenth + 1];
		strcpy(ptr, P.c_str());
	}

	int capacity() {
		return this->lenth;
	}

	char* append(const char* str)
	{
		int size = strlen(str);

		char* temp = new char[lenth + size + 1];
		strcpy(temp, this->ptr);
		strcpy(temp + lenth, str);

		delete[]ptr;
		this->ptr = temp;
		this->lenth = this->lenth + size;

		return ptr;
	}

private:
	char* ptr;
	int  lenth;//字符串长度
};

ostream& operator<<(ostream& out, mystring& P)
{
	out << P.c_str();
	return out;
}

int main()
{
	mystring A;
	A = "helloworld";
	cout << A << endl;

	mystring B("nihao");
	cout << B << endl;

	mystring C = A;

	cout << C.size() << endl;
	cout << C.length() << endl;

	char buf[32];
	strcpy(buf, C.c_str());
	cout << buf << endl;

	cout << C.at(4) << endl;
	cout << C[4] << endl;
	C[4] = 'A';
	cout << C << endl;

	mystring D(5, 'a');
	cout << D << endl;

	mystring E;
	E.assign(D);
	cout << E << endl;

	cout << E.capacity() << endl;
	char* p1 = &E[0];//这里说明下标运算符返回的一定是引用
	printf("%p\n", p1);

	E.append("1234567890");
	cout << E << endl;
	cout << E.capacity() << endl;
	char* p2 = &E[0];
	printf("%p\n", p2);

	//赋值运算符返回值为char*，是因为下面代码中会判断返回值的真假
	//如果是char*类型，则判断第1个字符是否为'\0'
	//如果是对象，则需要重载以后才能判断。
	//if( A="helloworld" )

	//判断是否相等，需要重载 == 运算符
	//if(A=="helloworld")
}

