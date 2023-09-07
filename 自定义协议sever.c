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

struct userinfo *head = NULL;

//用于接收用户的一帧数据
struct datainfo
{
	unsigned int cmd;					// cmd
	struct  sockaddr_in client_info; 	// 客户端的所有信息需要进行储存 ip地址与端口号
	char    data[1024];					// 客户端发送给服务器的数据
};


//服务器保存所有用户的信息节点
struct userinfo
{
	pthread_t tid;					//线程号
	int sockfd;	  					//套接字
	struct  sockaddr_in destinfo;	//客户端的所有信息需要进行储存 ip地址与端口号
	struct userinfo *next;			//指针域
};


struct userinfo* Head_Init(void)
{
	struct userinfo* head = (struct userinfo*)malloc(sizeof(struct userinfo));
	if (head == NULL)
	{
		printf("申请堆空间失败\n");
		return NULL;
	}

	head->tid = 0;
	head->sockfd = 0;
	
	memset(&head->destinfo, 0 , sizeof(head->destinfo));
	head->next = NULL;

	return head;
}


void Inset_List_Tail(struct userinfo* head, struct userinfo* new_node)
{
	struct userinfo* p = head;
	while(p->next != NULL)
	{
		p = p->next;
	}

	p->next = new_node;
}

//struct sockaddr_in ipaddr 你需要找到的ip地址与端口号
struct userinfo* Check_List(struct sockaddr_in ipaddr)
{
	struct userinfo* p  = head->next;

	char s1[32];   //
	char s2[32];

	//可以把我们的要找的ip进行储存 因为我们的ip地址是一个网络大端序 转换为本地端序
	strcpy(s1, inet_ntoa(ipaddr.sin_addr));

	//遍历链表.
	while(p != NULL)
	{
		//把链表当中的数据拷贝到s2当中
		strcpy(s2, inet_ntoa(p->destinfo.sin_addr));

		if(strcmp(s1,s2) == 0)
		{
			printf("对方在线\n");
			return p;
		}
		p = p->next;
	}

	return NULL;
}




//用于接收数据,
void *clinetrecv(void *arg)
{
	struct userinfo *node = (struct userinfo *)arg;
	struct userinfo *p = NULL;
	//需要保存数据 struct datainfo
	struct datainfo data;
	

	while(1)
	{

		//开始接收数据 客户端发送一个结构体(数据包),服务器则就收一个结构体
		//data当中有3个信息  1.cmd  2.指定ip与端口号 3.真实数据
		recv(node->sockfd, &data, sizeof(node), 0);

		//处理接收到的一帧数据,根据CMD 来确定功能
		if(data.cmd == 1)
		{
			//遍历在线用户的链表,查看我要发送的ip是否存在,
			p = Check_List(data.client_info);
			if (p == NULL)	//不存在   服务器回复客户端 用户不在线
			{
				printf("该用户不存在,数据无法转发\n");

				//给发送过来的客户端返回一条对方不在线的信息
				data.cmd = 3;
				send(node->sockfd, &data, sizeof(data), 0);
			}
			else	//如果存在 转发数据
			{
				data.client_info.sin_addr = p->destinfo.sin_addr; //把链表当中的结构体信息的ip赋值给 
				data.client_info.sin_port = p->destinfo.sin_port; //把链表当中的结构体信息的ip赋值给 

				//数据进行转发
				send(p->sockfd, &data, sizeof(data), 0);
			}
			
			

		}

		if (data.cmd == 2)
		{
			data.cmd = 4;  //如果客户端接收到了 cmd == 4 说明他要打印这些节点当中的数据
			p = head->next;

			while( p != NULL)
			{
				data.client_info.sin_addr = p->destinfo.sin_addr; //把链表当中的结构体信息的ip赋值给 
				data.client_info.sin_port = p->destinfo.sin_port; //把链表当中的结构体信息的ip赋值给
				//数据进行转发
				send(node->sockfd, &data, sizeof(data), 0);
				p = p->next;
			}

			//根据不同的CMD来做不同的事情
			//链表已经遍历完毕 设置cmd = 5 表示所有节点发送完毕。
			data.cmd = 5;
			send(node->sockfd, &data, sizeof(data), 0);
		}
	}
}


int main(int argc, char const *argv[])
{
	int sever_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sever_fd == -1)
	{
		printf("创建套接字失败\n");
		return -1;
	}

	//2.绑定服务器地址,但是在绑定服务器之前需要配置服务器的IP与端口号

	struct sockaddr_in serve_info;
	serve_info.sin_family = AF_INET;
	serve_info.sin_port   = htons(40001);
	serve_info.sin_addr.s_addr = htonl(INADDR_ANY);			//INADDR_ANY 代表自动获取本地IP地址


	int ret = bind(sever_fd, (struct sockaddr *)&serve_info,sizeof(serve_info));
	if (ret == -1)
	{
		printf("服务器绑定IP+端口号失败\n");
		return -1;
	}


	ret = listen(sever_fd, 10);
	if (ret == -1)
	{
		printf("监听失败\n");
		return -1;
	}

	//创建一个头节点
	head = Head_Init();

	struct sockaddr_in client_info;
	socklen_t len = sizeof(client_info);
	int clinet_fd;

	struct userinfo * p = NULL;

	while(1)
	{
		clinet_fd = accept(sever_fd, (struct sockaddr *)&client_info, &len);
		if (clinet_fd == -1)
		{
			printf("客户端连接失败\n");
			return -1;
		}

		printf("连接成功\n");

		//创建一个新的节点
		p = (struct userinfo *)malloc(sizeof(struct userinfo));
		if (p == NULL)
		{
			printf("新用户节点申请失败\n");
			continue;
		}

		p->sockfd 	= clinet_fd;   //把链接上服务器的客户端套接字放到节点当中
		p->destinfo = client_info; //把客户端的端口号与ip放到节点当中
		p->next     = NULL;
		pthread_create( &p->tid, NULL, clinetrecv, (void*)p);

		Inset_List_Tail(head, p);
	}


	return 0;
}