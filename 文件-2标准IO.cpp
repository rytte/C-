/********************/标准IO/************************************************************/

//fopen()函数
【头文件】
#include <stdio.h>
【函数原型】
FILE* fopen(const char* path, const char* mode);
【参数】
const char* path  打开文件的路径
const char* mode 打开文件对象的权限
{
	r	以只读方式打开文件，从文件开头处操作.
	r + 以可读可写的方式打开文件，
	w	以只写方式打开文件，如果文件存在就清空，不存在就创建
	w + 以读写方式打开文件，如果文件存在就清空，不存在就创建
	a	以只写方式打开文件，如果文件存在就追加写入，不存在就创建
	a + 以读写方式打开文件，如果文件存在就追加写入，不存在就创建
}
【返回值】
成功： 返回一个文件指针
失败： NULL


//fclose()函数
【头文件】
#include <stdio.h>
【函数原型】
int fclose(FILE* stream);
【参数】
FILE* stream  需要关闭的文件的文件指针
【返回值】
成功： 返回0
失败： 返回-1(EOF)


//fread()函数
//fwrite()函数
【头文件】
#include <stdio.h>
【函数原型】
size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);
【参数】
void* ptr		要读写的存储缓冲位置，
size_t size 	每一块存储区的大小（字节）
size_t nmemb	打算使用多少块存储区来操作数据
FILE* stream 	操作对象的文件流指针
【返回值】
成功：读取或者写入的完整的数据块的个数
失败：小于等于零


//clearerr()清除错误码函数
//feof()检查占位符函数是否到末尾
//ferror()获取错误码函数
//fileno()检查文件描述符函数
【头文件】
#include <stdio.h>
【函数原型】
void clearerr(FILE* stream); // 清除文件的错误编码
int feof(FILE* stream);		// 检查占位符是否到文件的末尾
【返回值】
成功：非零时，在文件的末尾
失败：为零时，不在文件末尾位置
【note】
feof的缺陷：就算文件光标移动到了文件末尾，也还需要再读一次，才能获得非零值
【函数原型】
int ferror(FILE* stream);  	// 检查文件操作过程出错编码
【返回值】
成功：为零时，说明操作没有错误
失败：非零时，表示遇到错误
【函数原型】
int fileno(FILE* stream);		// 检查文件描述符是多少
【返回值】
成功：返回文件描述符
失败：-1



//fseek()偏移函数
【头文件】
#include <stdio.h>
【函数原型】
int fseek(FILE* stream, long offset, int whence);
long ftell(FILE* stream);	// 返回当前文件位置距离文件开头处的长度
void rewind(FILE* stream);	// 将偏移量直接偏移到文件开头
【参数】
FILE* stream  偏移文件的对象指针
long offset  偏移量 字节
int whence 基准点
{
	SEEK_SET,  // 文件起始位置
	SEEK_CUR,  // 文件当前位置
	SEEK_END	// 文件末尾位置
}
【返回值】
成功：0
失败：-1


//标准输入函数
【头文件】
#include <stdio.h>
【函数原型】
int fgetc(FILE* stream);						// 从文件里面读取一个字符
char* fgets(char* str, int n, FILE* stream)		// 从文件中读取n-1字符串存储到指针str所指向的数据缓冲区，读到换行符结束
【返回值】
成功：返回str, 若到达文件末尾或者没有读取到任何字符，str 的内容保持不变，并返回 NULL.
失败： NULL
【函数原型】
int getc(FILE* stream);		// 从文件中获取一个字节（fgetc与getc区别：fgetc是函数，getc是宏函数）
int getchar(void);			// 获取缓冲区的一个字符
char* gets(char* str)；		//获取缓冲区的一个字符串（经常导致内存溢出被停用）

#include<errno.h>
//标准输出函数
【头文件】
#include <stdio.h>
【函数原型】
int fputc(int c, FILE* stream);				// 输出一个字符到文件中
int fputs(const char* s, FILE* stream);		// 输出一个字符串到文件中
int putc(int c, FILE* stream);				// 输出一个字符到文件中，fputc函数，putc宏定义
int putchar(int c);							// 输出一个字符
int puts(const char* s);					// 输出一个字符串
【参数】
int c			字符或者无符号字符 ASCII
const char* s	字符串数据
FEIL* stream	文件流指针


//格式化输出
【头文件】
#include <stdio.h>
【函数原型】
int printf(const char* format, ...);						// 格式化输出，输出到屏幕（stdout）
int dprintf(int fd, const char* format, ...);				// 格式化输出，输出到指定文件中（系统IO）
int fprintf(FILE* stream, const char* format, ...);			// 格式化输出，输出到指定文件中（标准IO）
int vfprintf(FILE* stream, const char* format, va_list arg);// 格式化输出，输出到指定文件中（标准IO），用于变参函数的构建
int sprintf(char* str, const char* format, ...);			// 组合字符串，将格式化的组合后的字符串存储到str中
int vsprintf(char* str, const char* format, va_list arg);	// 组合字符串，将格式化的组合后的字符串存储到str中，用于变参函数的构建
int snprintf(char* str, size_t size, const char* format, ...);	// 组合字符串，将格式化的组合后的size-1个字符串存储到str中（防止越界）
【参数】
const char* format 	格式化符号% d% s
FILE* stream 		文件流指针
int fd 				文件描述符
char* str 			str存储字符串的位置
size_t size 		组合字符串的大小


//格式化输入
【头文件】
#include <stdio.h>
【函数原型】
int scanf(const char* format, ...);						// 从键盘格式化输入
int fscanf(FILE* stream, const char* format, ...);		// 从文件格式化输入，把字符串转化为非字符串（从文件中获取数据）
int sscanf(const char* str, const char* format, ...);	// 从字符串格式化输入，把字符串转化为非字符串（拆分字符串）
【note】
格式化输入 / 输出，需要与文件中的数据分割符对应，（有符号可能无法识别）



//实例：sprintf与vsprintf的对比
#include <stdio.h>  
#include <stdarg.h>  

void my_vsprintf(char* str, const char* format, ...)	// 定义一个使用vsprintf的函数 
{
	va_list args;
	va_start(args, format);
	vsprintf(str, format, args); // 使用vsprintf  
	va_end(args);
}

int main() 
{
	char buffer1[100];
	char buffer2[100];
	int number = 123;

	my_vsprintf(buffer1, "The number is %d.", number);
	sprintf(buffer2, "The number is %d.", number);

	// 打印结果  
	printf("%s\n", buffer1); // 输出: The number is 123.  
	printf("%s\n", buffer2); // 输出: The number is 123.  

	return 0;
}



/********************/实例：实现ls/************************************************************/
// 实现ls -l  -rwxrwxrwx 1 root root 20 Jul 28 18:19 1.txt
int file(const char* path1) // 为防止path1被修改，可以加上const修饰
{
	// 初始化文件属性结构体
	struct stat buf;
	// 打开文件对应的属性
	stat(path1, &buf);
	// 1.获取文件类型
	switch (buf.st_mode & S_IFMT)
	{
	case S_IFSOCK: printf("s"); break;
	case S_IFLNK: printf("l"); break;
	case S_IFREG: printf("-"); break;
	case S_IFBLK: printf("b"); break;
	case S_IFDIR: printf("d"); break;
	case S_IFCHR: printf("c"); break;
	case S_IFIFO: printf("p"); break;
	}
	// 2.获取三个组的权限
	char rwx[] = { 'r', 'w', 'x' }; // r-0, w-1, x-2  , i%3
	for (int i = 0; i < 9; i++)
		printf("%c", buf.st_mode & (0400 >> i) ? rwx[i % 3] : '-');
	// 3获取文件硬链接数
	printf(" %ld", buf.st_nlink);
	// 4.获取文件的所有者
	printf(" %s", getpwuid(buf.st_uid)->pw_name);
	// 5.获取同组用户名
	printf(" %s", getgrgid(buf.st_gid)->gr_name);
	// 6.获取文件的大小
	printf(" %ld", buf.st_size);
	// 7.文件时间
	char* p = ctime(&buf.st_mtime); // strtok  strcat
	printf(" %s", p);
	// 8.文件名
	printf(" %s\n", path1);

	return 0;
}

int main(int argc, char* argv[])
{

	file(argv[1]);
	return 0;
}



/********************/实例：文件拷贝/************************************************************/
#include <stdio.h>
#include <string.h>

// 文件拷贝
int file_copy(char* src_path, char* dest_path)
{
	// 打开文件
	FILE* file1 = fopen(src_path, "r+");
	FILE* file2 = fopen(dest_path, "w+");
	if (NULL == file1 || NULL == file2)
	{
		perror("open failed!\n");
		return -1;
	}

	// 读写文件，实现拷贝
	char buf[1024] = { 0 };
	int ret;
	// 循环拷贝
	while (1)
	{
		// 方法一：
		ret = fread(buf, 1, 1, file1); //读取文件
		if (ret == 0)
			break;
		fwrite(buf, 1, 1, file2); // 写入文件

		// 方法二：
		ret = fgetc(file1); // 获取文件字符
		if (feof(file1) != 0) // 判断是否读完
			break;
		fputc(ret, file2); // 写入字符到文件

		// 方法三：fgets fputs
		fgets(buf, 5, file1);
		fputs(buf, file2);
		if (feof(file1) != 0) // 判断是否读完
			break;
		bzero(buf, 50);

		// 方法四：
		ret = getc(file1);
		if (feof(file1) != 0) // 判断是否读完
			break;
		putc(ret, file2);

	}
	// 关闭文件
	fclose(file1);
	fclose(file2);

}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		perror("参数不足\n");
		return -1;
	}
	// 拷贝文件
	file_copy(argv[1], argv[2]);

	return 0;
}



/********************/实例：格式化输出/************************************************************/
#include <stdio.h>

int main(int argc, char const* argv[])
{
	// 操作
	char name[20] = "jack";
	int age = 15;
	char sex[5] = "男";
	float score = 56.3;
	// 定义数组并清空
	char str[50] = { 0 };
	// 组合字符串，拼接字符串 （strcat）
	sprintf(str, "姓名：%s 性别：%s 年龄：%d 成绩:%.2f\n",
		name, sex, age, score);
	fprintf(stdout, "%s", str); // 输出到屏幕

	snprintf(str, 40, "姓名：%s 性别：%s 年龄：%d 成绩:%.2f\n",
		name, sex, age, score);
	fprintf(stdout, "%s", str); // 输出到屏幕

	return 0;
}


