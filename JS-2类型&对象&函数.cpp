/*************************/数据类型和运算符/***************************************************************************/

变量等命名规则：驼峰命名法


//关键字或运算符
var		定义变量
typeof  获取变量类型


//基本数据类型的关键字
String		字符串型
Number		数值型
Boolean		布尔型
Undefined	undefined型
Null		null型
Object		对象类型（不属于基本数据类型）


//Number说明
可以表示整型或浮点型
最大值： + 1.7976931348623157e+308
最小值： - 1.7976931348623157e+308
0以上的最小值：5e - 324
如果超过了这个范围，则会返回 ±Infinity

Infinity：正无穷
- Infinity：负无穷
NaN：非法数字（Not A Number）

二进制：0b 开头表示二进制，但是，并不是所有的浏览器都支持
八进制：0 开头表示八进制
十六进制：0x 开头表示十六进制

let bigIntger : BigInt = BigInt('999999999999999999999999999999999999999999');  //BigInt表示大整数防止精度丢失


//Undefined说明
1、Undefined 类型只有一个值，即 undefined
2、在使用 var 声明变量但未对其加以初始化时，这个变量的值就是 undefined。
3、使用 typeof 对没有初始化和没有声明的变量，会返回"undefined"。


//Null说明
1、Null 类型只有一个值，即 null。
2、undefined值实际上是由null值衍生出来的，所以如果比较undefined和null是否相等，会返回true。
3、从语义上看null表示的是一个空的对象，所以使用typeof检查null会返回一个Object。


//类型转换：转换为String类型
1、数据.toString()
2、String(数据)
3、数据 + ""


//类型转换：转换为Number类型
1、数据.toNumber()
纯数字的字符串，则直接将其转换为数字
字符串中有非数字的内容，则转换为NaN
字符串是一个空串或者是一个全是空格的字符串，则转换为0
true 转成 1
false 转成 0
null 转成 0
undefined 转成 NaN
2、parseInt(数据);		// 将字符串转换为整数
3、parseFloat(数据);		// 将字符串转换为浮点数


//类型转换：转换为Boolean类型
只能使用 Boolean() 函数

数字：除了0和NaN，其余的都是true
字符串：除了空串，其余的都是true
null和undefined：转换为false
Object：转换为true


//比较运算符
== 和 != ：相等/不相等运算，如果两个值类型不同，会自动转换为相同的类型，然后再比较
===和!== ：全等/不全等运算，如果两个值不相等或者类型不同，直接返回false


//引用数据类型
对象（Object）
数组（Array）
函数（Function）
日期（Date）
正则表达式（RegExp）
Map 和 Set（ES6 引入的集合类型）


//引用类型与基本类型的区别
特性        引用类型	                        基本类型
存储空间     堆内存                          栈内存
存储内容	    存储的是内存地址（引用）	        存储的是数据本身（值）
赋值行为	    赋值会共享同一个引用	            赋值会创建一个新的副本
比较  	    比较的是内存地址（引用是否相同）	比较的是值是否相同
可变性	    可变（对象的内容可以被修改）	    不可变（值一旦赋值不可修改）



/*************************/函数/***************************************************************************/
//函数创建：方式一
var fun = new Function("执行语句");

//函数创建：方式二
function 函数名(形参列表)
{
    执行语句
}

//函数创建：方式三（创建匿名函数，以变量接收作为函数名使用）
var 变量 = function(形参列表)
{
    执行语句
}


//函数返回值
1、函数中不写 return ，则会返回 undefined
2、 return 语句后不跟任何值时也是返回 undefined


//嵌套函数
在函数中声明的函数就是嵌套函数，嵌套函数只能在当前函数中可以访问，在当前函数外无法访问。
function fu() 
{
    function zi() 
    {
        console.log("我是儿子")
    }

    zi();
}


//立即执行函数
函数定义完，立即被调用，这种函数叫做立即执行函数。立即执行函数往往只会执行一次。
(function() {
    alert("我是一个匿名函数");
})();



/*************************/对象/***************************************************************************/
Object是对象类型，JavaScript中除了基本类型以外的值都是对象

//创建对象：方式一
var person = new Object();
person.name = "孙悟空";
person.age = 18;
console.log(person);

//创建对象：方式二
var person = {
    name: "孙悟空",
    age : 18,
    sayHello : function()
    {
        console.log(name + " hello")
    }
};
console.log(person);

//访问属性
方式1：对象.属性名
方式2：对象[属性名]

//删除属性
delete 对象.属性名

//遍历对象
for (var 变量 in 对象) {

}

//this对象
1、 this 在函数中永远都是window
2、 this 在方法中就是调用方法的那个对象
3、 this 在构造函数中就是新创建的那个对象
4、 this 在使用call和apply调用时，是传入的那个对象


//检查一个对象是否是一个类的实例
对象 instanceof 构造函数        //返回 true 或 false


//使用in判断对象及其原型中是否含有某个属性
function MyClass() { 
}

MyClass.prototype.name = "我是原型中的名字";

var mc = new MyClass();
mc.age = 18;

console.log("age" in mc);   //ture
console.log("name" in mc);  //true


//使用Object的hasOwnProperty()方法，可以检查自身对象是否含有某个非继承的方法或属性
console.log(mc.hasOwnProperty("age"));


//垃圾回收
JS中拥有自动的垃圾回收机制，会自动将这些垃圾对象从内存中销毁，我们只需要将不再使用的对象设置null即可。
person = null;



/*************************/对象进阶/***************************************************************************/
//工厂模式创建对象
function createPerson(name, age) 
{
    var obj = new Object();
    // 设置对象属性和方法
    obj.name = name;
    obj.age = age;
    obj.sayName = function() 
    {
        console.log(this.name);
    };

    return obj;         //返回创建的对象
}

var person1 = createPerson("孙悟空", 18);
var person2 = createPerson("猪八戒", 19);
var person3 = createPerson("沙和尚", 20);

console.log(person1);
console.log(person2);
console.log(person3);



//构造函数创建对象
function Person(name, age) 
{
    // 设置对象的属性和方法
    this.name = name;
    this.age = age;
    this.sayName = sayName;     // 抽取方法为全局函数，防止创建多个同样的函数对象浪费内存
}

function sayName() 
{
    console.log(this.name);
}

var person1 = new Person("孙悟空", 18);
var person2 = new Person("猪八戒", 19);
var person3 = new Person("沙和尚", 20);

console.log(person1);
console.log(person2);
console.log(person3);



//对象外定义方法，且不污染全局作用域：在Person类的原型（见下）对象中添加方法
function Person(name, age) {
    // 设置对象的属性
    this.name = name;
    this.age = age;
}

Person.prototype.sayName = function()       //无需在创建对象时再次声明
{         
    console.log(this.name);
};



//toString 方法
toString()函数用于将当前对象以字符串的形式返回。
该方法属于Object对象，由于所有的对象都"继承"了Object的对象实例，因此几乎所有的实例对象都可以使用该方法。
;{
    // 字符串
    var str = "Hello";
    console.log(str.toString());  // 输出 "Hello"

    // 数字
    var num = 15.26540;
    console.log(num.toString());  // 输出 "15.2654"

    // 布尔
    var bool = true;
    console.log(bool.toString());  // 输出 "true"

    // Object
    var obj = { name: "张三", age : 18 };
    console.log(obj.toString());  // 输出 "[object Object]"

    // 数组
    var array = ["CodePlayer", true, 12, -5];
    console.log(array.toString());  // 输出 "CodePlayer,true,12,-5"

    // 日期
    var date = new Date(2013, 7, 18, 23, 11, 59, 230);
    console.log(date.toString());  // 输出 "Sun Aug 18 2013 23:11:59 GMT+0800 (China Standard Time)"

    // 错误
    var error = new Error("自定义错误信息");
    console.log(error.toString());  // 输出 "Error: 自定义错误信息"

    // 函数
    console.log(Function.toString());  // 输出 "function Function() { [native code] }"
}


