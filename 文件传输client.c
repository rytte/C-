#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/stat.h>
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
	addr.sin_port = htons(10203);								//设置连接端口号
	inet_pton(AF_INET, argv[1], &addr.sin_addr);				//设置服务器IP

	int ret = connect(cfd, (struct sockaddr*)&addr, sizeof(addr));
	if (ret == -1)
	{
		printf("连接服务器失败\n");
		return -1;
	}
	printf("连接成功\n");

	//3. 向服务器发送文件	在链路层当中 一帧数据  46 ~ 1500	
	//先发送文件名
	send(cfd, argv[2], strlen(argv[2]), 0);

	//获取文件大小
	int fd = open(argv[2], O_RDWR);			//打开需要发送的文件
	if (fd == -1)
	{
		printf("%s 文件打开失败\n", argv[2]);
		return -1;
	}

	int fsize = lseek(fd, 0, SEEK_END);		//通过偏移获取文件大小
	lseek(fd, 0, SEEK_SET);					//移回光标

	//传输文件
	char data[1024];						//数据缓冲区
	int size;								//读取的文件大小
	while (fsize > 0)		//当还没读完
	{
		memset(data, 0, sizeof(data));
		size = read(fd, data, sizeof(data));
		if (size > 0)		//读取数据正常，则发送数据
		{
			send(cfd, data, size, 0);
			fsize -= size;
		}
		else
		{
			printf("数据读取失败\n");
			break;
		}
	}


	//4. 关闭客户端
	close(fd);
	close(cfd);
	return 0;
}