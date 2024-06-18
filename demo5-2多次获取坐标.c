#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <string.h>

int ts_fd;
// 定义Linux输入子系统结构体变量
struct input_event ts_buf;

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
		}
		// 如果输入事件类型为触摸屏，并且具体事件描述为y
		if(ts_buf.type==EV_ABS && ts_buf.code==ABS_Y)
		{
			*y=ts_buf.value*480/600; // 获取了y的坐标值
		}
		// 松开后没有坐标，结束坐标读取,松开的时候获取坐标
		if(ts_buf.type==EV_KEY && ts_buf.code==BTN_TOUCH && ts_buf.value==0)
		{
			break;
		}

	}
}

int main(int argc, char *argv[])
{
	int x,y;
	ts_open();
	while(1)
	{
		printf("点击获取坐标：\n");
		get_xy(&x, &y);
		printf("(%d,%d)\n", x, y);
	}
	
	close(ts_fd); 
	// 3.关闭
	return 0;
}