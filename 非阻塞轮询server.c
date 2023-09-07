#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

//UDP服务器

int main(int argc, char* argv[])
{
	//1.创建UDP通信套接字  
	int s_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (s_fd < 0)
	{
		perror("套接字创建失败\n");
		return -1;
	}

	//2.绑定自己的IP地址与端口号
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(20304);
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");

	int ret = bind(s_fd, (struct sockaddr*)&addr, sizeof(struct sockaddr));
	if (ret == -1)
	{
		printf("绑定套接字失败\n");
		return -1;
	}


	//将套接字设置为非阻塞
	long state = fcntl(s_fd, F_GETFL);
	state |= O_NONBLOCK;
	fcntl(s_fd, F_SETFL, state);



	//3.数据接收 recvfrom  返回值 : 失败-1  成功大于0的数据 等于 0 没有读取到数据
	struct sockaddr_in src;				//存放信息源的ip和端口号
	socklen_t srclen = sizeof(src);
	char buf[1024];

	while (1)		//轮询
	{
		printf("轮询中...\n");
		sleep(2);

		memset(buf, 0, sizeof(buf));
		int n = recvfrom(s_fd, buf, sizeof(buf), 0, (struct sockaddr*)&src, &srclen);		//阻塞等待数据
		if (n == -1 && errno == EAGAIN)		//资源暂不可得
		{
			continue;
		}
		else if (n > 0)						//输出数据
		{
			printf("接收到IP为 %s 端口号（%d）消息： %s \n", inet_ntoa(src.sin_addr), ntohs(src.sin_port), buf);
		}
	}
	

	//4.关闭服务器
	close(s_fd);

	return 0;
}





//重新设置为阻塞
//long state = fcntl(sockfd, F_GfETFL);
//state &= ~O_NONBLOCK;
//fcntl(sockfd, F_SETFL, state);