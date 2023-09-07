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

struct userinfo* Head;

typedef struct userinfo
{
	pthread_t tid;				//线程号
	int sockfd;					//客户端套接字
	struct sockaddr_in c_addr;	//客户端信息结构体
	struct userinfo* prev;		//指针域
	struct userinfo* next;
}user;


user* Head_Init(void);
void Insert_List(user* node);
void Delete_List(user* node);
void* Show_List(void);
void* receive(void* arg);



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

	addr.sin_family = AF_INET;								//使用IPV4方式进行通信
	addr.sin_port = htons(10203);							//设置连接端口号
	addr.sin_addr.s_addr = htonl(INADDR_ANY);				//设置本机IP，宏定义代表自动获取本机IPV4地址

	int ret = bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
	if (ret == -1)
	{
		printf("绑定套接字失败\n");
		return -1;
	}


	//3. 给等待连接的套接字设置监听
	listen(sfd, 10);


	//4. 等待客户端的连接，获取客户端通信套接字加入链表
	Head = Head_Init();												//创建并初始化一个头结点
	struct sockaddr_in temp_addr;									//临时保存连接过来的客户端的IP和端口号
	memset(&temp_addr, 0, sizeof(temp_addr));
	socklen_t len = sizeof(temp_addr);

	while (1)
	{
		printf("正在监听客户端连接...\n");
		int cfd = accept(sfd, (struct sockaddr*)&temp_addr, &len);	//获取客户端套接字
		if (cfd == -1)
		{
			printf("客户端连接失败\n");
			continue;
		}
		printf("连接成功\n");


		user* node = (user*)malloc(sizeof(user));	//创建新节点
		if (node == NULL)
		{
			printf("申请堆空间失败\n");
			continue;
		}

		node->sockfd = cfd;							//保存新客户端套接字
		node->c_addr = temp_addr;					//保存客户端ip和端口号信息

		Insert_List(node);							//新用户信息插入链表
		pthread_create(&node->tid, NULL, receive, (void*)node);	//创建新线程接收新客户端消息
	}


	close(sfd);				//关闭服务端
	return 0;
}



//头节点初始化
user* Head_Init(void)
{
	user* head = (user*)malloc(sizeof(user));	//申请堆空间
	if (head == NULL)
	{
		printf("申请堆空间失败\n");
		return NULL;
	}

	head->tid = 0;								//节点初始化
	head->sockfd = 0;
	memset(&head->c_addr, 0, sizeof(head->c_addr));
	head->next = head;
	head->prev = head;

	return head;
}


//新节点尾插
void Insert_List(user* node)
{
	user* pos;									//找到尾结点
	for (pos = Head; pos->next != Head; pos = pos->next);

	node->next = Head;							//插在最后
	node->prev = pos;
	pos->next = node;
	Head->prev = node;
}


//删除节点（用户退出）
void Delete_List(user* node)
{
	user* pos;
	for (pos = Head->next; pos->sockfd != node->sockfd; pos = pos->next);	//通过对比sockfd找到要删除的节点

	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
}


//遍历链表
void* Show_List(void)
{
	printf("当前连接用户\n");
	user* pos;
	for (pos = Head->next; pos != Head; pos = pos->next)
	{
		printf("客户端(套接字)：%d	IP < %s >	PORT < %d >\n", pos->sockfd, inet_ntoa(pos->c_addr.sin_addr), ntohs(pos->c_addr.sin_port));
	}
}


//新客户端接待函数
void* receive(void* arg)
{
	user* node = (user*)arg;

	char buf[100];
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		read(node->sockfd, buf, sizeof(buf));
		printf("客户端 %s（端口号 %d）：%s\n", inet_ntoa(node->c_addr.sin_addr), ntohs(node->c_addr.sin_port), buf);

		if (!strcmp(buf, "bye"))
		{
			printf("用户退出\n");
			Delete_List(node);
			pthread_exit(NULL);
		}

		if (!strcmp(buf, "list"))
		{
			Show_List();
		}
	}
}
