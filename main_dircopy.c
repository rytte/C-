#include "pthread_pool.h"


char path_src[500];	//源目录文件的路径
char path_dst[500];	//目标目录的文件路径

int Num;			//记录文件数量


int main(int argc, char const* argv[])
{
	thread_pool tmp;
	thread_pool* pool = &tmp;
	Pthread_Pool_Init(pool, 2);


	if (opendir("/home/gec/dst/") == NULL)				//目标目录不存在则创建
		mkdir("/home/gec/dst/", 0777);


	path(pool, "/home/gec/src/", "/home/gec/dst/");		//获取路径并复制

	printf("\n");

	sleep(1);

	Destroy_Pool(pool);

	return 0;
}



//用户自定义任务					将src（"/home/gec/src"）目录拷贝到dst（"/home/gec/dest"）中
void* mytask(void* arg)
{
	char buf[1024] = { '\0' };							//数据缓冲区

	int fd_r = open(path_src, O_RDWR);		//打开源文件,读取
	if (fd_r == -1)
	{
		printf("打开源文件失败\n");
		return NULL;
	}
	read(fd_r, buf, sizeof(buf));


	int fd_w = open(path_dst, O_CREAT | O_RDWR, 0777);			//打开目标文件，写入
	if (fd_r == -1)
	{
		printf("打开目标文件失败\n");
		return NULL;
	}
	write(fd_w, buf, sizeof(buf));

	printf("%s 拷贝成功\n", path_dst);

	close(fd_r);
	close(fd_w);

	return NULL;
}


void path(thread_pool* pool, char* dir_path, char* dest)
{
	struct dirent* info;						//目录内文件的结构体 指针

	DIR* dd = opendir(dir_path);				//目录的描述符 指针


	while ((info = readdir(dd)) != NULL)		//添加任务到任务链表当中
	{
		memset(path_src, 0, sizeof(path_src));					//清空源文件地址
		memset(path_dst, 0, sizeof(path_dst));					//清空目标文件地址


		if (info->d_name[0] == '.')
			continue;

		if (info->d_type == DT_DIR)				//如果是个目录文件
		{
			char temp_src[500];							//临时复制源文件路径，是个子目录
			sprintf(temp_src, "%s%s/", dir_path, info->d_name);	
			char temp_dst[500];							//临时复制目标文件路径，是个子目录
			sprintf(temp_dst, "%s%s/", dest, info->d_name);

			if (access(temp_dst, F_OK))					//创建目标子目录
			{
				mkdir(temp_dst, 0777);
			}

			path(pool, temp_src, temp_dst);				//递归
			continue;
		}
						
		sprintf(path_src, "%s%s", dir_path, info->d_name);		//拼接路径					
		sprintf(path_dst, "%s%s", dest, info->d_name);			//拼接路径



		printf("源文件路径：%s	  目标文件路径：%s\n", path_src, path_dst);

		Add_Task(pool, mytask, NULL);							//已获取路径，添加拷贝任务

		Num++;

		if (Num > pool->active_threads && pool->active_threads < 20)					//增加线程
			Add_Pthread(pool, 1);

		usleep(200 * 1000);
	}

	closedir(dd);
}