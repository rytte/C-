/********************/系统IO与标准IO/************************************************************/

//系统IO（文件IO）
系统IO又称文件IO，它与操作系统绑定。系统IO通过系统调用（系统内核提供的函数）来实现数据的读取和写入。
特点：
1、不带缓冲机制：系统IO直接读写实际文件，不带缓存。
2、操作对象：可以操作普通文件、驱动文件（如设备文件、网络文件等）。
3、系统调用：每次操作都会执行相关系统调用，频繁的系统调用会增加系统开销。
4、文件描述符：用文件描述符表示一个打开的文件，可以访问不同类型的文件，如普通文件、设备文件和管道文件等。

//标准IO
标准IO是由标准C库（第三方库<stdio.h>）提供的接口函数，它是对系统IO的封装和扩展，具有可移植性。
特点：
1、带缓冲机制：标准IO带有缓存机制，可以减少系统调用的次数，提高性能。包括全缓存、行缓存和不缓存等类型。
2、操作对象：标准IO主要操作普通文件。
3、流的概念：标准IO引入了流的概念，所有的IO操作都是通过流进行的。流是数据的通道，可以是文本流或二进制流。
4、标准设备：标准IO还定义了三个标准设备：stdin（标准输入设备，通常为键盘）、stdout（标准输出设备，通常为显示器终端）和stderr（标准错误输出设备，通常为显示器终端）。

//主要区别在于：
实现方式：系统IO直接通过系统调用进行I / O操作，而标准IO是对系统IO的封装和扩展，提供了更高级的接口和缓存机制。
操作对象：系统IO可以操作普通文件和驱动文件，而标准IO主要操作普通文件。
性能：由于标准IO带有缓存机制，因此在处理大量数据时通常比系统IO具有更好的性能。
可移植性：标准IO屏蔽了不同体系结构之间的差异，增加了程序的可移植性。


//特殊成员
虚拟文件系统中的文件类型结构体
file
{
	__file_no[1024];
}

__file_no[0]	固定键盘输入 宏STDIN scanf
__file_no[1]	固定屏幕输出 宏STDOUT printf
__file_no[2]	固定屏幕输出 宏STDERR perror



/********************/Linux系统IO函数/************************************************************/

//open()函数
【头文件】
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
【函数原型】
int open(const char* pathname, int flags);
int open(const char* pathname, int flags, mode_t mode);
【参数】
const char* pathname  文件对象的访问路径
flags				  文件对象操作权限
{
	O_RDONLY	只读权限
	O_WRONLY	只写权限
	O_RDWR		读写权限
	O_CREAT		创建权限
	O_EXCL		和新建权限配合，如果文件存在就退出（如文件不存在，就创建）
	O_TRUNC		和新建权限配合，如果文件存在就覆盖
	O_NOCTTY	无权限，默认
	O_APPEND	文件内容追加，主要写文件。
}
mode(建立新文件时才会生效)
{
	S_IRWXU 00700 权限，代表该文件所有者具有可读、可写及可执行的权限。
	S_IRUSR 或S_IREAD， 00400权限，代表该文件所有者具有可读取的权限。
	S_IWUSR 或S_IWRITE，00200 权限，代表该文件所有者具有可写入的权限。
	S_IXUSR 或S_IEXEC， 00100 权限，代表该文件所有者具有可执行的权限。
	S_IRWXG 00070权限，代表该文件用户组具有可读、可写及可执行的权限。
	S_IRGRP 00040 权限，代表该文件用户组具有可读的权限。
	S_IWGRP 00020权限，代表该文件用户组具有可写入的权限。
	S_IXGRP 00010 权限，代表该文件用户组具有可执行的权限。
	S_IRWXO 00007权限，代表其他用户具有可读、可写及可执行的权限。
	S_IROTH 00004 权限，代表其他用户具有可读的权限
	S_IWOTH 00002权限，代表其他用户具有可写入的权限。
	S_IXOTH 00001 权限，代表其他用户具有可执行的权限。
}
【返回值】
成功：返回一个新的文件描述符(默认从3开始)
失败：-1


//read()函数
【头文件】
#include <unistd.h>
【函数原型】
ssize_t read(int fd, void* buf, size_t count);
【参数】
int fd 	     需要读取的文件描述对象
void* buf    读取数据的缓冲区，需要存储空间
size_t count 计算读取的字节大小 字节为单位（想要读取的字节数）
【返回值】
成功：返回读到了实际字节数
失败：-1


//write()函数
【头文件】
#include <unistd.h>
【函数原型】
ssize_t write(int fd, const void* buf, size_t count);
【参数】
int fd			要往哪个文件中写数据
const void* buf 即将要写入的数据的缓冲区
size_t count	想要写入的字节数
【返回值】
成功：实际写入的字节数
失败：-1


//close()函数
【头文件】
#include <unistd.h>
【函数原型】
int close(int fd);
【参数】
int fd需要关系的文件
【返回值】
成功：0
失败：-1


//lseek()偏移函数
【头文件】
#include <sys/types.h>
#include <unistd.h>
【函数原型】
off_t lseek(int fd, off_t offset, int whence);
【参数】
int fd			对哪个文件进行文件位置偏移的修改
off_t offset	相对于基准点的偏移量
int whence		基准点
{
	SEEK_SET  文件的开头
	SEEK_CUR  文件的当前位置
	SEEK_END  文件的末尾
}
【返回值】
成功：偏移量（字节数）
失败：-1；


//stat()文件属性函数
【头文件】
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
【函数原型】
int stat(const char* pathname, struct stat* buf);
【参数】
const char* pathname  需要查看的文件的路径名
struct stat* buf   文件属性结构体指针
struct stat 
{
	dev_t     st_dev;         /* 文件存储的设备号*/
	ino_t     st_ino;         /* 索引号 文件的身份证  */
	mode_t    st_mode;        /* 文件类型和权限 */
	nlink_t   st_nlink;       /* 硬链接数 */
	uid_t     st_uid;         /* 创建者用户ID */
	gid_t     st_gid;         /* 同组用户ID */
	dev_t     st_rdev;        /* 特殊设备ID*/ 驱动文件，字符设备文件
	off_t     st_size;        /* 文件大小（字节）*/
	blksize_t st_blksize;     /* 写入数据建议值（512） */
	blkcnt_t  st_blocks;      /* 文件所占用的数据块的数目 */
	struct timespec st_atim;  /* 最后访问文件的时间 */
	struct timespec st_mtim;  /* 最后修改文件的时间 */
	struct timespec st_ctim;  /* 最后修改文件属性的时间 */
}
【返回值】
成功：0
失败：-1
【note】
*st_mode：可以帮助我们判断文件的类型和权限
文件类型
{
	//stat(pathname, &st);
	//if (S_ISREG(st.st_mode)) {}
	S_ISREG(m)			普通文件		regular file
	S_ISDIR(m)			目录文件		directory
	S_ISCHR(m)			字符设备文件 character device
	S_ISBLK(m)			块设备文件	block device
	S_ISFIFO(m)			管道文件		FIFO(named pipe)
	S_ISLNK(m)			链接文件		symbolic link
	S_ISSOCK(m)			网络文件		socket

	//if ((st.st_mode & S_IFMT) == S_IFREG) {}
	S_IFMT     0170000  bit mask for the file type bit field
	S_IFSOCK   0140000	网络文件		socket
	S_IFLNK    0120000	链接文件		symbolic link
	S_IFREG    0100000	普通文件		regular file
	S_IFBLK    0060000	块设备文件	block device
	S_IFDIR    0040000	目录文件		directory
	S_IFCHR    0020000	字符设备文件	character device
	S_IFIFO    0010000	管道文件		FIFO
}
文件权限
{
	//判断
	S_ISUID     04000   set - user - ID bit 创建者ID
	S_ISGID     02000   set - group - ID bit(see below)  同组用户ID
	S_ISVTX     01000   sticky bit(see below) 其他用户ID

	//创建者 此组的用户拥有的权限
	S_IRWXU     00700   owner has read, write, and execute permission
	S_IRUSR     00400   owner has read permission
	S_IWUSR     00200   owner has write permission
	S_IXUSR     00100   owner has execute permission

	//同组用户的权限
	S_IRWXG     00070   group has read, write, and execute permission
	S_IRGRP     00040   group has read permission
	S_IWGRP     00020   group has write permission
	S_IXGRP     00010   group has execute permission

	//其他用户的权限
	S_IRWXO		00007  others(not in group) have read, write, and execute permission
	S_IROTH     00004   others have read permission
	S_IWOTH     00002   others have write permission
	S_IXOTH     00001   others have execute permission
}


//access()文件存在函数
【头文件】
#include <unistd.h>
【函数原型】
int access(const char* pathname, int mode);
【参数】
const char* pathname  需要判断的文件的路径
int mode			  判断文件对应的权限
{
	R_OK	读权限
	W_OK	写权限
	X_OK	执行权限
	F_OK	文件存在
}
【返回值】
成功：0
失败：-1


//getpwuid()获取文件所有者
【头文件】
#include <sys/types.h>
#include <pwd.h>
【函数原型】
struct passwd* getpwuid(uid_t uid);
【参数】
文件属性结构体的中的uid
【返回值】
结构体类型指针，指向对应的用户名
struct passwd
{
	char* pw_name;       /* 用户名*/
	char* pw_passwd;     /* 密码.*/
	uid_t pw_uid;        /* 用户ID.*/
	gid_t pw_gid;        /*组ID.*/
	char* pw_gecos;      /*真实名*/
	char* pw_dir;        /* 主目录.*/
	char* pw_shell;      /*使用的shell*/
};


//dup()重定向文件描述符函数
【头文件】
#include <unistd.h>
【函数原型】
int dup(int oldfd);
int dup2(int oldfd, int newfd);
【参数】
int oldfd  需要重定向的旧文件描述符
int newfd 指定的新的重定向文件描述符
【返回值】
成功：返回新的文件描述符
失败：-1
如果没有指定新的文件描述符，在原本的文件描述符基础上往后加一。



/********************/实例/************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const* argv[])
{
	// 打开文件
	int fd = open("1.txt", O_RDWR);
	if (-1 == fd)
	{
		perror("open 1.txt failed!\n");
		return -1;
	}
	// 将hello写入1.txt
	char w_buf[10] = { "hello" };
	int w_ret = write(fd, w_buf, strlen(w_buf)); // sizeof() 写10字节
	printf("实际写入的字节w_ret: %d\n", w_ret);

	// 调整文件位置偏移量
	lseek(fd, 0, SEEK_SET);

	// 读取文件中的数据
	char r_buf[10] = { 0 }; // 定义缓冲区并清空
	int r_ret = read(fd, r_buf, 10);
	if (r_ret == -1)
	{
		perror("read failed!\n");
		return -1;
	}
	printf("数据缓冲区r_buf: %s\n", r_buf);
	printf("实际读取的字节数r_ret: %d\n", r_ret);


	return 0;
}







