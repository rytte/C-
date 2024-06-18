#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <sys/mman.h>

int lcd_fd;
int *lcd_map;

// 打开lcd
int lcd_open(void)
{
	// 1.打开lcd
	lcd_fd = open("/dev/fb0", O_RDWR);
	if(-1 == lcd_fd)
	{
		perror("open lcd failed!\n");
		return -1;
	}
	// 2.对lcd进行内存映射
	lcd_map = mmap(NULL, 
				800*480*4, 
				PROT_READ|PROT_WRITE, 
				MAP_SHARED, 
				lcd_fd, 
				0);
	if(MAP_FAILED == lcd_map)
	{
		perror("mmap failed!\n");
		return -1;
	}
}

// 显示图片
int show_bmp(char *bmp_path, int x0, int y0)
{
	// 2.打开图片
	int bmp_fd = open(bmp_path, O_RDWR);
	if(-1 == bmp_fd)
	{
		perror("open lcd failed!\n");
		return -1;
	}
	// 获取头信息
	char head[54] = {0};
	read(bmp_fd, head, 54);
	int w = *((int *)&head[18]);
	int h = *((int *)&head[22]);
	// printf("(%d, %d)\n", w, h);
	// 处理Windows补齐的垃圾字节
	int n_add; // 需要补齐的字节数
	int add_a; // 补齐后的字节数
	n_add = (4-w*3%4)%4;
	add_a = w*3+n_add;
	char bmp_add[add_a*h]; // 包括了垃圾值的图片信息
	// 偏移去掉头信息
	lseek(bmp_fd, 54, SEEK_SET);
	// 3.读取图片像素数据
	read(bmp_fd, bmp_add, sizeof(bmp_add));

	char bmp_buf[w*h*3];
	for(int j=0; j<h; j++)
		memcpy(&bmp_buf[w*3*j], &bmp_add[add_a*j], w*3);

	// 4.23位转32位
	int buf_32[w*h];
	for(int i=0; i<w*h; i++)
						//b			g				r				a
		buf_32[i] = bmp_buf[0+i*3]<<0 | bmp_buf[1+i*3]<<8 | bmp_buf[2+i*3]<<16 | 0x00<<24;
	
	// 将图片翻转，写入LCD内存映射
	int x,y;
	for(y=0; y<h; y++)
		for(x=0; x<w; x++)
			lcd_map[800*(y+y0)+x+x0] = buf_32[w*(h-1-y)+x];

	close(bmp_fd);
}

int main(int argc, char *argv[])
{
	lcd_open();
	// 清屏
	int x,y;
	for(y=0; y<480; y++)
		for(x=0; x<800; x++)
			lcd_map[800*y+x] = 0x000000;
	int i=50;
	while(1)
	{
		show_bmp("jd.bmp", i++, 400);
		sleep(0.5);
		if(i>750)
			break;
	}
	

	munmap(lcd_map, 800*480*4);
	close(lcd_fd);
	return 0;
}
