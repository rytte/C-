#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

//1.打开lcd					失败返回-1
//2.对lcd申请内存映射		失败返回-1
//3.打开图片文件			失败返回-1
//4.定义数组存放头信息数据
//5.定义变量获取图片长和宽
//6.移除头信息
//7.定义数组存放图片位图信息
//8.24位图片转换为32位	
//9.数据翻转地写入映射内存
//10.关闭图片和lcd

int main(int argc, char* argv[])
{
	int lcd_fd = open("/dev/fb0", O_RDWR);	//1.打开lcd			失败返回-1
	if (-1 == lcd_fd)
	{
		perror("open lcd failed\n");
		return -1;
	}

	int* lcd_map = mmap(NULL,				//2.对lcd申请内存映射	失败返回-1
		800 * 480 * 4,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		lcd_fd,
		0);
	if (lcd_map == MAP_FAILED)
	{
		perror("mmap failed\n");
		close(lcd_fd);
		return -1;
	}

	int bmp_fd = open(argv[1], O_RDWR);		//3.打开图片文件	失败返回-1
	if (-1 == bmp_fd)
	{
		perror("open bmp failed\n");
		close(lcd_fd);
		return -1;
	}

	char head[54];							//4.定义数组存放头信息数据
	read(bmp_fd, head, 54);
	int w = *((int*)&head[18]);				//5.定义变量获取图片长和宽
	int h = *((int*)&head[22]);
	printf("w=%d\nh=%d\n", w, h);

	lseek(bmp_fd, 54, SEEK_SET);			//6.移除头信息
	char bmp_buf[w * h * 3];				//7.定义数组存放图片位图信息
	read(bmp_fd, bmp_buf, w * h * 3);

	int lcd_32[800 * 480];					//8.24位图片数据转换为32位	
	for (int i = 0; i < w * h; i++)
		lcd_32[i] = bmp_buf[0 + i * 3] << 0 | bmp_buf[1 + i * 3] << 8 | bmp_buf[2 + i * 3] << 16 | 0x00 << 24;
	//b						g							r						a

	for (int y = 0; y < h; y++)				//9.数据翻转地写入映射内存
		for (int x = 0; x < w; x++)
			lcd_map[800 * y + x] = lcd_32[w * (h - 1 - y) + x];

	close(bmp_fd);							//10.关闭图片和lcd
	close(lcd_fd);

	return 0;
}






//int add;	//每行需要补齐的字节数		//6.处理window补齐的无效字节
//int add_w;	//补齐后的宽度
//add = (4 - w * 3 % 4) % 4;
//add_w = w * 3 + add;

//char bmp_add[add_w * h];				//7.定义包含无效字节的图片数据数组
//lseek(bmp_fd, 54, SEEK_SET);			//8.移除头信息
//read(bmp_fd, bmp_add, sizeof(bmp_add));	//9.读取图片像素数据

//for (int j = 0; j < h; j++)
//	memcpy(&bmp_buf[w * 3 * j], &bmp_add[add_w * j], w * 3);


