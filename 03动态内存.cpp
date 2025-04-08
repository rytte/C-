/********************/动态内存/************************************************************/
C++ 程序中的内存分为两个部分：

栈：在函数内部声明的所有变量都将占用栈内存。
堆：这是程序中未使用的内存，在程序运行时可用于动态分配内存。

分配堆空间： new 作用相当于 malloc()。 new 不只是分配了内存，它还创建了对象，并调用构造函数。
释放堆空间： delete 作用相当于 free()。 delete 会调用析构函数。

new  数据类型			//申请单个数据类型大小的堆空间，具体堆空间大小由系统根据类型来决定
new  数据类型[N]			//申请N个数据类型大小的堆空间，如果有带参构造函数则可以 new 数据类型[N]{{arg, arg},{arg, arg}...} 方式传入参数。
new  数据类型(data)		//申请单个数据类型大小的堆空间并传递参数(若数据类型为类类型，则参数传递给它的构造函数)

delete  指针(堆空间首地址)	//释放单个数据类型的堆空间内存
delete[]  指针				//释放N个数据类型的堆空间内存，释放大小为编译器在new[]时的记录值


//区别
(1)malloc和free都是函数, new 和 delete 是关键字
(2)malloc返回值为void*, new 会根据数据类型来确定返回值。（）
(3)malloc分配内存失败返回 nullptr, new 失败会抛出 std::bad_alloc 异常
(4)malloc和free不会调用类的构造与析构， new 会调用构造， delete 会调用析构。

//注意
C++中函数返回值为指针时，不会发生隐式类型转换。

//new底层实现
1、一般是调用内存分配函数 malloc
2、调用构造函数
3、返回对象的指针

//new数组长度保存
int* arr = new int[5];
在MSVC中，数组长度会保存在arr - 4的位置，值为字节数，即 * (arr - 4) = 20;


//实例
int* p1 = new int;				//申请一个int类型大小的堆空间
delete p1;						//释放堆空间

int* p2 = new int[3];			//申请 3个 int类型的堆空间
delete[]p2;						//释放从指针p开始的堆空间数组

int* p3 = new int(99);			//申请1个int型堆空间，同时对该int型进行赋值
delete p3;

//int *p = malloc(100);			//报错，c++中函数返回值没有隐式类型转换
int* p4 = (int*)malloc(4);
free(p4);

char* p5 = new char('A');
delete p5;


//支持 new 推导数组长度（C++20）
实例：
int* x = new int[] {1, 2, 3};
char* s = new char[] {"hello world"};

//允许数组转换为未知长度的数组（C++20）
void f(int(&)[]){}
int arr[1];
int main()
{
	f(arr);
	int(&r)[] = arr;
}


//在delete运算符中析构对象（C++）
C++20允许由程序员来控制析构函数的执行。此前重载 delete 时会自动执行析构函数。
struct ClassName
{
	ClassName(){}
	~ClassName() { cout << "call dtor" << endl; }

	void operator delete(ClassName* ptr, std::destroying_delete_it)		//原先只有delete(void* ptr)
	{
		ptr->~ClassName();
		cout << "call delete" << endl;
		::operator delete(ptr);
	}
};
ClassName* x = new ClassName;
delete x;



