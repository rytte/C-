#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <net/if.h>

//UDP组播接收端
//其发送端dstIP设为组播地址即可,端口号设定为接收目标绑定的端口号

int main(int argc, char* argv[])
{
	//1.创建UDP通信套接字  
	int s_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (s_fd < 0)
	{
		perror("套接字创建失败\n");
		return -1;
	}


	//配置组播结构体
	struct ip_mreqn mult;
	mult.imr_multiaddr.s_addr = inet_addr("224.0.1.200");     //组播的IP地址
	mult.imr_address.s_addr = inet_addr("192.168.12.99");     //你的IP地址
	mult.imr_ifindex = if_nametoindex("ens33");
	setsockopt(s_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mult, sizeof(mult));


	//2.绑定接收的IP地址与端口号，不可冲突
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


	//3.数据接收 recvfrom  返回值 : 失败-1  成功大于0的数据 等于 0 没有读取到数据
	struct sockaddr_in src;				//存放信息源的ip和端口号
	socklen_t srclen = sizeof(src);

	char buf[1024];
	memset(buf, 0, sizeof(buf));

	recvfrom(s_fd, buf, sizeof(buf), 0, (struct sockaddr*)&src, &srclen);			//阻塞等待数据
	printf("接收到IP为 %s 端口号（%d）消息： %s \n", inet_ntoa(src.sin_addr), ntohs(src.sin_port), buf);

	//4.关闭服务器
	close(s_fd);

	return 0;
}