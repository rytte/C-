('''********************'''aiohttp'''************************************************************'''


aiohttp 库（一个基于 asyncio 的异步 HTTP 客户端/服务器框架）


#安装
pip install aiohttp

#安装加速功能扩展
pip install aiohttp[speedups]



('''********************'''异步Web服务器'''************************************************************'''

from aiohttp import web  
  
async def handle(request):  
    return web.Response(text="Hello, aiohttp!")  
  
app = web.Application()  
app.router.add_get('/', handle)  
  
if __name__ == "__main__":  
    web.run_app(app)
    


('''********************'''异步HTTP客户端'''************************************************************'''
 
import aiohttp  
import asyncio  
  
async def fetch(url):  
    async with aiohttp.ClientSession() as session:  
        async with session.get(url) as response:  
            return await response.text()  
  
async def main():  
    url = 'http://api.example.com/data'  
    result = await fetch(url)  
    print(result)  
  
asyncio.run(main())









