#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/input.h>

int tx, ty;

char bmp[4][20] =
{
	"1.bmp",
	"2.bmp",
	"3.bmp",
	"4.bmp"
};

//触摸屏滑动操作
int get_xy()
{
	int x, y;
	int x0, y0;
	int x1, y1;
	int tx_flag = 0;
	int ty_flag = 0;

	//打开触摸屏驱动
	int ts_fd = open("/dev/input/event0", O_RDWR);
	if (ts_fd == -1)
	{
		perror("open failed");
		return -1;
	}

	//创建输入子系统结构体，用来保存读取的触摸屏事件
	struct input_event ts;

	//检测有无触摸事件产生
	while (1)
	{
		//如果产生了触摸动作，就把触摸数据读取到子系统
		read(ts_fd, &ts, sizeof(ts));

		//获取坐标
		if (ts.type == EV_ABS)
		{
			if (ts.code == ABS_X)
			{
				x = ts.value * 800 / 1024;
				if (tx_flag == 0)
				{
					x0 = x;
					tx_flag = 1;
				}
			}
			if (ts.code == ABS_Y)
			{
				y = ts.value * 480 / 614;
				if (ty_flag == 0)
				{
					y0 = y;
					ty_flag = 1;
				}
			}
		}

		//判断手指是否离开了屏幕，按键事件来判断
		if (ts.type == EV_KEY && ts.code == BTN_TOUCH)
		{
			x1 = x;
			tx = x;

			y1 = y;
			ty = y;
			break;
		}
	}

	int x_offset = x1 - x0;
	int y_offset = y1 - y0;

	printf("初始坐标(%d,%d)\n", x0, y0);
	printf("结束坐标(%d,%d)\n", x1, y1);
	printf("x偏移量为 %d\n", x_offset);
	printf("y偏移量为 %d\n", y_offset);


	/* 	if(tx>700&&tx<800&&ty>80&&ty<100)
		{
			printf("进入主界面\n");
			return 1;
		}

		if(ty>0&&ty<80)
		{
			if(tx>0&&tx<200)
			{
				printf("进入锁屏界面\n");
				return 2;
			}
			if(tx>600&&tx<800)
			{
				printf("退出程序\n");
				return 3;
			}
		}

		if(ty>100&&ty<300)
		{
			if(tx>100&&tx<200)
			{
				printf("进入相册界面\n");
				return 4;
			}
			if(tx>350&&tx<450)
			{
				printf("进入音乐界面\n");
				return 5;
			}
			if(tx>600&&tx<700)
			{
				printf("进入视频界面\n");
				return 6;
			}
		} */

		// abs 函数获取绝对值
	if (x_offset > 50 && (abs(x_offset) > abs(y_offset)))
	{
		printf("右滑\n");
		return 1;
	}

	if (y_offset > 50 && (abs(x_offset) < abs(y_offset)))
	{
		printf("下滑\n");
		return 2;
	}

	if (x_offset < 50 && (abs(x_offset) > abs(y_offset)))
	{
		printf("左滑\n");
		return 3;
	}

	if (y_offset < 50 && (abs(x_offset) < abs(y_offset)))
	{
		printf("上滑\n");
		return 4;
	}

	//关闭驱动
	close(ts_fd);

}

//在lcd的任意范围显示任意大小的bmp图片(lcd范围内)
int showbmp(char* filename, int w, int h, int x0, int y0)
{
	//打开lcd驱动
	int lcd_fd = open("/dev/fb0", O_RDWR);
	if (lcd_fd == -1)
	{
		perror("open failed");
		return -1;
	}

	//申请好虚拟内存
	unsigned char* lcd = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
	if (lcd == NULL)
	{
		perror("mmap failed");
		return -1;
	}

	//打开bmp图片
	int bmp_fd = open(filename, O_RDWR);
	if (bmp_fd == -1)
	{
		perror("open bmp failed");
		return -1;
	}

	//读取bmp的24位颜色数据
	unsigned char bmp[w * h * 3];
	read(bmp_fd, bmp, 54);
	read(bmp_fd, bmp, w * h * 3);

	//把24位数据转换为32位数据，同时丢到虚拟内存里
	int x, y;
	for (y = y0; y < h + y0; y++)
	{
		for (x = x0; x < w + x0; x++)
		{
			//第y行第x个像素点
			lcd[0 + 4 * x + 800 * 4 * y] = bmp[0 + (x - x0) * 3 + w * 3 * (h - 1 - (y - y0))];//B
			lcd[1 + 4 * x + 800 * 4 * y] = bmp[1 + (x - x0) * 3 + w * 3 * (h - 1 - (y - y0))];//G
			lcd[2 + 4 * x + 800 * 4 * y] = bmp[2 + (x - x0) * 3 + w * 3 * (h - 1 - (y - y0))];//R
			lcd[3 + 4 * x + 800 * 4 * y] = 0;                                //A
		}
	}

	//关闭相应的文件
	close(lcd_fd);
	close(bmp_fd);
	munmap(lcd, 800 * 480 * 4);

}

//播放MV
int vedio()
{
	system("mplayer -slave -quiet -input  file=/pipe  -geometry  0:0 -zoom -x 800 -y 480  dream.avi &");
	sleep(10);

	system("killall -kill mplayer");

}

//播放音乐
int music()
{
	//显示音乐界面
	showbmp("music.bmp", , , , );
	system("mplayer -slave -quiet -input  file=/pipe jay.mp3 &  ");
	sleep(10);

	system("killall -kill mplayer");

}
//相册功能
int photo()
{
	int i = 0, j = 3;

	showbmp(bmp[i], 800, 480, 0, 0);
	while (1)
	{
		ret = get_xy();

		if (ret == 1)
		{
			showbmp(bmp[j], 800, 480, 0, 0);
			j--;
			if (j < 0)
			{
				j = 3;
			}
		}
		if (ret == 3)
		{
			i++;
			if (i > 3)
			{
				i = 0;
			}
			showbmp(bmp[i], 800, 480, 0, 0);
		}
		if (ret == 2 || ret == 4)//返回
		{
			break;
		}
	}

}
//开始界面
int start()
{
	showbmp("start.bmp", 800, 480, 0, 0);
	while (1)
	{
		get_xy();
		if (tx > 0 && tx < 0 && ty>0 && ty < 0)
		{
			break;
		}
	}


}
int main()
{
	int ret = 0;

	while (1)
	{
		start();
		while (1)
		{
			showbmp("main.bmp", 800, 480, 0, 0);
			ret = get_xy();
			if (ty > 0 && ty < 0 && tx>0 && tx < 0)
			{
				photo();
				tx = 0;
				ty = 0;
				ret = 0;
			}
			if (ty > 100 && ty < 300 && tx>350 && tx < 450)
			{
				music();
				tx = 0;
				ty = 0;
				ret = 0;
			}

			if (ty > 100 && ty < 300 && tx>600 && tx < 700)
			{
				vedio();
				tx = 0;
				ty = 0;
				ret = 0;
			}
			if ()//锁屏
			{

				break;
			}
			if ()//退出
			{
				showbmp("byebye.bmp", , , , );
				return 0;
			}
		}
	}
}

return 0;
}