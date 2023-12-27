/********************/管道/************************************************************/
管道的局限性：
1、数据不能进程自己写，自己读
2、管道中数据不可以反复读取，一旦读走，管道中的数据将消失
3、采用半双工通信方式，数据只能单向流动


/************************************************************/
PIPE 无名管道

无名管道特征:
1、其本质是一个伪文件（实为内核缓冲区）
2、由两个文件描述符进行引用，一个表示读端，另一个表示写端
3、数据只能从管道的写端流入，从读端流出

无名管道其它特点 :
1.无名管道没有名字, 所以无法使用open()进行打开。创建成功后, 只能够通过文件描述符进行查找, 不会生成文件。
2.无名管道采用 read()、 write()、close()函数来进行操作。不能使用lseek()函数来进行定位.
3.无名管道如果没有进程写入信息, 读取数据的那一端则会阻塞等待。直到有进程写入数据到无名管道当中为止.
4.无名管道只能用于亲缘进程间通信。
5.无名管道只能用于一对一的简单通信情形。


创建无名管道：
#include <unistd.h>
int pipe(int fds[2])				//创建一个无名管道。成功返回，失败返回-1。		
									//参数：自定义的一个整型数组，fds[0]是读端，fds[1]是写端。


/************************************************************/
FIFO 有名管道

有名管道特点：
1.有名管道可以用于任意进程间进行通信(与有无血缘进程无关)。
2.有名管道使用open()函数来获取 FIFO(有名管道) 的文件描述符进行读写。
3.有名管道没有固定的读写端, 既可以当读端, 也可以作为写端。
4.有名管道与普通文件一样 : 可以使用read() / write()来读写。
5.有名管道与普通文件不同 : 不可以使用lseek()函数来进行定位, 原因与PIPE相同。
6.有名管道具有写入原子性, 支持多个进程进行同时进行写操作, 而且数据不会互相践踏(错乱)。
7.有名管道First In First Out(先进先出), 最先被写入的 FIFO 的数据, 最先被读取出来。


创建有名管道：
#include <sys/types.h>
#include <sys/stat.h>
int mkfifo(const char* pathname, mode_t mode)			//创建或打开有名管道。成功返回0，失败返回-1。		
														//参数：*pathname：路径名		mode：操作权限(0777)

删除有名管道：
#include <unistd.h>
int unlink(const char* pathname)						//删除有名管道。成功返回0，失败返回-1。		参数*pathname：要删除的有名管道路径



/********************/无名管道实例/************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const* argv[])
{
	int fd[2];
	int ret = pipe(fd);		//int pipe(int pipefd[2]);	存放2个无名管道的文件描述符 pipefd[0]为读端 pipefd[1]为写端,失败返回-1
	if (ret == -1)
	{
		printf("创建无名管道失败\n");
		return -1;
	}

	pid_t pid = fork();
	if (pid > 0)   	//父进程：作为写端
	{
		printf("请输入你要发送的数据:\n");
		char write_data[100];
		scanf("%s", write_data);								//输入
		write(fd[1], write_data, strlen(write_data));			//写入

		wait(NULL);
	}
	else if (pid == 0) //子进程：作为读端
	{
		char read_data[100] = { 0 };
		read(fd[0], read_data, sizeof(read_data));				//读取
		printf("接收到父进程的信息为:%s\n", read_data);			//打印
	}
	else
		printf("创建失败\n");

	close(fd[0]);
	close(fd[1]);
	return 0;
}



/********************/有名管道实例/************************************************************/
//读端
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define FIFO_PATH "/home/gec/fifo"

int Fifo_Init(void)
{
	int ret = access(FIFO_PATH, F_OK);			//判断管道文件是否已经存在
	if (ret != 0)
		mkfifo(FIFO_PATH, 0777);				//不存在则创建
	int fifo_fd = open(FIFO_PATH, O_RDWR);		//打开管道文件
	return fifo_fd;
}


int main(int argc, char const* argv[])
{
	int fifo_fd = Fifo_Init();

	char rbuf[100] = { 0 };
	read(fifo_fd, rbuf, sizeof(rbuf));
	printf("读取到的数据为 :%s\n", rbuf);

	close(fifo_fd);
	unlink(FIFO_PATH);		//删除管道

	return 0;
}


/************************************************************/
//写端
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define FIFO_PATH "/home/gec/fifo"

int Fifo_Init(void)
{
	int ret = access(FIFO_PATH, F_OK);			//判断管道文件是否已经存在
	if (ret != 0)
		mkfifo(FIFO_PATH, 0777);				//不存在则创建
	int fifo_fd = open(FIFO_PATH, O_RDWR);		//打开管道文件
	return fifo_fd;
}

int main(int argc, char const* argv[])
{

	int fifo_fd = Fifo_Init();

	char wbuf[100] = { 0 };
	printf("请输入一个数据\n");
	scanf("%s", wbuf);
	write(fifo_fd, wbuf, strlen(wbuf));

	close(fifo_fd);

	return 0;
}


