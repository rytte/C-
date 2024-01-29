/********************/mplayer/************************************************************/
//格式
mplayer - slave - quiet - zoom - x 800 - y 480 - wid + 窗口ID  1.avi

- slave  :利用从模式打开mplayer 播放器    （只有在从模式下，才可以接受用户的命令）
- quiet  ：去除杂项信息
- zoom - x 800 - y 480   指定播放窗体的大小
- wid : 指定播放的窗口ID

//成员函数
get_time_length()  		//返回值是播放文件的长度，以秒为单位。
seek value()   			//向前查找到文件的位置播放 参数value为秒数。
get_percent_pos()		//返回文件的百分比（0--100）
get_time_pos() 			//打印出在文件的当前位置用秒表示，采用浮点数
volume <value>[abs] 	//增大 / 减小音量，或将其设置为<value>，如果[abs]不为零
例 : volume 100 1  	设置音量为100 中间的为音量的大小。
