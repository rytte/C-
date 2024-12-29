/*************************/Exception/***************************************************************************/
当错误发生时，JavaScript 提供了错误信息的内置 error 对象。error 对象提供两个有用的属性：name 和 message 。

name	设置或返回错误名
message	设置或返回错误消息（一条字符串）

//name的值
错误名			描述
EvalError		已在 eval() 函数中发生的错误
RangeError		已发生超出数字范围的错误
ReferenceError	已发生非法引用
SyntaxError		已发生语法错误
TypeError		已发生类型错误
URIError		在 encodeURI() 中已发生的错误


//异常捕获
try 
{
    // 可能发生异常的代码
    console.log(a);
    console.log("a未定义肯定报错，你看不见我");
}
catch (error) 
{
    // 发生错误执行的代码
    console.log(error);
}
finally 
{
    // 无论是否出错都会执行的代码
    console.log("finally 执行了 ...")
}


//主动抛出异常
function foo(num) {         /*该函数接收一个数字，返回它的平方。*/
    if (typeof num == "number") {
        return num * num;
    }
    else {
        throw new TypeError("您输入的是一个非法数字！")
    }
}

console.log(foo(4));
console.log(foo("abc"));


//自定义异常
function MyError(message) {
    this.message = "注意：这是自定义的错误"
        this.name = "自定义错误";
}
MyError.prototype = new Error();

try {
    throw new MyError("注意：这是自定义错误类型")
}
catch (error) {
    console.log(error.message)
}



/*************************/JSON/***************************************************************************/
JSON：JavaScript Object Notation（JavaScript 对象标记法），它是一种存储和交换数据的语法。

//值类型
字符串（在 JSON 中，字符串值必须由双引号编写）
数字
对象（JSON 对象）
数组
布尔
null

//创建JSON对象
var person = { "name": "zhangsan", "age" : 62, "city" : "BeiJing" };
console.log(person);

//JSON字符串转JS对象
var jsonStr = '{"name":"孙悟空","age":18,"gender":"男"}';
var obj = JSON.parse(jsonStr);
console.log(obj);

//JS对象转JSON字符串
var obj = { name: "猪八戒", age : 28, gender : "男" };
var jsonStr = JSON.stringify(obj);
console.log(jsonStr);



/*************************/AJAX/***************************************************************************/
AJAX 是一种用于创建快速动态网页的技术，通过在后台与服务器进行少量数据交换，AJAX 可以使网页实现异步更新，这意味着可以在不重新加载整个网页的情况下，对网页的某部分进行更新。

//原理
AJAX 的核心是 XMLHttpRequest 对象。 所有现代浏览器都支持 XMLHttpRequest 对象。
XMLHttpRequest 对象用于幕后同服务器交换数据，这意味着可以更新网页的部分，而不需要重新加载整个页面。
需要注意的是，出于安全原因，现代浏览器不允许跨域访问，这意味着尝试加载的网页和 XML 文件都必须位于相同服务器上。

//创建
variable = new XMLHttpRequest();

//AJAX的XMLHttpRequest对象方法
方法	                                描述
new XMLHttpRequest()	            创建新的 XMLHttpRequest 对象
abort()	                            取消当前请求
getAllResponseHeaders()	            返回头部信息
getResponseHeader()	                返回特定的头部信息
open(method, url, async, user, psw)	规定请求method：请求类型 GET 或 POST
                                              url：文件位置
                                            async：true（异步）或 false（同步）
                                             user：可选的用户名称
                                              psw：可选的密码
send()	                            将请求发送到服务器，用于 GET 请求
send(string)	                    将请求发送到服务器，用于 POST 请求
setRequestHeader()	                向要发送的报头添加标签 / 值对

//AJAX的XMLHttpRequest对象属性
属性	                                描述
onreadystatechange	                定义当 readyState 属性发生变化时被调用的函数
readyState	                        保存 XMLHttpRequest 的状态。
                                        0：请求未初始化
                                        1：服务器连接已建立
                                        2：请求已收到
                                        3：正在处理请求
                                        4：请求已完成且响应已就绪
responseText	                    以字符串返回响应数据
responseXML	                        以 XML 数据返回响应数据
status	                            返回请求的状态号
                                        200: "OK"
                                        403 : "Forbidden"
                                        404 : "Not Found"
                                        如需完整列表请访问 Http 消息参考手册
statusText	                            返回状态文本（比如 “OK” 或 “Not Found”）


//GET请求


