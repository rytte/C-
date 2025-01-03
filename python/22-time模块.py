('''********************'''time 模块'''************************************************************'''

Python 提供了一个 time 和 calendar 模块可以用于格式化日期和时间。

时间间隔是以秒为单位的浮点小数。
每个时间戳都以自从 1970 年 1 月 1 日午夜（历元）经过了多长时间来表示。

import time


#获取当前的时间戳
time()方法       

ticks = time.time()
ticks
1688196786.4401593          


#struct_time
时间元组struct_time是一个由9组数字构成的元组，用于表示时间。它具有以下属性：
序号	 属性	      值
0	     tm_year	  2008
1	     tm_mon	      1 到 12
2	     tm_mday	  1 到 31
3	     tm_hour	  0 到 23
4	     tm_min	      0 到 59
5	     tm_sec	      0 到 61 (60或61 是闰秒)
6	     tm_wday	  0 到 6 (0是周一)
7	     tm_yday	  一年中的第几天，1 到 366
8	     tm_isdst     是否为夏令时，值有：1(夏令时)、0(不是夏令时)、-1(未知)，默认 -1


#获取当前的时间
localtime(secs=time.time()) 方法可以将时间戳转换为struct_time元组表示的本地时间

localtime = time.localtime(time.time())
localtime
time.struct_time(tm_year=2023, tm_mon=7, tm_mday=1, tm_hour=15, tm_min=45, tm_sec=21, tm_wday=5, tm_yday=182, tm_isdst=0)


#获取格式化的当前时间
asctime(struct_time=localtime()) 方法可以将struct_time元组表示的时间格式化为易读的时间。
localtime = time.asctime( time.localtime(time.time()) )
localtime
'Sat Jul  1 15:51:00 2023'


#格式化日期
strftime(format[, t]) 方法可以将struct_time元组表示的时间进行自定义格式化。

time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
'2023-07-01 15:54:37'
time.strftime("%a %b %d %H:%M:%S %Y", time.localtime())
'Sat Jul 01 15:55:22 2023'


#将格式化时间转化为时间戳
mktime(tupletime) 方法配合 strptime(str, format='%a %b %d %H:%M:%S %Y') 方法将格式化的时间转化为时间戳

time.mktime(time.strptime('Sat Jul 01 15:55:22 2023',"%a %b %d %H:%M:%S %Y"))
1688198122.0


#日期格式化符号
%y   两位数的年份表示（00-99）
%Y   四位数的年份表示（000-9999）
%m   月份（01-12）
%d   月内中的一天（0-31）
%H   24小时制小时数（0-23）
%I   12小时制小时数（01-12）
%M   分钟数（00=59）
%S   秒（00-59）

%a   本地简化星期名称
%A   本地完整星期名称
%b   本地简化的月份名称
%B   本地完整的月份名称
%c   本地相应的日期表示和时间表示
%j   年内的一天（001-366）
%p   本地A.M.或P.M.的等价符
%U   一年中的星期数（00-53）星期天为星期的开始
%w   星期（0-6），星期天为星期的开始
%W   一年中的星期数（00-53）星期一为星期的开始
%x   本地相应的日期表示
%X   本地相应的时间表示
%Z   当前时区的名称
%%   %号本身


#其它方法
1       time.perf_counter()  # 返回系统运行时间。由于返回值的基准点是未定义的，所以，只有连续调用的结果之间的差才是有效的。
2       time.process_time()  # 返回进程运行时间。由于返回值的基准点是未定义的，所以，只有连续调用的结果之间的差才是有效的。
3       time.altzone num     # 返回格林威治西部的夏令时地区的偏移秒数。若该地区在格林威治东部会返回负值（如西欧，包括英国）。
time.altzone -28800 
-61200
4       time.ctime([secs])   # 作用于asctime()方法相同
5	    time.gmtime([secs])  # 接收时间戳并返回格林威治天文时间下的时间元组t。注：t.tm_isdst始终为0	
6	    time.sleep(secs)     # 推迟调用线程的运行，secs指秒数。	
7	    time.strptime(str,fmt='%a %b %d %H:%M:%S %Y') # 根据fmt的格式把一个时间字符串解析为时间元组。	
8	    time.tzset()         # 根据环境变量TZ重新初始化时间相关设置。
	 
Time模块包含了以下2个非常重要的属性：

time.timezone     属性time.timezone是当地时区（未启动夏令时）距离格林威治的偏移秒数（>0，美洲;<=0大部分欧洲，亚洲，非洲）。
time.tzname       属性time.tzname包含一对根据情况的不同而不同的字符串，分别是带夏令时的本地时区名称，和不带的。



