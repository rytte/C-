/********************/C++调用Python/************************************************************/
通过cpython的C API调用实现。


//Qt Creator配置Python解释器
1、工具 >> 选项 >> 环境 >> External Tools
2、添加 >> Add Category >> 重命名为RunPy
3、添加 >> Add Tool >> 重命名为Python3
4、执行档：C:\Users\13055\miniconda3\python.exe
参数：% { CurrentDocument:FilePath }
工作目录：% { CurrentDocument:Path }
Base environment：System Environment
5、Apply >> OK
6、运行点击：工具 >> 外部 >> RunPy >> Python3



/********************/python调用C++/************************************************************/
cython：cython是python语言的一个超集，它允许Python程序员编写C扩展模块。
pybind11：pybind11是一个轻量级的仅头文件库，主要用于创建现有C++代码的Python绑定。
ctypes：ctypes是Python的一个标准库，它提供了C兼容的数据类型，并允许调用共享库（如DLL或.so文件）中的函数。
Boost.Python：Boost.Python是Boost库的一部分，它提供了一套用于创建Python扩展的API。
SWIG：通过SWIG，你可以为C / C++函数和类创建包装器，这些包装器使得Python等语言能够调用这些C / C++代码。
cffi：cffi是一个Python的外部函数接口，它提供了一个简单且快速的方式来调用C代码。


//pybind11为主流方式
流程：使用pybind11库将cpp文件编译成python库文件，供python代码使用
pybind11 是一个 header - only library，只需要头文件（还有cmake）即可使用

1、获取头文件，以及cmake支持文件
方法一：
安装 pybind11：pip install pybind11
查看安装的路径：pip show pybind11
cmake中
set(pybind11_DIR C : / Users / 13055 / miniconda3 / Lib / site - packages / pybind11 / share / cmake / pybind11)
find_package(pybind11 REQUIRED)
方法二：
从 GitHub 获取。(https://github.com/pybind/pybind11) pybind11源文件夹放在工程目录下
cmake：add_subdirectory(pybind11 - 2.13.6 /)
2、编写 C++ 代码 (example.cpp)
3、编译 C++ 代码（CMake）
mkdir build
cd build
cmake ..
make (或者MSBuild pybind11.sln)
将生成一个名为 example.cpython - *.so（在 Unix 系统上）或 example.cp3 * .pyd（在 Windows 上）的共享库文件，其中 * 是你的 Python 版本号。
4、在 Python 中使用模块    //导入时该目录下需要有pyd文件，以及相关的链接库文件
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

//带依赖库
//include_directories(${ PROJECT_SOURCE_DIR } / FFmpeg / include)
//link_directories(${ PROJECT_SOURCE_DIR } / FFmpeg / lib)
//target_link_libraries(example PRIVATE
//    ${ PROJECT_SOURCE_DIR } / FFmpeg / lib / avformat.lib
//    ${ PROJECT_SOURCE_DIR } / FFmpeg / lib / avcodec.lib
//)


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
// 私有成员无需绑定
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











