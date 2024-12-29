/*************************/数组对象/***************************************************************************/
可以存放不同类型元素

//数组创建
var arr = new Array();
arr[0] = 1;
arr[1] = "2";
arr[2] = 3;
arr[3] = "4";

var arr = [1, "2", 3, "4"];


//数组遍历
for (var i = 0; i < arr.length; i++) 
{
    console.log(arr[i]);
}

arr.forEach(
    function(value, index, obj)     //参数: 当前元素, 当前元素的索引, 数组
{
    console.log(value + " #### " + index + " #### " + obj);
});


//数组方法
var arr = ["孙悟空", "猪八戒", "沙和尚"];
var result = arr.push("唐僧", "蜘蛛精", "白骨精", "玉兔精");   //在末尾添加一个或多个元素，并返回新的长度
var result = arr.pop();                                      //删除最后一个元素，并返回删除的元素
var result = arr.unshift("牛魔王", "二郎神");                 //在开头添加一个或多个元素，并返回新的长度
var result = arr.shift();                                    //删除第一个元素，并返回删除的元素
var result = arr.slice(1, -2);                               //切片，不会改变原数组
                                            //参数：开始元素的索引(含)，结束元素的索引(不含)。负数为倒数的意思
var result = arr.splice(1, 0, "牛魔王", "铁扇公主", "红孩儿"); //删除数组中的指定元素，并返回删除的元素
                                            //参数：开始元素的索引，删除的数量，新增元素列表。新增元素会插入到开始元素之前
var result = arr.concat(arr2, arr3, "牛魔王", "铁扇公主");    //连接多个数组，并将新的数组返回
var result = arr.join("@-@");                                //将数组转换为一个字符串，用参数连接各元素。默认使用','
arr.reverse();                                               //反转数组，该方法会直接修改原数组
arr.sort();                                                  //对数组中的元素按照Unicode编码进行排序，也会影响原数组
                                             //注意：对数字进排序时，可能会得到错误的结果。
arr.sort(function(a, b)                                      //使用回调函数排序
{
    return a - b;
});
回调函数中需要定义两个形参。浏览器会根据回调函数的返回值来决定元素的顺序
1、返回值 > 0，则元素会交换位置
2、返回值 < 0，则元素位置不变
3、返回值 = 0，则认为两个元素相等，也不交换位置
因此
1、如果需要升序排列，则返回 a - b
2、如果需要降序排列，则返回 b - a



/*************************/函数对象/***************************************************************************/
//call()和apply()方法
在调用call()和apply()可以将一个对象指定为第一个参数，此时这个对象将会成为函数执行时的this
call()方法可以将实参在对象之后依次传递，apply()方法需要将实参封装到一个数组中统一传递

function fun(a, b) {
    console.log("a = " + a);
    console.log("b = " + b);
    console.log("fun = " + this);
}

var obj = {
    name: "obj",
    sayName : function() {
        console.log(this.name);
    }
};

fun(2, 3);
console.log("===============");
fun.call(obj, 2, 3);
console.log("===============");
fun.apply(obj, [2, 3]);


//this
1、 this 在函数中永远都是window
2、 this 在方法中就是调用方法的那个对象
3、 this 在构造函数中就是新创建的那个对象
4、 this 在使用call和apply调用时，是传入的那个对象


//arguments参数
在调用函数时，浏览器每次都会传递进两个隐含的参数：
函数的上下文对象： this
封装实参的对象： arguments

arguments是一个参数类数组对象，它也可以通过索引来操作数据，也可以获取长度

arguments[0]：表示第一个实参
arguments[1]：表示第二个实参
…

arguments有一个属性叫做callee，该属性就是当前函数对象

function fun(a, b) 
{

    console.log(arguments[0]);              // 获取第一个参数
    console.log(arguments.length);          // 获取实参的个数
    console.log(arguments.callee);          // 看看它的函数对象
    console.log(arguments.callee == fun);   //返回true
}

fun("Hello", "World");



/*************************/Date对象/***************************************************************************/
在JavaScript中使用Date对象来表示一个时间。

var date = new Date();          //获取当前代码执行的时间
console.log(date);
console.log(date.getFullYear());    //获取当前日期对象的年份(四位数字年份)
console.log(date.getMonth());       //获取当前日期对象的月份(0 ~ 11)
console.log(date.getDate());        //获取当前日期对象的日数(1 ~ 31)
console.log(date.getHours());       //获取当前日期对象的小时(0 ~ 23)
console.log(date.getMinutes());     //获取当前日期对象的分钟(0 ~ 59)
console.log(date.getSeconds());     //获取当前日期对象的秒钟(0 ~ 59)
console.log(date.getMilliseconds());//获取当前日期对象的毫秒(0 ~ 999)



/*************************/Math对象/***************************************************************************/
Math和其它的对象不同，它不是一个构造函数，它属于一个工具类不用创建对象，它里边封装了数学运算相关的属性和方法。

/*固定值*/
console.log("PI = " + Math.PI);
console.log("E  = " + Math.E);
console.log("===============");
/*正数*/
console.log(Math.abs(1));        //可以用来计算一个数的绝对值
console.log(Math.ceil(1.1));     //可以对一个数进行向上取整，小数位只有有值就自动进1
console.log(Math.floor(1.99));   //可以对一个数进行向下取整，小数部分会被舍掉
console.log(Math.round(1.4));    //可以对一个数进行四舍五入取整
console.log("===============");
/*负数*/
console.log(Math.abs(-1));       //可以用来计算一个数的绝对值
console.log(Math.ceil(-1.1));    //可以对一个数进行向上取整，小数部分会被舍掉
console.log(Math.floor(-1.99));  //可以对一个数进行向下取整，小数位只有有值就自动进1
console.log(Math.round(-1.4));   //可以对一个数进行四舍五入取整
console.log("===============");
/*随机数*/
//Math.random()：可以用来生成一个0-1之间的随机数
//生成一个0-x之间的随机数：Math.round(Math.random()*x)
//生成一个x-y之间的随机数：Math.round(Math.random()*(y-x)+x)
console.log(Math.round(Math.random() * 10));            //生成一个0-10之间的随机数
console.log(Math.round(Math.random()* (10 - 1) + 1));  //生成一个1-10之间的随机数
console.log("===============");
/*数学运算*/
console.log(Math.pow(12, 3));   //Math.pow(x,y)：返回x的y次幂
console.log(Math.sqrt(4));      //Math.sqrt(x) ：返回x的平方根



/*************************/String对象/***************************************************************************/
var str = "Hello,World!";
str.length                  //获取字符串长度
str.charAt(1)               //根据索引获取指定位置的字符
str.charCodeAt(1)           //根据索引获取指定位置的字符的字符编码（Unicode编码）
str.concat("你好，", "世界！")    //连接两个或多个字符串并返回
str.indexOf("o")            //检索一个字符串中是否含有指定内容，有则返回其第一次出现的索引，没有则返回 - 1
str.indexOf("o", 5)         //可以指定第二个参数，指定开始查找的位置
str.lastIndexOf("o")        //同indexOf，但从后往前找
str.lastIndexOf("o", 5)     //同indexOf，但从后往前找
str.slice(1, -1);           //切片，不影响原字符串。参数: 开始索引，结束索引。省略第二个参数，则会截取到后边所有的
                            //索引为负数的话将会从后边计算
str.substring(1, -1);       //参数同slice。
                            //但该方法不能接受负值作为参数，如果传递了一个负值，则使用0
                            //并且如果第二个参数小于第一个，则自动交换参数
str.substr(6, 6);           //截取字符串。参数：开始索引，截取长度
str.toUpperCase();          //将一个字符串转换为大写并返回
str.toLowerCase();          //将一个字符串转换为小写并返回

//以下的方法支持正则表达式，可以直接传入RegExp对象
str.split(",");             //根据参数(字符串)拆分字符串，返回字符串数组
str.search(/ a[bef]c / );   //搜索字符串中是否含有指定内容，有则返回第一次出现的索引，没有则返回-1
str.match(/ [a - z] / ig);  //从一个字符串中将符合条件的内容提取出来，封装到一个数组中返回
                            //默认情况下只会找到第一个符合要求的内容，找到以后就停止检索
                            //我们可以设置正则表达式为全局匹配模式，这样就会匹配到所有的内容
str.replace(/ [a - z] / gi, "@_@"); //将字符串中指定内容替换为新的内容，默认只会替换第一个，但是可以设置全局匹配替换全部



/*************************/RegExp对象/***************************************************************************/
//匹配模式
i：忽略大小写
g：全局匹配模式
ig：忽略大小写且全局匹配模式
m：执行多行匹配

可以为一个正则表达式设置多个匹配模式，且顺序无所谓


//使用对象创建
var 变量名 = new RegExp("正则表达式", "匹配模式");

这个正则表达式可以来检查一个字符串中是否含有ab：
var reg = new RegExp("ab", "i");
var str = "Abc";
var result = reg.test(str);
console.log(result);            //true


//使用字面量创建
var 变量名 = /正则表达式/匹配模式;

这个正则表达式可以来检查一个字符串中是否含有a
var reg = /a/i;
var str = "Abc";
var result = reg.test(str);
console.log(result);            //true


