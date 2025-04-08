/********************/ES10新特性/************************************************************/
//对象方法拓展
Object.fromEntries()		//将一个键值对数组转为对象，是Object.entries()的逆操作。

//字符串方法拓展
let str = "   iloveyou   ";
console.log(str.trimStart());	//只去除前边的空格
console.log(str.trimEnd());		//只去除后边的空格

//数组方法拓展
flat() 方法会按照一个可指定的层数递归遍历数组，并将所有元素与遍历到的子数组中的元素合并为一个新数组返回
参数：展开层数，默认为1
const arr = [1, 2, 3, 4, [5, 6, [7, 8, 9]]];
console.log(arr.flat());			//[1, 2, 3, 4, 5, 6, Array(3)]

flatMap() 方法首先使用映射函数映射每个元素，然后将结果压缩成一个新数组。它与 map 连着层数为1的 flat 几乎相同，但 flatMap 通常在合并成一种方法的效率稍微高一些。
var arr1 = [1, 2, 3, 4];
console.log(arr1.map(x = > x * 2));			//[2, 4, 6, 8]
var arr2 = [1, 2, 3, 4];
console.log(arr2.flatMap(x = > x * 2));		//[2, 4, 6, 8]

//Symbol属性拓展
Symbol.prototype.description用来读取Symbol的描述值

let s = Symbol("张三");
console.log(s.description);		//张三



/********************/ES11新特性/************************************************************/
//class 私有属性
私有属性只能在class中访问

class Person {
    //公有属性
    name;
    //私有属性
    #age;
    #weight;

    //构造方法
    constructor(name, age, weight) {
        this.name = name;
        this.#age = age;
        this.#weight = weight;
    }

    //普通方法
    intro() {
        console.log(this.name);
        console.log(this.#age);
        console.log(this.#weight);
    }
}

const girl = new Person("小可爱", 18, "45kg");     //实例化
girl.intro();


//Promise.allSettled
该Promise.allSettled()方法返回一个在所有给定的promise都已经fulfilled或rejected后的promise，
并带有一个对象数组，每个对象表示对应的promise结果。
当您有多个彼此不依赖的异步任务成功完成时，或者您总是想知道每个promise的结果时，通常使用它。

相比之下，Promise.all() 更适合彼此相互依赖或者在其中任何一个reject时立即结束。


//字符串方法扩展
String.prototype.matchAll()     //返回一个包含所有匹配正则表达式的结果及分组捕获组的迭代器。


//可选链操作符
当我们要使用传进来的一个属性值的时候，我们不知道这个属性值到底有没有传，
我们可以使用&& 运算符一级一级判断，就像这样 const dbHost = config && config.db && config.db.host; 
但是这样会显得很麻烦，所以在ES11 中就提供了可选链操作符，它就简化了代码，
变成了这样 const dbHost = config ? .db ? .host; 
另一方面，即使用户没有传入这个属性，我们用了也不会报错，而是undefined


//动态 import
以前我们import 导入模块是在一开始的时候就全部导入了，这样在模块很多的时候，会显得网页速度加载很慢，在ES11中提供了动态import。

动态导入的特点
1、按需加载：模块只有在需要时才会加载，优化了性能，尤其适合大型项目。
2、返回一个 Promise：动态导入是异步的，可以使用.then 或 await 获取模块内容。
3、模块路径可以动态计算：与 import 静态导入不同，动态导入允许路径在运行时确定。
4、与 Tree Shaking 兼容：动态导入不会破坏 Tree Shaking。


//BigInt类型
BigInt数据类型的目的是比Number数据类型支持的范围更大的整数值。
可以安全地使用更加准确时间戳，大整数ID等，而无需使用变通方法。 
它就是JS 第二个数字数据类型，也将是 JS 第8种基本数据类型。

let n = 521n;       //BigInt字面量：在数字的后边加上一个n


//globalThis
全局属性 globalThis 包含全局的 this 值(window)，类似于全局对象（global object）。
console.log(globalThis);



/********************/ES12新特性/************************************************************/

//String.prototype.replaceAll()
String.prototype.replace() 只能替换第一个匹配项，若要替换所有匹配项，需要使用正则表达式的全局模式 / g。
replaceAll() 允许直接替换字符串中所有匹配的子字符串。

let str = "hello world, hello JavaScript";
console.log(str.replaceAll("hello", "Hi"));     // 输出: "Hi world, Hi JavaScript"


//Promise.any()
Promise.any() 只要有一个 Promise 成功（fulfilled），它就会返回这个成功的值，而忽略其他失败的 Promise。
如果所有 Promise 都失败，则返回 AggregateError 错误。

let p1 = Promise.reject("Error 1");
let p2 = new Promise((resolve) = > setTimeout(resolve, 100, "Success"));
let p3 = Promise.reject("Error 3");

Promise.any([p1, p2, p3])
.then(console.log) // 输出: "Success"
.catch (console.error);


//WeakRef（弱引用）
WeakRef 允许创建对对象的弱引用，垃圾回收（GC）不会因为 WeakRef 存在而保留对象。适用于缓存等场景，但需谨慎使用。

let obj = { name: "John" };
let weakRef = new WeakRef(obj);

console.log(weakRef.deref() ? .name); // 可能输出 "John"，但如果 `obj` 被垃圾回收了，则输出 `undefined`


//逻辑赋值运算符
ES12 增加了 "&&=", "||=", "??=" 三种逻辑赋值运算符，使代码更简洁。

let a = null;
a || = "default"; // 如果 a 为 falsy，则赋值
console.log(a); // 输出 "default"

let b = 10;
b &&= 20; // 只有 b 为 truthy 时才赋值
console.log(b); // 输出 20

let c = null;
c ? ? = "fallback"; // 只有 c 为 null 或 undefined 时才赋值
console.log(c); // 输出 "fallback"


//私有字段的 # 修饰符（已完善）
之前 # 作为私有字段在 ES10 / ES11 已经引入，ES12 进一步完善了其行为。
# 开头的字段只能在类的内部访问，外部访问会报错。

class Person {
    #name;
    constructor(name) {
        this.#name = name;
    }
    getName() {
        return this.#name;
    }
}

let p = new Person("Alice");
console.log(p.getName()); // 输出 "Alice"
console.log(p.#name); // 语法错误，无法访问私有字段


//Object.hasOwn()
Object.hasOwn() 是 Object.prototype.hasOwnProperty() 的更安全替代方法。
避免了 hasOwnProperty 可能被对象本身覆盖的问题。

let obj = { key: "value" };
console.log(Object.hasOwn(obj, "key")); // true
console.log(Object.hasOwn(obj, "other")); // false


