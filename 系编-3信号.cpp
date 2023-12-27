/********************/信号/************************************************************/)
信号是Linux进程间通信(IPC)中唯一的异步通信方式。

一个进程收到信号时的处理方式与CPU收到中断请求时的处理方式一样。
收到信号的进程会跳入信号处理函数，执行完后再跳回原来的位置继续执行。

所有信号的产生以及处理全部都是由 内核 负责完成的。

信号会打断睡眠。


/************************************************************/
递达：递送并且到达进程。
未决：产生和递达之间的状态，主要是因为阻塞或屏蔽导致的该状态。

阻塞信号集(信号屏蔽字)：
将某些信号加入到集合当中，对他们设置屏蔽，当屏蔽 X 信号后，再收到该信号，该信号将会被推后处理（解除屏蔽后）。

未决信号集：
1.信号产生时，未决信号集当中描述该信号的位会立刻被置为1，表示该信号处于未决状态。当信号被处理完毕后，该信号位会立即被反转为0。
2.信号产生后由于某些原因（主要是信号阻塞）没有抵达，这类信号的集合称之为未决信号集，在屏蔽解除前，信号一直处于未决状态。


信号的处理方式有三种：忽略、捕捉和默认动作。两种信号不能被忽略和捕捉（分别是 SIGKILL和SIGSTOP）。



/********************/可靠信号和不可靠信号/************************************************************/
非实时信号：1~31 不可靠信号，同一个不可靠信号同时发生多次时，只会留一个信号，其它都会丢失。

		不可靠信号都对应着一个系统事件，当产生某个事件时，将产生这个事件的对应值。
		如按ctrl + c时，会产生SIGINT信号，对应的默认反应是进程终止。


实时信号：34 ~64 可靠信号，同一个信号同时发生多次时可以排队等待执行，不会丢失。

		可靠信号也都有缺省动作，默认反应都是结束进程。


/********************/相关函数/************************************************************/
发送信号
#include <sys/types.h>
#include <signal.h>
int kill(pid_t pid, int sig)		//向指定进程发送一个信号。成功返回0，失败返回-1。
									//参数pid：小于 -1：发送给进程组里所有的进程(该进程组的ID号, 例如发送给1234这个进程组, 该参数该填写 -1234);
											 //等于 -1：信号将被发送给所有的进程
											 //等于  0：信号将被发送给与当前进程组中的所有进程;
											 //大于  0：信号将被发送给指定的进程;
									//参数sig：将要发送的信号值或信号名

接收信号
#include <signal.h>
void (*signal(int signum, void (*handler)(int))) (int)	
									//捕捉信号及处理。成功返回最近一次调用参数列表中函数指针的值，失败返回SIG_ERR。
									//参数sig：将要发送的信号值或信号名
									//参数二：SIG_IGN 忽略，SIG_DFL 默认动作，*handler 处理函数

发送信号
int sigqueue(pid_t pid, int sig, const union sigval value)
									//发送信号。成功返回0，失败返回-1。
									//参数三: 是一个联合体,携带的额外数据.需要发送数据时,需要定义该类型的联合体，如下
									union sigval
									{
										int   sival_int;    //携带整数
										void* sival_ptr;    //携带一个通用型指针.  指向共享内存的首地址,并不能传递一个字符串.
									};

接收信号
int sigaction(int sig, const struct sigaction* act, struct sigaction* oldact)
									//捕获及处理信号
									//参数二：结构指针，新设置的struct sigaction结构体
									//参数三：以前，保存当前进程设置的响应信息.不想保存则直接填写NULL

	

/********************/信号阻塞/************************************************************/
信号阻塞：在信号里，阻塞是把信号挂起，进程不受指定信号的干扰，等到解除了阻塞之后，再去响应该信号。

信号阻塞掩码集：Linux中定义的 "sigset_t" 类型变量，该变量存放了Linux中所有你想要阻塞的信号的集合，所以被称之为信号阻塞掩码集.
				"sigset_t" 类型变量其实是一个结构体，结构体里有一个成员是一个整型变量，存放着Linux中的信号值.

#include <signal.h>
int sigemptyset(sigset_t* set)						//将阻塞信号集清空
int sigfillset(sigset_t* set)						//将所有信号(62个)添加到信号集中
int sigaddset(sigset_t* set, int signum)			//将指定的一个信号添加到信号集中
int sigdelset(sigset_t* set, int signum)			//将一个指定信号从信号集中剔除
int sigismember(const sigset_t* set, int signum)	//判断一个指定的信号是否在信号集中
		//参数解析
		参数 sigset_t* set : 用户自定义信号集.
		参数 int signum : 要添加、剔除、判断的信号.
		//返回值：
		成功返回1，失败返回0。
		其中sigismember() 成功返回1，说明该信号集中有你要查找的信号，失败返回 -1。

int sigprocmask(int how, const sigset_t* set, sigset_t* oldset)		//阻塞或解除信号。成功返回0，失败返回-1。
		//参数解析
		参数1 int how : 可以在原有阻塞的信号集基础上, 添加, 替换, 解除信号.
						SIG_BLOCK : (合并)设置信号阻塞, 在 oldset 原有的信号集中, 添加 set 中的信号.
						SIG_UNBLOCK : (解除)解除信号阻塞, 在 oldset 原有的阻塞的信号基础上, 解除set中的信号.
						SIG_SETMASK : (替换)设置信号阻塞, 将 oldset 里原有的阻塞信号, 替换为set中的信号.
		
		参数2 const sigset_t* set : 存放要阻塞信号集 或 解除阻塞的信号集
		参数3 sigset_t* oldset : 存放当前进程原有的信号集.如果你不使用它, 可以直接设置为NULL.
		
int sigpending(sigset_t* set)						//读取当前进程的未决信号集。成功返回0，失败返回-1。参数为传出参数。



/********************/信号跳转/************************************************************/
#include <setjmp.h>
int setjmp(jmp_buf env)
int sigsetjmp(sigjmp_buf env, int savesigs)
//参数env : 跳转标志.
//参数savesigs : 如果为非0, 则跳转后该信号不会被阻塞, 如果为0, 则该信号会被阻塞.

setjmp()函数在跳转以后, 同样的信号会被阻塞.
sigsetjmp()函数在跳转以后, 可以设置同样的信号是否被阻塞.


#include <setjmp.h>
void longjmp(jmp_buf env, int val)
void siglongjmp(sigjmp_buf env, int val)
//参数env : 跳转标志.
//参数val : 设置跳转位置的结果.

这是两组函数, 需要配套使用.
setjmp()函数	会跳转到  longjmp()函数   对应的位置
sigsetjmp()函数 会跳转到 siglongjmp()函数 对应的位置



/********************/信号知识点总结/************************************************************/
//1.信号的特点 简单 能够携带的信息比较少 特定的情况才会触发信号
//2.信号是由我们自己触发的，但是是由内核负责发送和处理
//3.未决 递达
//4.内核是如何去处理未决信号的.
	// 一旦产生一个信号,则该信号会被添加到未决信号掩码集当中,把该信号的标志位置成1.
	// 再去查看阻塞掩码集对应的标志位,如果阻塞掩码集当中该位为1，则表示该信号被阻塞，内核不做处理
	// 直到阻塞掩码集的标志位被置成0，这时内核才会去处理该信号，当该信号被处理完毕后，会把未决信号
	// 掩码集当中的标志位置成0.


// 实时信号与非实时信号的区别在哪
// 实时信号 	34 ~ 64号信号 如果同一个信号产生多次,会响应多次。并且会排队响应.
// 非实时信号 	1 ~ 31号信号  如果同一时间内，产生多个信号，则只会响应一次,其余的信号会被丢弃，响应并无顺序可言


//5,signal kill   sigqueue sigation  siginfo_t
//6.信号的阻塞掩码集 sigaddset sigdelset sigfillset sigemtpyset sigismember
//  sigpromask 1.设置阻塞掩码集 2.解除阻塞掩码集 3.用旧的掩码集替换新的掩码集

// sigpending 读取内核当中的未决信号掩码集
// longjmp 跳转 setjmp     			相同的信号只会响应一次  
// 设置标志位 siglongjmp sigsetjmp sigsetjmp第二个参数如果为非0 则响应多次 否则响应一次

//信号安全: 全局变量不能够在信号处理函数当中使用  信号会打断进程的睡眠态



/********************/kill和signal实例/************************************************************/
//kill发送信号
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const* argv[])
{
	kill(atoi(argv[1]), SIGINT);		//参数1：目标进程	参数2：发送的信号

	return 0;
}


/************************************************************/
//signal接收信号
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void headler(int arg)						//int arg 形参 : 标示的是信号值
{
	printf("我收到了 %d 号信号\n", arg);
}

int main(int argc, char const* argv[])
{
	signal(SIGINT, headler);	//参数1：处理的信号		参数2：处理动作：SIG_IGN 忽略、SIG_DFL 默认动作、处理函数的指针

	while (1)
	{
		printf("PID : %d\n", getpid());
		sleep(1);
	}
	return 0;
}



/********************/sigqueue和sigaction实例/************************************************************/
//sigqueue发送
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const* argv[])
{
	//参数三： const union sigval value
	//   union sigval {
	//            int   sival_int;   可以发送一个整型变量
	//            void *sival_ptr;   可以发送一个共享内存的地址
	//        };

	union sigval value;
	value.sival_int = 100;

	printf("%d\n", getpid());

	sigqueue(atoi(argv[1]), SIGINT, value);		//参数1：目标进程	参数2：发送的信号	参数3：携带的数据

	return 0;
}


/************************************************************/
//sigaction接收
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void Fun1(int arg)
{
	printf("收到了 %d 号信号\n", arg);
}

void Fun(int arg, siginfo_t* inof, void* a)
{
	printf("收到了 %d 号信号\n", inof->si_signo);
	printf("%d 发送的信号\n", inof->si_pid);
	printf("收到的额外数据是 %d\n", inof->si_int);
}

int main(int argc, char const* argv[])
{
	printf("%d\n", getpid());
	//参数1 int sig： 接收的信号信号
	//参数2 const struct sigaction *act, 接收信号的方式 (用户自己配置)
	//参数3 struct sigaction *oldact   , 旧的接收信号方式
	struct sigaction act;
	act.sa_sigaction = Fun1;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);

	while (1);
	return 0;
}


/********************/阻塞掩码集/************************************************************/
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void printf_set(sigset_t* set)
{
	for (size_t i = 1; i < 64; i++)
	{
		if (sigismember(set, i))
			putchar('1');
		else
			putchar('0');
	}
	printf("\n");
}

int main(int argc, char const* argv[])
{
	sigset_t Set_sig;				             //定义sigset_t类型的变量.
	sigemptyset(&Set_sig);		            	 //清空信号集

	//添加信号到 Set_sig 信号集中
	sigaddset(&Set_sig, SIGINT);
	sigaddset(&Set_sig, SIGALRM);
	sigaddset(&Set_sig, SIGQUIT);

	sigprocmask(SIG_BLOCK, &Set_sig, NULL);		//设置阻塞

	printf("阻塞8s\n");
	sleep(8);

	sigpending(&Set_sig);                       //读取阻塞掩码集
	printf_set(&Set_sig);                       //输出阻塞掩码集

	sigprocmask(SIG_UNBLOCK, &Set_sig, NULL);   //解除阻塞
	pause();

	return 0;
}



/********************/信号跳转/************************************************************/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

jmp_buf flag;		//跳转标记

void func(int sig)
{
	printf("recv sig=%d\n", sig);
	if (sig == SIGUSR1)
		siglongjmp(flag, 1);//跳转到setjmp(flag),并且函数结果为1
	if (sig == SIGUSR2)
		siglongjmp(flag, 2);
}

int main()
{
	printf("pid=%d\n", getpid());

	int num = sigsetjmp(flag, 0);//第二个参数只要是非0就行了
	switch (num)
	{
	case 1: printf("flag=1\n");	break;
	case 2: printf("flag=2\n"); break;
	default:printf("flag=%d\n", num); break;
	}

	signal(SIGUSR1, func);
	signal(SIGUSR2, func);
	while (1);
	return 0;
}

