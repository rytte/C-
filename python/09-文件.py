('''********************'''open() 方法'''************************************************************'''
 Python open() 方法用于打开一个文件，并返回文件对象。如果该文件无法被打开，会抛出 OSError。
 文件对象是一个可迭代对象，可以使用 for 语句等读取。
 注意：文件操作完成后一定要调用 close() 方法关闭文件对象，否则操作数据还在内存中未被写入。


open() 函数常用形式是接收两个参数：文件名(file)和模式(mode)。

open(file, mode='r')     #一般格式
open(file, mode='r', buffering=-1, encoding=None, errors=None, newline=None, closefd=True, opener=None)     #完整语法格式


参数说明:
file:       必需，文件路径（相对或者绝对路径）。
mode:       可选，文件打开模式
buffering:  设置缓冲
encoding:   一般使用utf8
errors:     报错级别
newline:    区分换行符
closefd:    传入的 file 参数类型
opener:     设置自定义开启器，开启器的返回值必须是一个打开的文件描述符。


mode 参数有：

mode参数	描述              #默认为文本模式，如果要以二进制模式打开，加上 b 。
t	    文本模式 (默认)。
x	    写模式，新建一个文件，如果该文件已存在则会报错。
b	    二进制模式。
+	    可读可写。
U	    通用换行模式（Python 3 不支持）。

r	    只读。文件指针位于开头。这是默认模式。
rb	    二进制格式只读。文件指针位于开头。这是默认模式。一般用于非文本文件如图片等。
r+	    读写。文件指针位于开头。
rb+	    二进制格式读写。文件指针位于开头。一般用于非文本文件如图片等。

w	    可写。已存在则打开并清空内容。不存在则新建。
wb	    二进制格式可写。已存在则打开并清空内容，不存在则新建。一般用于非文本文件如图片等。
w+	    读写。已存在则打开并清空内容。不存在则新建。
wb+	    二进制格式读写。已存在则打开并清空内容，不存在则新建。一般用于非文本文件如图片等。

a	    追加。文件指针位于末尾。不存在则新建。
ab	    二进制格式追加。文件指针位于末尾。不存在则新建。
a+	    读写并追加。文件指针位于末尾。不存在则新建。
ab+	    二进制格式读写并追加。文件指针位于末尾。不存在则新建。


file 对象使用 open 函数来创建：f = open()

序号	方法及描述
1	    f.close()        关闭文件。关闭后文件不能再进行读写操作。

2	    f.flush()        刷新文件内部缓冲，直接把内部缓冲区的数据立刻写入文件, 而不是被动的等待输出缓冲区写入。

3	    f.fileno()       返回一个整型的文件描述符(file descriptor FD 整型), 可以用在如os模块的read方法等一些底层操作上。

4	    f.isatty()       如果文件连接到一个终端设备返回 True，否则返回 False。

5	    f.next()         返回文件下一行。#Python 3 中的 File 对象不支持 next() 方法。

6	    f.read([size])   从文件读取指定的字节数，如果未给定或为负则读取所有。

7	    f.readline([size])       读取整行，包括 "\n" 字符。

8	    f.readlines([sizeint])   读取所有行并返回列表，若给定sizeint>0，返回总和大约为sizeint字节的行, 实际读取值可能比 sizeint 较大, 因为需要填充缓冲区。

9	    f.seek(offset[, whence]) 移动文件指针到指定位置，whence:0表示文件开头，1表示当前位置，2表示文件末尾

10	    f.tell()                 返回当前文件指针所在位置。

11	    f.truncate([size])       从文件的首行首字符开始，截断 size 个字符，无 size 表示在当前位置截断，截断位置后面的所有字符被删除，其中 windows 系统下的换行代表2个字符大小。

12	    f.write(str)             将字符串写入文件，返回写入的字符长度。

13	    f.writelines(sequence)   向文件写入一个序列字符串列表，换行需要自己添加换行符。



'''********************'''pathlib 路径处理'''************************************************************'''
#Python3.4之后才支持该模块
>>>from pathlib import Path       
>>>p = Path.cwd()       #获取当前路径
>>>p
WindowsPath('D:/Microsoft Visual Studio/repos/Python笔记')
>>>q = p / "FishC.txt"  #路径拼接
>>>q
WindowsPath('D:/Microsoft Visual Studio/repos/Python笔记/FishC.txt')
>>>p.is_dir()           #判断是否为目录
True
>>>p.is_file()          #判断是否为文件
False
>>>p.exists()           #判断路径是否存在
True
>>>p.name               #获取文件名/目录，带后缀
'Python笔记'
>>>p.stem               #获取文件名/目录，不带后缀
'Python笔记'
>>>p.suffix             #获取文件后缀
''
>>>p.parent             #获取父级目录
WindowsPath('D:/Microsoft Visual Studio/repos')
>>>ps = p.parents       #获取逻辑祖先路径构成的不可变序列，该序列支持迭代和索引
>>>ps
<WindowsPath.parents>
>>>for i in ps:
...    print(i)
...
D:\Microsoft Visual Studio\repos
D:\Microsoft Visual Studio
D:\
>>>p.parts              #将路径的各个组件拆分成元组
('D:\\', 'Microsoft Visual Studio', 'repos', 'Python笔记')
>>>p.stat()             #查询文件或目录的信息
os.stat_result(st_mode=16895, st_ino=1688849860267879, st_dev=3601936673, st_nlink=1, st_uid=0, st_gid=0, st_size=4096, st_atime=1687515957, st_mtime=1687515948, st_ctime=1687112226)
>>>Path("./doc").resolve()          #相对路径转换为绝对路径
WindowsPath('D:/Microsoft Visual Studio/repos/Python笔记/doc')
>>>for i in p.iterdir():            #获取当前路径下所有子文件和子目录，返回生成器
...    print(i)
...
D:\Microsoft Visual Studio\repos\Python笔记\.vs
D:\Microsoft Visual Studio\repos\Python笔记\01-Python基础.py
D:\Microsoft Visual Studio\repos\Python笔记\02-数据类型与运算.py
D:\Microsoft Visual Studio\repos\Python笔记\03-序列.py
D:\Microsoft Visual Studio\repos\Python笔记\04-字典与集合.py
D:\Microsoft Visual Studio\repos\Python笔记\05-条件与循环语句.py
D:\Microsoft Visual Studio\repos\Python笔记\06-函数.py
D:\Microsoft Visual Studio\repos\Python笔记\07-文件.py
D:\Microsoft Visual Studio\repos\Python笔记\10-其它.py
D:\Microsoft Visual Studio\repos\Python笔记\app.py
D:\Microsoft Visual Studio\repos\Python笔记\Python笔记.pyproj
D:\Microsoft Visual Studio\repos\Python笔记\Python笔记.sln
#以下有删除文件风险，不做演示
>>>n = p / "FishC"
>>>n.mkdir()            #创建目录。设置参数parent=True可以创建路径上不存在的目录
>>>f = n.open("r")      #打开文件，路径已存在对象n中不必填写
>>>n.rename("NewFishC.txt")     #文件重命名，若不填写路径则会使用默认路径
>>>m = Path(NewFishC.txt)
>>>m.replace(n)         #替换指定的文件或目录（将m文件或目录，替换到n的位置，n被删除）
>>>n.unlink()           #删除文件
>>>n.parent.rmdir()     #删除目录

>>>p = Path('.')
>>>p.glob("*.txt")      #强大的查找功能，返回生成器（部分参数说明：*/表示当前路径下的所有目录，**/表示当前路径下的所有目录及其子目录）



'''********************'''with 语句'''************************************************************'''
with 语句会自动进行关闭文件操作
常规操作中，在文件操作语句发生错误时，close()语句将不会被执行，对文件的操作也将不会被写入，    #据说3.11版本可以被写入
而使用 with 语句，将可以确保关闭文件，错误语句前的操作也就会被写入。

#常规操作文件
>>>f = open("FishC.txt", "w")
>>>f.write("hello")
5
>>>f.close()

#使用with语句
>>>with open("FishC.txt","w") as f:
...    f.write("hello")
...
5


with 语句实现原理建立在上下文管理器之上。
上下文管理器是一个实现 __enter__ 和 __exit__ 方法的类。

在文件对象中定义了 __enter__ 和 __exit__ 方法，即文件对象也实现了上下文管理器，
首先调用 __enter__ 方法，然后执行 with 语句中的代码，最后调用 __exit__ 方法。
即使出现错误，也会调用 __exit__ 方法，也就是会关闭文件流。
这个概念类似于 try-finally 块的使用。


'''********************'''pickle 操作'''************************************************************'''
pickle操作可以将Python对象序列化，转换为二进制字节流文件保存起来

#保存下面的序列对象
x, y, z = 1, 2, 3
s = "FishC"
1 = ["小甲鱼", 520, 3.14]
d = {"one :1, "two":2}

import pickle

with open("data.pkl", "wb") as f:       #将文件保存为.pkl文件(pickle文件)，要以二进制格式打开
    pickle.dump((x, y, z, s, l, d), f)  #以元组方式打包参数再传入


#读取上面转换的data.pkl文件
import pickle

with open("data.pkl", "rb") as f:       #以二进制格式打开
    x, y, z, s, l, d = pickle.load(f)   #读取并解包

print(x, y, z, s, l, d, sep="\n")       #sep="\n"表示以"\n"作为每个打印对象的分隔符



'''********************'''OS 方法'''************************************************************'''
os 模块提供了非常丰富的方法用来处理文件和目录。常用的方法如下表所示：

序号	方法及描述
1	    os.access(path, mode)               检验权限模式
2	    os.chdir(path)                      改变当前工作目录
3	    os.chflags(path, flags)             设置路径的标记为数字标记。
4	    os.chmod(path, mode)                更改权限
5	    os.chown(path, uid, gid)            更改文件所有者
6	    os.chroot(path)                     改变当前进程的根目录
7	    os.close(fd)                        关闭文件描述符 fd
8	    os.closerange(fd_low, fd_high)      关闭所有文件描述符，从 fd_low (包含) 到 fd_high (不包含), 错误会忽略
9	    os.dup(fd)                          复制文件描述符 fd
10	    os.dup2(fd, fd2)                    将一个文件描述符 fd 复制到另一个 fd2
11	    os.fchdir(fd)                       通过文件描述符改变当前工作目录
12	    os.fchmod(fd, mode)                 改变一个文件的访问权限，该文件由参数fd指定，参数mode是Unix下的文件访问权限。
13	    os.fchown(fd, uid, gid)             修改一个文件的所有权，这个函数修改一个文件的用户ID和用户组ID，该文件由文件描述符fd指定。
14	    os.fdatasync(fd)                    强制将文件写入磁盘，该文件由文件描述符fd指定，但是不强制更新文件的状态信息。
15	    os.fdopen(fd[, mode[, bufsize]])    通过文件描述符 fd 创建一个文件对象，并返回这个文件对象
16	    os.fpathconf(fd, name)              返回一个打开的文件的系统配置信息。name为检索的系统配置的值，它也许是一个定义系统值的字符串，这些名字在很多标准中指定（POSIX.1, Unix 95, Unix 98, 和其它）。
17	    os.fstat(fd)                        返回文件描述符fd的状态，像stat()。
18	    os.fstatvfs(fd)                     返回包含文件描述符fd的文件的文件系统的信息，Python 3.3 相等于 statvfs()。
19	    os.fsync(fd)                        强制将文件描述符为fd的文件写入硬盘。
20	    os.ftruncate(fd, length)            裁剪文件描述符fd对应的文件, 所以它最大不能超过文件大小。
21	    os.getcwd()                         返回当前工作目录
22	    os.getcwdb()                        返回一个当前工作目录的Unicode对象
23	    os.isatty(fd)                       如果文件描述符fd是打开的，同时与tty(-like)设备相连，则返回true, 否则False。
24	    os.lchflags(path, flags)            设置路径的标记为数字标记，类似 chflags()，但是没有软链接
25	    os.lchmod(path, mode)               修改连接文件权限
26	    os.lchown(path, uid, gid)           更改文件所有者，类似 chown，但是不追踪链接。
27	    os.link(src, dst)                   创建硬链接，名为参数 dst，指向参数 src
28	    os.listdir(path)                    返回path指定的文件夹包含的文件或文件夹的名字的列表。
29	    os.lseek(fd, pos, how)              设置文件描述符 fd当前位置为pos, how方式修改: SEEK_SET 或者 0 设置从文件开始的计算的pos; SEEK_CUR或者 1 则从当前位置计算; os.SEEK_END或者2则从文件尾部开始. 在unix，Windows中有效
30	    os.lstat(path)                      像stat(),但是没有软链接
31	    os.major(device)                    从原始的设备号中提取设备major号码 (使用stat中的st_dev或者st_rdev field)。
32	    os.makedev(major, minor)            以major和minor设备号组成一个原始设备号
33	    os.makedirs(path[, mode])           递归文件夹创建函数。像mkdir(), 但创建的所有intermediate-level文件夹需要包含子文件夹。
34	    os.minor(device)                    从原始的设备号中提取设备minor号码 (使用stat中的st_dev或者st_rdev field )。
35	    os.mkdir(path[, mode])              以数字mode的mode创建一个名为path的文件夹.默认的 mode 是 0777 (八进制)。
36	    os.mkfifo(path[, mode])             创建命名管道，mode 为数字，默认为 0666 (八进制)
37	    os.mknod(filename[, mode=0600, device])     创建一个名为filename文件系统节点（文件，设备特别文件或者命名pipe）。
38	    os.open(file, flags[, mode])        打开一个文件，并且设置需要的打开选项，mode参数是可选的
39	    os.openpty()                        打开一个新的伪终端对。返回 pty 和 tty的文件描述符。
40	    os.pathconf(path, name)             返回相关文件的系统配置信息。
41	    os.pipe()                           创建一个管道. 返回一对文件描述符(r, w) 分别为读和写
42	    os.popen(command[, mode[, bufsize]])        从一个 command 打开一个管道
43	    os.read(fd, n)                      从文件描述符 fd 中读取最多 n 个字节，返回包含读取字节的字符串，文件描述符 fd对应文件已达到结尾, 返回一个空字符串。
44	    os.readlink(path)                   返回软链接所指向的文件
45	    os.remove(path)                     删除路径为path的文件。如果path 是一个文件夹，将抛出OSError; 查看下面的rmdir()删除一个 directory。
46	    os.removedirs(path)                 递归删除目录。
47	    os.rename(src, dst)                 重命名文件或目录，从 src 到 dst
48	    os.renames(old, new)                递归地对目录进行更名，也可以对文件进行更名。
49	    os.rmdir(path)                      删除path指定的空目录，如果目录非空，则抛出一个OSError异常。
50	    os.stat(path)                       获取path指定的路径的信息，功能等同于C API中的stat()系统调用。
51	    os.stat_float_times([newvalue])     决定stat_result是否以float对象显示时间戳
52	    os.statvfs(path)                    获取指定路径的文件系统统计信息
53	    os.symlink(src, dst)                创建一个软链接
54	    os.tcgetpgrp(fd)                    返回与终端fd（一个由os.open()返回的打开的文件描述符）关联的进程组
55	    os.tcsetpgrp(fd, pg)                设置与终端fd（一个由os.open()返回的打开的文件描述符）关联的进程组为pg。
56	    os.tempnam([dir[, prefix]])         Python3 中已删除。返回唯一的路径名用于创建临时文件。
57	    os.tmpfile()                        Python3 中已删除。返回一个打开的模式为(w+b)的文件对象 .这文件对象没有文件夹入口，没有文件描述符，将会自动删除。
58	    os.tmpnam()                         Python3 中已删除。为创建一个临时文件返回一个唯一的路径
59	    os.ttyname(fd)                      返回一个字符串，它表示与文件描述符fd 关联的终端设备。如果fd 没有与终端设备关联，则引发一个异常。
60	    os.unlink(path)                     删除文件路径
61	    os.utime(path, times)               返回指定的path文件的访问和修改的时间。
62	    os.walk(top[, topdown=True[, onerror=None[, followlinks=False]]])   输出在文件夹中的文件名通过在树中游走，向上或者向下。
63	    os.write(fd, str)                   写入字符串到文件描述符 fd中. 返回实际写入的字符串长度
64	    os.path 模块                        获取文件的属性信息。
65	    os.pardir()                         获取当前目录的父目录，以字符串形式显示目录名。
66	    os.replace()                        重命名文件或目录。