/********************/IPC通信/************************************************************/
三种通信方式区别：

管道通信: 使用磁盘上的文件进行通信.
信号	: 使用的是操作系统作为媒介进行通信.
IPC 通信: 使用Linux内核进行通信.

uboot : 被称之为启动单元.主要任务是初始化硬件上的磁盘.
kernel: 多进程, 多线程需要有管理机制, 主要任务是用来协调各个任务之间的调度.
fs :	是一个文件系统, 包含了所有文件资源管理器, 所有的磁盘文件以及所有设置好的环境变量.


//IPC通信KEY
功能： 获取一个当前未使用的IPC 的key

#include <sys/types.h>
#include <sys/ipc.h>
key_t ftok(const char* pathname, int proj_id);

//参数解析
参数1  const char* pathname :  一个合法的路径(必须存在的路径，而且必须是纯linux的路径, 共享文件夹不能创建)
参数2  int proj_id : 随意的一个正整数

//返回值
成 功 : 返回合法未用的键值.
失 败 : -1;

//注意点
1.两个进程中的两个这参数都相同, 那么产生的键值一样，否则就不一样.
2.第一个参数一般是取进程所在的目录, 一个项目需要通信的几个进程会再同一目录下.
3.同一个目录中, 进程有多个IPC(进程间通信)对象时, 可以通过参数2来进行区分



/********************/消息队列/************************************************************/
消息队列提供一种带有数据标识的特殊管道，使得每一段被写入的数据都变成带标识的消息，可以根据标识正确读取消息。就像多条并存的管道一样。

注意事项：
1.数据从消息队列中读取出来以后，消息队列里的数据会消失，消息队列里的数据会被删除掉。
2.消息队列中，如果数据没有被读取完毕，则会残留在消息队列当中，累积起来。
3.在读取数据时，假如消息队列中没有指定的消息标识符，程序则会阻塞等待消息数据。
4.在消息队列中，多个消息标识符相同，需遵循先进先出的规则。

//相关函数
获取消息队列ID号
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int msgget(key_t key, int msgflg);  //成功返回消息队列ID号，失败返回-1
                                    //参数1：消息队列的键值   
                                    //参数2：IPC_CREAT: 如果key对应的MSG不存在, 则创建MSG；   
                                           //IPC_EXCL : 如果key对应的MSG存在, 则报错. 
                                           //mode: MSG的访问权限(八进制权限, 例如 0666).
                                    

发送与接收
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int msgsnd(int msgid, const void* msgp, size_t msgsz, int msgflg);      //成功返回0，失败返回-1
例：msgsnd(msgid, &msg, sizeof(msg), 0);

            参数1 int msqid : 消息队列的ID号
            参数2 const void* msgp : 存放需要发送的信息结构体
            查看帮助手册, 手册告诉我们, 消息队列在发送消息时, 需要把消息打包成一个结构体进行发送
            struct msgbuf
            {
                long mtype;       /* 消息标识符 */
                char mtext[1];    /* 需要发送的数据 数据类型名可自定义 */
            };
			参数3 size_t msgsz : 发送数据的大小
			参数4 int msgflg : 默认设置为0
ssize_t msgrcv(int msqid, void* msgp, size_t msgsz, long msgtyp, int msgflg);       //成功返回接收的字节数，失败返回-1
例：msgrcv(msgid, &msg, sizeof(msg), 1, 0);

            参数1 int msgsnd   : 消息队列的ID
            参数2 void* msgp   : 存放接收的信息
            参数3 size_t msgsz : 接收数据的大小
            参数4 long msgtyp  : 消息标识符(重点)
            参数5 int msgflg   : 默认设置为0

删除，设置，获取消息队列属性信息
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int msgctl(int msqid, int cmd, struct msqid_ds* buf);       //成功返回0，失败返回-1

            参数1 int msqid : 消息队列ID
            参数2 int cmd :
                    IPC_STAT  获取该MSG的信息，储存在结构体msqid_ds中
                    IPC_SET   设置该MSG的信息，储存在结构体msqid_ds
                    IPC_RMID  删除该MSG, 并且唤醒所有阻塞在该MSG上的进程，
                    同时忽略第三个参数.直接填写NULL;
            参数3 struct msqid_ds* buf : 相关信息结构体缓冲区

                //消息队列的信息结构体
                struct msqid_ds
                {
                struct ipc_perm msg_perm;     /* 权限相关信息 */
                time_t          msg_stime;    /* 最后一次发送消息的时间 */
                time_t          msg_rtime;    /* 最后一次接受消息的时间 */
                time_t          msg_ctime;    /* 最后一次状态变更的时间 */
                unsigned long   __msg_cbytes; /* 当前消息队列中的数据尺寸 */
                msgqnum_t       msg_qnum;     /* 当前消息队列中的消息个数 */
                msglen_t        msg_qbytes;   /* 消息队列的最大数据尺寸 */
                pid_t           msg_lspid;    /* 最后一个发送消息进程的PID */
                pid_t           msg_lrpid;    /* 最后一个接受消息进程的PID */
                };

            //消息队列权限相关信息
            struct ipc_perm
            {
                key_t          __key;       /* 当前消息队列的键值 */
                uid_t          uid;         /* 当前消息队列所有者的UID */
                gid_t          gid;         /* 当前消息队列所有者的GID */
                uid_t          cuid;        /* 当前消息队列创建者的UID */
                gid_t          cgid;        /* 当前消息队列创建者的GID */
                unsigned short mode;        /* 消息队列的读写权限 */
                unsigned short __seq;       /* 序列号 */
            };



/********************/消息队列实例/************************************************************/
//接收
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

#define KEY_PATH "/home/gec"

struct mymsg
{
	long   msg_flag;         /* Message type. */
	char   msg_data[100];    /* Message text. */
};


int main(int argc, char const* argv[])
{
	//1.创建键值
	key_t key = ftok(KEY_PATH, 1);
	if (key == -1)
	{
		printf("创建键值失败\n");
		return -1;
	}
	//2.获取消息队列ID
	int msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0777);
	if (msgid == -1)
	{
		if (errno == EEXIST)
		{
			printf("打开消息队列成功\n");
			msgid = msgget(key, 0777);
		}
		else
		{
			printf("获取消息队列的ID失败\n");
		}
	}
	printf("键值为:%x\n", key);
	printf("消息队列的ID号为 ：%d\n", msgid);

	//3.读取数据
	struct mymsg recv_data;
	memset(&recv_data, 0, sizeof(recv_data));
	msgrcv(msgid, &recv_data, sizeof(recv_data), 3, 0);
	printf("%s\n", recv_data.msg_data);

	//获取消息队列的属性
	// struct msqid_ds buf;
	// msgctl(msgid, IPC_STAT, &buf);
	// printf("消息队列中有 %ld 条消息\n",buf.msg_qnum);
	// printf("最后一个发送消息的PID号 %d\n",buf.msg_lspid);

	//设置消息队列的属性(并不是所有的属性都能进行设置)
	// struct msqid_ds buf;
	// buf.msg_perm.mode = 0655;
	// msgctl(msgid, IPC_SET, &buf);


	//删除消息队列
	//msgctl(msgid, IPC_RMID, NULL);

	return 0;
}


/************************************************************/
//发送
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/msg.h>
#include <errno.h>

#define KEY_PATH "/home/gec"

struct mymsg
{
	long   msg_flag;         /* Message type. */
	char   msg_data[100];    /* Message text. */
};

int main(int argc, char const* argv[])
{
	//1.创建
	key_t key = ftok(KEY_PATH, 1);
	if (key == -1)
	{
		printf("创建键值失败\n");
		return -1;
	}
	//2.获取消息队列ID号
	int msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0777);
	if (msgid == -1)
	{
		if (errno == EEXIST)
		{
			printf("打开消息队列成功\n");
			msgid = msgget(key, 0777);
		}
		else
		{
			printf("获取消息队列的ID失败\n");
		}
	}
	printf("键值为:%x\n", key);
	printf("消息队列的ID号为 ：%d\n", msgid);

	//3.发送数据
	struct mymsg data;
	memset(&data, 0, sizeof(data));
	data.msg_flag = 1;
	strcpy(data.msg_data, "hello");
	msgsnd(msgid, &data, strlen(data.msg_data), 0);

	memset(&data, 0, sizeof(data));
	data.msg_flag = 2;
	strcpy(data.msg_data, "world");
	msgsnd(msgid, &data, strlen(data.msg_data), 0);

	memset(&data, 0, sizeof(data));
	data.msg_flag = 3;
	strcpy(data.msg_data, "hello world");
	msgsnd(msgid, &data, strlen(data.msg_data), 0);

	return 0;
}

