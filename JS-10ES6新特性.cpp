/********************/ES6新特性/************************************************************/
1、let关键字
2、const关键字
3、解构赋值
4、模板字符串
5、简化对象写法
6、箭头函数
7、rest 参数(...)
8、spread 扩展运算符(...)
9、Symbol 类型
10、迭代器
11、生成器
12、Promise
13、Set
14、Map
15、Class 类
16、数值扩展
17、对象扩展
18、模块化
19、深拷贝和浅拷贝


/************************************************************/
//let 关键字
let 关键字用来声明变量，可以取代 var 关键字。

let 声明的变量的特点：
1、不允许重复声明
2、块级作用域
3、不存在变量提升（变量提升，即将声明自动提升到作用域顶部）
4、不影响作用域链


//let和var对比
特性	            var	                        let
作用域	        函数作用域（整个函数内有效）  块作用域（当前{}块内有效）
变量提升	        提升并初始化为 undefined	    提升但不初始化（存在暂时性死区，访问会抛出 ReferenceError 错误）
允许重复声明	    ✅ 可以	                    ❌ 不可以（重复声明将抛出SyntaxError）
绑定 window	    ✅ 是	                    ❌ 否
循环作用域	    共享一个作用域	            每次迭代创建新的作用域

全局对象的属性（浏览器环境）
var：在全局作用域声明 var 变量，该变量会被添加为全局对象的一个属性（在浏览器中是 window 对象的属性）。
let：在全局作用域声明 let 变量，它不会成为全局对象的属性。


//const 关键字
const 关键字用来声明常量，const 声明有以下特点：

1、不允许重复声明
2、块级作用域
3、声明必须赋初始值
4、值不允许修改
5、标识符一般为大写


/************************************************************/
//变量的解构赋值
ES6 允许按照一定模式，从数组和对象中提取值，对变量进行赋值，这被称为解构赋值。
注意：频繁使用对象方法、数组元素，就可以使用解构赋值形式

/*数组的解构赋值*/
const arr = ["张学友", "刘德华", "黎明", "郭富城"];
let[zhang, liu, li, guo] = arr;
console.log(zhang);			//张学友
console.log(liu);			//刘德华
console.log(li);			//黎明
console.log(guo);			//郭富城

/*对象的解构赋值*/
const lin = {
    name: "林志颖",
    tags : ["车手", "歌手", "小旋风", "演员"]
};
let{ name, tags } = lin;
console.log(name);          //林志颖
console.log(tags);          //["车手", "歌手", "小旋风", "演员"]


/************************************************************/
//模板字符串
模板字符串（Template Literals）是一种定义字符串的新方式，用反引号(``) 包裹，可以轻松地嵌入变量和表达式。
${变量名} 可以引用变量。

const name = 'Alice';
const greeting = `Hello, ${ name }!`;
console.log(greeting); // 输出: Hello, Alice!

支持多行字符串：
const text = `这是
多行
字符串`;
console.log(text);


/************************************************************/
//简化对象写法
对象字面量的简化写法，当对象的属性名和变量名相同时，可以省略键值对。

const name = 'Alice';
const age = 25;
const person = { name, age };
console.log(person); // 输出: { name: 'Alice', age: 25 }


/************************************************************/
//箭头函数
箭头函数是一种更简洁的函数写法，使用 = > 定义。

箭头函数中的 this 取决于它定义时的作用域，而不是调用时的对象。在类成员函数作回调函数时通常需要定义为箭头函数。

const add = (a, b) = > a + b;
console.log(add(2, 3)); // 输出: 5

//无arguments
箭头函数：没有 arguments，只能用 ...rest
const arrowFunc = (...args) = > {
    console.log(args); // [1, 2, 3]
};
arrowFunc(1, 2, 3);

//对比
特性	            箭头函数(= > )	            普通函数(function)
this 绑定	    继承外层作用域的 this	        取决于调用方式
arguments	    无（使用 ...rest 代替）	    有
new 关键字	    ❌ 不能用作构造函数	        ✅ 可作为构造函数
prototype	    ❌ 没有	                    ✅ 具有
作为对象方法	    ❌ this 指向外层作用域	    ✅ this 指向调用者
回调函数	        适用于 setTimeout、map 等	可能需要.bind(this)
适用场景	        小型回调、保持 this 绑定	    方法、构造函数、复杂逻辑


/************************************************************/
//rest 参数(...)
Rest 参数用于接收函数多余的参数并将它们存放在一个数组中。

function sum(...nums) {
    return nums.reduce((acc, num) = > acc + num, 0);
}
console.log(sum(1, 2, 3, 4)); // 输出: 10


/************************************************************/
//spread 扩展运算符(...)
扩展运算符（Spread Operator）将数组或对象展开。

const arr = [1, 2, 3];
const newArr = [...arr, 4, 5];
console.log(newArr); // 输出: [1, 2, 3, 4, 5]

const obj = { a: 1, b : 2 };
const newObj = { ...obj, c: 3 };
console.log(newObj); // 输出: { a: 1, b: 2, c: 3 }


/************************************************************/
//Symbol 类型
Symbol 是一种基本数据类型，创建独一无二的值，常用于对象属性名以避免冲突。

const sym = Symbol('description');
const obj = { [sym] : 'value' };
console.log(obj[sym]); // 输出: value


/************************************************************/
//迭代器
迭代器是一种接口，为对象提供按需访问其元素的方法，常与 for...of 循环配合使用。

const arr = [1, 2, 3];
const iterator = arr[Symbol.iterator]();
console.log(iterator.next()); // { value: 1, done: false }


//生成器
生成器（Generator）是可以暂停和恢复执行的特殊函数，用 function * 定义。

function * generate() {
    yield 1;
    yield 2;
    yield 3;
}
const gen = generate();
console.log(gen.next()); // { value: 1, done: false }


/************************************************************/
//Promise
Promise 用于异步编程，表示一个异步操作的最终结果。

const promise = new Promise((resolve, reject) = > {
    setTimeout(() = > resolve('Done!'), 1000);
});
promise.then(result = > console.log(result)); // 输出: Done!


/************************************************************/
//Set
Set 是一种集合数据结构，存储值的同时保证值的唯一性。

const set = new Set([1, 2, 2, 3]);
console.log(set); // 输出: Set { 1, 2, 3 }


/************************************************************/
//Map
Map 是一种键值对集合，键可以是任意类型。

const map = new Map();
map.set('key', 'value');
console.log(map.get('key')); // 输出: value

//特点
1、基于哈希表（Hash Table）
2、有序性，Map 保持键值对的插入顺序
3、性能优化（内部可能采用 数组 + 哈希表 的混合结构进行优化）

//Map vs Object
特性	        Map	                            Object
键的类型	    任意类型（对象、数组、基本类型）	只能是字符串和 Symbol
迭代顺序	    按插入顺序	                    数字键按升序，其它键按插入顺序
性能	        适合大规模数据存储，查找快	        适用于少量键值对的存储
适用场景	    需要高效查找、大量动态键	        作为数据结构的基类


/************************************************************/
//class 类
class 是创建对象的语法糖，本质上是 prototype 的语法封装。

class Person 
{
    constructor(name) 
    {
        this.name = name;
    }
    greet() 
    {
        console.log(`Hello, ${ this.name }`);
    }
}
const person = new Person('Alice');
person.greet(); // 输出: Hello, Alice

class Xiaoming extends Person {       // extends 关键字进行类继承
    constructor(name) {
        super(name);                // super() 调用父类构造
    }
    greet()
    {
        super.greet();              // super.方法名 调用父类方法
        super.name = "xiaoming"     // super.变量名 调用父类属性
    }
};   


/************************************************************/
//数值扩展
新增了一些有用的数学方法，如 Number.isNaN、Number.isInteger 等。

console.log(Number.isNaN(NaN)); // 输出: true
console.log(Number.isInteger(4.5)); // 输出: false


/************************************************************/
//对象扩展
新增了一些对象操作的方法，如 Object.assign、Object.entries 等。

const target = { a: 1 };
const source = { b: 2 };
Object.assign(target, source);
console.log(target); // 输出: { a: 1, b: 2 }


/************************************************************/
//模块化
使用 import 和 export 实现模块化，便于代码分离和复用。

1、启用 ES6 模块系统，支持 import 和 export 语法。
2、自动启用严格模式(use strict)，即使代码中没有显式写 use strict; 。
3、支持异步加载，不会阻塞 HTML 解析（相当于 defer）。
4、避免变量污染全局作用域，每个 module 代码都是独立作用域。

//js文件中
【math.js】
export function add(a, b) 
{
    return a + b;
}

【main.js】
import { add } from './math.js';
console.log(add(2, 3)); // 输出: 5


//HTML文件中
【index.html】
<script type = "module">
import { sayHello } from './utils.js';
sayHello();
</script>

【utils.js】
export function sayHello() {
    console.log('Hello, ES Module!');
}


/************************************************************/
//浅拷贝和深拷贝
浅拷贝只拷贝对象的第一层，深拷贝会递归拷贝所有层级的对象。
浅拷贝常用 Object.assign 或扩展运算符。深拷贝需要手动实现或使用库（如 Lodash）。

//使用Object.assign
const obj1 = { a: 1, b : { c: 2 } };
const obj2 = Object.assign({}, obj1);

//使用扩展运算符
const obj = { a: 1, b: { c: 2 } };
const shallowCopy = { ...obj }; // 浅拷贝

//方法对比
方法	                            类型	        适用场景	                                    备注
Object.assign()	                浅拷贝	    复制对象，但不拷贝嵌套对象	                    仍然是引用传递
... 扩展运算符	                浅拷贝	    复制对象和数组	                            仍然是引用传递
JSON.parse(JSON.stringify(obj))	深拷贝	    适用于简单数据（无函数、undefined、Symbol）	丢失 Date、RegExp、function
structuredClone() (ES2021)	    深拷贝	    适用于 Date、ArrayBuffer 等	                不支持函数和 Symbol
_.cloneDeep()（Lodash）	        深拷贝	    最完整的深拷贝	                            推荐



