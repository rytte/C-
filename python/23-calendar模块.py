('''********************'''calendar 模块'''************************************************************'''
Calendar 模块有很广泛的方法用来处理年历和月历。星期一是默认的每周第一天，星期天是默认的最后一天。

import calendar

#打印某月的日历
month(year, month, w=2, l=1) 方法返回一个多行字符串格式的year年month月日历，两行标题，一周一行。
                            每日宽度间隔为w字符。每行的长度为7*w+6。l是每星期的行数。

>>> print(calendar.month(2023, 7))          #使用print函数才会转义\n进行换行
     July 2023
Mo Tu We Th Fr Sa Su
                1  2
 3  4  5  6  7  8  9
10 11 12 13 14 15 16
17 18 19 20 21 22 23
24 25 26 27 28 29 30
31


#其它方法
序号	函数及描述
1	calendar.calendar(year,w=2,l=1,c=6)
    #返回一个多行字符串格式的 year 年年历，3 个月一行，间隔距离为 c。 每日宽度间隔为w字符。每行长度为 21* W+18+2* C。l 是每星期行数。

2	calendar.firstweekday( )
    #返回当前每周起始日期的设置。默认情况下，首次载入 calendar 模块时返回 0，即星期一。

3	calendar.isleap(year)
    #是闰年返回 True，否则为 False。

4	calendar.leapdays(y1,y2)
    #返回在Y1，Y2两年之间的闰年总数。

5	calendar.monthcalendar(year,month)
    #返回一个整数的单层嵌套列表。每个子列表装载代表一个星期的整数。Year年month月外的日期都设为0;范围内的日子都由该月第几日表示，从1开始。

6	calendar.monthrange(year,month)
    #返回两个整数。第一个是该月的星期几，第二个是该月有几天。星期几是从0（星期一）到 6（星期日）。

7	calendar.prcal(year, w=0, l=0, c=6, m=3)
    #相当于 print (calendar.calendar(year, w=0, l=0, c=6, m=3))。

8	calendar.prmonth(theyear, themonth, w=0, l=0)
    #相当于 print(calendar.month(theyear, themonth, w=0, l=0))。

9	calendar.setfirstweekday(weekday)
    #设置每周的起始日期码。0（星期一）到6（星期日）。

10	calendar.timegm(tupletime)
    #和time.gmtime相反：接受一个时间元组形式，返回该时刻的时间戳（1970纪元后经过的浮点秒数）。

11	calendar.weekday(year,month,day)
    #返回给定日期的日期码。0（星期一）到6（星期日）。月份为 1（一月） 到 12（12月）。


