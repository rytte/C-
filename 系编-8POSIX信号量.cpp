/********************/POSIX有名信号量/************************************************************/

IPC信号量中可以通过"struct sembuf"结构体来控制每次的PV操作中的加减数量，通过 semop函数的第3个参数来控制PV操作的次数.
但是有名信号量它只能够进行 + 1操作 与 - 1操作, 所以有名信号量比IPC信号量更为简单.

这种有名信号量的名字由类似"/somename"这样的字符串组成，注意前面有一个正斜杠，
这样的信号量其实是一个特殊的文件，创建成功之后将会被放置在系统的一个特殊的虚拟文件系统 / dev / shm 之中，
不同的进程间只要约定好一个相同的名字，他们就可以通过这种有名信号量来相互协调。

有名信号量跟system - V的信号量都是系统范畴的，在进程退出之后他们并不会自动消失，而需要手工删除并释放资源。

部分函数需要链接 -pthread

//使用步骤
1、使用sem_open()来创建或者打开一个有名信号量。
2、使用sem_wait()和 sem_post()来分别进行Р操作和V操作。
3、使用sem_close()来关闭他。
4、使用sem_unlink()来删除他，并释放系统资源。


//相关函数
创建，打开一个POSIX有名信号量
#include <fcntl.h>
#include <sys/stat.h> 
#include <semaphore.h>
sem_t* sem_open(const char* name, int oflag);			//用法与OPEN函数类似。成功返回信号量指针，失败返回SEM_FAILED
sem_t* sem_open(const char* name, int oflag, mode_t mode, unsigned int value);

			参数1 const char* name : 信号量的名字.
			参数2 int oflag : O_CREAT  如果该名字对应的信号量不存在，则创建
							  O_EXCL   如果该名字对应的信号量已存在，则报错
							  mode_t mode : 八进制读写权限
							  unsigned int value : 信号量的初始值.

P/V操作
#include <semaphore.h>
int sem_wait(sem_t * sem);		//等待资源 P操作 只-1 不够0则阻塞等待。成功返回0，失败返回-1。
int sem_post(sem_t* sem);		//释放资源 V操作 只+1 此操作永远不会阻塞。成功返回0，失败返回-1。

关闭、删除有名信号量
int sem_close(sem_t* sem);			//参数：信号量指针。成功返回0，失败返回-1
int sem_unlink(const char* name);	//参数：信号量名字。成功返回0，失败返回-1



/********************/POSIX无名信号量/************************************************************/
如果我们要解决的是一个进程内部的线程间的同步互斥, 那么也许不需要使用有名信号量，
因为这些线程共享同一个内存空间，我们可以定义更加轻量化的、基于内存的(不在任何文件系统内部）无名信号量来达到目的。

无名信号量由于存在于进程的共同内存当中，因此可以非常方便的与进程内的各条线程同步互斥，一旦进程退出信号量也将消失。

//使用步骤
1，在这些线程都能访问到的区域定义这种变量（比如全局变量)，类型是sem_t.
2，在任何线程使用它之前，用sem_init()初始化他。
3，使用sem_wait()和 sem_post()来分别进行P、V操作。
4，不再需要时，使用sem_destroy()来销毁他。

其中sem_wait()和 sem_post()跟 POSIX有名信号量是一样的，初始化和销毁函数接口有所不同。


//相关函数
初始化和销毁
#include <semaphore.h>
int sem_init(sem_t* sem, int pshared, unsigned int value);
int sem_destroy(sem_t* sem);

			参数1 sem_t* sem : 信号量指针
			参数2 int pshared : 该信号量的作用范围: 0为线程间，非0为进程间
								无名信号量一般用在进程内的线程间，因此pshared参数一般都为0。
								当将此种信号量用在进程间时，必须将他定义在各个进程都能访问的地方——比如共享内存之中。
			参数3 unsigned int value : 信号量初始值


//信号量总结
1, sys - V信号量较古老, 语法艰涩, POSIX信号量简单，轻量。
2, sys - V信号量可以对代表多种资源的多个信号量元素同一时间进行原子性的P / V操作, POSIX信号量每次只能操作一个信号量。
3, sys - V信号量和named - sem是系统范围的资源, 进程消失之后继续存在, 而unnamed - sem是进程范围的资源, 随着进程的退出而消失
4, sys - V信号量的P / V操作可以对信号量元素加减大于1的数值, 而POSIX信号量每次P / V操作都是加减1。
5, sys - V信号量甚至还支持撤销操作——一个进程对sys - V信号量进行P / V操作时可
以给该操作贴上需要撤销的标识, 那么当进程退出之后, 系统会自动撤销那些做了标识的操作。而 POSIX信号没有此功能。
6, sys - V信号量和 named - sem适合用在进程间同步互斥, 而unamed - sem适合用在线程间同步互斥。

总的来说，system - V的信号量功能强大但臃肿，如果在现实工作中不需要那些高级功能，建议使用接口清晰、逻辑简单的POSIX信号量。



/********************/有名信号量实例/************************************************************/
#include "head.h"
#define PATH "/home/gec"

sem_t* data; 	//数据资源
sem_t* space; 	//空间资源
char* shm_addr;
int shm_id;

void func(int sig)             //主函数结束前 或 收到SIGINT信号时执行
{
    shmdt(shm_addr);
    shmctl(shm_id, IPC_RMID, NULL);

    sem_close(data);           //关闭信号量
    sem_close(space);
    sem_unlink("data");        //删除信号量
    sem_unlink("space");
}

int main(int argc, char const* argv[])
{
    signal(SIGINT, func);        //确保ctrl+c终止程序时关闭资源

    shm_id = shmget(ftok(PATH, 3), 1024, IPC_CREAT | IPC_EXCL | 0777);       //获取共享内存id
    if (shm_id == -1)
    {
        if (errno == EEXIST)
            shm_id = shmget(ftok(PATH, 3), 1024, 0777);
        else
        {
            perror("申请共享内存失败\n");
            return -1;
        }
    }

    shm_addr = shmat(shm_id, NULL, 0);                    //共享内存映射
    if (shm_addr == NULL)
    {
        perror("映射内存失败\n");
        return -2;
    }


    data = sem_open("/data", O_CREAT, 0777, 0);        //申请一个信号量,该信号量代表着数据,因为一开始我们是没有数据的,所以初始为0
    if (data == SEM_FAILED)
    {
        printf("申请信号量失败.\n");
        return -3;
    }

    space = sem_open("/space", O_CREAT, 0777, 1);       //申请一个信号量,该信号量代表着数据的使用权,如果我们把数据放到空间中,该空间的资源会-1;
    if (space == SEM_FAILED)
    {
        printf("申请信号量失败.\n");
        return -3;
    }

    while (1)
    {
        sem_wait(space);                        //等待资源 P操作 只-1  不够0则阻塞等待
        fgets(shm_addr, 1024, stdin);
        sem_post(data);                         //释放资源 V操作 只+1  此操作永远不会阻塞

        if (strncmp(shm_addr, "over", 4) == 0)
            break;
    }

    func();

    return 0;
}



/********************/无名信号量实例/************************************************************/
#include "head.h"

sem_t s;                   //定义一个POSIX无名信号量

void* routine(void* arg)
{
    char* buf = (char*)arg;

    while (1)               //计算buf中的字符串的长度
    {
        sem_wait(&s);       // P操作，静静等待对方的数据准备好。。。    //1 0     
        printf("%lu\n", strlen(buf));
    }
}


int main(int argc, char** argv)
{
    sem_init(&s, 0, 0);   //参数一：信号量指针  //参数二：作用范围（零代表线程间使用，非零代表进程间使用）   //参数三：信号量初始值

    char buf[100];
    pthread_t tid;
    pthread_create(&tid, NULL, routine, (void*)buf);

    while (1)              //不断输入数据到buf
    {
        fgets(buf, 100, stdin);
        sem_post(&s);     // V操作，使用信号量通知对方可以开始计算了     //0 1
    }

    sem_destroy(&s);      //摧毁信号量
    return 0;
}

