#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>


//用于接收用户的一帧数据
struct datainfo
{
	unsigned int cmd;					// cmd
	struct  sockaddr_in client_info; 	// 客户端的所有信息需要进行储存 ip地址与端口号
	char    data[1024];					// 客户端发送给服务器的数据
};

void *SendInfo(void *arg)
{
	int socket = *(int *)arg;

	struct datainfo sendata;
	char dest_ip[32];
	while(1)
	{
		printf("请输入CMD:\n");
		scanf("%d",&sendata.cmd);

		printf("请输入要发送的对象\n");
		scanf("%s",dest_ip);
		sendata.client_info.sin_addr.s_addr = inet_addr(dest_ip);

		printf("你要发送的内容:\n");
		scanf("%s",sendata.data);

		send(socket, &sendata, sizeof(sendata), 0);
	}
}


void *RecvInfo(void *arg)
{
	int socket = *(int *)arg;

	struct datainfo recvdata;

	while(1)
	{	
		memset(&recvdata, 0 , sizeof(recvdata));
		recv(socket, &recvdata, sizeof(recvdata), 0);

		if (recvdata.cmd == 1) //说明是点对点的发送数据
		{
			printf("recv %s 用户的信息 %s\n", 
					inet_ntoa(recvdata.client_info.sin_addr),
					recvdata.data);
		}
		else if(recvdata.cmd == 3)  //接受服务器返回的数据,在线则会接收到某个用户的信息 不在线打印对方不在线
		{
			printf("Ip为 : %s 的用户不存在\n", inet_ntoa(recvdata.client_info.sin_addr));
		}
		else if (recvdata.cmd == 4)
		{
			printf("用户信息为 : %s \n", inet_ntoa(recvdata.client_info.sin_addr));
		}
		else if(recvdata.cmd == 5)
		{
			printf("所有的用户信息已查找完毕\n");
		}
	}
}



int main(int argc, char const *argv[])
{
	//1.创建套接字
	int clinet_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clinet_fd == -1)
	{
		printf("创建套接字失败\n");
		return -1;
	}


	//2.连接服务器,配置服务器的信息 ip+端口号
	struct sockaddr_in sever_info;
	sever_info.sin_family = AF_INET;
	sever_info.sin_port   = htons(40000);
	sever_info.sin_addr.s_addr   = inet_addr(argv[1]);


	//功能：发送连接请求    三次握手就是由该函数发起.
	//int sockfd : 哪个套接字要连接服务器
	//const struct sockaddr *addr : 你要连接服务器的结构体信息
	//socklen_t addrlen : 服务器的结构体信息大小
	//返回值： 成功返回0 失败返回 -1；
	int ret = connect(clinet_fd, (struct sockaddr *)&sever_info,sizeof(sever_info));
	if (ret == -1)
	{
		printf("请求失败..\n");
		return -1;
	}

	pthread_t sendtid, recvtid;
	pthread_create(&sendtid, NULL , SendInfo, (void *)&clinet_fd);
	pthread_create(&recvtid, NULL , RecvInfo, (void *)&clinet_fd);

	pthread_join(sendtid,NULL);
	pthread_join(recvtid,NULL);

}