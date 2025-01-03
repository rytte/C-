('''********************'''asyncio 模块'''************************************************************'''

 1、异步函数定义：使用 async def 而不是常规的 def 来定义一个异步函数。
 async def my_async_function():  
    # 异步代码  
    pass


 2、 await 表达式：在异步函数内部，你可以使用 await 关键字来等待一个异步操作完成。
 这通常用于调用其他异步函数或执行异步任务。
async def fetch_data():  
    response = await some_async_http_request()  #等待some_async_http_request()函数完成再向下运行
    return response


 3、运行异步代码：你不能直接调用异步函数并期待它立即执行。你需要使用事件循环来运行它。
 通常，你可以使用 asyncio.run() 来运行顶层异步函数。
 import asyncio  
  
async def main():  
    # 异步代码  
    pass  
  
asyncio.run(main())



('''********************'''实例'''************************************************************'''

import asyncio  
  
# 定义第一个异步函数，模拟异步操作  
async def task1():  
    print('Task 1 started')  
    # 模拟异步操作耗时，比如等待I/O操作完成  
    await asyncio.sleep(2)  
    print('Task 1 finished')  
  
# 定义第二个异步函数，同样模拟异步操作  
async def task2():  
    print('Task 2 started')  
    # 假设这个异步操作耗时较短  
    await asyncio.sleep(1)  
    print('Task 2 finished')  
  
# 主协程函数  
async def main():  
    # 并发执行task1和task2  
    # 注意：这里并没有显式地等待task1和task2完成，因为asyncio.gather会等待所有传入的协程完成  
    await asyncio.gather(task1(), task2())  
  
# 运行主协程  
# asyncio.run会自动创建一个事件循环，运行传入的协程，并在完成后关闭事件循环  
asyncio.run(main())

