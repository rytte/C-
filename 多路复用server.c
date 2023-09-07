#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>
#include <netinet/in.h>

//服务器

int main(int argc, char* argv[])
{
	//1. 创建套接字对象
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1)
	{
		printf("创建套接字失败\n");
		return -1;
	}


	//2. 绑定套接字（绑定端口号和IP地址） 
	struct sockaddr_in addr;									//设置服务器的网络地址信息结构体 
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;								//使用IPV4方式进行通信
	addr.sin_port = htons(10203);						//设置连接端口号
	addr.sin_addr.s_addr = htonl(INADDR_ANY);					//设置本机IP，宏定义代表自动获取本机IPV4地址

	int ret = bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
	if (ret == -1)
	{
		printf("绑定套接字失败\n");
		return -1;
	}


	//3. 给等待连接的套接字设置监听
	listen(sfd, 10);												//第二个参数代表等待连接数


	//4. 使用多路复用
	int maxfd = sfd;		//定义需要监控的文件描述符最大值
	struct timeval t;		//定义超时时间结构体
	fd_set rset;			//定义读操作文件集合
	int clientfd[10];		//定义客户端连接的套接字数组
	int num = 0;			//客户端连接的个数

	struct sockaddr_in c_addr;									//保存连接过来的客户端的IP地址和端口号
	socklen_t len = sizeof(c_addr);
	while (1)
	{
		FD_SET(sfd, &rset);				//向rset里面放入要监控的文件描述符
		for (int i = 0; i < num; i++)
		{
			FD_SET(clientfd[i], &rset);
		}

		t.tv_sec = 2;					//设置超时时间为2秒
		t.tv_usec = 0;

		//检测各集合的文件描述符变动，ret返回变动的数量。超时属性t表示阻塞监听的时间，超时则不再阻塞继续运行代码
		ret = select(maxfd + 1, &rset, NULL, NULL, &t);	
		if (ret < 0)					//select函数出错
		{
			perror("select failed\n");
			return -1;
		}
		else if (ret == 0)				//监听时间内没有任何文件有IO操作
		{
			printf("超时结束\n");
		}
		else if (ret > 0)				//有文件进行了IO操作
		{
			if (FD_ISSET(sfd, &rset))	//先判断监控文件描述符是否还在集合中
			{
				printf("有客户端连接\n");
				//处理客户端连接，生成新的专用通信套接字
				clientfd[num] = accept(sfd, (struct sockaddr*)&c_addr, &len); 
				if (clientfd[num] == -1)
				{
					perror("accept failed\n");
					return -1;
				}
				//必须保证maxfd始终是最大的文件描述符
				if (maxfd < clientfd[num])
				{
					maxfd = clientfd[num];
				}

				num++;					//数组下标+1
			}

			for (int i = 0; i < num; i++)
			{
				if (FD_ISSET(clientfd[i], &rset))	//收发消息
				{
					char buf[32] = { 0 };
					recv(clientfd[i], buf, 32, 0);
					printf("接收到数据：%s\n", buf);
				}
			}
		}

		//其它任务
		int i = 5;
		while (i--)
		{
			printf("%d\n", i);
			sleep(1);
		}
	}


	//5. 关闭服务端                                  
	close(sfd);
	return 0;
}