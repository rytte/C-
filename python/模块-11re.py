('''********************'''re 模块'''************************************************************'''
re 模块使 Python 语言拥有全部的正则表达式功能。
由于正则表达式通常都包含反斜杠，所以你最好使用原始字符串来表示它们，即字符串前加上 r 使转义字符不生效。
compile 函数根据一个模式字符串和可选的标志参数生成一个正则表达式对象。该对象拥有一系列方法用于正则表达式匹配和替换。

import re


'''************************************************************'''
# re.match 函数
re.match 函数会从字符串的起始位置匹配，如果不是起始位置匹配成功的话，match()就返回 None。

re.match(pattern, string, flags=0)  
#pattern：正则表达式    string：要匹配的字符串    flags：标志位，用于控制正则表达式的匹配方式，如：是否区分大小写，多行匹配等等。

匹配成功re.match方法返回一个匹配的对象，否则返回None。

实例：
re.match('www', 'www.runoob.com').span()        # 在起始位置匹配，span()方法会返回匹配内容在字符串中的起始位置和结束位置。
(0, 3)
re.match('com', 'www.runoob.com')               # 不在起始位置匹配
None


match 和 search 方法在字符串中成功匹配到内容之后，会返回一个匹配对象，没匹配到就返回 None。

返回的匹配对象的方法，可以获取匹配表达式。
group(num=0)	    返回正则中组号匹配的字符串，group() 可以一次输入多个组号，返回一个包含那些组所对应值的元组。默认返回全部分组内容。
groups()	        返回一个包含所有分组匹配的字符串的元组，从 1 到 所含的分组号。

实例：
line = "Cats are smarter than dogs"
Obj = re.match( r'(.*) are (.*?) .*', line, re.M|re.I)
if Obj:
   print ("Obj.group() : ", Obj.group())
   print ("Obj.group(1) : ", Obj.group(1))
   print ("Obj.group(2) : ", Obj.group(2))
else:
   print ("No match!!")

执行结果如下：
Obj.group() :  Cats are smarter than dogs
Obj.group(1) :  Cats
Obj.group(2) :  smarter


'''************************************************************'''
# re.search 函数
re.search 函数扫描整个字符串并返回第一个成功的匹配。

re.search(pattern, string, flags=0) 
#pattern：正则表达式    string：要匹配的字符串    flags：标志位，用于控制正则表达式的匹配方式，如：是否区分大小写，多行匹配等等。

实例：
>>> re.search('www', 'www.runoob.com').span()           # 在起始位置匹配
(0, 3)
>>> re.search('com', 'www.runoob.com').span()           # 不在起始位置匹配
(11, 14)

re.match 只匹配字符串的开始，如果字符串开始不符合正则表达式，则匹配失败，函数返回 None，而 re.search 匹配整个字符串，直到找到一个匹配。


'''************************************************************'''
# re.sub 函数
re.sub 函数用于替换字符串中的匹配项，返回替换后的整个字符串对象。

re.sub(pattern, repl, string, count=0, flags=0)

参数：
pattern : 正则表达式。
repl :    替换的字符串，也可为一个函数。
string :  被查找替换的原始字符串。
count :   模式匹配后替换的最大次数，默认 0 表示替换所有的匹配。
flags :   编译时用的匹配模式，数字形式。

实例：                         
phone = "2004-959-559 # 这是一个电话号码"
# 删除注释
num = re.sub(r'#.*$', "", phone)
print ("电话号码 : ", num)
# 移除非数字的内容
num = re.sub(r'\D', "", phone)
print ("电话号码 : ", num)


'''************************************************************'''
# re.findall 函数
re.findall 函数在字符串中找到正则表达式匹配的所有内容，并返回一个列表。如果有多个匹配模式，则返回元组列表，如果没有找到匹配的，则返回空列表。

re.findall(pattern, string, flags=0)

实例：
>>> result = re.findall(r'(\w+)=(\d+)', 'set width=20 and height=10')
>>> result
[('width', '20'), ('height', '10')]


'''************************************************************'''
# re.finditer 函数
re.finditer 函数在字符串中找到正则表达式所匹配的所有子串，并把它们作为一个迭代器返回。

re.finditer(pattern, string, flags=0)

实例：
>>> it = re.finditer(r"\d+","12a32bc43jf3") 
>>>for match in it: 
...    print (match.group() )
...
12 
32 
43 
3


'''************************************************************'''
# re.split 函数
re.split 方法按照能够匹配的子串将字符串分割，返回一个列表。

re.split(pattern, string, maxsplit=0, flags=0)      #参数maxsplit：分割次数，默认无限次。

实例：
>>> re.split('\W+', 'runoob, runoob, runoob.')      #以非单词字符分割，即这里的","
['runoob', 'runoob', 'runoob', '']
>>> re.split('(\W+)', ' runoob, runoob, runoob.')   #加括号表示将用于分割的字符也一起返回
['', ' ', 'runoob', ', ', 'runoob', ', ', 'runoob', '.', '']
>>> re.split('\W+', ' runoob, runoob, runoob.', 1)  #分割一次
['', 'runoob, runoob, runoob.']
 
>>> re.split('a*', 'hello world')                   # 对于一个找不到匹配的字符串而言，split 不会对其作出分割
['hello world']


'''************************************************************'''
# compile 函数
compile 函数返回一个正则表达式（pattern）对象，供 match() 和 search() 这两个函数使用。

re.compile(pattern[, flags])

参数：
pattern : 一个字符串形式的正则表达式
flags :   可选，表示匹配模式，比如忽略大小写，多行模式等，具体参数如下：
    re.I  忽略大小写
    re.L  表示特殊字符集 \w, \W, \b, \B, \s, \S 依赖于当前环境
    re.M  多行模式
    re.S  即为' . '并且包括换行符在内的任意字符（' . '不包括换行符）
    re.U  表示特殊字符集 \w, \W, \b, \B, \d, \D, \s, \S 依赖于 Unicode 字符属性数据库
    re.X  为了增加可读性，忽略空格和' # '后面的注释


compile 函数返回的正则表达式对象的方法
pattern.match(string, start=0, end=0)   返回匹配内容对象    #string：匹配的字符串   start：匹配开始位置    end：匹配结束位置，默认为字符串尾部
pattern.search(string, start=0, end=0)  返回匹配内容对象

pattern.findall(string, start=0, end=0)   全文匹配，将所有匹配结果放到一个list中返回（用于内容少的字符串）
pattern.finditer(string, start=0, end=0)  全文匹配，将所有匹配结果放到一个迭代器中返回（用于内容多的字符串）
pattern.sub(repl, content, count=0)    返回替换后的对象     #repl：替换的字符串，可以是函数  content：要替换的内容  count：替换次数，默认全部替换


实例：
>>> pattern = re.compile(r'\d+')                    # 用于匹配至少一个数字
>>> m = pattern.match('one12twothree34four')        # 查找头部，没有匹配
>>> print( m )
None
>>> m = pattern.match('one12twothree34four', 3, 10) # 从'1'的位置开始匹配，正好匹配
>>> print( m )                                      # 返回一个 Match 对象
<_sre.SRE_Match object at 0x10a42aac0>
>>> m.group()
'12'
>>> m.start()
3
>>> m.end()
5
>>> m.span()
(3, 5)


