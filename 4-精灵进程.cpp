/********************/精灵进程/************************************************************/
在一个会话中，前台进程组只有一个，而后台进程组可以有多个。
前台进程组最大的特点是：可以接收控制终端发来的信号。

程序在终端执行时添加一个"&"号，使得进程进入后台进程组：
gec@ubuntu:~$ . / a.out &
上述后台进组进程 a.out 与下面的后台进程（或称精灵进程、守护进程）无关。

//会话（session）
会话可以理解为就是进程组的进程组，会话的作用可总结为：
1、可关联一个控制终端（比如键盘）设备，并从控制终端获得输入信息
2、可对会话内的所有进程组统一发送信号
3、可将控制终端的关闭动作，转换为触发挂断信号并发送给所有进程


//进程组函数
#include <sys/types.h>
#include <unistd.h>
int setpgid(pid_t pid, pid_t pgid)				//将进程PID的所在进程组设置为PGID
		//如果pid == 0，则设置本进程。
		//如果pgid == 0，等价于pgid == pid，把自身的这个进程设置为一个进程组，该进程就是该进程组当中的唯一一个进程。
pid_t getpgid(pid_t pid)						//获取进程PID所在进程组GID
pid_t setsid(void);								//创建一个新的会话。

//系统日志函数
void openlog(const char* ident, int option, int facility)		//打开日志文件
			参数：	const char* ident, 写入信息的前缀
					option,	   写入进程的PID
					facility   标志位，打开syslog，守护进程

void syslog(int priority, const char* format, ...)				//系统日志写入
			参数：  priority   发送优先级  LOG_DEBUG
					format     发送的内容
void closelog(void);											//关闭日志文件



/********************/精灵进程实例/************************************************************/
//精灵进程（Daemon）
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <ipc.h>
#include <shm.h>

int main(void)
{
	signal(SIGHUP, SIG_IGN);				//忽略终端关闭信号

	int pid = fork();						//创建的子进程脱离终端控制
	if (pid > 0)
		exit(0);
	else if (pid == 0)						//创建的孙子进程防止再次获取控制终端权限
	{
		pid = fork();
		if (pid > 0)
			exit(1);
	}

	int sid = setsid();						//创建会话
	if (sid == -1)
	{
		perror("setsid failed\n");
		return -1;
	}

	printf("%s\n", getcwd(NULL, 0));		//查看路径
	int ret = chdir("/");					//更改路径
	if (ret == -1)
	{
		perror("chdir failed\n");
		return -2;
	}

	umask(0);								//关闭文件权限掩码

	close(STDIN_FILENO);					//关闭继承的文件资源
	int fd = open("/dev/null", O_RDWR);		//关闭文件描述符0
	if (fd == -1)
	{
		perror("open failed\n");
		return -2;
	}
	close(STDOUT_FILENO);					//关闭标准输出
	close(STDERR_FILENO);					//关闭标准出错

	while (1);								//守护进程开始工作
}


/********************/会话实例/************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void showid()
{
	printf("本进程ID:%d\t", getpid());
	printf("父进程ID:%d\t", getppid());
	printf("进程组ID:%d\t", getpgid(0));
	printf("所在会话ID:%d\n", getsid(0));
}

int main()
{
	if (fork() == 0)
	{
		showid();
		// 将本进程的所属进程组，设置为等于本进程ID
		// 即：创建一个仅包含自身的进程组并将自身置入其中
		if (setpgid(0, 0) < 0)
		{
			perror("setpgid() failed");
		}
		else
		{
			showid();
		}
	}
	pause();
}



/********************/系统日志实例/************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <syslog.h>

int Daemon_Init(void)
{
	pid_t pid;

	//创建孙子进程
	pid = fork();
	if (pid > 0)
		exit(0);
	else if (pid == 0)
	{
		pid = fork();
		if (pid > 0)
			exit(1);
	}

	//孙子进程执行的代码
	pid = setsid();							//创建新的会话

	int ret = chdir("/");					//改变工作路径

	umask(0022);							//改变文件访问权限掩码

	close(STDIN_FILENO);					//关闭文件描述符 0
	int fd = open("/dev/null", O_RDWR);		//文件描述符fd为0
	if (fd == -1)
	{
		perror("open error\n");
		return -2;
	}
	close(STDOUT_FILENO);					//关闭标准输出
	close(STDERR_FILENO);					//关闭标准出错
}

int main(void)
{
	Daemon_Init();

	//打开系统日志
	//daemon_test    是写入的前缀
	//LOG_PID        将进程的PID写入
	//LOG_DAEMON     守护进程，打开syslog
	openlog("HELLO", LOG_CONS | LOG_PID, LOG_DAEMON);
	while (1)
	{
		//往日志文件中写入内容
		syslog(LOG_DEBUG, "I am a daemonAAA!");
		sleep(2);
		syslog(LOG_DEBUG, "I am a daemonBBB!");
		sleep(2);
	}
	return 0;
}

