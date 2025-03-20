/*************************/ECMAScript6新特性/***************************************************************************/
//let 关键字
let 关键字用来声明变量，可以取代 var 关键字。

let 声明的变量的特点：
1、不允许重复声明
2、块级作用域
3、不存在变量提升
4、不影响作用域链


//let和var对比
重复声明
var：同一个作用域中可以多次声明同一个变量，不会抛出错误。
let：同一个作用域中不允许重复声明同一个变量。如果在同一个块级作用域内再次声明 let 变量，将抛出 SyntaxError。

作用域差异（Scope）
var：函数作用域，也就是说，变量会在当前函数内有效，或者如果是在函数外部声明，则是全局作用域。
这意味着如果你在一个块级结构（例如 if 语句或 for 循环）中使用 var，它仍然会在外部函数或全局范围内可见。
let：块级作用域，也就是说，变量仅在其声明所在的{} 块内有效。这个特性使得 let 在处理多层嵌套的代码时更加安全和直观。

变量提升（Hoisting）
var：声明的变量会被提升到函数顶部（或全局作用域顶部），但是初始化的值不会被提升。也就是说，如果你在声明之前访问 var 变量，值会是 undefined。
let：虽然 let 也会进行变量提升，但 不会初始化。如果你尝试在声明之前访问 let 变量，JavaScript 会抛出 ReferenceError 错误。

全局对象的属性（浏览器环境）
var：如果你在全局作用域使用 var 声明变量，这个变量会被添加为全局对象的一个属性（在浏览器中是 window 对象的属性）。
let：如果你在全局作用域使用 let 声明变量，它不会成为全局对象的属性。

死区（Temporal Dead Zone）
let 引入了一个概念叫做 死区（Temporal Dead Zone，TDZ）。在 let 变量声明之前，如果访问它，就会抛出 ReferenceError 错误。这个问题在 var 中是不存在的。


//const 关键字
const 关键字用来声明常量，const 声明有以下特点：

1、不允许重复声明
2、块级作用域
3、声明必须赋初始值
4、值不允许修改
5、标识符一般为大写


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


//简化对象写法
对象字面量的简化写法，当对象的属性名和变量名相同时，可以省略键值对。

const name = 'Alice';
const age = 25;
const person = { name, age };
console.log(person); // 输出: { name: 'Alice', age: 25 }


//箭头函数
箭头函数是一种更简洁的函数写法，使用 = > 定义，不绑定自己的 this。

const add = (a, b) = > a + b;
console.log(add(2, 3)); // 输出: 5


//rest 参数(...)
Rest 参数用于接收函数多余的参数并将它们存放在一个数组中。

function sum(...nums) {
    return nums.reduce((acc, num) = > acc + num, 0);
}
console.log(sum(1, 2, 3, 4)); // 输出: 10


//spread 扩展运算符(...)
扩展运算符（Spread Operator）将数组或对象展开。

const arr = [1, 2, 3];
const newArr = [...arr, 4, 5];
console.log(newArr); // 输出: [1, 2, 3, 4, 5]

const obj = { a: 1, b : 2 };
const newObj = { ...obj, c: 3 };
console.log(newObj); // 输出: { a: 1, b: 2, c: 3 }


//Symbol 类型
Symbol 是一种基本数据类型，创建独一无二的值，常用于对象属性名以避免冲突。

const sym = Symbol('description');
const obj = { [sym] : 'value' };
console.log(obj[sym]); // 输出: value


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


//Promise
Promise 用于异步编程，表示一个异步操作的最终结果。

const promise = new Promise((resolve, reject) = > {
    setTimeout(() = > resolve('Done!'), 1000);
});
promise.then(result = > console.log(result)); // 输出: Done!


//Set
Set 是一种集合数据结构，存储值的同时保证值的唯一性。

const set = new Set([1, 2, 2, 3]);
console.log(set); // 输出: Set { 1, 2, 3 }


//Map
Map 是一种键值对集合，键可以是任意类型。

const map = new Map();
map.set('key', 'value');
console.log(map.get('key')); // 输出: value


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


//数值扩展
新增了一些有用的数学方法，如 Number.isNaN、Number.isInteger 等。

console.log(Number.isNaN(NaN)); // 输出: true
console.log(Number.isInteger(4.5)); // 输出: false


//对象扩展
新增了一些对象操作的方法，如 Object.assign、Object.entries 等。

const target = { a: 1 };
const source = { b: 2 };
Object.assign(target, source);
console.log(target); // 输出: { a: 1, b: 2 }


//模块化
使用 import 和 export 实现模块化，便于代码分离和复用。

【math.js】
export function add(a, b) 
{
    return a + b;
}

【main.js】
import { add } from './math.js';
console.log(add(2, 3)); // 输出: 5


//浅拷贝和深拷贝
浅拷贝只拷贝对象的第一层，深拷贝会递归拷贝所有层级的对象。浅拷贝常用 Object.assign 或扩展运算符。

const obj = { a: 1, b : { c: 2 } };
const shallowCopy = { ...obj }; // 浅拷贝
深拷贝需要手动实现或使用库（如 Lodash）。



