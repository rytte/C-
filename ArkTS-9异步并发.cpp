/********************/异步并发/************************************************************/

//并发
在同一时间内，多个任务同时执行。
对于多核设备，这些任务可能同时在不同CPU上并行执行。
对于单核设备，多个任务不会在同一时刻并行执行，但是CPU会在某个任务休眠或进行IO操作等状态下切换任务，调度执行其他任务，提升CPU的资源利用率。


//多线程并发（Thread - based Concurrency）
* 由多个线程执行任务，每个线程可以运行在不同 CPU 核心上。
* 适用于CPU 密集型任务（如视频解码、计算机视觉）。
* 线程可以真正地并行执行，如果任务数 <= CPU 核心数，操作系统可能会把每个线程分配到不同的核心。

//异步并发（Async Concurrency）
* 主要依赖事件驱动，不一定使用多个线程，通常是在同一个线程中调度多个任务，采用 协程（coroutines）或事件循环（event loop）机制。
* 适用于I / O 密集型任务（如网络请求、数据库访问、文件读写）。
* 任务是异步执行的，但通常仍然运行在单个 CPU 核心上。


// Promise 和 async / await
异步代码会被挂起并在之后继续执行，同一时间只有一段代码执行，适用于单次I / O任务的场景开发，例如一次网络请求、一次文件读写等操作。
无需另外启动线程执行。



/********************/Promise/************************************************************/
// 三种状态
Promise 有三种状态：pending（进行中）、fulfilled（已完成）和rejected（已拒绝）。
Promise对象创建后处于pending状态，并在异步操作完成后转换为 fulfilled 或 rejected 状态。

// Promise 实例
import { BusinessError } from '@kit.BasicServicesKit';

const promise : Promise<number> = new Promise((resolve : Function, reject : Function) = > {
    setTimeout(() = > {
        const randomNumber : number = Math.random();
        if (randomNumber > 0.5) {
            resolve(randomNumber);          // 执行resolve回调函数并将随机数作为参数传递
        }
        else {
            reject(new Error('Random number is too small'));  // 执行reject回调函数并传递一个错误对象作为参数
        }
    }, 1000);
})

promise.then((result: number) = > {             // then 方法可以指定两个参数，分别为 resolve 和 reject 传入的参数
    console.info(`Random number is ${ result }`);
}).catch ((error: BusinessError) = > {          // catch 方法可以指定一个参数，即 reject 传入的参数
    console.error(error.message);
});

*当 Promise 被 reject 且未通过 catch 方法来处理时，会触发 unhandledrejection 事件。
* 可使用errorManager.on('error')接口监听该事件，以全局捕获未处理的 Promise reject。



/********************/async / await/************************************************************/
async / await是一种用于处理异步操作的Promise语法糖，使得编写异步代码变得更加简单和易读。

async 关键字声明一个函数为异步函数，返回Promise对象
await 关键字等待异步函数完成，达到同步效果，返回Promise的解析值（完成或拒绝）


// async / await 实例
模拟了一个以同步方式执行异步操作的场景，该操作会在3秒钟后返回一个字符串。

async function myAsyncFunction() : Promise<string>{
  const result : string = await new Promise((resolve : Function) = > {
    setTimeout(() = > {
      resolve('Hello, world!');
    }, 3000);
  });
  console.info(result); // 输出：Hello, world!
  return result;
}

@Entry
@Component
struct Index {
    build() {
        Row() {
            Text('Hello World')
                .onClick(async() = > {
                    let res = await myAsyncFunction();
                    console.info("res is: " + res);
            })
        }
        .height('100%')
    }
}



