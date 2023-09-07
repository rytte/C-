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

//客户端

int main(int argc, char* argv[])
{
	//1. 创建套接字
	int cfd = socket(AF_INET, SOCK_STREAM, 0);
	if (cfd == -1)
	{
		printf("创建套接字失败\n");
		return -1;
	}


	//2. 设置并连接服务器的端口号和IP地址
	struct sockaddr_in addr;									//设置服务器的网络地址信息结构体 
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;									//使用IPV4方式进行通信
	addr.sin_port 	= htons(10203);								//设置连接端口号
	inet_pton(AF_INET, argv[1], &addr.sin_addr);				//设置服务器IP

	int ret = connect(cfd, (struct sockaddr*)&addr, sizeof(addr));
	if (ret == -1)
	{
		printf("连接服务器失败\n");
		return -1;
	}


	//3. 客户端和服务端通信
	char buf[100];
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		printf("请输入：");
		scanf("%s", buf);
		write(cfd, buf, strlen(buf));

		if (!strcmp(buf, "bye"))
		{
			printf("已断开连接\n");
			break;
		}
	}


	//4. 关闭客户端
	close(cfd);
	return 0;
}