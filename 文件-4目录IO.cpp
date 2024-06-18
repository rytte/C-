

//opendir()打开目录函数
【头文件】
#include <sys/types.h>
#include <dirent.h>
【函数原型】
DIR * opendir(const char* name);
【参数】
const char* name 需要打开目录的位置
【返回值】
成功：返回指向目录文件的流指针，指向目录
失败： NULL


//readdir()读取目录函数
【头文件】
#include <dirent.h>
【函数原型】
struct dirent* readdir(DIR * dirp);
【参数】
DIR* dirp  要读取的目录对应的目录文件流指针
【返回值】
成功： 返回目录结构体指针
失败： NULL
struct dirent 
{
    ino_t          d_ino;       /* 节点编号*/
    off_t          d_off;       /* 偏移到下一个节点*/
    unsigned short d_reclen;    /* 目录的长度*/
    unsigned char  d_type;      /* 文件类型 */
    char           d_name[256]; /* 文件名 */
};
d_type：文件类型
{
    DT_BLK    	  块设备文件
    DT_CHR    	  字符设备.
    DT_DIR     	  目录文件
    DT_FIFO    	  管道文件
    DT_LNK       链接文件
    DT_REG       普通文件
    DT_SOCK      网络文件
    DT_UNKNOWN 未知类型
}


//closedir()关闭目录函数
【头文件】
#include <sys/types.h>
#include <dirent.h>
【函数原型】
int closedir(DIR * dirp);
【参数】
DIR* dirp 需要关闭的目录流指针
【返回值】
成功：0
失败：-1


//mkdir()创建目录函数
【头文件】
#include <sys/stat.h>
【函数原型】
int mkdir(const char* path, mode_t mode);
【参数】
const char* path    目录文件的目录名
mode_t mode         目录文件创建权限 0777
【返回值】
成功：0
失败：-1



/********************/实例：打印目录树/************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

// 递归查询目录
int my_tree(char* pathname)
{
	// 定义数组保存路径
	char path[1024] = { 0 };
	// 定义目录结构体指针
	struct dirent* my_dirent;
	// 定义记录目录层数
	static int flag = 0, i;

	// 1.开打目录
	DIR* my_dir = opendir(pathname);
	if (NULL == my_dir)
	{
		perror("open error!\n");
		return -1;
	}
	// 2.循环读取
	while ((my_dirent = readdir(my_dir)) != NULL)
	{
		// 1.剔除隐藏文件
		if (my_dirent->d_name[0] == '.')
			continue;

		// 2.如果是目录文件，继续读取
		if (my_dirent->d_type == DT_DIR) // 目录文件
		{
			// 打印空格
			for (i = 0; i < flag; i++)
				printf("   ");
			// printf("flag: %d\n", flag);
			printf("|__");
			sprintf(path, "%s/%s", pathname, my_dirent->d_name);
			// printf("当前文件路径为：%s\n", pathname);
			// 打印目录
			printf("%s\n", my_dirent->d_name);
			// 目录的层数
			flag++;
			// 遇到子目录，调用自身，读取下一级目录
			my_tree(path);
			flag--;
		}
		else // 普通文件 直接打印
		{
			// 打印空格
			for (i = 0; i < flag; i++)
				printf("   ");
			// 打印文件名
			printf("|__");
			printf(" %s\n", my_dirent->d_name);
		}
	}
	closedir(my_dir);
}

int main(int argc, char* argv[])
{
	printf("%s\n", argv[1]);
	my_tree(argv[1]);

	return 0;
}

