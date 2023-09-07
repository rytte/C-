#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

//UDP客户端

int main(int argc, char* argv[])
{
	//1.创建UDP通信套接字  
	int c_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (c_fd < 0)
	{
		perror("创建套接字失败\n");
		return -1;
	}

	//2.配置服务器的IP地址与端口号
	struct sockaddr_in dst;
	dst.sin_family = AF_INET;
	dst.sin_port = htons(20304);
	dst.sin_addr.s_addr = inet_addr(argv[1]);

	//3.发送数据  sendto
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	printf("请输入MSG...\n");
	scanf("%s", buf);
	sendto(c_fd, buf, sizeof(buf), 0, (struct sockaddr*)&dst, sizeof(dst));

	//4.关闭客户端
	close(c_fd);
	return 0;
}