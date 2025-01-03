

json模块提供了四个主要的函数：dump、dumps、load和loads。用于Json对象和Python对象之间的转换。



#dump函数
将对象序列化为JSON，并写入文件中。

import json  
data = {'name': 'ZhangSan', 'age': 30, 'city': 'ShenZhen'}  
with open('data.json', 'w') as f:  
    json.dump(data, f)



#dumps函数
将对象序列化为JSON字符串返回。

import json  
data = {'name': 'ZhangSan', 'age': 30, 'city': 'ShenZhen'}  
json_string = json.dumps(data, indent=4)  
print(json_string)



#load函数
从文件中读取JSON文件，并反序列化为对象。

import json  
with open('data.json', 'r') as f:  
    loaded_data = json.load(f)  
print(loaded_data)



#loads函数
将JSON格式的字符串反序列化为对象

import json  
json_string = '{"name": "ZhangSan", "age": 30, "city": "ShenZhen"}'  
python_object = json.loads(json_string)  
print(python_object)




#JSON 解码为 Python 类型转换表
<JSON>	            <Python>
object	            dict
array	            list
string	            str
number(int)	        int
number(real)	    float
true	            True
false	            False
null	            None

#Python 编码为 JSON 类型转换表
<Python>	                            <JSON>
dict	                                object
list, tuple	                            array
str	                                    string
int,float,int-&float-derived Enums	    number
True	                                true
False	                                false
None	                                null
