/********************/互斥锁mutex/************************************************************/

//线程同步
同步，即协同步调，按预定的先后次序运行。
线程同步，指一个线程发出某一功能调用时，在没得到结果之前，该调用将阻塞不返回。同时其他线程为保证数据一致性，不能调用该功能。

产生数据混乱的原因：
1.争夺共享资源
2.线程的调度随机（意味着数据访问会出现竞争）
3.线程间缺乏必要的同步机制

从以上三点来看，前两点是不能够进行改变的。
如果要提高效率，传递数据，资源就必须要共享，那只要共享资源，就一定会出现竞争，出现了竞争关系，数据就会很容易错乱。
所以只能从第三点着手解决，使多个线程在访问共享资源的时候出现互斥。


互斥锁使得共享资源同一时刻只能一个线程访问。

//相关函数
#include <pthread.h>
pthread_mutex_t m;				//定义一个互斥锁变量
pthread_mutex_init(&m, NULL);	//初始化锁，在任何线程使用该互斥锁之前都必须要先初始化
pthread_mutex_lock(&m);			//访问临界资源之前 上锁
pthread_mutex_unlock(&m);       //使用完临界资源后 解锁 
pthread_mutex_destroy(&m)       //不需要使用后, 销毁锁 

//死锁处理
死锁是使用锁不恰当导致的现象，一般来说，Posix的线程终止有三种情况：
1、对一个锁重复上锁。
2、两条线程，各自已经持有一把锁，但是去请求另把锁。
3、线程在运行过程当中，上了锁，但由某种未知的原因，没有来得及解锁就异常结束。

死锁处理方式
#include <pthread.h>
void pthread_cleanup_push(void (*routine)(void*), void* arg);  //参数1：自定义的解锁函数	参数2：取消时需要解开的锁资源，也就是传递给参数1的参数
void pthread_cleanup_pop(int execute);		//参数：0表示非正常退出时执行，正常退出不执行。非0表示无论是否正常退出都执行。



/********************/读写锁/************************************************************/

读写锁只对写操作加以限制，读锁可以重复添加（或者不用添加），极大地提高了效率。

读写锁特性，写时独占资源，读时共享资源。

//相关函数
pthread_rwlock_t rwlock;			// 定义一个读写锁变量
pthread_rwlock_init(&rwlock, NULL);	// 初始化读写锁
pthread_rwlock_wrlock(&rwlock);		//添加写锁。写锁与任何锁都是互斥的
pthread_rwlock_rdlock(&rwlock);		//添加读锁。读锁是可以添加多个的，可以被多个线程同时访问，所以读锁也被称为共享锁
pthread_rwlock_unlock(&rwlock);		//解开写锁。访问完不解锁会形成死锁，死锁也就意味着此共享资源无法被其他线程访问
pthread_rwlock_destroy(&rwlock);	//在程序结束之前，应该销毁读写锁



/********************/互斥锁实例/************************************************************/
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

pthread_mutex_t mutex;

void handler(void* arg)                //死锁处理函数
{
    printf("[%u] is end.\n", (unsigned)pthread_self());
    pthread_mutex_unlock((pthread_mutex_t*)arg);           //解锁
}

void* thread_fun(void* arg)
{
    pthread_cleanup_push(handler, (void*)&mutex);
    pthread_mutex_lock(&mutex);

    while (1)
    {
        printf("1111111\n");
        sleep(1);
    }

    pthread_cleanup_pop(0);    //参数：0表示非正常退出时执行，非0为无论是否正常退出都执行
}

void* thread_fun1(void* arg)
{
    pthread_mutex_lock(&mutex);         //上锁
    while (1)
    {
        printf("2222222\n");
        sleep(1);
    }
    pthread_mutex_unlock(&mutex);       //解锁
}

int main()
{

    pthread_mutex_init(&mutex, NULL);

    pthread_t tid, tid1;
    pthread_create(&tid, NULL, thread_fun, NULL);
    pthread_create(&tid1, NULL, thread_fun1, NULL);

    sleep(2);


    pthread_cancel(tid);

    pthread_join(tid, NULL);
    pthread_join(tid1, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}



/********************/读写锁实例/************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_rwlock_t rwlock;        // 定义一个读写锁

int global = 0;                 // 全局变量，这是典型的共享资源

//============ WRITE lock ============//
// 游戏规则：每当你要对临界资源进行写操作的时候，必须加写锁
// 加了写锁之后，不可加任何其他的锁，写锁就是互斥锁

//============ READ lock ============//
// 游戏规则：每当你要对临界资源进行读操作的时候，可以加读锁，也可以不加锁
// 加了读锁之后，可以加其他的读锁，读锁就是共享锁

// 在结束对共享资源的访问之后，一定要解锁，否则会引起死锁


void* routine1(void* arg)       //写函数
{
    //pthread_rwlock_wrlock(&rwlock);
    global += 1;
    printf("I am %s, now global=%d\n", (char*)arg, global);
    sleep(1);
    //pthread_rwlock_unlock(&rwlock);

    pthread_exit(NULL);
}

void* routine2(void* arg)       //写函数
{
    pthread_rwlock_wrlock(&rwlock);
    global = 100;
    printf("I am %s, now global=%d\n", (char*)arg, global);
    sleep(1);
    pthread_rwlock_unlock(&rwlock);

    pthread_exit(NULL);
}

void* routine3(void* arg)       //读函数
{
    pthread_rwlock_rdlock(&rwlock);
    printf("I am %s, now global=%d\n", (char*)arg, global);
    sleep(1);
    pthread_rwlock_unlock(&rwlock);

    pthread_exit(NULL);
}

void* routine4(void* arg)       //读函数
{
    pthread_rwlock_rdlock(&rwlock);
    printf("I am %s, now global=%d\n", (char*)arg, global);
    sleep(1);
    pthread_rwlock_unlock(&rwlock);

    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    pthread_rwlock_init(&rwlock, NULL);              // 初始化读写锁

    pthread_t t1, t2, t3, t4;
    pthread_create(&t1, NULL, routine1, "thread 1");
    pthread_create(&t2, NULL, routine2, "thread 2");
    pthread_create(&t3, NULL, routine3, "thread 3");
    pthread_create(&t4, NULL, routine4, "thread 4");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_rwlock_destroy(&rwlock);                  //摧毁读写锁

    return 0;
}
