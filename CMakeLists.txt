"********************"CMake"************************************************************"
CMake是一个跨平台的安装（编译）工具，用于生成Makefile文件。


编写好 CMakeList.txt 文件后，执行：cmake .
生成Makefile文件，执行：make
生成编译后的可执行文件。


"************************************************************"
cmake_minimum_required(VERSION 2.8)

project(demo)

add_executable(main main.c testFunc.c)


"************************************************************"

把指定目录下所有的源文件存储在一个变量中，命令：

aux_source_directory(dir var)

第一个参数dir是指定目录，第二个参数var是用于存放源文件列表的变量。



#实例
cmake_minimum_required (VERSION 2.8)

project (demo)

aux_source_directory(. SRC_LIST)

add_executable(main ${SRC_LIST})


"************************************************************"
aux_source_directory()也存在弊端，它会把指定目录下的所有源文件都加进来，
可能会加入一些我们不需要的文件，此时我们可以使用set命令去新建变量来存放需要的源文件


#实例
cmake_minimum_required (VERSION 2.8)

project (demo)

set( SRC_LIST
	 ./main.c
	 ./testFunc1.c
	 ./testFunc.c)

add_executable(main ${SRC_LIST})


"********************"不同目录下有多个源文件"************************************************************"
模块分别在 test_func 和 test_func1 目录下，include_directories：该命令是用来向工程添加多个指定头文件的搜索路径

也可以在main.c里使用include来指定路径，如下
#include "test_func/testFunc.h"
#include "test_func1/testFunc1.h"


#实例
cmake_minimum_required (VERSION 2.8)

project (demo)

include_directories (test_func test_func1)

aux_source_directory (test_func SRC_LIST)
aux_source_directory (test_func1 SRC_LIST1)

add_executable (main main.c ${SRC_LIST} ${SRC_LIST1})


"********************"项目结构"************************************************************"
一般会把源文件放到src目录下，
把头文件放入到include文件下，
生成的对象文件放入到build目录下，
最终输出的可执行程序文件会放到bin目录下，
这样整个结构更加清晰。


#实例
cmake_minimum_required (VERSION 2.8)

project (demo)

add_subdirectory (src)



add_subdirectory：这个语句的作用是增加编译子目录。其基本语法格式是：
add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
一共有三个参数，后两个是可选参数.

source_dir 源代码目录
指定一个包含CMakeLists.txt和代码文件所在的目录，该目录可以是绝对路径，
也可以是相对路径，对于后者相对路径的起点是CMAKE_CURRENT_SOURCE_DIR。
此外，如果子目录再次包含的CMakeLists.txt，则将继续处理里层的CMakeLists.txt，而不是继续处理当前源代码。

binary_dir 二进制代码目录
这个目录是可选的，如果指定，cmake命令执行后的输出文件将会存放在此处，
若没有指定，默认情况等于source_dir没有进行相对路径计算前的路径，也就是CMAKE_BINARY_DIR。

EXCLUDE_FROM_ALL标记
这个标志是可选的，如果传递了该参数表示新增加的子目录将会排除在ALL目录之外（可能是make系统中的make all？），
表示这个目录将从IDE的工程中排除。用户必须显式在子文件这个编译目标（手动cmake之类的）。
指定了这个文件夹，表示这个文件夹是独立于源工程的，这些函数是有用但是不是必要的，比如说我们一系列的例子。


add_subdirectory 这个命令用于添加源文件子目录，同时还可以指定中间二进制和目标二进制的生成路径。
EXCLUDE_FROM_ALL将会将这个目录从编译中排除，如工程的例子需要等待其他编译完成后再进行单独的编译。
通常子目录应该包含自己的project()命令，这样以来整个编译命令将会产生各自的目标文件。
如果把CMakeLists.txt与VS IDE比较，总的CMakeLists.txt就相当于解决方案，子CMakeLists.txt就相当于在解决方案下的工程文件。
还有一个需要注意的是，如果编译父CMakeLists时依赖了子CMakeLists.txt中的源文件，
那么该标志将会被覆盖（也就是也会处理），以满足编译任务。

这里指定src目录下存放了源文件，当执行cmake时，就会进入src目录下去找src目录下的CMakeLists.txt，
所以在src目录下也建立一个CMakeLists.txt

aux_source_directory (. SRC_LIST)

include_directories (../include)

add_executable (main ${SRC_LIST})

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

这里的set其实是和前面的一样，只是EXECUTABLE_OUTPUT_PATH是个系统自带的预定义变量，其意义如下：

* EXECUTABLE_OUTPUT_PATH ：目标二进制可执行文件的存放位置
* PROJECT_SOURCE_DIR：工程的根目录
所以，这里set的意思是把存放elf文件的位置设置为工程根目录下的bin目录。



cmake_minimum_required (VERSION 2.8)

project (demo)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory (src SRC_LIST)

include_directories (include)

add_executable (main ${SRC_LIST})



"********************"动态库和静态库的编译"************************************************************"
cmake_minimum_required (VERSION 3.5)

project (demo)

set (SRC_LIST ${PROJECT_SOURCE_DIR}/testFunc/testFunc.c)

add_library (testFunc_shared SHARED ${SRC_LIST})
add_library (testFunc_static STATIC ${SRC_LIST})

set_target_properties (testFunc_shared PROPERTIES OUTPUT_NAME "testFunc")
set_target_properties (testFunc_static PROPERTIES OUTPUT_NAME "testFunc")

set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


