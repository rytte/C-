/********************/共享内存/************************************************************/
共享内存是效率最高的IPC，它们的数据不需要经过内核。
共享内存可使得相同的一块物理内存多次映射到不同的进程虚拟空间中，这样的效果就相当于多个进程的虚拟内存空间重叠在一起。


//相关函数
获取共享内存ID号
#include <sys/ipc.h>
#include <sys/shm.h>
int shmget(key_t key, size_t size, int shmflg);		//成功返回共享内存ID号，失败返回-1

			参数1 key_t key   : 共享内存的键值，相同键值申请的映射内存区域相同（同一块内存），反之则不同。键值也可以自己定，是个整数就可以。
			参数2 size_t size : 申请共享内存的大小.
								单位为字节数, 要求为512字节的正数倍数.512字节为一页(4KB),
								所谓的页指的是内核为了提高程序性能, 对内存实行分页管理,就像我们之前所学习的结构体字节对齐相似.
			参数3 int shmflg : 权限设置。类似 open 的参数.
						IPC_CREAT	  : 如果key对应的共享内存不存在，则创建之
						IPC_EXCL	  : 如果该对应的共享内存已存在，则报错
						SHM_HUGETLB   : 使用“大页面”来分配共享内存
						SHM_NORESERVE : 不在交换分区中为这块共享内存保留空间
						mode		  : 共享内存的访问权限（八进制，如0644)

获取共享内存首地址，可以进行映射或解除映射
#include <sys/types.h>
#include <sys/shm.h>
void* shmat(int shmid, const void* shmaddr, int shmflg);  //获取共享内存首地址
int shmdt(const void* shmaddr);                           //解除内存映射，不允许再访问这个块共享区域

            参数 1 int shmid : 共享内存ID.
            参数 2 const void* shmaddr : 一般为NULL, 系统会自动选择一个合适的虚拟内存空间地址映射.
            参数 3 int shmflg          : 内存区域的权限, 填写 SHM_RDONLY 为只读的方式映射共享内存，填其它为可读写，一般填写为 0.

                返回值 :
                成 功 : 返回共享内存的首地址.
                失 败 : 返回 - 1;

删除共享内存ID
#include <sys/ipc.h>
#include <sys/shm.h>
int shmctl(int shmid, int cmd, struct shmid_ds* buf);          //成功返回0，失败返回-1

            参数 1 int shmid : 需要删除共享内存的ID号.
            参数 2 int cmd : 系统宏定义如下
                IPC_STAT  获取属性信息，放置到buf 中
                IPC_SET   设置属性信息为buf指向的内容, 并不是所有的信息都能够设置.
                IPC_RMID  将共享内存标记为“即将被删除”状态
            参数 3 struct shmid_ds* buf : 保存要 获取 或 设置 的共享内存信息。在删除时, 该参数填写NULL.

            //属性信息结构体
            struct shmid_ds
            {
                struct ipc_perm shm_perm;    /* 所有权和权限 */
                size_t          shm_segsz;   /* 共享内存的大小 (bytes) */
                time_t          shm_atime;   /* 最后一次映射时间 */
                time_t          shm_dtime;   /* 最后一个解除映射时间 */
                time_t          shm_ctime;   /* 最后状态更改时间 */
                pid_t           shm_cpid;    /* 创建这个共享内存的进程ID号 */
                pid_t           shm_lpid;    /* 最后一次映射共享内存的进程ID号 */
                shmatt_t        shm_nattch;  /* 该共享内存目前有多少个进程链接,关联 */
                ...
            };

            //权限结构体
            struct ipc_perm
            {
                key_t          __key;    /* 该 SHM 的键值*/
                uid_t          uid;      /* 所有者的有效 UID */
                gid_t          gid;      /* 所有者的有效 GID */
                uid_t          cuid;     /* 创建者的有效 UID */
                gid_t          cgid;     /* 创建者的有效 GID */
                unsigned short mode;     /* 读写权限 + SHM_DEST + SHM_LOCKED 标记 */
                unsigned short __seq;    /* 序列号 */
            };

//注意点:当使用IPC_RMID后, 上述结构体 struct ipc_perm 中的成员 mode 将可以监测出 SHM_DEST,
         //但SHM并不会真正的被删除, 要等到 shm_nattch 连接数为 0 时, 才会被真正的删除,IPC_RMID只是为删除做准备, 而不是立即删除..
            


/********************/共享内存实例/************************************************************/
//接收端
#include "head.h"

int main()
{
    key_t key = ftok("/home/gec", 10);				//获取一个key值
    printf("key is  %d\n", key);

    int shmid = shmget(key, 1024, IPC_CREAT | 0666);	//获取共享内存的id
    char* p = shmat(shmid, NULL, 0);					//根据共享内存id映射一块内存空间到进程

    while (1)										//接收数据，把共享内存的数据输出
    {
        printf("recv is %s\n", p);
        bzero(p, 1024);
        sleep(1);
    }

    shmdt(p);							//撤销映射
    shmctl(shmid, IPC_RMID, NULL);		//删除共享内存

    return 0;
}


/************************************************************/
//发送端
#include "head.h"

int main()
{
    key_t key = ftok("/home/gec", 10);				//获取一个key值
    printf("key is  %d\n", key);

    int shmid = shmget(key, 1024, IPC_CREAT | 0666);	//获取共享内存的id
    char* p = shmat(shmid, NULL, 0);					//根据共享内存id映射一块内存空间到进程

    while (1)										    //发送数据，把数据写入到共享内存
    {
        printf("写入数据：");
        scanf("%s", p);
    }

    shmdt(p);							//撤销映射
    shmctl(shmid, IPC_RMID, NULL);		//删除共享内存

    return 0;
}


