#include "pthread_pool.h"


//初始化线程池	参数一：指定线程池；参数二：初始化后线程数量
//步骤：初始化线程池结构体、创建线程
bool Pthread_Pool_Init(thread_pool* pool, unsigned int thread_number)
{

	pthread_mutex_init(&pool->lock, NULL);					   	 //初始化互斥锁
	pthread_cond_init(&pool->cond, NULL);						 //初始化条件变量
	pool->shutdown = false;										 //初始标志位 为 假 代表不销毁 true代表销毁


	pool->task_list = (struct task*)malloc(sizeof(struct task));			//为任务链表的头节点申请堆空间,方便后面添加任务进行使用
	if (pool->task_list == NULL)
	{
		printf("申请任务链表头节点失败\n");
		return false;
	}


	pool->tids = (pthread_t*)malloc(sizeof(pthread_t) * MAX_ACTIVE_THREADS);//申请堆空间用于保存线程池的所有的线程号
	if (pool->tids == NULL)
	{
		printf("申请储存线程号堆空间失败\n");
		return false;
	}


	pool->task_list->next = NULL;					//对任务链表的头节点进行初始化

	pool->max_waiting_tasks = MAX_WAITING_TASKS;	//对等待的任务数量进行初始化

	pool->waiting_tasks = 0;						//需要处理的任务数量进行初始化

	pool->active_threads = thread_number;			//对初始化的线程数量赋值

									
	for (size_t i = 0; i < thread_number; i++)		//循环创建线程
	{
		int ret = pthread_create(&((pool->tids)[i]), NULL, routine, (void*)pool);
		if (ret != 0)
		{
			printf("%s\n", strerror(ret));
			return false;
		}
	}

	return true;
}



//函数功能：添加任务到任务链表
//参数一：你需要把任务添加到哪个线程池当中
//参数二：你需要添加的任务
//参数三：传递给该任务的参数
bool Add_Task(thread_pool* pool, void* (*do_task)(void* arg), void* arg)
{

	struct task* new_task = (struct task*)malloc(sizeof(struct task));		//初始化一个任务链表的新节点
	if (new_task == NULL)
	{
		printf("为任务节点申请堆空间失败\n");
		return false;
	}


	//对新节点的数据域与指针域进行初始化
	new_task->do_task = do_task;						//把一个任务添加到链表的节点当中
	new_task->arg = arg;							    //把传递进来的参数写到链表当中去
	new_task->next = NULL;


	if (pool->waiting_tasks >= MAX_WAITING_TASKS)		//若任务链表当中任务数大于1000,则释放刚刚申请出来的任务。
	{
		fprintf(stderr, "任务太多无法添加\n");			//提前让出CPU资源
		free(new_task);
		return false;
	}

	//===========添加任务前上锁==============
	pthread_mutex_lock(&(pool->lock));

	struct task* tmp = pool->task_list;					//遍历找到最后一个节点
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}

	tmp->next = new_task;								//让最后一个节点指向新的节点（节点尾插）

	pool->waiting_tasks++;								//当前待处理的任务进行 +1

	pthread_mutex_unlock(&(pool->lock));
	//===========处理完该节点解锁=============

	pthread_cond_signal(&(pool->cond));					//唤醒一条线程开始工作


	return true;				//添加任务成功
}



//处理死锁函数
void headler(void* arg)			//如果被取消的时候，处于上锁状态，被取消的线程依旧自动解锁，再响应取消
{
	printf(">>%ld<< 进入解锁\n", pthread_self());
	pthread_mutex_unlock((pthread_mutex_t*)arg);
}



//线程处理任务函数，参数为线程池首地址
//取下任务节点并执行
void* routine(void* arg)
{
	thread_pool* pool = (thread_pool*)arg;								//先把数据类型强转
	struct task* p = NULL;
	while (1)
	{
		pthread_cleanup_push(headler, (void*)&pool->lock);				//防止线程被意外取消,会出现死锁的情况	//headler: 处理死锁的函数

		//==============取下节点前上锁，因为任务链表是一个共享资源=============
		pthread_mutex_lock(&(pool->lock));	

		if (pool->waiting_tasks == 0 && pool->shutdown == false)		//当线程池当中没有任务并且线程池不被销毁的情况下
		{
			pthread_cond_wait(&(pool->cond), &(pool->lock));			//等待条件变量（阻塞线程，等待新任务）
		}

		if (pool->waiting_tasks == 0 && pool->shutdown == true)			//如果线程池当中没有任务 并且 线程池将要被销毁的情况下
		{
			pthread_mutex_unlock(&(pool->lock));			//先解锁
			pthread_exit(NULL);								//退出线程
		}

		//取下节点，运行任务
		p = pool->task_list->next;							//取下第一个节点P运行.
		pool->task_list->next = p->next;
		p->next = NULL;


		pool->waiting_tasks--;								//待执行的任务个数 -1

		pthread_mutex_unlock(&(pool->lock));				//解锁
		//==========================已解锁并退出线程============================

		pthread_cleanup_pop(0);

		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);	//防止执行任务的过程被意外取消,将线程设置为不可取消的状态
		(p->do_task)(p->arg);									//执行任务（函数调用）
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);	//当任务执行完毕之后,将线程设置为可取消.

		free(p);												//该任务已经被消费完毕,释放该节点
	}
}



//往线程池当中添加线程
//参数一：线程池
//参数二：要往该线程池当中添加多少条线程
int Add_Pthread(thread_pool* pool, unsigned int number)
{
	if (number == 0)												//添加数目为0时表示查看当前有多少条活跃线程
		return pool->active_threads;

	unsigned int total_threads = pool->active_threads + number;		//把原有的线程的数量 加上新添加的数量
	unsigned int value = 0;											//添加成功的线程数目

	for (size_t i = pool->active_threads; i < total_threads && i < MAX_ACTIVE_THREADS; i++)		//最多只能够创建 19
	{
		int ret = pthread_create(&(pool->tids)[i], NULL, routine, (void*)pool);
		if (ret != 0)
		{
			printf("%s\n", strerror(ret));
			break;
		}
		value++;
	}
	pool->active_threads += value;									//实际添加后的数量

	return pool->active_threads;
}



//删除线程
int Delete_Pthread(thread_pool* pool, unsigned int delnumber)
{
	if (delnumber == 0)												//删除数目为0时表示查看当前有多少条活跃线程
		return pool->active_threads;

	int temp = pool->active_threads - delnumber;					//剩余线程数
	temp = temp > 0 ? temp : 1;										//如果剩余线程数量要小于0 至少保留一条线程

	int i;
	for (i = pool->active_threads - 1; i > temp - 1; i--)
	{
		errno = pthread_cancel(pool->tids[i]);						//从最后一条线程开始取消
		if (errno != 0)
		{
			break;
		}
	}
	//此时 i 等于 tmp -1;
	if (i == pool->active_threads - 1)					//删除失败
		return -1;
	else
	{
		pool->active_threads = i + 1;					//删除一部分或全部删除完成
		return pool->active_threads;
	}
}



//销毁整个线程池
bool Destroy_Pool(thread_pool* pool)
{
	pool->shutdown = true;								//1.把线程池销毁的标志位置成true

	pthread_cond_broadcast(&pool->cond);				//2.唤醒所有在沉睡的线程,让它们恢复解锁状态并退出


	for (size_t i = 0; i < pool->active_threads; i++)	//3.等待线程退出
	{
		errno = pthread_join(pool->tids[i], NULL);

		if (errno != 0)
			printf("join [%ld] error %s\n", pool->tids[i], strerror(errno));		//回收线程资源失败，报错
		else
			printf("[%ld] exit\n", pool->tids[i]);									//回收线程资源成功
	}

	//如果执行到该位置代表所有的线程已退出
	free(pool->task_list);
	free(pool->tids);
}
