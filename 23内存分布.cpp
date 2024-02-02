

//类成员的内存分布
先定义的在前


//类继承时的子类内存分布
class A {};
class B : public A {};

基类A的成员在前，派生类B的成员在后。


//多继承时的派生类内存分布
class A {};
class B {};
class C {};
class D : public A, public B, public C {};

首先是基类A的部分，然后是基类B的部分，最后是基类C的部分。每个基类部分都有自己的数据成员和虚表指针（如果有虚函数的话）。


//菱形继承
class A {};
class B : public A {};
class C : public A {};
class D : public B, public C {};

顺序：A-B-A-C-D


//虚函数和虚表



需要注意的是，具体的内存布局可能受到编译器、编译选项以及对齐规则的影响。
在某些情况下，编译器可能会在派生类对象中插入一些额外的字节，以满足对齐要求。
因此，确切的内存布局可能因编译器而异。




/********************/实例/************************************************************/
#include <iostream>
using namespace std;

class GrandParent
{
public:
        int fun() {};

private:
        int a{ 10 };
        int b{ 20 };
};


class Parent1 : public GrandParent
{
private:
        int a{ 30 };
        int b{ 40 };
};


class Parent2 : public GrandParent
{
private:
        int a{ 50 };
        int b{ 60 };
};


class Child : public Parent1, public Parent2
{
public:
        Child() {}

private:
        int a{ 70 };
        char b;                         //此处进行字节对齐
        int c{ 80 };
};

int main() {
        GrandParent grandParent;
        Child* child = new Child;
        int* ptr = (int*)child;
        cout << sizeof(GrandParent) << endl;        //输出8，类定义本身不占用内存空间，此处为计算大小
        cout << sizeof(grandParent) << endl;        //输出8
        cout << sizeof(Child) << endl;                   //输出44，说明 GrandParent 成员被继承了两次（无论公有还是私有）

        printf("%p\n", child);
        printf("%p\n", ++child);                        //偏移一个类大小个字节
        printf("%p\n", ptr);

        printf("ptr:%d\n", *ptr);                        //输出10，Parent1
        printf("+1：%d\n", *(ptr + 1));             //输出20
        printf("+2：%d\n", *(ptr + 2));             //输出30
        printf("+3：%d\n", *(ptr + 3));             //输出40
        printf("+4：%d\n", *(ptr + 4));             //输出10，Parent2
        printf("+5：%d\n", *(ptr + 5));             //输出20
        printf("+6：%d\n", *(ptr + 6));             //输出50
        printf("+7：%d\n", *(ptr + 7));             //输出60
        printf("+8：%d\n", *(ptr + 8));             //输出70，Child
        printf("+9：%d\n", *(ptr + 9));             //输出-842150451
        printf("+10: %d\n", *(ptr + 10));           //输出80

        return 0;
}

