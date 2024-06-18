#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

//fb0设备显示参数

int main(int argc, char *argv[])
{
	int fd = open("/dev/fb0", O_RDWR);
	if(-1 == fd)
	{
		perror("open failed!\n");
		return -1;
	}
	// fb固定参数获取
	struct fb_fix_screeninfo fix;
	ioctl(fd, FBIOGET_FSCREENINFO, &fix);
	printf("帧缓冲的长度为：%d\n", fix.smem_len);
	printf("一行的字节总数为：%d\n", fix.line_length);
	// fb可变参数获取
	struct fb_var_screeninfo var;
	ioctl(fd, FBIOGET_VSCREENINFO, &var);
	printf("横向分辨率：%d\n", var.xres);
	printf("纵向分辨率：%d\n", var.yres);
	printf("像素位数：%d\n", var.bits_per_pixel);
	printf("红色：%d\n", var.red.length);
	printf("蓝色偏移量：%d\n", var.blue.offset);

	return 0;
}
