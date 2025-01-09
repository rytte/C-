

#安装FastAPI
pip install fastapi

#安装ASGI服务
pip install uvicorn


#main.py
from fastapi import FastAPI

app = FastAPI()

@app.get('/')  
def root():  
    return {'message': 'Hello World'}


#启动服务
uvicorn main:app --reload       #app:在模块中app=FastAPI()行中创建的对象。 --reload:代码更改后自动重启服务
或者
uvicorn main:app --host 0.0.0.0 --port 8000


#访问服务
浏览器访问127.0.0.1:8000，
得到{"Hello":"World"} ,说明环境安装成功


#API交互文档
启动服务后，FastAPI会自动给生成两个交互文档：
SwaggerUI：http://127.0.0.1:8000/docs
ReDoc：http://127.0.0.1:8000/redoc
http://127.0.0.1:8000/openapi.json


#编码相关
路径操作装饰器
@app.get('/')       #当FastAPI接收一个使用GET方法访问路径为/的请求时这个函数会被调用，也可使用其他请求方法的装饰器，如下
@app.post()
@app.put()
@app.delete()
@app.options()
@app.head()
@app.patch()
@app.trace()


#接口文档
即 http://127.0.0.1:8000/docs 页面的编辑

from fastapi import FastAPI  

app = FastAPI(title='测试api应用程序', description='整体描述')  

@app.get(path='/', summary='接口注释', description='接口描述', tags= ['Root'])  
def read_root():      
    return {"Hello": "World"}

@app.get("/list/query1")  
def list_query1(page:int = 1,limit:int = 10):  
    """ 
    多行备注 
    - param page: 页数 
    - param limit: 每页个数 
    - return: 以给定页数和每页个数为数据的对象，字段为page,limit 
    """  
    return

@app.get("/list/query2")  
def list_query2(page:int = 1,limit :int = None):  
    """ 
    多行备注 
    | *参数名称* | *参数类型* | *默认值* | *释义* | 
    | :--: | :--: | :--: | :--: | 
    | page | int | 1 | 页数| 
    | limit | int | none | 每页个数| 
    
    | *返回值类型* | *释义* | 
    | :--: | :--: | 
    | page | 页数 | 
    | limit | 每页个数 | 
    """  
    return

