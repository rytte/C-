/********************/工具链/************************************************************/
//MSYS2
MSYS2是一个包含MinGW - w64工具链、GNU工具集和一些开源库的平台，它提供了一种在Windows上编译和运行Unix / Linux程序的方式。
MSYS2与MinGW - w64相似，但比MinGW - w64更完整和稳定，提供了Pacman包管理器以方便用户安装和管理软件包。

//MinGW
MinGW - w64是一个Windows下的C / C++编程工具集，它提供了运行在Windows上的GNU工具集和GCC编译器。
MinGW - w64与MSYS2类似，但主要用于编译Windows本地应用程序，而非Unix / Linux程序。
MinGW - w64也可以用于交叉编译，为其他平台生成Windows可执行文件。

//Cygwin
Cygwin是一个在Windows平台上运行的兼容性层，提供了类Unix环境的工具和开发库。
Cygwin将Unix程序编译为Windows本地代码，然后在Windows上运行。
它提供了最完整的Linux / Unix环境，但相对于MSYS2和MinGW - w64，Cygwin的性能较差。

//比较
MSYS2适用于需要在Windows上编译和运行Unix / Linux程序的场景，
MinGW - w64适用于编译Windows本地应用程序的场景，
Cygwin适用于需要最完整的Linux / Unix环境的场景。
MSYS2和Cygwin被WSL2取代。


// MinGW安装
https://github.com/niXman/mingw-builds-binaries/releases (跳转至MinGW - w64的GitHub仓库)

版本标识的解释："电脑系统架构-gcc版本号-release-操作系统接口协议-异常处理模型"
i686为32位，x86_64为64位
win32为windows操作系统，posix为其他操作系统
dwarf针对32位，seh针对64位
优先选择ucrt

解压后添加至环境变量即可。







