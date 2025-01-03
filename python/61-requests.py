('''********************'''requests 模块'''************************************************************'''
 requests模块是一个非常流行的HTTP库，用于向网站发送HTTP/1.1请求，并获取响应结果。
 

#安装
 pip install requests


#requests 方法
requests 提供的函数可以向指定 URL 发送 HTTP 请求，调用任一函数都会返回一个 response 对象。

delete(url, args)	        发送 DELETE 请求到指定 url
get(url, params, args)	    发送 GET 请求到指定 url
head(url, args)	            发送 HEAD 请求到指定 url
patch(url, data, args)	    发送 PATCH 请求到指定 url
post(url, data, json, args)	发送 POST 请求到指定 url
put(url, data, args)	    发送 PUT 请求到指定 url
request(method, url, args)	向指定的 url 发送指定的请求方法


#request请求实例
import requests             # 导入 requests 包
x = requests.request('get', 'https://www.runoob.com/')      # 发送请求
print(x.status_code)        # 返回网页内容
200


#get请求实例：
import requests
x = requests.get('https://www.runoob.com/')     # 发送请求，返回response对象，该对象包含了具体的响应信息，如状态码、响应头、响应内容等
print(x.text)            # 返回网页内容
print(x.status_code)     # 返回 http 的状态码
print(x.headers)         # 获取响应头
print(x.content)         # 获取响应内容
print(x.reason)          # 响应状态的描述
OK
print(x.apparent_encoding)  # 返回编码方式
utf-8


#其它response方法
close	                关闭与服务器的连接
cookies	                返回一个 CookieJar 对象，包含了从服务器发回的 cookie
elapsed	                返回一个 timedelta 对象，包含了从发送请求到响应到达之间经过的时间量，可以用于测试响应速度。比如 r.elapsed.microseconds 表示响应到达需要多少微秒。
encoding	            解码 r.text 的编码方式
history	                返回包含请求历史的响应对象列表（url）
is_permanent_redirect	如果响应是永久重定向的 url，则返回 True，否则返回 False
is_redirect	            如果响应被重定向，则返回 True，否则返回 False
iter_content	        迭代响应
iter_lines	            迭代响应的行
json	                返回结果的 JSON 对象 (结果需要以 JSON 格式编写的，否则会引发错误)
links	                返回响应的解析头链接
next	                返回重定向链中下一个请求的 PreparedRequest 对象
ok	                    检查 "status_code" 的值，如果小于400，则返回 True，如果不小于 400，则返回 False
raise_for_status	    如果发生错误，方法返回一个 HTTPError 对象
request	                返回请求此响应的请求对象
url	                    返回响应的 URL



#设置请求头实例
import requests  
headers = {  
    'User-Agent': 'my-app/0.0.1',  
    'Authorization': 'Bearer your_token_here'  
}  
response = requests.get('http://httpbin.org/headers', headers=headers)  
print(response.json())


#post请求实例
格式：
requests.post(url, data={key: value}, json={key: value}, args)
参数：
url  请求 url。
data 参数为要发送到指定 url 的字典、元组列表、字节或文件对象。
json 参数为要发送到指定 url 的 JSON 对象。
args 为其他参数，比如 cookies、headers、verify等。

import requests
x = requests.post('https://www.runoob.com/try/ajax/demo_post.php')
print(x.text)


#附加请求参数
发送请求我们可以在请求中附加额外的参数，例如请求头、查询参数、请求体等，例如：

headers = {'User-Agent': 'Mozilla/5.0'}                 # 设置请求头
params = {'key1': 'value1', 'key2': 'value2'}           # 设置查询参数
data = {'username': 'example', 'password': '123456'}    # 设置请求体
response = requests.post('https://www.runoob.com', headers=headers, params=params, data=data)
上述代码发送一个 POST 请求，并附加了请求头、查询参数和请求体。


