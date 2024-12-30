/*************************/Cookie/***************************************************************************/
Cookie 是一种小型文本文件，通常由 Web 服务器 创建并存储在用户的计算机或设备上，主要用于在用户与网站之间传递信息。
它在浏览器和服务器之间交换数据时扮演着重要角色，尤其是在管理会话、存储用户偏好设置、追踪用户行为等方面。

//基本特点
小数据存储：每个 Cookie 的数据量一般较小（最大通常为 4KB），只能存储简单的文本数据。
客户端存储：Cookie 存储在用户的浏览器本地，浏览器会自动发送 Cookie 给相应的服务器，通常是在每次请求时。
跨请求传递：Cookie 的数据会随着用户的每个请求自动发送到指定的服务器或网站，服务器根据这些数据来识别用户、维持会话等。


//Cookie操作
JavaScript 可以使用 document.cookie 属性来创建 、读取、及删除 Cookie。

//创建：添加一个过期时间（以 UTC 或 GMT 时间），路径
document.cookie = "username=zhangsan; expires=Thu, 18 Dec 2043 12:00:00 GMT; path=/";

//读取：返回值为字符串
var cookies = document.cookie;	

//修改：直接覆盖
document.cookie = "username=zhangsan";
document.cookie = "username=lisi";

//删除：设置 expires 参数为以前的时间即可
document.cookie = "username=; expires=Thu, 01 Jan 1970 00:00:00 GMT";

/**
 * Cookie值设置函数
 * @param cname   cookie名称
 * @param cvalue  cookie值
 * @param exdays  过期天数
 */
function setCookie(cname, cvalue, exdays) {
    var d = new Date();
    d.setTime(d.getTime() + (exdays * 24 * 60 * 60 * 1000));
    var expires = "expires=" + d.toGMTString();
    document.cookie = cname + "=" + cvalue + "; " + expires;
}

/**
 * Cookie值获取函数
 * @param cname  cookie名称
 * @returns {string}
 */
function getCookie(cname) {
    var name = cname + "=";
    var ca = document.cookie.split(';');
    for (var i = 0; i < ca.length; i++) {
        var c = ca[i].trim();
        if (c.indexOf(name) == 0) return c.substring(name.length, c.length);
    }
    return "";
}


/*************************/WebStorage/***************************************************************************/
WebStorage是HTML5中本地存储的解决方案之一，用以弥补Cookie的缺点


//Cookie缺点
1、数据大小：4KB限制
2、安全性问题：由于在HTTP请求中的Cookie是明文传递的（HTTPS不是），带来的安全性问题还是很大的。
3、网络负担：Cookie会被附加在每个HTTP请求中，在HttpRequest和HttpResponse的header中都是要被传输的，无形中增加了一些不必要的流量损失。


//WebStorage分类
Web Storage又分为两种： sessionStorage 和 localStorage ，即这两个是Storage的两个实例，使用的API都相同。
WebStorage只能存储字符串类型，对于复杂的对象可以使用ECMAScript提供的JSON对象的stringify和parse来处理。


//LocalStorage
localStorage在本地永久性存储数据，除非显式将其删除或清空。

localStorage.setItem(key, value);      //保存单个数据
localStorage.getItem(key);             //读取单个数据
localStorage.removeItem(key);          //删除单个数据
localStorage.clear();                  //删除所有数据
localStorage.key(index);               //获取某个索引的key


//SessionStorage
sessionStorage对象存储特定于某个对话的数据，也就是它的生命周期为当前窗口或标签页，
一旦窗口或标签页被永久关闭了，那么所有通过sessionStorage存储的数据也就被清空了。
存储在sessionStorage中的数据可以跨越页面刷新而存在，同时如果浏览器支持，
浏览器崩溃并重启之后依然可以使用（注意：Firefox和Weblit都支持，IE则不行）。

因为sessionStorage对象绑定于某个服务器会话，所以当文件在本地运行的时候是不可用的。
存储在sessionStorage中的数据只能由最初给对象存储数据的页面访问到，所以对多页面应用有限制。

sessionStorage.setItem(key, value);     //保存单个数据
sessionStorage.getItem(key);            //读取单个数据
sessionStorage.removeItem(key);         //删除单个数据
sessionStorage.clear();                 //删除所有数据
sessionStorage.key(index);              //获取某个索引的key



/*************************/Closure/***************************************************************************/
//闭包
当一个嵌套的内部(子)函数引用了嵌套的外部(父)函数的变量(函数)时，就产生了闭包

//什么才是闭包？
理解一：闭包是嵌套的内部函数（绝大部分人认为）
理解二：包含被引用变量（函数）的对象（极少部分人认为）

//简单理解
两个嵌套的函数：外层函数是装饰器，内层函数是闭包

//闭包的作用
它的最大用处有两个，一个是可以读取函数内部的变量，另一个就是让这些变量的值始终保持在内存中

//生命周期：
产生：在嵌套内部函数定义执行完时就产生了(不是在调用)
死亡：在嵌套的内部函数成为垃圾对象时就死亡了

//应用实例
function myModule() 
{
    var msg = 'Hello, World';       //私有数据

    //操作数据的函数
    function doSomething() {
        console.log('doSomething() ' + msg.toUpperCase());
    }

    function doOtherthing() {
        console.log('doOtherthing() ' + msg.toLowerCase());
    }

    //向外暴露对象(给外部使用的方法)
    return {
        doSomething: doSomething,
        doOtherthing : doOtherthing
    }
}

var module = myModule();
module.doSomething();
module.doOtherthing();

