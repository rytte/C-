/********************/信号量/************************************************************/
Linux中用到的信号量有3种 : ststem - V信号量、POSIX有名信号量和POSIX无名信号量。

信号量不是用来传输数据的，它是在多线程或多进程环境下使用的一种措施，用来协调各进程或线程在通信时对于共享资源的访问。

信号量可以理解为：作用于进程之间的整型全局变量。


//三种信号量
ststem - V信号量、POSIX有名信号量是使用在进程间通信，而POSIX无名信号量使用在线程间通信.

ststem - V信号量：是一种信号量的集合，它可以包含多个信号量元素，而多个信号量元素是可以与信号量集合并存的。
POSIX有名/无名信号量：多个资源是不可以并存的.

//信号量的特点
1、信号量是具有原子性操作的变量，是由电气特性直接提供的(CPU的电路直接提供支持的，硬件上支持的)。
2、信号量所代表的意义是一个资源的数量，所以它一定是非负数的。
3、如果某个信号量的值，变为了负数，则会阻塞等待，等待资源增加。


//基本概念
临界资源：多个进程或线程有可能同时访问的资源（变量、链表、文件等等）称为共享资源，也称为临界资源。
临界区：  访问这些资源的代码称为临界代码，这些代码区域称为临界区(critical zone)。
P操作：   程序进入临界区之前必须要对资源进行申请，这个动作被称为Р操作(减法).
V操作：	  程序离开临界区之后必须要释放相应的资源，这个动作被称为V操作(加法).



/********************/SEM信号量相关函数/************************************************************/
获取信号量ID号
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int semget(key_t key, int nsems, int semflg);			//成功返回信号量ID，失败返回-1
			参数1 key_t key : 信号量的键值.
			参数2 int nsems : 信号量的元素个数.(有多少个信号量)
			参数3 int semflg : 访问权限.
						IPC_CREAT : 不存在则创建
						IPC_EXCL  : 信号量存在则报错
						mode	  : 信号量访问权限0777

获取或者设置信号量的相关属性
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int semctl(int semid, int semnum, int cmd, ...);   //可变参函数。返回值与参数3相关，设置为GETVAL则返回信号量的值。失败返回-1。

            参数1 int semid : 需要操作的信号量数组的ID.
            参数2 int semnum : 需要操作的信号量数组中的第几个元素.(数组下标).
            参数3 int cmd : 需要执行的命令(宏定义).
                    GETVAL 获取信号量的值(现有的值)
                    SETVAL 设置信号量的初始值
                    IPC_RMID 删除信号量.
                    IPC_STAT 获取属性信息
                    该函数为可变参函数.根据参数3的变化而变化.

        代码使用简单示例:
            int semctl(semid, 0, GETVAL);     //这时表示我要获取信号量序号(下标)为 0 的值, 成功返回信号量序号为 0 对应的值.
            int semctl(semid, 0, SETVAL, 5);  //这时表示我要设置信号量序号(下标)为 0 的值为 5. 成功则返回 0.
            int semctl(semid, 0, IPC_RMID);   //这时表示我要删除信序号为0的信号量.


        使用以上函数接口，需要注意以下几点:
            1, 这是一个变参函数，根据cmd 的不同，可能需要第四个参数，第四个参数是一个如下所示的联合体，
                用户必须自己定义 :
            union semun
            {
                int val;                  /*当cmd为SETVAL时使用*/
                struct semid_ds* buf;     /*当cmd为IPC_STAT或IPC_SET时使用*/
                unsigned short* array;   /*当cmd为GETALL或 SETALL时使用*/
                struct seminfo* _buf;    /*当cmd为IPC_INFO时使用*/
            };

            2, 使用IPC_STAT 和 IPC_SET需要用到以下属性信息结构体 :
            struct semid_ds
            {
                struct ipc_perm sem_perm;     /*权限相关信息*/
                time_t sem_otime;             /*最后一次semop( )的时间*/
                time_t sem_ctime;             /*最后一次状态改变时间*/
                unsigned shortsem_nsems;      /*信号量元素个数*/
            }
        权限结构体如下:
            struct ipc_perm
            {
                key_t  __key;/*该信号量的键值 key */
                uid_t   uid;/*所有者有效UID*/
                gid_t   gid;/*所有者有效GID*/
                uid_t   cuid;/*创建者有效UID*/
                gid_t cgid;/*创建者有效GID岁/
                unsigned short mode;/*读写权限*/
                unsigned short _seq;/*序列号*/
            };

            3, 使用IPC_INFO时，需要提供以下结构体:
            struct seminfo
            {
                int semmap;  /*当前系统信号量总数*/
                int semmni;  /*产系统信号量个数最大值*/
                int semmns;  /*系统所有信号量元素总数最大值*/
                int semmnu;  /*信号量操作撤销结构体个数最大值*/
                int semmsl;  /*单个信号量中的信号量元素个数最大值*/
                int semopm;  /*调用semop()时操作的信号量元素个数最大值*/
                int semume;  /*单个进程对信号量执行连续撤销操作次数的最大值*/
                int semusz;  /*撤销操作的结构体的尺寸*/
                int semvmx;  /*信号量元素的值的最大值*/
                int semaem;  /*撤销操作记录个数最大值*/
            };

申请访问临界资源
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int semop(int semid, struct sembuf* sops, size_t nsops)

            参数1 int semid : 信号量数组的ID.
            参数2 struct sembuf* sops : 结构体指针, 结构体如下
            struct sembuf
            {
                unsigned short sem_num;  /* 需要操作的信号量数组下标 */
                short          sem_op;   /* 该信号量数组下标的值操作,加法(V操作)或减法(P操作) */
                short          sem_flg;  /* 操作选项,SEM_UNDO,(还原信号量的值) */
                //3.你一开始设置了一个值,在做P操作或则V操作时,会改变信号量数组对应元素的值,Linux系统会保留其值,
                //设置这个宏定义之后,下次运行程序时,信号量的值会恢复原始你设置的值.(相当于复位).
            }
            参数3 size_t nsops : 需要操作几次.

注意：
1.当某一个信号量数组下标的值为 0 时, 如果要继续进行 P(减法) 操作, 会导致当前进程阻塞.
信号量的值不可能为负数.假设你将该值设置为负数的话, 该数据则不会生效.
2.信号量在做 V(加法) 操作时, 永远不会阻塞;



/********************/信号量实例/************************************************************/
//接收端
#include "head.h"

int main()
{
    //获取两个key值
    key_t key1 = ftok("/home/gec", 10);
    key_t key2 = ftok("/home/gec", 18);

    int shmid = shmget(key1, 1024, IPC_CREAT | 0666);		//获取共享内存的id
    int semid = semget(key2, 2, IPC_CREAT | 0666);			//根据key值申请一个信号量id
    char* p = shmat(shmid, NULL, 0);						//根据共享内存id映射一块内存空间到进程

    //初始化信号量 ---设置信号量属性
    //把空间设置成1  数据设置成 0
    semctl(semid, 0, SETVAL, 1);//空间 1
    semctl(semid, 1, SETVAL, 0);//数据 0	

    struct sembuf space;				//准备空间v操作结构体
    space.sem_num = 0;
    space.sem_op = 1;
    space.sem_flg = 0;

    struct sembuf data;					//准备数据p操作结构体
    data.sem_num = 1;
    data.sem_op = -1;
    data.sem_flg = 0;

    //发送数据，把数据写入到共享内存
    while (1)
    {
        semop(semid, &data, 1);			 //数据执行p操作

        printf("recv is %s\n", p);

        semop(semid, &space, 1);			//空间执行v操作
    }

    shmdt(p);							//撤销映射
    shmctl(shmid, IPC_RMID, NULL);		//删除共享内存
    semctl(semid, 1, IPC_RMID);			//删除信号量

    return 0;
}


/************************************************************/
//发送端
#include "head.h"

int main()
{
    //获取两个key值
    key_t key1 = ftok("/home/gec", 10);
    key_t key2 = ftok("/home/gec", 18);

    int shmid = shmget(key1, 1024, IPC_CREAT | 0666);		//获取共享内存的id
    int semid = semget(key2, 2, IPC_CREAT | 0666);			//根据key值申请一个信号量id
    char* p = shmat(shmid, NULL, 0);						//根据共享内存id映射一块内存空间到进程

    //初始化信号量 ---设置信号量属性
    //把空间设置成1  数据设置成 0
    semctl(semid, 0, SETVAL, 1);//空间 1
    semctl(semid, 1, SETVAL, 0);//数据 0	

    struct sembuf space;		//准备空间p操作结构体
    space.sem_num = 0;
    space.sem_op = -1;
    space.sem_flg = 0;

    struct sembuf data;			//准备数据v操作结构体
    data.sem_num = 1;
    data.sem_op = 1;
    data.sem_flg = 0;

    //发送数据，把数据写入到共享内存
    while (1)
    {
        semop(semid, &space, 1);			//空间执行p操作

        scanf("%s", p);

        semop(semid, &data, 1);			//数据执行v操作
    }

    shmdt(p);							//撤销映射
    shmctl(shmid, IPC_RMID, NULL);		//删除共享内存
    semctl(semid, 1, IPC_RMID);			//删除信号量

    return 0;
}

