"********************"CMake"************************************************************"
CMake是一个跨平台的安装（编译）工具，用于生成Makefile文件。

文件名格式：CMakeList.txt 或 .cmake 后缀文件。

#执行
编写好 CMakeList.txt 文件后，执行：cmake .
生成Makefile文件，执行：make
生成编译后的可执行文件。


#变量
变量类型：所有变量都是 string 类型
声明变量： set(变量名 变量值)			set(var 123)
移除变量： unset(变量名)
引用变量： ${变量名}
打印变量： message("var = ${var}")


#列表
列表是有多个值的变量，它也是字符串
set(list_var 1 2 3 4 5)


#操作符
优先级：括号 > 一元 > 二元 > 逻辑 
【一元】
EXIST
COMMAND
DEFINED
【二元】
EQUAL
LESS
LESS_EQUAL
GREATER
GREATER_EQUAL
STREQUAL
STRLESS
STRLESS_EQUAL
STRGREATER
STRGREATER_EQUAL
VERSION_EQUAL
VERSION_LESS
VERSION_GREATER_EQUAL
MATCHES
【逻辑】
NOT
AND
OR


#布尔常量值
类型			值
true			1，TRUE，ON，YES，Y，非0的值
false			0，FALSE，OFF，NO，N，IGNORE，NOTFOUND，空字符串，以 -NOTFOUND 结尾的字符串


#条件命令
if(表达式)
	COMMAND(ARGS ...)
elseif(表达式)
	COMMAND(ARGS ...)
else(表达式)
	COMMAND(ARGS ...)
endif(表达式)


#循环命令
while(表达式)
	COMMAND(ARGS ...)
endwhile(表达式)


#循环遍历
foreach(循环变量 参数1 参数2 ... 参数N)			#foreach(item 1 2 3)					
	COMMAND(ARGS ...)									#message("item = ${item}")
endforeach(循环变量)										#endforeach(item)

foreach(item RANGE 3)				#从1到3
foreach(item RANGE 1 5 2)			#从1到5增量为2
foreach(item IN LISTS 列表名)		#遍历列表


#循环控制命令
break() 命令可以跳出整个循环
continue()命令可以跳出当前循环


#自定义函数
function(函数名 参数1 参数2 ... 参数N)
	COMMAND(ARGS ...)	
endfunction(函数名)


#函数内置变量
ARGC		#函数参数个数
ARGV		#函数全部参数
ARGV0		#函数第一个参数


#自定义宏命令
macro(宏名 参数1 参数2 ... 参数N)
	COMMAND(ARGS ...)	
endmacro(宏名)


#变量作用域
全局层：cache 变量，在整个项目范围可见，一般在 set 定义变量时，指定 cache 参数就能定义为 cache 变量。
目录层：在当前目录 CMakeLists.txt 中定义，以及在该文件包含的其它cmake源文件中定义的变量。
函数层：在命令函数中定义的变量，属于函数作用域内的变量。



"********************"CMakeList.txt"************************************************************"
cmake_minimum_required(VERSION 2.8)						#指定cmake最低支持的版本（可选）

project(demo)

include_directories(目录1 目录2 目录N)							#不同目录下有多个源文件时，使用该命令来向工程添加多个指定头文件的搜索路径

aux_source_directory(目录名 变量名)								#把指定目录下所有的源文件存储在一个变量中，不包含子目录。"."表示当前目录。

set( SRC_LIST  ./main.c  ./testFunc1.c  ./testFunc.c)		#也可以使用set命令去新建变量来存放需要的源文件

add_executable(main ${SRC_LIST})								#添加可执行文件（文件名 源文件）

add_definitions(-DFOO -DDEBUG)									#为当前路径以及子目录的源文件加入由-D引入的define flag。用于添加编译参数

add_subdirectory(子目录名 [输出路径])							#子目录也需要包含有CMakeList.txt
						
set_directory_properties(PROPERTIES prop1 value1 prop2 value2)		#设置目录属性

set_property(<GLOBAL | 
					DIRECTORY [dir] | 
					TARGET [target ...] |
					SOURCE [src1 ...] |
					TEST [test1 ...] |
					CACHE [entry1 ...]>
					[APPEND]
					PROPERTY name [value ...])	
					#在给定的作用域内设置一个命名的属性
					#第一个参数决定属性影响的作用域：
					#GLOBAL：全局作用域
					#DIRECTORY：默认当前路径，也可以用[dir]指定路径
					#TARGET：目标作用域
					#SOURCE：源文件作用域
					#TEST：测试作用域
					#CACHE：必须指定0个或多个cache中已有的条目

#设置全局变量
set(EXECUTABLE_OUTPUT_PATH  [输出路径])				#设置可执行文件的输出路径
set(LIBRARY_OUTPUT_PATH [输出路径])						#设置库文件的输出路径
set(CMAKE_CXX_FLAGS  "-Wall std=c++11")				#设置C++编译参数

#文件操作命令
file(WRITE filename "message")									#覆盖写入message到文件
file(APPEND filename "message")								#追加写入message到文件
file(READ filename var [LIMIT numBytes] [OFFSET offset] [HEX])		#读取内容并存储到var中，offset处读取numBytes个字节，Hex表示以16进制形式存储
file(RENAME filename newname)								#重命名
file(REMOVE filename [file1 file2 ...])							#删除文件
file(REMOVE_RECURSE filename [file1 file2 ...])			#递归地删除文件
file(DOWNLOAD url file [TIMEOUT timeout] [STATUS status] [LOG log] [EXPERTED_MD5 sum] [SHOW_PROGRESS])		#根据指定的url下载文件
file(MAKE_DIRECTORY [dir1 dir2 ...])							#创建目录
file(TO_CMAKE_PATH path result)								#把path转换为以unix的/开头的cmake风格路径，保存在result中
file(TO_NATIVE_PATH path result)								#把cmake风格路径转换为本地风格路径
file(GLOB var [RELATIVE path] [globbing expressions]...)		#将所有匹配查询表达式的文件生成一个文件list并存储进variable



"********************"动静态库"************************************************************"

#添加一个库
add_library(库名变量 [库类型] [EXCLUDE_FROM_ALL] 指定库的源文件)		#库类型：STATIC(静态库)  SHARED(动态库)  MODULE(在使用dyld的系统有效，不支持dyld则等同于SHARED)
EXCLUDE_FROM_ALL	使用该宏表示库不被默认构建

#导入一个库
add_library(库名变量 库类型 IMPORTED)													#库类型：STATIC、SHARED、MODULE、UNKNOWN
set_target_properties(库名变量 PROPERTIES IMPORTED 库路径/${ANDROID_ABI}/libtest.so)

#编译一个库
cmake_minimum_required (VERSION 3.5)
project (demo)
set (SRC_LIST ${PROJECT_SOURCE_DIR}/testFunc/testFunc.c)
add_library (testFuncStatic STATIC ${SRC_LIST})
set_target_properties (testFuncStatic PROPERTIES OUTPUT_NAME "testFunc")
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#链接目标库
target_link_libraries(库名变量 库1 库2 库N)

