/*************************/ECMAScript7新特性/***************************************************************************/
//数组方法扩展
Array.prototype.includes：此方法用来检测数组中是否包含某个元素，返回布尔类型值

const mingzhu = ["西游记", "红楼梦", "三国演义", "水浒传"];
console.log(mingzhu.includes("西游记"));			//true


//幂运算
**操作符的作用和 Math.pow 的作用是一样，请看代码：

console.log(2 ** 10);
console.log(Math.pow(2, 10));



/*************************/ECMAScript8新特性/***************************************************************************/
//async 函数
async function fn() {

}

async 函数的返回值：
1、返回的结果不是一个 Promise 类型的对象，返回的结果就是成功 Promise 对象
2、返回的结果如果是一个 Promise 对象，具体需要看执行resolve方法还是reject方法
3、抛出错误，返回的结果是一个失败的 Promise

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
Object.keys()           //返回一个给定对象的所有可枚举键值的数组
Object.values()         //返回一个给定对象的所有可枚举属性值的数组
Object.entries()        //返回一个给定对象自身可遍历属性[key, value] 的数组
Object.getOwnPropertyDescriptors    //返回指定对象所有自身属性的描述对象



/*************************/ECMAScript9新特性/***************************************************************************/
//对象拓展
Rest 参数与 spread 扩展运算符在 ES6 中已经引入，不过 ES6 中只针对于数组，在 ES9 中为对象提供了像数组一样的 rest 参数和扩展运算符

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

const skillFour = {
    r: '猛龙摆尾'
};

const mangseng = { ...skillOne, ...skillTwo, ...skillThree, ...skillFour };
console.log(mangseng);


//正则表达式拓展
1、命名捕获分组
2、正向断言
3、反向断言
4、dotAll模式

