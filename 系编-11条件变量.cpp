/********************/条件变量/************************************************************/
假设有线程拿到了锁资源，但中途因为其他资源不够需要临时暂停，
那么此时可以通过条件变量释放互斥锁，让其他需要拿到互斥锁的线程先运行，当条件满足时，再使原线程拿到互斥锁。

条件变量并不是锁。
条件变量是在互斥锁的基础上添加了更为灵活的方法，但是条件变量是不可以单独使用，它必须要配合互斥锁进行使用。
满足某个条件的时候，条件变量可以帮助我们阻塞线程或解除线程的阻塞。


//相关函数
初始化、销毁条件变量
#include <semaphore.h>
int pthread_cond_init(pthread_cond_t* restrict cond, const pthread_condattr_t* restrict attr);  //初始化条件变量。成功返回0，失败返回-1。
            参数1：条件变量
            参数2：条件变量的属性，一般设置为NULL, 系统默认属性。

int pthread_cond_destroy(pthread_cond_t* cond);    //销毁条件变量。成功返回0，失败返回-1。


等待资源，唤醒线程
#include <semaphore.h>
int pthread_cond_wait(pthread_cond_t* restrict cond, pthread_mutex_t* restrict mutex);      //阻塞一条线程

特点:
1.阻塞等待，参数1的条件变量
2.释放已经掌握的互斥锁，相当于解开互斥锁, 值得注意的是1，2步操作是具有原子性操作的
3.使得线程处于睡眠状态，等待被唤醒，如果该线程被唤醒，则会解除阻塞，并重新获取互斥锁

int pthread_cond_timedwait(pthread_cond_t * restrict cond, 
                           pthread_mutex_t * restrict mutex, 
                           const struct timespec* restrict abstime);
int pthread_cond_signal(pthread_cond_t* cond);    //只唤醒某个等待中的线程。解除线程的阻塞   
int pthread_cond_broadcast(pthread_cond_t* cond); //唤醒全部的线程

            参数cond  : 条件变量
            参数mutex : 互斥锁
            参数restrict abstime : 超时时间限制

                    参数3该结构体中有两个值：
                        tv_sec, tv_usec 分别是秒和纳秒。
                        tv_usec 此值有范围限制的，就是不能超过1秒即1000000000纳秒。
                        如果超出1秒，就要在tv_sec 此值增加一秒;

            返回值：成功返回0，失败返回-1。
                    
            pthread_cond_wait()与pthread_cond_timedwait()两个函数功能是一样的，但后者可以设置超时时间。
            
    注意：1、pthread_cond_wait()，互斥锁mutex将会立即被解锁, 然后该线程才会进入到阻塞状态。
          2、被唤醒的线程并不能立即从pthread_cond_wait()中返回，而是必须要先获得配套的互斥锁。



/********************/条件变量实例/************************************************************/
#include "head.h"

pthread_cond_t  cond;    //定义一个条件变量
pthread_mutex_t mutex;   //定义一个互斥锁

int count = 0;  //代表的钱

void diedie(int arg)
{
	pthread_mutex_lock(&mutex);			//上锁

	count += 100;						//打钱
	printf("钱打过去了\n");

	pthread_cond_signal(&cond);			//唤醒最先等待的线程
	//pthread_cond_broadcast(&cond);	//唤醒全部线程
	
	pthread_mutex_unlock(&mutex);		//解锁
}

void *xiaoming(void *arg)
{
	int i = 3;
	while(i--)
	{
		pthread_mutex_lock(&mutex);		//上锁

		while(count < 13)				//等待钱的到来
		{
			printf("小明说：爹爹快打钱\n");
			pthread_cond_wait(&cond, &mutex);
			//1.阻塞线程
			//2.解锁
			//3.进入睡眠状态
		}
		//当满足以上条件的时候.则是需要付钱走人.
		sleep(1);
		count -= 13;
		printf("小明账户上还有 %d \n",count);
		
		pthread_mutex_unlock(&mutex);	//解锁
	}
}

void *meimei(void *arg)
{
	int i = 3;
	while(i--)
	{	
		pthread_mutex_lock(&mutex);		//上锁

		while(count < 13)				//等待钱的到来
		{
			printf("妹妹说：爹爹快打钱\n");
			pthread_cond_wait(&cond, &mutex);
			//1.阻塞线程
			//2.解锁
			//3.进入睡眠状态
		}
		//当满足以上条件的时候.则是需要付钱走人.
		sleep(1);
		count -= 13;
		printf("妹妹账户上还有 %d \n",count);

		pthread_mutex_unlock(&mutex);	//解锁
	}
}


int main(int argc, char const *argv[])
{
	signal(SIGINT, diedie);

	pthread_cond_init(&cond, NULL);				//初始化条件变量
	pthread_mutex_init(&mutex,NULL);			//初始化互斥锁

	pthread_t tid,tid1;							//创建线程
	pthread_create(&tid, NULL, xiaoming, NULL);
	pthread_create(&tid1, NULL, meimei, NULL);

	pthread_join(tid,NULL);						//等待线程退出

	pthread_cond_destroy(&cond);				//销毁条件变量
	pthread_mutex_destroy(&mutex);				//销毁互斥锁

	while(1);

	return 0;
}


