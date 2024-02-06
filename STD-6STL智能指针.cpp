/********************/RAII模型/************************************************************/

RAII，全称为Resource Acquisition Is Initialization，汉语是“资源获取即初始化”。
简单说来就是，在资源获取的时候将其封装在某类的对象中，
利用"栈资源会在相应对象的生命周期结束时自动销毁"来自动释放资源，即，构造函数创建时初始化获取资源，并将资源释放写在析构函数中。
所以这个RAII其实就是和智能指针的实现是类似的。



/********************/智能指针/************************************************************/
#include <memory>
using namespace std;


//定义格式
智能指针<数据类型>指针名(指向的对象);


unique_ptr<int> uptr; 		//独占型的智能指针
shared_ptr<int> sptr;		//共享型智能指针
weak_ptr<int> wptr;		//弱引用型指针指针


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



/********************/unique_ptr<>/************************************************************/
智能指针 unique_ptr
① 对于unique_ptr，实现独占式拥有概念，同一时间只能有一个智能指针可以指向该对象;
② 无法进行拷贝构造和拷贝赋值，但是可以进行移动构造和移动赋值。


1、当unique_ptr的对象被销毁时，它会自动释放指向的堆空间
2、unique_ptr是独占型智能指针，只允许一个智能指针指向同一块内存，因此不能调用拷贝构造函数。

//成员方法
operator*()		获取当前 unique_ptr 指针指向的数据。
operator->()		重载->号，当智能指针指向的数据类型为自定义的结构体时，通过->运算符可以获取其内部的指定成员。
operator =()		重载了 = 赋值号，从而可以将 nullptr 或者一个右值 unique_ptr 指针直接赋值给当前同类型的 unique_ptr 指针。
operator []()		重载了[] 运算符，当 unique_ptr 指针指向一个数组时，可以直接通过[] 获取指定下标位置处的数据。
get()				获取当前 unique_ptr 指针内部包含的普通指针。
get_deleter()		获取当前 unique_ptr 指针释放堆内存空间所用的规则。
operator bool()	unique_ptr 指针可直接作为 if 语句的判断条件，以判断该指针是否为空，如果为空，则为 false；反之为 true。
release()			释放当前 unique_ptr 指针对所指堆内存的所有权，但该存储空间并不会被销毁。
reset(p)			其中 p 表示一个普通指针，如果 p 为 nullptr，则当前 unique_ptr 也变成空指针；反之，则该函数会释放当前 unique_ptr 指针指向的堆内存（如果有），然后获取 p 所指堆内存的所有权（p 为 nullptr）。
swap(x)			交换当前 unique_ptr 指针和同类型的 x 指针。



/********************/shared_ptr<>/************************************************************/
智能指针 shared_ptr
① 对于shared_ptr，实现共享式拥有概念，即多个指针可以指向相同的对象，该对象及其资源会在其所指对象不再使用时，自动释放与对象相关的资源;
② 带有引用计数机制，支持多个指针度下行指向同一内存(实现共享)。


1.当shared_ptr的对象被销毁时, 会查看当前是否有其他指针指向这个堆空间，如果没有了，则释放; 如果还存在，则不释放。
2.shared_ptr是在unique_ptr的基础上，增加了一个计数值count,用来保存指向这个堆空间的指针个数，只有当计数值为0的时候，才会释放内存。

//成员方法
operator=()		重载赋值号，使得同一类型的 shared_ptr 智能指针可以相互赋值。
operator*()		重载* 号，获取当前 shared_ptr 智能指针对象指向的数据。
operator->()		重载->号，当智能指针指向的数据类型为自定义的结构体时，通过->运算符可以获取其内部的指定成员。
swap()			交换 2 个相同类型 shared_ptr 智能指针的内容。
reset()			当函数没有实参时，该函数会使当前 shared_ptr 所指堆内存的引用计数减 1，同时将当前对象重置为一个空指针；当为函数传递一个新申请的堆内存时，则调用该函数的 shared_ptr 对象会获得该存储空间的所有权，并且引用计数的初始值为 1。
get()				获得 shared_ptr 对象内部包含的普通指针。
use_count()		返回同当前 shared_ptr 对象（包括它）指向相同的所有 shared_ptr 对象的数量。
unique()			判断当前 shared_ptr 对象指向的堆内存，是否不再有其它 shared_ptr 对象再指向它。
operator bool()	判断当前 shared_ptr 对象是否为空智能指针，如果是空指针，返回 false；反之，返回 true。


//make_shared<>
可以使用 make_shared 函数来创建共享指针，它是一个模板函数，可以接受任何类型的参数，
并返回一个指向该类型对象的共享指针。它可以将控制块和对象一起分配在堆上，
从而避免了两次内存分配，并减少了引用计数的内存开销，相对于直接使用 new 或 shared_ptr 的构造函数，make_shared 更为高效。
//语法
std::shared_ptr<T> make_shared< T >( Args&&... args );



/********************/weak_ptr<>/************************************************************/
智能指针 weak_ptr
① 对于weak_ptr, 解决shared_ptr相互引用的问题：若两个share_ptr指针相互引用，那么两个指针都将无法释放，从而导致死锁问题。
② 而weak_ptr是对对象的一种弱引用，可以绑定到shared_ptr, 但是不会增加的对象引用计数。


1.weak_ptr一般是shared_ptr的辅助使用。
2.weak_ptr指向相同的内存时，use_count的数值不会 + 1


operator=()	重载 = 赋值运算符，是的 weak_ptr 指针可以直接被 weak_ptr 或者 shared_ptr 类型指针赋值。
swap(x)	其中 x 表示一个同类型的 weak_ptr 类型指针，该函数可以互换 2 个同类型 weak_ptr 指针的内容。
reset()	将当前 weak_ptr 指针置为空指针。
use_count()	查看指向和当前 weak_ptr 指针相同的 shared_ptr 指针的数量。
expired()	判断当前 weak_ptr 指针为否过期（指针为空，或者指向的堆内存已经被释放）。
lock()	如果当前 weak_ptr 已经过期，则该函数会返回一个空的 shared_ptr 指针；反之，该函数返回一个和当前 weak_ptr 指向相同的 shared_ptr 指针。



/********************/enable_shared_from_this<>/************************************************************/
std::enable_shared_from_this 是一个模板基类，通常与其他智能指针（特别是 std::shared_ptr）一起使用，
以允许一个对象从其自身的成员函数内部获取一个指向其自身的 std::shared_ptr。

这个类的主要用途是当你有一个成员函数，它需要在内部创建一个指向对象自身的 std::shared_ptr，
但是你没有直接的 std::shared_ptr 来构造它时。
std::enable_shared_from_this 允许对象在已经被 std::shared_ptr 管理的情况下做到这一点。


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

注意，只有当一个对象已经被 std::shared_ptr 管理时，shared_from_this() 才能被安全地调用。
如果对象没有被 std::shared_ptr 管理，调用 shared_from_this() 会导致运行时错误。




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



	//A开始指向NULL;
	Person* ptr = A.release();
	delete ptr;

	cout << "--------" << endl;

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



