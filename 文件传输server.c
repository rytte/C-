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
	listen(sfd, 1);												//第二个参数代表等待连接数


	//4. 无限等待客户端的连接，获取客户端通信套接字
	struct sockaddr_in c_addr;									//保存连接过来的客户端的IP地址和端口号
	memset(&c_addr, 0, sizeof(c_addr));
	socklen_t len = sizeof(c_addr);

	int cfd = accept(sfd, (struct sockaddr*)&c_addr, &len);		//获取连接套接字（并非客户端的套接字）
	if (cfd == -1)
	{
		printf("连接失败\n");
		return -1;
	}
	printf("当前连接的对象为：%d\n", cfd);


	//5. 接收客户端文件		在链路层当中 一帧数据  46 ~ 1500
	//接收文件名
	char name[256] = { 0 };				//文件名
	char data[1024] = { 0 };			//存储接收的数据
	int size;							//每次读取的大小

	recv(cfd, name, sizeof(name), 0);
	printf("收到文件名为：%s\n", name);

	//拼接文件路径
	char path[256] = { 0 };
	getcwd(path, sizeof(path));			//获取当前工作路径
	sprintf(path, "%s/%s", path, name);
	printf("拼接后文件路径为：%s\n", path);

	//创建文件
	int fd = open(path, O_CREAT | O_RDWR, 0777);
	if (fd == -1)
	{
		printf("打开 %s 失败\n", path);
		return -2;
	}
	usleep(100 * 1000);

	//传输文件
	while (1)
	{
		memset(data, 0, sizeof(data));
		size = recv(cfd, data, sizeof(data), 0);
		if (size > 0)								//如果还能读取到数据
		{
			write(fd, data, size);					//则全部写入
		}
		else
		{
			perror("\n");							//报错或全部写完
			break;
		}
	}


	//6. 关闭服务端  
	close(fd);
	close(sfd);
	return 0;
}