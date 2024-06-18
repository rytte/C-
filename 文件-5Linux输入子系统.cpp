/********************/系统IO与标准IO/************************************************************/
//内存映射
【头文件】
#include <sys/mman.h>
【函数原型】
void* mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void* addr, size_t length);
【参数】
void* addr		//内存映射的起始地址，如果为NULL，内核自动选择
size_t length	//内存映射的空间大小（字节）
int prot		// 内存映射的空间的权限 （读写）
int flags		// 一般选择分享这块内存
int fd			// 要对哪一个文件进行内存映射
off_t offset	// 偏移量，决定每一次写入的位置，
【返回值】
成功： 申请到内存的指针
失败： NULL


//Linux输入子系统
触摸屏操作：电阻屏 电容屏
输入事件：外接设备（键盘，鼠标，触摸屏）对系统的操作，当接入的第三方平台发生输入改变的时候，称为事件的发生

什么是输入子系统？
操作系统的输入设备，将Linux系统中所有往系统中输入信号的设备统称为输入子系统

触摸屏驱动： / dev / input / event0；（开发板）
查看输入子系统的头文件： / usr / include / linux / input.h(ubuntu)

输入子系统中会分析事件的类型、编码、值
struct input_event 
{
	struct timeval time;	// 事件发生的时间
	__u16 type;				// 事件类型  // 用来分辨输入子系统中哪一个设备产生了动作
	__u16 code;				// 事件编码  // 用来分辨设备中，哪一个部位产生了动作
	__s32 value;			// 事件的值  // 记录产生动作的部位的数据值
};

type类型：
#define EV_SYS 0x00 事件结束
#define EV_KEY 0x01 用于描述键盘，按键或者类似的设备
#define EV_REL 0x02 用于描述相对位移，鼠标，滚轮
#define EV_ABS 0x03 用于描述绝对位移，触摸屏的坐标


