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

//服务器
//客户端发送OOB信息时使用send函数并使用标志位MSG_OOB

int cfd;

void recvOOB(int sig)
{
	char oob;
	recv(cfd, &oob, 1, MSG_OOB); //接收对端的OOB带外数据
	printf("接收到OOB数据：%c\n", oob);
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
	listen(sfd, 5);												//第二个参数代表等待连接数


	//4. 无限等待客户端的连接，获取客户端通信套接字
	struct sockaddr_in c_addr;									//保存连接过来的客户端的IP地址和端口号
	memset(&c_addr, 0, sizeof(c_addr));
	socklen_t len = sizeof(c_addr);

	cfd = accept(sfd, (struct sockaddr*)&c_addr, &len);		//获取连接套接字（并非客户端的套接字）
	if (cfd == -1)
	{
		printf("连接失败\n");
		return -1;
	}
	printf("当前连接的对象为：%d\n", cfd);



	//设置复用属性
	int a = 1;
	socklen_t length = sizeof(a);
	ret = setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&a, length);
	if (ret < 0)
	{
		printf("设置复用属性失败\n");
		return -1;
	}

	//设置水位线（接收下限）
	int low = 10;
	socklen_t b = sizeof(a);
	setsockopt(cfd, SOL_SOCKET, SO_RCVLOWAT, (const void*)&low, b);

	//接收OOB数据
	signal(SIGURG, recvOOB);			//捕捉信号SIGURG
	fcntl(cfd, F_SETOWN, getpid());	//指定信号的接收者



	//5. 客户端和服务端通信
	char buf[100];
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		read(cfd, buf, sizeof(buf));
		printf("接收到来自 %d 的信息：%s\n", cfd, buf);
		
		if (!strcmp(buf, "bye"))
		{
			printf("对方已断开连接\n");
			break;
		}
	}


	//6. 关闭服务端                                  
	close(sfd);
	return 0;
}






//多路复用方式

//fd_set eset;
//FD_ZERO(&eset);
//FD_SET(cfd, &eset);						// 将套接字加入描述符集合中
//select(cfd + 1, NULL, NULL, &eset, NULL); // 监听 OOB
//if (FD_ISSET(cfd, &eset))
//{
//	char oob;
//	recv(cfd, &oob, 1, MSG_OOB);			//接收对端的OOB带外数据
//}