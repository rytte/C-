
/********************/方式1/************************************************************/
方式1：使用 system() 函数执行 Python 脚本

#include <cstdlib>
#include <iostream>

int main() 
{
    // 执行 Python 脚本
    int result = system("python C:/path_to_your_script/hello.py");

    if (result == 0)
        std::cout << "Python script executed successfully!" << std::endl;
    else
        std::cerr << "Error executing Python script." << std::endl;


    return 0;
}



/********************/方式2/************************************************************/
方式2：Python C API，直接执行 Python 嵌入代码 或 脚本文件

#include <Python.h>
#include <iostream>
//.pro：添加头文件和库文件
//INCLUDEPATH += C:\Users\13055\miniconda3\include
//LIBS += -LC:\Users\13055\miniconda3\libs -lpython310

int main(int argc, char* argv[])
{
    _putenv("PYTHONHOME=C:\\Users\\13055\\miniconda3");
    _putenv("PYTHONPATH=C:\\Users\\13055\\miniconda3\\Lib");

    // 初始化 Python 解释器
    Py_Initialize();

    // 直接在 C++ 代码中执行 Python 代码
    const char* code = R"(
print("Hellp Cpp!")
)";
    PyRun_SimpleString(code);

    // 直接在 C++ 代码中执行 Python 脚本
    FILE* fp = _Py_fopen("C:/path_to_your_script/hello.py", "r");
    if (fp != nullptr) 
    {
        PyRun_SimpleFile(fp, script_path);
        fclose(fp);
    }
    else 
    {
        std::cerr << "Failed to open Python script" << std::endl;
    }

    // 结束 Python 解释器
    Py_Finalize();
    return 0;

}



/********************/方式3/************************************************************/
方式3：Python C API，调用类和函数，适合需要数据交互的情况

#include <Python.h>
#include <iostream>

//技巧：可以将Module、Argument、Object、Class、Function封装成一个或多个类来管理。

//.pro：添加头文件和库文件
//INCLUDEPATH += C:\Users\13055\AppData\Local\Programs\Python\Python310\include
//LIBS += -LC:\Users\13055\AppData\Local\Programs\Python\Python310\libs -lpython310

int main(int argc, char* argv[])
{
    _putenv("PYTHONHOME=C:\\Users\\13055\\miniconda3");
    _putenv("PYTHONPATH=C:\\Users\\13055\\miniconda3\\Lib");

    // 初始化Python解释器
    Py_Initialize();

    // 添加Python脚本的目录到你的PYTHONPATH
    PyRun_SimpleString("import sys; sys.path.append(\"../python_cpp\")");

    // 加载Python脚本模块
    PyObject* pName = PyUnicode_FromString("script");
    PyObject* pModule = PyImport_Import(pName);

    if (pModule == nullptr)
    {
        PyErr_Print();
        std::cerr << "Failed to load \"script\" module." << std::endl;
        return -1;
    }


    //////////////////////////函数调用//////////////////////////
        // 获取函数对象
    PyObject* pFunc = PyObject_GetAttrString(pModule, "add_numbers");

    if (PyCallable_Check(pFunc))
    {
        // 准备参数
        PyObject* pArgs = PyTuple_New(2);
        PyTuple_SetItem(pArgs, 0, PyLong_FromLong(2));
        PyTuple_SetItem(pArgs, 1, PyLong_FromLong(3));

        // 调用函数并获取结果
        PyObject* pValue = PyObject_CallObject(pFunc, pArgs);

        if (pValue != nullptr)
        {
            // 将结果转换为整数并打印
            long result = PyLong_AsLong(pValue);
            std::cout << "Result of add_numbers(2, 3): " << result << std::endl;
        }
        else
        {
            PyErr_Print();
        }
    }
    else
    {
        if (PyErr_Occurred())
        {
            PyErr_Print();
        }
        std::cerr << "Cannot find function \"add_numbers\"" << std::endl;
    }


    //////////////////////////类调用//////////////////////////
        // 获取模块中的类
    PyObject* pClass = PyObject_GetAttrString(pModule, "MyClass");

    if (pClass && PyType_Check(pClass))
    {
        // 创建一个包含构造函数参数的元组
        PyObject* pArgs = PyTuple_New(1);               // 假设有一个参数
        PyTuple_SetItem(pArgs, 0, PyLong_FromLong(42)); // 将值42放在元组的第一个位置

        // 调用构造函数创建类的实例
        PyObject* pInstance = PyObject_CallObject(pClass, pArgs);

        if (pInstance && PyObject_IsInstance(pInstance, (PyObject*)pClass))
        {
            // 调用print_value方法
            PyObject* pResult = PyObject_CallMethod(pInstance, "print_value", nullptr);

            // 如果print_value方法没有返回值（或者我们不关心它），则忽略pResult，否则打印异常
            if (!pResult)
            {
                PyErr_Print(); // 打印异常信息
            }
        }
        else
        {
            if (PyErr_Occurred())
            {
                PyErr_Print();
            }
            std::cerr << "Failed to create instance of MyClass.\n";
        }
    }
    else
    {
        if (PyErr_Occurred())
        {
            PyErr_Print();
        }
        std::cerr << "Failed to get MyClass from module.\n";
    }


    // 关闭Python解释器
    Py_Finalize();

    return 0;
}



/********************/方式4/************************************************************/
方式4：使用 Pybind11 API

#include <pybind11/embed.h>  // pybind11 提供的嵌入式 API
#include <iostream>

namespace py = pybind11;

int main() 
{
    // 初始化 Python 解释器
    py::scoped_interpreter guard{};

    try 
    {
        // 导入并执行 Python 文件
        py::exec(R"(
print("Hellp Cpp!")
        )");
    }
    catch (const py::error_already_set& e) 
    {
        std::cerr << "Python error: " << e.what() << std::endl;
    }

    return 0;
}
