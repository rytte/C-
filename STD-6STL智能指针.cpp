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
2、unique_ptr是独占型智能指针，只允许一个智能指针指向同一块内存，不能调用拷贝构造函数。

成员方法 :
operator=另一个对象：
	reset(另一个对象)：先释放原指针指向的堆空间，再指向新的堆空间
	release()：返回当前指针指针指向的对象，然后智能指针指向NULL;

智能指针的使用与普通指针相同，都有* 和->符号


/********************/shared_ptr<>/************************************************************/
智能指针 shared_ptr
① 对于shared_ptr，实现共享式拥有概念，即多个指针可以指向相同的对象，该对象及其资源会在其所指对象不再使用时，自动释放与对象相关的资源;
② 带有引用计数机制，支持多个指针度下行指向同一内存(实现共享)。


1.当shared_ptr的对象被销毁时, 会查看当前是否有其他指针指向这个堆空间，如果没有了，则释放; 如果还存在，则不释放。
2.shared_ptr是在unique_ptr的基础上，增加了一个计数值count,用来保存指向这个堆空间的指针个数，只有当计数值为0的时候，才会释放内存。

成员方法 :
	use_count()：获取指向堆空间的智能指针的个数

operator=另一个对象：
	reset(另一个对象)：先释放原指针指向的堆空间，再指向新的堆空间

	智能指针的使用与普通指针相同，都有* 和->符号


/********************/weak_ptr<>/************************************************************/
智能指针 weak_ptr
① 对于weak_ptr, 解决shared_ptr相互引用的问题：若两个share_ptr指针相互引用，那么两个指针都将无法释放，从而导致死锁问题。
② 而weak_ptr是对对象的一种弱引用，可以绑定到shared_ptr, 但是不会增加的对象引用计数。


1.weak_ptr一般是shared_ptr的辅助使用。
2.weak_ptr指向相同的内存时，use_count的数值不会 + 1



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



