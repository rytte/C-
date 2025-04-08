/********************/ES7新特性/************************************************************/
//数组方法扩展
Array.prototype.includes：此方法用来检测数组中是否包含某个元素，返回布尔类型值

const mingzhu = ["西游记", "红楼梦", "三国演义", "水浒传"];
console.log(mingzhu.includes("西游记"));			//true


//幂运算
**操作符的作用和 Math.pow 的作用是一样，如下：

console.log(2 ** 10);
console.log(Math.pow(2, 10));



/********************/ES8新特性/************************************************************/
//async 函数
async function fn() {

}

async 函数的返回值：
1、async 函数始终返回 Promise。
2、如果 return 一个普通值，则自动封装为 Promise.resolve(value)。
3、如果 return 一个 Promise，则直接返回该 Promise。
4、如果 throw 错误，则返回 Promise.reject(error)。
5、需要使用 then / catch 处理 async 函数的返回值，或者用 await。

//实例
async function fn() 
{
    return new Promise((resolve, reject) = > 
    {
        resolve('成功的数据');
        // reject("失败的错误");
    });
}

const result = fn();

result.then(value = > {     //调用 then 方法
    console.log(value);
}, reason = > {
    console.warn(reason);
});


//await 表达式
async 和 await 两种语法结合可以让异步代码像同步代码一样

await 表达式的注意事项：
1、 await 必须写在 async 函数中
2、 await 右侧的表达式一般为 promise 对象
3、 await 返回的是 promise 成功的值
4、 await 的 promise 失败了, 就会抛出异常, 需要通过 try…catch 捕获处理

//实例
const p = new Promise((resolve, reject) = > {   //创建 promise 对象
    resolve("用户数据");
    //reject("失败啦!");
})

async function fun()              //await 要放在 async 函数中.
{
    try {
        let result = await p;
        console.log(result);
    }
    catch (e) {
        console.log(e);
    }
}
fun();      //调用函数


await 表达式的案例演示：async与await封装AJAX请求

// 发送 AJAX 请求, 返回的结果是 Promise 对象
function sendAJAX(url) 
{
    return new Promise((resolve, reject) = > 
    {
        const x = new XMLHttpRequest();         //1. 创建对象
        x.open('GET', url);                     //2. 初始化
        x.send();                               //3. 发送
        x.onreadystatechange = function()       //4. 事件绑定
        {
            if (x.readyState == = 4) 
            {
                if (x.status >= 200 && x.status < 300) 
                {
                    resolve(x.response);//成功
                }
                else 
                {
                    reject(x.status);//失败
                }
            }
        }
    })
}

async function fun()        // async 与 await 测试
{

    let joke = await sendAJAX("https://api.apiopen.top/getJoke");           //发送 AJAX 请求 1
    let tianqi = await sendAJAX('https://www.tianqiapi.com/api/?version=v1&city=%E5%8C%97%E4%BA%AC&appid=23941491&appsecret=TXoD5e8P')    //发送 AJAX 请求 2

    console.log(joke);
    console.error(tianqi);//为了区别数据，我这里用红色的error输出
}
fun();      // 调用函数


//对象方法拓展
Object.keys()           //返回一个对象的所有可枚举键值的数组
Object.values()         //返回一个对象的所有可枚举属性值的数组
Object.entries()        //返回一个对象的所有键值对的数组
Object.getOwnPropertyDescriptors    //返回对象所有自身属性的描述对象


//Trailing Comma
允许函数参数最后加逗号，提高可读性


//字符串方法拓展
String.prototype.padStart() / padEnd()	    //补全字符串，格式化文本

console.log("5".padStart(3, "0")); // "005"
console.log("123".padEnd(6, ".")); // "123..."


//多线程共享内存，提高性能
【SharedArrayBuffer】允许多个 Web Worker 共享内存。
【Atomics】          提供原子操作，防止多线程竞争条件（race condition）。

const buffer = new SharedArrayBuffer(1024);
const view = new Uint8Array(buffer);
Atomics.store(view, 0, 42);
console.log(Atomics.load(view, 0)); // 42



/********************/ES9新特性/************************************************************/
//对象拓展
对象也支持 Rest 参数与 spread 扩展运算符

//对象展开
function connect({ host, port, ...user }) 
{
    console.log(host);
    console.log(port);
    console.log(user);
}

connect({
    host: '127.0.0.1',
    port : 3306,
    username : 'root',
    password : 'root',
    type : 'master'
});

//对象合并
const skillOne = {
    q: '天音波'
};

const skillTwo = {
    w: '金钟罩'
};

const skillThree = {
    e: '天雷破'
};

const mangseng = { ...skillOne, ...skillTwo, ...skillThree };
console.log(mangseng);


//正则表达式拓展
1、命名捕获分组
2、正向断言
3、反向断言
4、dotAll模式

