/********************/多线程/************************************************************/
线程是从进程中切割出的一部分资源，线程也能够实现多任务并发执行。

进程是系统资源分配的最小单位。线程是系统调度的最小单位。


//多线程模型
一对一模型：一个用户级线程映射到一个内核级线程
优点：真正并发(一个线程阻塞时其他线程不受影响)、充分利用多个处理器的优势，提升整体性能
缺点：线程数量限制、上下文切换开销

多对一模型：多个用户级线程映射到一个内核级线程
优点：高效的上下文切换、几乎无限制的线程数量、简化内核设计
缺点：并发度受限、不支持真正的并行执行

多对多模型：n个用户级线程映射到m个内核级线程(n>=m)
优点：结合了多对一模型和一对一模型的优点，既允许创建大量的用户线程以支持高并发性，又能够通过多个内核线程在多处理器系统上实现真正的并行执行。
缺点：管理和调度相对复杂


//线程资源
线程共享资源：
1.文件描述符表
2.每种信号的处理方式 ， 不推荐把信号与线程进行结合使用
3.当前工作路径
4.用户ID与组ID
5.内存地址空间 例如.test / .data / .bss / heap / 共享库

线程非共享资源：
1.线程ID
2.处理器线程和栈指针(内核栈，用于保存寄存器当中的临时值)
3.独立的栈空间（用户空间栈）
4.errno变量
5.信号屏蔽字
6.调度优先级

线程优缺点：
优点： 1.提高程序的并发性   2.开销小           3.数据通信，共享方便
缺点： 1.库函数，不稳定     2.调试, 编写困难   3.对信号支持不太友好
优点相对突出，缺点均不是硬伤，在能够同时使用进程和线程实现某一功能时，优先选择线程。



/********************/相关函数/************************************************************/
编译时需要链接线程库 -pthread

创建线程
#include <pthread.h>
int pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start_routine) (void*), void* arg);

	//参数解析
	参数1：新线程TID。传出参数, 用于保存新创建出来线程的id号。(正整数)
	参数2：线程属性。一般设置为NULL, 表示使用系统默认的属性。(标准属性)
	参数3：线程执行函数。(函数指针)传入返回值为void*的函数，也称为线程任务函数。
	参数4：传递给线程的参数。
	
	//返回值
	成 功 : 返回0
	失 败 : 返回errno

获取线程ID号（TID）
#include <pthread.h>
pthread_t pthread_self(void);		//返回线程ID号，此函数不会失败。

退出线程
#include <pthread.h>
void pthread_exit(void* retval);		//参数：用于保存线程退出值，传递给主线程中 pthread_join() 的返回值

等待线程退出
#include <pthread.h>
int pthread_join(pthread_t thread, void** retval);		//阻塞等待子线程退出，成功返回0，失败返回errno

			参数1：等待回收的线程ID号
			参数2：储存线程退出值的指针.(保留线程退出时所返回的数据)

		该函数会使调用者阻塞等待，直到所指定的线程退出为止。
		该函数返回时系统将回收退出线程的资源，调用线程可以获得退出线程的返回值。

取消线程
#include <pthread.h>
int pthread_cancel(pthread_t thread);       //参数：需要取消的线程ID号。成功返回0，失败返回错误码。
        
        注意：当线程被取消时, 该线程不会立即退出, 会继续执行直到遇到取消函数点时, 线程才会结束
			  该取消点可以通过 man 7 pthreads 可以进行查看具备这些取消点系统调用列表
              如果该线程当中没有取消点, 会导致该线程是无法正常退出的,
			  为了避免这种情况发生, 程序员自身也是可以自己设置取消点 void pthread_testcancel(void);

设置线程取消属性
#include <pthread.h>
int pthread_setcancelstate(int state, int* oldstate);	//设置当前线程取消的状态：可取消 或 不可取消，默认为可取消
int pthread_setcanceltype(int type, int* oldtype);		//设置当前线程取消的类型：延时取消 与 立即取消，默认延时取消

			参数 state
			PTHREAD_CANCEL_ENABLE        //可以取消，默认是可以被取消的.
			PTHREAD_CANCEL_DISABLE       //不可取消
			
			参数 oldstate：传入参数，用于保存原本线程的取消状态, 不想保存则设置为NUL。

			参数 type
			PTHREAD_CANCEL_DEFERRED			//延迟取消，默认为延迟取消
			PTHREAD_CANCEL_ASYNCHRONOUS     //立即取消

			参数 oldtype：传入参数，用于保存原本线程的取消类型, 不想保存则设置为NULL。


/************************************************************/
线程属性结构体
pthread_attr_t 类型变量,是Linux中用于存放线程属性的结构体类型定义如下.
        typedef struct
        {
             int detachstate;                   //线程的分离状态
             int schedpolicy;                   //线程调度策略
             struct sched_param schedparam;     //线程的调度参数
             int inheritsched;                  //线程的继承性
             int scope;                         //线程的作用域
             size_t guardsize;                  //线程栈末尾的警戒缓冲区大小
             int stackaddr_set;
             void* stackaddr;                   //线程栈的位置
             size_t stacksize;                  //线程栈的大小
        }pthread_attr_t;

    线程的属性有很多,设置思路都一样.以设置线程分离属性为例.

        线程的分离属性分为两种 : 可分离 与 不可分离
            可分离：  1.线程创建以后,不需要主线程进行回收(想回收也回收不了),线程结束时,会被系统自动回收.
                      2.在主线程中join回收线程时,主线程将不再阻塞等待该线程.
            不可分离：线程创建以后,需要主进程去主动回收.(线程被创建后,该线程被系统默认为可结合的状态).
    
    
设置分离属性的方式有两种：

方式1：
    函数作用: 设置线程属性分离.(在线程服务函数中使用) 
    函数原型:         

#include <pthread.h>
int pthread_detach(pthread_t thread)    //参数：需要分离的线程号。成功返回0，失败返回错误码。

在分离的线程内需要配合 pthread_t pthread_self(void) 函数获取自己的线程号使用
    

方式2：
线程属性设置的基本步骤
    1.定义线程属性变量并初始化
        int pthread_attr_init(pthread_attr_t *attr);
    2.根据你想设置的属性,选择对应的函数进行设置。
        //pthread_attr_setxxxx();
        //设置线程分离属性
        int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate); 
    3.创建线程,使用刚才初始化好的程属性变量.填写到pthread_create()函数的第二个参数当中.
    4.销毁属性变量
        int pthread_attr_destroy(pthread_attr_t *attr);
        
参数解析: 
    pthread_attr_t *attr : 为  pthread_attr_t 类型变量.
    int detachstate      :  宏定义.
              PTHREAD_CREATE_DETACHED   //表示可分离
              PTHREAD_CREATE_JOINABLE   //表示不可分离
              
线程的分离与非分离主要体现在该线程在执行完任务以后,还需不需要向创建的这个线程的任务发送信息。
如果需要发送,则设置为非分离,不需要则设置为分离.


/************************************************************/
设置或获取当前线程的优先级继承关系
#include <pthread.h>
int pthread_attr_setinheritsched(pthread_attr_t* attr, int inheritsched);           //设置优先级关系
int pthread_attr_getinheritsched(const pthread_attr_t* attr, int* inheritsched);    //获取优先级关系
        参数1：需要操作的属性
        参数2：继承的关系
                PTHREAD_INHERIT_SCHED     继承创建这个新线程的线程任务的调度关系.
                PTHREAD_EXPLICIT_SCHED    使用attr属性中的调度关系创建线程.


设置或获取当前线程的优先级调度关系
#include <pthread.h>
int pthread_attr_setschedpolicy(pthread_attr_t* attr, int policy);           //设置优先级调度方式
int pthread_attr_getschedpolicy(const pthread_attr_t* attr, int* policy);    //获取优先级调度方式

        参数 attr：  需要被设置的属性.
        参数 policy：需要被调度的方式.有以下三种，其中 SCHED_FIFO 和 SCHED_RR 调度方法需要管理员root权限才能使用。
                    SCHED_FIFO：先进先出的调度方式。设置有静态优先级 0 ~99, 数字越大，优先级越高。
                                优先级的高的会一直霸占CPU资源一直运行,只有高优先级运行完毕,才会轮到优先级低的线程运行.
                                如果静态优先级相同，那么一定要等待前一个线程运行结束后，才会轮到下一个线程运行.

                    SCHED_RR : 时间片轮转调度方法。设置动态优先级 - 19 ~20。数值越小，优先级越高。
                               为每一个线程设置了时间片，当线程运行完这段时间片以后，会切换到当前相同静态优先级的下一个线程中。
                               如果某一个线程一直在运行，这个线程的动态优先级会随着时间的增加，逐渐降低。到下一个线程运行.

                    SCHED_OTHER : 静态优先级为0，所有的关于静态优先级设置都无效.


设置或获取进程的静态优先级
#include <pthread.h>
int pthread_attr_setschedparam(pthread_attr_t* attr, const struct sched_param* param);
int pthread_attr_getschedparam(const pthread_attr_t* attr, struct sched_param* param);

        参数 pthread_attr_t* attr: 线程号
        参数 const struct sched_param* param : 静态优先级结构体
        struct sched_param
        {
            int sched_priority;     /* Scheduling priority */
        };

