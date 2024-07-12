/********************/目录IO/************************************************************/

//opendir()打开目录函数
#include <sys/types.h>
#include <dirent.h>

DIR * opendir(const char* name);	//打开目录并返回目录文件的指针，失败返回NULL

参数：需要打开目录的路径


//readdir()读取目录函数
#include <dirent.h>

struct dirent* readdir(DIR * dirp);		//读取目录并返回包含目录信息的目录结构体指针，失败返回NULL

参数：要读取的目录的目录文件流指针
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
#include <sys/types.h>
#include <dirent.h>

int closedir(DIR * dirp);		//成功返回0，失败返回-1

参数：需要关闭的目录流指针


//mkdir()创建目录函数
#include <sys/stat.h>

int mkdir(const char* path, mode_t mode);		//成功返回0，失败返回-1

参数1：目录文件路径
参数2：目录文件创建权限，如0777



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

