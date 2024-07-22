/********************/模块/************************************************************/
模块 旨在解决C++传统头文件机制的一些缺点，如编译速度慢、代码重复和命名空间污染等问题。
模块 提供了一种更现代化、更高效的代码组织和重用方式，替代传统的头文件机制。


//提高编译速度，减少冗余解析
模块预编译和中间表示：模块可以被预编译为二进制格式的编译单元。每当需要使用时编译器可直接读取。而头文件在每个包含它们的翻译单元中都会被重复解析和编译。

//提供更好的模块化和封装性；简化依赖管理，优化编译过程。
明确的导出(export)和导入机制(import), 模块显式定义了哪些符号（函数、类、变量等）是导出的，这些符号可以被其他模块或翻译单元使用，而其他符号则是私有的。
从而减少重复定义(命名冲突)的问题。


//VS设置
1.C / C++->语言标准->设置为C++20或C++latest
2.C / C++->语言标准->启用实验性的C++标准库模块->是
3.C / C++->高级->编译为->作为C++模块代码编译



/********************/实例;/************************************************************/
// main.cpp
import myModule;

int main() {
    int result = add(3, 4);
    int result2 = subtract(7, 2);

    MyClass obj;
    obj.sayHello();
    return 0;
}


// myModule.ixx - 模块接口单元（相当于头文件）
import <iostream>;
export module myModule;

export int add(int a, int b) {
    return a + b;
}

export int subtract(int a, int b);

export class MyClass {
public:
    void sayHello() const {
        std::cout << "Hello from MyClass" << std::endl;
    }
};


// myModule_impl.ixx - 模块实现单元（相当于源文件）
module myModule;

int subtract(int a, int b) {
    return a - b;
}

