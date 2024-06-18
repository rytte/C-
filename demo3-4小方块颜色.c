#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

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
	int col_buf[800*480] = {0};
	int x,y;
	for(y=150; y<300; y++)
	{
		for(x=200; x<500; x++)
			col_buf[800*y+x] = 0x00ff00; // 绿色
	}
	
	// 3.write
	write(lcd_fd, col_buf, sizeof(col_buf));

	// 4.关闭
	close(lcd_fd);
	return 0;
}