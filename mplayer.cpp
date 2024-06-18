/********************/mplayer/************************************************************/
//格式
mplayer - slave - quiet - zoom - x 800 - y 480 - wid + 窗口ID  1.avi

- slave  : 利用从模式打开mplayer 播放器（只有在从模式下，才可以接受用户的命令）
- quiet  ：去除杂项信息
- zoom - x 800 - y 480   指定播放窗体的大小
- wid : 指定播放的窗口ID
- input file = / pipe  设置通信管道（命令的输入端）
- geometry  0 : 0     播放的起点坐标

//slave模式
mplayer默认是从键盘上获得控制信息
在slave模式下，MPlayer为后台运行的程序，不再截获键盘事件，MPlayer会从标准输入读一个换行符（\n）分隔开的命令。
#mplayer - input cmdlist		// 会打印出一份当前mplayer所支持的所有slave模式的命令

//常用Mplayer命令
loadfile string		//参数string 为 歌曲名字。 
volume 100 1		//设置音量 中间的为音量的大小。
mute  1 / 0			//静音开关
pause				//暂停/取消暂停
get_time_length		//返回值是播放文件的长度，以秒为单位。
seek value			//向前查找到文件的位置播放 参数value为秒数。
get_percent_pos		//返回文件的百分比（0--100）
get_time_pos		//打印出在文件的当前位置用秒表示，采用浮点数
volume[abs]			//增大/减小音量，或将其设置为，如果[abs]不为零
quit[value]			//退出MPlayer。可选的整数[value]的值作为返回代码。为mplayer的进程（默认值：0）。

get_file_name		//打印出当前文件名
get_meta_album		//打印出当前文件的'专辑'的元数据
get_meta_artist		//打印出当前文件的'艺术家'的元数据
get_meta_comment	//打印出当前文件的'评论'的元数据
get_meta_genre		//打印出当前文件的'流派'的元数据
get_meta_title		//打印出当前文件的'标题'的元数据
get_meta_year		//打印出当前文件的'年份'的元数据


//成员函数
get_time_length()  		//返回值是播放文件的长度，以秒为单位。
seek value()   			//向前查找到文件的位置播放 参数value为秒数。
get_percent_pos()		//返回文件的百分比（0--100）
get_time_pos() 			//打印出在文件的当前位置用秒表示，采用浮点数
volume <value>[abs] 	//增大 / 减小音量，或将其设置为<value>，如果[abs]不为零
例 : volume 100 1  	设置音量为100 中间的为音量的大小。



//开发板使用mplayer
1.复制mplayer到开发板bin目录下并设置权限777
2.复制视频dream.avi到开发板程序
3.播放视频 mplayer dream.avi

//控制命令
1.创建管道
mkfifo pipe （如果创建失败，删除旧的管道（rm pipe），重新创建mkfifo pipe）
chmod 777 pipe
2.后台播放视频
mplayer - slave - quiet - input  file = / pipe - geometry  0:0 - zoom - x 800 - y 480  dream.avi &
3.往管道里面填写控制命令
按回车回到命令行
echo pause >> pipe   //暂停 继续
echo volume - 10 >> pipe //音量-10
echo volume + 10 >> pipe //音量+10
echo seek + 5 > pipe //快进5	 
echo seek - 5 > pipe //快退5
killall - kill mplayer   关闭播放器
4.代码操作
system("mplayer -slave -quiet -input  file=pipe  -geometry  0:0 -zoom -x 800 -y 480  dream.avi &  ");
system("echo pause >>  pipe");
system("mplayer -slave -quiet -input  file=pipe 1.mp3 &  ");//播放音乐	 

