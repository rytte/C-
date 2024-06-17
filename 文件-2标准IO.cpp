//标准IO
fopen()
fread()
fwrite()
fclose()

//特殊成员
虚拟文件系统中的文件类型结构体
file
{
	__file_no[1024];
}

__file_no[0]	固定键盘输入 宏STDIN scanf
__file_no[1]	固定屏幕输出 宏STDOUT printf
__file_no[2]	固定屏幕输出 宏STDERR perror


SEEK_SET	文件的开头
SEEK_CUR	文件的当前位置
SEEK_END	文件的末尾
