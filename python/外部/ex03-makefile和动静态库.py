('''********************'''Makefile'''************************************************************'''
创建：新建文件，命名为 Makefile

执行：make + 目标

注意：
1、缩进必须使用TAB键，使用空格会报错
2、Makefile 文件是从下往上编译的，使用all可以不受此限制依次推导
3、注释使用井号#
4、如果出现xxx is up to data表示所有的依赖文件没有更新

#多目录结构
src         源文件（*.c）
include     功能函数的头文件（*.h）
lib         库文件（*.so   *.a）
bin         可执行文件（ELF）
Makefile    工程管理文件

编译：gcc  /src/main.c  /src/fun.c  lib.funcS.a  -o  /bin/main  -I ./include  -L ./lib  -l funcD
                                    #编译静态库				 #声明头文件目录 #声明库目录 #链接动态库


# Makefile 书写规则
依赖：源文件.c
目标：要生成的可执行文件

手动编译：gcc main.c func1.c func2.c –o main
make编译：
#编译一个文件
main:main.c func1.c func2.c            #目标:依赖（多个依赖文件使用空格隔开）

clean:
    rm main

#同时编译多个文件实例
all:demo1 demo2               # all表示生成多个目标文件

demo1:demo1.c
    gcc demo1.c -o demo1

demo2:demo2.c
    gcc demo2.c -o demo2

clean:
    rm demo1 demo2


#实例：将一个main.c文件编译成可执行文件，保留其.o .i .s文件
#目标：依赖
all:main.i main.s main.o main       # all表示生成多个目标文件，在此处会从左向右依次推导出可执行文件。
#预处理
main.i:main.c
	gcc main.c -o main.i -E
#编译
main.s:main.i
	gcc -S main.i -o main.s
#汇编
main.o:main.s
	gcc main.s -o main.o -c
#链接
main:main.o
	gcc main.o -o main
clean:
	rm main.i main.s main.o main



'''********************'''变量'''************************************************************'''
变量默认为字符串类型

# shell 与 makefile 的区别
				shell		  makefile
引用变量	  ${变量名}	      $(变量名)
赋值"="      =两边无空格   =两边允许有空格

#系统环境变量
CC：编译器的名字，默认 CC 等价于gcc
RM：删除文件，默认 RM 等价于rm -f

#符号
$^     所有依赖文件
$@     所有目标文件
$<     所有依赖文件中的第一个文件
%.o	   任意的.o文件
*.o	   所有的.o文件
=		替换
+=		追加
:=		恒等于

如果我们写TAR = test，就表示下面的代码中，我们可以用TAR代表test文件。
如果再写TAR += test1，就表示TAR代表test和test1。
CC := gcc 就表示下面写gcc的地方全部可以用CC代替，因为gcc这个是不会变的，是常量，所以可以用恒等于替换，这个不能用+=。


#伪指令  .PHONY:clean

#实例：
C_SRC= main.c add.c			#定义变量存储依赖文件
C_BIN= main				    #定义变量存储目标文件
CC = gcc					#给系统变量重赋值

$(C_BIN):$(C_SRC)			#目标：依赖
	$(CC) $^ -o $@

.PHONY:clean				#伪指令
clean:
	$(RM) $(C_BIN)

add:main.c add.c
	gcc $< -o $@


#函数
函数调用方式和变量一样，$(函数名)

$(wildcard argv1,argv2,argv3)		argv为参数
(作用：在某个路径下，寻找对应的匹配文件  
例子：寻找当前目录下的点c文件

$(patsubst %.c,%.o,依赖文件)
(作用：将所有的*.c结尾的文件，改为*.o结尾，（只是简单的名称修改）
例子：寻找当前目录下的文件，修改文件的后缀

$(foreach <var>,<list>,<text>)
(foreach本身有分割的作用，并且是循环分割
作用：循环的将list中的数据赋值给var,输入到text里面。var是一个变量名，list是一个表达式，text里面使用var，做数据的调用，



'''********************'''动静态库'''************************************************************'''
库文件在Linux环境中，以二进制的形式存储，即.o文件就是库文件

libfun.a     静态库：在编译时，与函数一起编译。由于是静态编译链接，在编译后，无需静态库的存在。
libfun.so    动态库：在运行时，和函数一起运行。由于是动态编译链接，所以在执行文件的时候，必须要有动态库才能执行。


#库文件的意义
1、减少工程当中的代码量。
2、保护工程权益。（源码不可见）


#制作静态库文件
1、将功能函数的源文件.c编译为.o文件（二进制文件）		    命令：gcc func1.c -c		gcc func2.c -c
2、将所有.o文件编译成.a文件，文件名需以lib开头。		    命令：ar rcs libfuncS.a func1.o func2.o
3、链接静态库。											    命令：gcc main.c libfuncS.a -o main

多目录结构编译：gcc  /src/main.c  libfuncS.a  -o  /bin/main  -I ./include  -L ./lib


#制作动态库文件
1、将功能函数的源文件.c编译为.o文件（二进制文件）		    命令：gcc func1.c -c		gcc func2.c -c
2、将所有.o文件编译成.so文件，文件名需以lib开头。		    命令：gcc -shared -fPIC -o libfuncD.so func1.o func2.o
3、链接动态库。链接时，丢掉lib和.so，且必须使用-L和-l参数。	命令：gcc main.c -o main -L -l funcD

多目录结构编译：gcc  /src/main.c  -o  /bin/main  -I ./include  -L ./lib  -l funcD



