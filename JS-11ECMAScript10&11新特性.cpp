/*************************/ECMAScript10新特性/***************************************************************************/
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



/*************************/ECMAScript11新特性/***************************************************************************/
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


