#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char *argv[])
{
	// 1.打开lcd驱动
	int lcd_fd = open("/dev/fb0", O_RDWR);
	if(-1 == lcd_fd)
	{
		perror("open lcd failed!\n");
		return -1;
	}
	// 2.将颜色数据写入开发板
	char col_buf[800*480*4] = {0};
	for(int i=0; i<800*480; i++)
	{
		col_buf[0+i*4] = 0x00;	//b
		col_buf[1+i*4] = 0x00;	//g
		col_buf[2+i*4] = 0xff;	//r
		col_buf[3+i*4] = 0x00;	//a
	}
	
	// 3.write
	write(lcd_fd, col_buf, sizeof(col_buf));

	// 4.关闭
	close(lcd_fd);
	return 0;
}