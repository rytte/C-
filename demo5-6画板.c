#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <string.h>

int lcd_fd;
int *lcd_map;
int ts_fd;

// 定义Linux输入子系统结构体变量
struct input_event ts_buf;

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


// 打开触摸屏驱动
int ts_open(void)
{
	// 1.打开触摸屏驱动
	ts_fd = open("/dev/input/event0", O_RDWR);
	if(-1 == ts_fd)
	{
		perror("open ts failed!\n");
		return -1;
	}
}

// 获取坐标
int get_xy(int *x, int *y)
{
	int flag=0;
	// 2.读取数据
	while(1)
	{
		// 清空结构体数据
		memset(&ts_buf, 0, sizeof(ts_buf));
		// 将触摸屏中的数据读取，并放到输入子系统结构体变量中
		read(ts_fd, &ts_buf, sizeof(ts_buf));
		// 如果输入事件类型为触摸屏，并且具体事件描述为x
		if(ts_buf.type==EV_ABS && ts_buf.code==ABS_X)
		{
			*x=ts_buf.value*800/1024; // 获取了x的坐标值
			flag++;
		}
		// 如果输入事件类型为触摸屏，并且具体事件描述为y
		if(ts_buf.type==EV_ABS && ts_buf.code==ABS_Y)
		{
			*y=ts_buf.value*480/600; // 获取了y的坐标值
			flag++;
		}
		// 松开后没有坐标，结束坐标读取,松开的时候获取坐标
		if(flag == 2)
		{
			flag=0;
			printf("(%d,%d)\n", *x, *y);
			int a, b;
			for(b=(*y-5); b<(*y+5); b++)
				for(a=(*x-5); a<(*x+5); a++)
					lcd_map[800*b+a] = 0xFF0000;
		}

	}
}




int main(int argc, char *argv[])
{
	lcd_open();
	ts_open();
	// 清屏
	int x,y;
	
	while(1)
	{
		printf("画板：\n");
		for(y=0; y<480; y++)
				for(x=0; x<800; x++)
					lcd_map[800*y+x] = 0xFFFFFF;
		get_xy(&x, &y);

	}
	

	munmap(lcd_map, 800*480*4);
	close(lcd_fd);
	close(ts_fd);
	return 0;
}
