/********************/RAII模型/************************************************************/

RAII（Resource Acquisition Is Initialization，资源获取即初始化）是C++资源管理的重要思想。
在 C++ 中写类时，只要类中涉及资源管理（内存、文件、线程、锁等），就应该遵循 RAII 原则来设计。
如标准库中的 STL 容器、智能指针等都是RAII。

//核心思想
资源的获取应与对象的生命周期绑定。

具体来说：
1、在对象构造时获取资源（如内存、文件句柄、锁、网络连接等）；
2、在对象析构时释放资源；
3、这样就能利用作用域自动管理资源，防止泄漏或未释放。

//非 RAII 风格的问题
void func() {
	FILE* fp = fopen("xxx.txt", "r");
	// 中间一旦异常，fclose 根本没机会执行
	fclose(fp);
}



/********************/智能指针/************************************************************/
#include <memory>
using namespace std;


//定义格式
智能指针<数据类型>指针名(指向的对象，可选删除器);

unique_ptr<int> uptr; 		//独占型的智能指针
shared_ptr<int> sptr;		//共享型智能指针
weak_ptr<int> wptr;			//弱引用型指针指针


因为智能指针是c++11的特性，所以编译时加上 - std = c++11

//优点
1、自动内存管理： 智能指针自动处理内存的分配和释放，无需手动调用 new 和 delete 。
2、避免内存泄漏： 由于智能指针自动管理内存，因此减少了忘记释放内存导致的内存泄漏的风险。
3、避免悬挂指针问题： unique_ptr 和 shared_ptr 在对象生命周期结束时自动释放内存，防止了悬挂指针问题。
4、提高代码可读性： 智能指针有助于表达代码中的所有权关系，使得代码更加清晰和易于理解。
5、异常安全： 当使用智能指针时，如果在分配内存后发生异常，智能指针会确保分配的内存被正确释放，从而提高了程序的异常安全性。
6、RAII（资源获取即初始化）： 智能指针符合 RAII 原则，即资源在构造时获取，在析构时释放。这种方式简化了资源管理的代码结构。


//被废弃的智能指针
auto_ptr是被废弃的，这个指针有BUG。它的进阶就是unique_ptr。

智能指针 auto_ptr
① 对于auto_ptr，实现独占式拥有概念，同一时间只能有一个智能指针可以指向该对象;
② 但是auto_ptr在c++17中被摒弃，其主要问题在于对象所有权的转移，
   比如在函数参数传递过程中，对象的所有不会返还，从而存在潜在的内存崩溃问题，不能指向数组，也不能作为STL容器成员


//共有成员方法
operator*()			获取当前 unique_ptr 指针指向的数据。
operator->()		重载->箭头号，可以像普通指针一样直接操作成员。
operator =()		重载 = 赋值号，可以直接赋值 nullptr 或者另一个同类型的 unique_ptr 指针。
operator []()		重载[] 运算符，当 unique_ptr 指针指向一个数组时，可以直接通过[] 获取指定下标位置处的数据。
operator bool()		允许 unique_ptr 作为布尔值在条件语句中使用，检查它内部的原始指针是否为空。
swap(x)				将当前智能指针和同类型的 x 智能指针管理的对象交换（删除器类型也应相同）。



/********************/unique_ptr<>/************************************************************/
template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
public:
	// 构造函数
	unique_ptr(T* ptr, Deleter deleter = Deleter());	//删除器默认std::default_delete<T>，即调用delete操作符

	// 其它成员函数
};

① 对于unique_ptr，实现独占式拥有概念，同一时间只能有一个智能指针可以指向该对象。也因此不能调用拷贝构造函数，但可以进行移动构造和移动赋值;
② 当unique_ptr的对象被销毁时，它会自动释放指向的堆空间。


//成员方法
get()				获取内部包含的普通指针。
get_deleter()		获取释放堆内存空间所用的函数对象。
release()			释放当前 unique_ptr 所指对象的管理权，但不会释放该对象。
reset()				不传参或传 nullptr ，会释放当前智能指针管理的对象，并指向 nullptr 。若传入普通指针，则会释放当前对象并重新指向新传入的指针。


//make_unique<>		(C++14)
std::make_unique 是一个工厂函数，用于创建 std::unique_ptr 实例并返回。它更加安全且避免了使用裸指针。



/********************/shared_ptr<>/************************************************************/
① 对于shared_ptr，实现共享式拥有概念，即多个指针可以指向相同的对象，该对象及其资源会在其所指对象不再使用时，自动释放与对象相关的资源;
② 当shared_ptr的对象被销毁时, 会查看当前是否有其他指针指向这个堆空间，如果没有了，则释放; 如果还存在，则不释放。
③ 带有引用计数机制，支持多个指针度下行指向同一内存(实现共享)。
④ shared_ptr是在unique_ptr的基础上，增加了一个计数值count, 用来保存指向这个堆空间的指针个数，只有当计数值为0的时候，才会释放内存。


//成员方法
get()			获得 shared_ptr 对象内部包含的普通指针。
use_count()		返回所有指向对象的引用计数。（也即指向该对象的shared_ptr的数量）
unique()		若当前 shared_ptr 是唯一的所有者（即引用计数为 1），则返回 true ，否则返回 false 。
reset()			不传参或传 nullptr ，会释放当前智能指针管理的对象，并指向 nullptr ，同时引用计数-1；若传入普通指针，则会释放当前对象，同时引用计数 - 1，然后重新指向新传入的指针，并且引用计数 + 1。


//make_shared<>
std::shared_ptr<T> make_shared<T>(Args&&... args);		//原型

std::make_shared 是一个工厂函数（模板），用于创建 std::shared_ptr 实例并返回，
相对于直接使用 new 或 shared_ptr 的构造函数，make_shared 更为高效。他避免了两次内存分配，并减少了引用计数的内存开销。



/********************/weak_ptr<>/************************************************************/
① 对于weak_ptr, 解决shared_ptr相互引用的问题：若两个share_ptr指针相互引用，那么两个指针都将无法释放，从而导致死锁问题。
② 而weak_ptr是对对象的一种弱引用，可以绑定到shared_ptr, 但是不会增加的对象引用计数（即weak_ptr不会使use_count+1）。


//成员方法
use_count()	返回所有指向对象的引用计数。（也即指向该对象的shared_ptr的数量）
expired()	判断当前 weak_ptr 指针为否过期（指针为空，或者指向的堆内存已经被释放）。
lock()		如果当前 weak_ptr 已经过期，则该函数会返回一个空的 shared_ptr 指针；反之，该函数返回一个和当前 weak_ptr 指向相同的 shared_ptr 指针。
reset()		释放当前智能指针管理的对象，并指向 nullptr 。不接受参数。



/********************/enable_shared_from_this<>/************************************************************/
std::enable_shared_from_this 是一个模板基类，通常与 std::shared_ptr 一起使用，
允许一个对象从其自身的成员函数内部创建一个指向其自身的 std::shared_ptr。

确保对象的生命周期不被提前销毁，从而避免出现悬挂指针或访问已销毁对象的情况。

注意：只有当一个对象已经被 std::shared_ptr 管理时，shared_from_this() 才能被安全地调用，否则会导致运行时错误。


#include <iostream>  
#include <memory>  

class MyClass : public std::enable_shared_from_this<MyClass> 
{
public:
	void doSomething() 
	{	
		std::shared_ptr<MyClass> ptr = shared_from_this();				// 获取一个指向当前对象的 shared_ptr  	
		std::cout << "Doing something with the shared_ptr" << std::endl;	// 现在你可以使用这个 ptr 做任何事情  
	}
};

int main() 
{
	std::shared_ptr<MyClass> obj = std::make_shared<MyClass>();		// 创建一个 MyClass 的 shared_ptr  
	
	obj->doSomething();										// 调用成员函数，该函数内部使用 shared_from_this()  
	return 0;
}



/********************/unique_ptr<>实例/************************************************************/
#include <iostream>
#include <memory>

using namespace std;


class Person {
public:
	Person(int _a) :a(_a) {
		cout << "Person 构造" << endl;
	}
	~Person() {
		cout << "Person 析构  a=" << a << endl;
	}
	void show() {
		cout << "Person::show() a=" << a << endl;
	}

	int a;
};

int main()
{
	unique_ptr<Person> A(new Person(100));

	//报错
	//unique_ptr<Person> B = A;

	//A = NULL;//已经释放掉了A指向的堆空间
	A.reset(new Person(200));

	//使用方式与普通指针保持一致
	A->show();
	(*A).show();


	//手动接收并释放;
	Person* ptr = A.release();
	delete ptr;
}



/********************/share_ptr<>实例/************************************************************/
#include <iostream>
#include <memory>

using namespace std;

class Person {
public:
	Person(int _a) :a(_a) {
		cout << "Person 构造" << endl;
	}
	~Person() {
		cout << "Person 析构  a=" << a << endl;
	}
	void show() {
		cout << "Person::show() a=" << a << endl;
	}
	int a;
};

void func(shared_ptr<Person>& P)
{
	shared_ptr<Person> M = P;

	cout << "P.use_count()=" << P.use_count() << endl;
}


int main()
{
	shared_ptr<Person> A(new Person(100));
	cout << "A.use_count()=" << A.use_count() << endl;


	shared_ptr<Person> B = A;
	cout << "A.use_count()=" << A.use_count() << endl;
	cout << "B.use_count()=" << B.use_count() << endl;

	cout << "---" << endl;
	func(A);
	cout << "---" << endl;
	cout << "A.use_count()=" << A.use_count() << endl;

	cout << "-----------------------" << endl;
	A.reset(new Person(200));
	cout << "A.use_count()=" << A.use_count() << endl;
	cout << "B.use_count()=" << B.use_count() << endl;

	cout << "-----------------------" << endl;

	A->show();
	(*A).show();

}



/********************/weak_ptr<>实例/************************************************************/
#include <iostream>
#include <memory>

using namespace std;

class Person;

struct mylist {
	/* shared_ptr<Person> next;
	shared_ptr<Person> prev; */

	weak_ptr<Person> next;
	weak_ptr<Person> prev;
};

class Person {
public:
	Person() {
		cout << "Person 构造" << endl;
	}
	~Person() {
		cout << "Person 析构" << endl;
	}

	struct mylist node;
};

int main()
{
	shared_ptr<Person> A(new Person);
	shared_ptr<Person> B(new Person);

	A->node.next = B;
	B->node.prev = A;
}



