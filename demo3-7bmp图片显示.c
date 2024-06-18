#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char *argv[])
{
	// 1.打开lcd
	int lcd_fd = open("/dev/fb0", O_RDWR);
	if(-1 == lcd_fd)
	{
		perror("open lcd failed!\n");
		return -1;
	}
	// 2.打开图片
	int bmp_fd = open("/Even/share/kq.bmp", O_RDWR);
	if(-1 == bmp_fd)
	{
		perror("open lcd failed!\n");
		return -1;
	}
	// 偏移去掉头信息
	lseek(bmp_fd, 54, SEEK_SET);
	// 3.读取图片像素数据
	char bmp_buf[800*480*3];
	read(bmp_fd, bmp_buf, sizeof(bmp_buf));
	// 4.将24位图片转换为32位
	/*************************方法一，每一个像素后补一个透明度***/
	/*char buf32[800*480*4];
	for(int i=0; i<800*480; i++)
	{
		buf32[0+i*4] = bmp_buf[0+3*i]; // b
		buf32[1+i*4] = bmp_buf[1+3*i]; // g
		buf32[2+i*4] = bmp_buf[2+3*i]; // r
		buf32[3+i*4] = 0x00;    // a
	}*/
	/***************方法二：位移*****************/
	int buf_32[800*480];
	for(int i=0; i<800*480; i++)
	{						//b				g					r					a
		buf_32[i] = bmp_buf[0+i*3]<<0 | bmp_buf[1+i*3]<<8 | bmp_buf[2+i*3]<<16 | 0x00<<24;
	}

	// 将图片翻转，写入LCD
	int x,y;
	int buf_fz[800*480];
	for(y=0; y<480; y++)
	{
		for(x=0; x<800; x++)
		{
			buf_fz[800*y+x] = buf_32[800*(479-y)+x];
		}
	}

	// 3.将像素数据写入lcd
	write(lcd_fd, buf_fz, sizeof(buf_fz));
	return 0;
}





