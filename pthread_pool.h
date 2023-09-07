#ifndef __PTHREAD_POOL_H_
#define __PTHREAD_POOL_H_

#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <errno.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <dirent.h>

#define MAX_WAITING_TASKS  1000   //最大的任务量
#define MAX_ACTIVE_THREADS 20     //最大的活跃线程数量

//任务节点的设计
struct task
{
	void *(*do_task)(void *arg);  //函数指针 指向某一个任务的.
	void *arg;                    //传递给该任务的参数
	struct task * next;           //指向下一个节点的指针
};

//设计线程池结构体
typedef struct pthread_pool
{
	pthread_mutex_t lock; 			//互斥锁
	pthread_cond_t cond; 			//条件变量
	struct task *task_list;			//任务链表的头节点
	pthread_t *tids;			    //用于指向一个堆空间,该堆空间储存的全部都是线程号
	unsigned int max_waiting_tasks; //最大的任务数量
	unsigned int waiting_tasks;		//需要处理的任务数量
	unsigned int active_threads;	//活跃的线程数量
	bool shutdown;					 //标志位代表线程池是否要被销毁
}thread_pool;



//线程池基本函数
bool Pthread_Pool_Init(thread_pool *pool, unsigned int thread_number);			//线程池初始化
bool Add_Task(thread_pool *pool, void *(*do_task)(void *arg), void *arg);		//添加任务
int Add_Pthread(thread_pool *pool, unsigned int number);						//添加线程
int Delete_Pthread(thread_pool *pool, unsigned int delnumber);					//删除线程
void *routine(void *arg);														//线程处理任务函数
void headler(void *arg);														//死锁处理函数
bool Destroy_Pool(thread_pool *pool);											//摧毁线程池


//自定义任务
void* mytask(void* arg);
void path(thread_pool* pool, char* dir_path, char* dest);

#endif