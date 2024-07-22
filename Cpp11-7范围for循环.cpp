/********************/范围 for 循环/************************************************************/
该特性隐藏了迭代器的初始化、比较和更新过程

for (element : container)
{
	//循环体
}

element是一个临时的变量声明，代表容器中的每一个元素
container是一个可迭代的对象，如容器、数组等。对象必须满足以下2个条件中的任意一个：
① 对象类型定义了begin和end的成员函数
② 定义了以对象类型为参数的begin和end的普通函数


//有几种类型的对象可以直接用于范围 for 循环
数组：可以直接用范围 for 循环。
标准库容器（如 std::vector, std::list, std::map 等）：可以直接用范围 for 循环。
具有 begin 和 end 成员函数或与 begin 和 end 非成员函数一起使用的类：这些函数返回迭代器。
对于初始化列表{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }，它会自动转换为 std::initializer_list<int>，这是一个标准库类型，具有 begin 和 end 成员函数，因此也可以用于范围 for 循环。




示例1（遍历容器）：
std::map<int, std::string> mymap{ {1, "hello"}, {2, "world"}, {3, "!"} };

for (const auto& e : mymap)
{
	cout << e.first() << " " << e.second() << endl;
}

示例2（遍历数组）：
int arr[] = { 0,1,2,3,4,5 };

for (auto e : arr)
{
	cout << e << endl;
}

示例3
for (int i : {1, 2, 3, 4, 5})
{
	cout << i << endl;
}

// 优化
* 一般来说对复杂对象使用引用，对基础类型使用值，这样可以减少对内存的拷贝。
* 若在循环过程中不会修改引用对象，可以在范围声明中加上 const 修饰符，以帮助编译器生成更加高效的代码。


C++17标准：begin()和end()返回值类型不必相同
C++20标准：范围声明之前可以执行初始化语句，用";"隔开





//自定义支持范围for循环的容器
#include <iostream>

class CustomContainer {
public:
    CustomContainer(std::initializer_list<int> list) : data(new int[list.size()]), size(list.size()) {
        std::copy(list.begin(), list.end(), data);
    }

    ~CustomContainer() {
        delete[] data;
    }

    class Iterator {
    public:
        Iterator(int* ptr) : ptr(ptr) {}

        int& operator*() const { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }

    private:
        int* ptr;
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size); }

private:
    int* data;
    size_t size;
};

int main() {
    CustomContainer container = { 1, 2, 3, 4, 5 };

    for (int i : container) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
