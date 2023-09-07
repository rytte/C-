#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>

//服务器

struct userinfo
{
	int sock;					//客户端套接字
	struct sockaddr_in addr;	//客户端信息结构体
};

int Count = 0;	//连接数



void* receive(void* arg)
{
	struct userinfo* p = (struct userinfo*)arg;

	char buf[100];
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		read(p->sock, buf, sizeof(buf));
		printf("客户端 %s（端口号 %d）：%s\n", inet_ntoa(p->addr.sin_addr), ntohs(p->addr.sin_port), buf);

		if (!strcmp(buf, "bye"))
		{
			printf("用户退出\n");
			pthread_exit(NULL);
		}
	}
}



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
	struct sockaddr_in addr;									//设置自己的网络地址信息结构体 
	memset(&addr, 0, sizeof(addr));

	addr.sin_family		 = AF_INET;								//使用IPV4方式进行通信
	addr.sin_port		 = htons(10203);						//设置连接端口号
	addr.sin_addr.s_addr = htonl(INADDR_ANY);					//设置本机IP，宏定义代表自动获取本机IPV4地址

	int ret = bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
	if (ret == -1)
	{
		printf("绑定套接字失败\n");
		return -1;
	}


	//3. 给等待连接的套接字设置监听
	listen(sfd, 10);											//第二个参数代表最大连接数量


	//4. 等待客户端的连接，获取客户端通信套接字
	struct userinfo* client[10];								//创建指针数组存放所有客户端信息
	pthread_t tid[10];

	struct sockaddr_in c_addr;									//保存连接过来的客户端的IP地址和端口号
	memset(&c_addr, 0, sizeof(c_addr));
	socklen_t len = sizeof(c_addr);

	while (1)
	{
		if (Count < 10)
		{
			printf("正在监听客户端连接...\n");
			int cfd = accept(sfd, (struct sockaddr*)&c_addr, &len);	//获取客户端套接字
			if (cfd == -1)
			{
				printf("连接失败\n");
				continue;
			}

			client[Count] = malloc(sizeof(struct userinfo));	//申请堆空间保存客户端信息
			if (client[Count] == NULL)
			{
				printf("申请堆空间失败\n");
				continue;
			}

			client[Count]->sock = cfd;					//保存新客户端套接字
			client[Count]->addr = c_addr;					//保存客户端ip和端口号信息

			//创建新线程接收新客户端消息
			pthread_create(&tid[Count], NULL, receive, (void*)client[Count]);
			Count++;
		}
	}


	//关闭服务端                                  
	close(sfd);
	return 0;
}