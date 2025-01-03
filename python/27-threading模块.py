'''********************'''threading 模块'''************************************************************'''
线程可以被抢占（中断）。
在其他线程正在运行时，线程可以暂时搁置（也称为睡眠） -- 这就是线程的退让。

线程可以分为:
内核线程：由操作系统内核创建和撤销。
用户线程：不需要内核支持而在用户程序中实现的线程。

在 Python3 中"thread" 模块被废弃。为了兼容性，Python3 将 thread 重命名为 "_thread"。现在一般使用 threading 模块。

import threading


'''************************************************************'''
#创建线程
函数式：调用 _thread 模块中的start_new_thread()函数来产生新线程。语法如下:

_thread.start_new_thread ( function, args[, kwargs] )
参数：
    function : 线程函数。
    args :     传递给线程函数的参数,他必须是个tuple类型。
    kwargs :   可选参数。

实例
#!/usr/bin/python3

import _thread
import time

# 为线程定义一个函数
def print_time( threadName, delay):
   count = 0
   while count < 5:
      time.sleep(delay)
      count += 1
      print ("%s: %s" % ( threadName, time.ctime(time.time()) ))

# 创建两个线程
try:
   _thread.start_new_thread( print_time, ("Thread-1", 2, ) )
   _thread.start_new_thread( print_time, ("Thread-2", 4, ) )
except:
   print ("Error: 无法启动线程")

while 1:
   pass
执行以上程序输出结果如下：

Thread-1: Wed Jan  5 17:38:08 2022
Thread-2: Wed Jan  5 17:38:10 2022
Thread-1: Wed Jan  5 17:38:10 2022
Thread-1: Wed Jan  5 17:38:12 2022
Thread-2: Wed Jan  5 17:38:14 2022
Thread-1: Wed Jan  5 17:38:14 2022
Thread-1: Wed Jan  5 17:38:16 2022
Thread-2: Wed Jan  5 17:38:18 2022
Thread-2: Wed Jan  5 17:38:22 2022
Thread-2: Wed Jan  5 17:38:26 2022

执行以上程后可以按下 ctrl-c 退出。


'''************************************************************'''
# threading 模块方法
threading 模块除了包含 _thread 模块中的所有方法外，还提供的其他方法：

threading.currentThread()   返回当前的线程变量。
threading.enumerate()       返回一个包含正在运行的线程的list。正在运行指线程启动后、结束前，不包括启动前和终止后的线程。
threading.activeCount()     返回正在运行的线程数量，与len(threading.enumerate())有相同的结果。

# threading 模块中Thread类的方法
run()           用以表示线程活动的方法。
start()         启动线程活动。
join([time])    等待至线程中止。这阻塞调用线程直至线程的join() 方法被调用中止-正常退出或者抛出未处理的异常-或者是可选的超时发生。
isAlive()       返回线程是否活动的。
getName()       返回线程名。
setName()       设置线程名。


'''************************************************************'''
#使用 threading 模块创建线程
我们可以通过直接从 threading.Thread 继承创建一个新的子类，并实例化后调用 start() 方法启动新线程，即它调用了线程的 run() 方法：

实例：
#!/usr/bin/python3

import threading
import time

exitFlag = 0

class myThread (threading.Thread):
    def __init__(self, threadID, name, delay):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.delay = delay
    def run(self):
        print ("开始线程：" + self.name)
        print_time(self.name, self.delay, 5)
        print ("退出线程：" + self.name)

def print_time(threadName, delay, counter):
    while counter:
        if exitFlag:
            threadName.exit()
        time.sleep(delay)
        print ("%s: %s" % (threadName, time.ctime(time.time())))
        counter -= 1

# 创建新线程
thread1 = myThread(1, "Thread-1", 1)
thread2 = myThread(2, "Thread-2", 2)

# 开启新线程
thread1.start()
thread2.start()
thread1.join()
thread2.join()
print ("退出主线程")


以上程序执行结果如下；

开始线程：Thread-1
开始线程：Thread-2
Thread-1: Wed Jan  5 17:34:54 2022
Thread-2: Wed Jan  5 17:34:55 2022
Thread-1: Wed Jan  5 17:34:55 2022
Thread-1: Wed Jan  5 17:34:56 2022
Thread-2: Wed Jan  5 17:34:57 2022
Thread-1: Wed Jan  5 17:34:57 2022
Thread-1: Wed Jan  5 17:34:58 2022
退出线程：Thread-1
Thread-2: Wed Jan  5 17:34:59 2022
Thread-2: Wed Jan  5 17:35:01 2022
Thread-2: Wed Jan  5 17:35:03 2022
退出线程：Thread-2
退出主线程


'''********************'''锁'''************************************************************'''
使用 Thread 对象的 Lock 和 Rlock 可以实现简单的线程同步，这两个对象都有 acquire 方法和 release 方法，
对于那些需要每次只允许一个线程操作的数据，可以将其操作放到 acquire 和 release 方法之间。

实例：
#!/usr/bin/python3

import threading
import time

class myThread (threading.Thread):
    def __init__(self, threadID, name, delay):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.delay = delay
    def run(self):
        print ("开启线程： " + self.name)
        # 获取锁，用于线程同步
        threadLock.acquire()
        print_time(self.name, self.delay, 3)
        # 释放锁，开启下一个线程
        threadLock.release()

def print_time(threadName, delay, counter):
    while counter:
        time.sleep(delay)
        print ("%s: %s" % (threadName, time.ctime(time.time())))
        counter -= 1

threadLock = threading.Lock()
threads = []

# 创建新线程
thread1 = myThread(1, "Thread-1", 1)
thread2 = myThread(2, "Thread-2", 2)

# 开启新线程
thread1.start()
thread2.start()

# 添加线程到线程列表
threads.append(thread1)
threads.append(thread2)

# 等待所有线程完成
for t in threads:
    t.join()
print ("退出主线程")
执行以上程序，输出结果为：

开启线程： Thread-1
开启线程： Thread-2
Thread-1: Wed Jan  5 17:36:50 2022
Thread-1: Wed Jan  5 17:36:51 2022
Thread-1: Wed Jan  5 17:36:52 2022
Thread-2: Wed Jan  5 17:36:54 2022
Thread-2: Wed Jan  5 17:36:56 2022
Thread-2: Wed Jan  5 17:36:58 2022
退出主线程



'''********************'''线程优先级队列（ Queue）'''************************************************************'''
Python 的 Queue 模块中提供了同步的、线程安全的队列类，
包括FIFO（先入先出)队列Queue，LIFO（后入先出）队列LifoQueue，和优先级队列 PriorityQueue。

这些队列都实现了锁原语，能够在多线程中直接使用，可以使用队列来实现线程间的同步。

#Queue 模块中的常用方法
Queue.qsize()                   返回队列的大小
Queue.empty()                   如果队列为空，返回True,反之False
Queue.full()                    如果队列满了，返回True,反之False。Queue.full 与 maxsize 大小对应
Queue.get([block[, timeout]])   获取队列，timeout等待时间
Queue.get_nowait()              相当Queue.get(False)
Queue.put(item)                 写入队列，timeout等待时间
Queue.put_nowait(item)          相当Queue.put(item, False)
Queue.task_done()               在完成一项工作之后，Queue.task_done()函数向任务已经完成的队列发送一个信号
Queue.join()                    实际上意味着等到队列为空，再执行别的操作


实例：
#!/usr/bin/python3

import queue
import threading
import time

exitFlag = 0

class myThread (threading.Thread):
    def __init__(self, threadID, name, q):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.q = q
    def run(self):
        print ("开启线程：" + self.name)
        process_data(self.name, self.q)
        print ("退出线程：" + self.name)

def process_data(threadName, q):
    while not exitFlag:
        queueLock.acquire()
        if not workQueue.empty():
            data = q.get()
            queueLock.release()
            print ("%s processing %s" % (threadName, data))
        else:
            queueLock.release()
        time.sleep(1)

threadList = ["Thread-1", "Thread-2", "Thread-3"]
nameList = ["One", "Two", "Three", "Four", "Five"]
queueLock = threading.Lock()
workQueue = queue.Queue(10)
threads = []
threadID = 1

# 创建新线程
for tName in threadList:
    thread = myThread(threadID, tName, workQueue)
    thread.start()
    threads.append(thread)
    threadID += 1

# 填充队列
queueLock.acquire()
for word in nameList:
    workQueue.put(word)
queueLock.release()

# 等待队列清空
while not workQueue.empty():
    pass

# 通知线程是时候退出
exitFlag = 1

# 等待所有线程完成
for t in threads:
    t.join()
print ("退出主线程")
以上程序执行结果：

开启线程：Thread-1
开启线程：Thread-2
开启线程：Thread-3
Thread-3 processing One
Thread-1 processing Two
Thread-2 processing Three
Thread-3 processing Four
Thread-1 processing Five
退出线程：Thread-3
退出线程：Thread-2
退出线程：Thread-1
退出主线程


