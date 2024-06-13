/********************/C++调用Python/************************************************************/
通过cpython的C API调用实现。


/********************/python调用C++/************************************************************/
cython：cython是python语言的一个超集，它允许Python程序员编写C扩展模块。
pybind11：pybind11是一个轻量级的仅头文件库，主要用于创建现有C++代码的Python绑定。
ctypes：ctypes是Python的一个标准库，它提供了C兼容的数据类型，并允许调用共享库（如DLL或.so文件）中的函数。
Boost.Python：Boost.Python是Boost库的一部分，它提供了一套用于创建Python扩展的API。
SWIG：通过SWIG，你可以为C / C++函数和类创建包装器，这些包装器使得Python等语言能够调用这些C / C++代码。
cffi：cffi是一个Python的外部函数接口，它提供了一个简单且快速的方式来调用C代码。

//pybind11为主流方式
1、安装 pybind11：pip install pybind11。（pip 安装的 pybind11 主要用于开发，并不包含编译 Python 扩展所需的头文件）
2、从 GitHub 克隆 pybind11 仓库或使用其他方式获取 pybind11 头文件。
3、编写 C++ 代码 (example.cpp)
4、编译 C++ 代码（CMake）
cmake ..
make (或者MSBuild project.sln)
将生成一个名为 example.cpython - *.so（在 Unix 系统上）或 example.cp3 * .pyd（在 Windows 上）的共享库文件，其中 * 是你的 Python 版本号。
5、在 Python 中使用模块
import example  
print(example.add(3, 4))  //输出 7



// example.cpp
#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int a, int b) {
    return a + b;
}

PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function which adds two numbers");
}


//CMakeLists.txt
cmake_minimum_required(VERSION 3.5)

project(pybind11 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(pybind11 - 2.12.0 / )
pybind11_add_module(example main.cpp)



////////绑定类////////
// myclass.h  
#ifndef MYCLASS_H  
#define MYCLASS_H  

class MyClass {
public:
    MyClass(int value) : value_(value) {}

    int getValue() const { return value_; }

    void setValue(int value) { value_ = value; }

private:
    int value_;
};

#endif // MYCLASS_H


// pybind_example.cpp  
// 静态函数使用def_static替代def
// 重载函数使用py::overload_cast<>转换
#include <pybind11/pybind11.h>  
#include "myclass.h"  

namespace py = pybind11;

PYBIND11_MODULE(example, m) {
    py::class_<MyClass>(m, "MyClass")
        .def(py::init<int>())
        .def("get_value", &MyClass::getValue)
        .def("set_value", &MyClass::setValue);
}


//使用
import example  

# 创建一个 MyClass 的实例
my_obj = example.MyClass(10)

# 调用方法
print(my_obj.get_value())  # 输出: 10
my_obj.set_value(20)
print(my_obj.get_value())  # 输出 : 20


