/********************/内置类型/************************************************************/
在 JavaScript 中，可以使用 new 关键字实例化的内置类型（构造函数）包括以下几类：

1、基础对象：Object、Array、Function、RegExp、Date、Error
2、包装对象（不推荐）：String、Number、Boolean
3、类型化数组：ArrayBuffer、TypedArray（如 Int8Array）
4、集合：Map、Set、WeakMap、WeakSet
5、代理：Proxy
6、异步处理：Promise
7、国际化 API：Intl.DateTimeFormat 等


/************************************************************/
//1. 基础对象（Object 相关）
Object			创建一个普通对象
Array			创建数组
Function		创建函数对象（不推荐，通常使用函数声明或箭头函数）
RegExp			创建正则表达式对象
Date			创建日期对象
Error			创建错误对象（可派生，如 TypeError, ReferenceError 等）

//示例
const obj = new Object(); // 等同于 {}
const arr = new Array(1, 2, 3); // 等同于 [1, 2, 3]
const func = new Function("x", "return x * x"); // 不推荐
const regex = new RegExp("\\d+"); // 等同于 /\d+/
const date = new Date(); // 创建日期对象
const err = new Error("发生错误"); // 错误对象


/************************************************************/
//2. 原始值的包装对象（Primitive Wrapper Objects）
JavaScript 提供了一些包装类，用于封装原始类型的数据，但一般不推荐使用 new 关键字实例化它们：

String			字符串包装对象
Number			数字包装对象
Boolean			布尔值包装对象

//示例
const str = new String("hello");  // String {"hello"}
const num = new Number(123);      // Number {123}
const bool = new Boolean(true);   // Boolean {true}

console.log(typeof str);  // object（不推荐使用 new）
console.log(typeof num);  // object（不推荐使用 new）
console.log(typeof bool); // object（不推荐使用 new）

// 直接使用字面量更好
const str2 = "hello";  // 推荐
const num2 = 123;      // 推荐
const bool2 = true;    // 推荐

💡 注意： 使用 new String()、new Number()、new Boolean() 会创建对象，而不是原始值，所以不推荐。


/************************************************************/
//3. 类型化数组（TypedArray）
JavaScript 提供了一组 类型化数组（TypedArray），用于处理二进制数据（如 WebGL、音视频处理等）。

ArrayBuffer			创建固定大小的内存缓冲区
DataView			以任意格式读取 ArrayBuffer
Int8Array			8 位有符号整数数组
Uint8Array			8 位无符号整数数组
Uint8ClampedArray	8 位无符号整数数组（像素处理）
Int16Array			16 位有符号整数数组
Uint16Array			16 位无符号整数数组
Int32Array			32 位有符号整数数组
Uint32Array			32 位无符号整数数组
Float32Array		32 位浮点数数组
Float64Array		64 位浮点数数组

//示例
const buffer = new ArrayBuffer(16);  // 分配 16 字节
const view = new DataView(buffer);   // 视图操作
const intArray = new Int8Array([1, 2, 3]);  // 8 位整数数组
console.log(intArray[0]);  // 1


/************************************************************/
//4. 结构化数据（集合）
Map			    创建键值对映射（键可为任何类型）
WeakMap		    创建键为对象的映射（弱引用）
Set			    创建值唯一的集合
WeakSet		    创建存储对象的集合（弱引用）

//示例
const map = new Map();
map.set("key", "value");

const weakMap = new WeakMap();
const obj = {};
weakMap.set(obj, "private data"); // 只允许对象作为 key

const set = new Set([1, 2, 3, 3]);  // 自动去重
console.log(set.has(2));  // true

💡 适用于： 去重、缓存、私有数据存储等。


/************************************************************/
//5. 代理（Proxy & Reflect）
Proxy	        创建代理对象，拦截对象操作
Reflect	        提供对象操作的方法（不需要 new）

//Proxy示例
const target = { message: "hello" };
const handler = {
    get(obj, prop) {
        return prop in obj ? obj[prop] : "默认值";
    }
};
const proxy = new Proxy(target, handler);
console.log(proxy.message);  // "hello"
console.log(proxy.unknown);  // "默认值"

//Reflect示例
方法	                                    作用	                            等价操作
Reflect.get(target, prop)	            获取对象属性	                    target[prop]
Reflect.set(target, prop, value)	    设置对象属性	                    target[prop] = value
Reflect.has(target, prop)	            检查属性是否存在	                prop in target
Reflect.deleteProperty(target, prop)	删除属性	                        delete target[prop]
Reflect.ownKeys(target)	                获取对象所有的键（包括 Symbol）	Object.getOwnPropertyNames(target).concat(Object.getOwnPropertySymbols(target))
Reflect.defineProperty(target, prop, descriptor)	定义属性	            Object.defineProperty(target, prop, descriptor)
Reflect.getOwnPropertyDescriptor(target, prop)	    获取属性描述符	    Object.getOwnPropertyDescriptor(target, prop)
Reflect.isExtensible(target)	        判断对象是否可扩展	            Object.isExtensible(target)
Reflect.preventExtensions(target)	    禁止对象扩展	                    Object.preventExtensions(target)
Reflect.construct(target, args)	        相当于 new target(...args)	    new target(...args)
Reflect.apply(target, thisArg, args)	调用函数	                        target.apply(thisArg, args)

💡 适用于： 代理对象行为，如数据劫持（Vue 3 响应式原理）。


/************************************************************/
//6. Promise & 异步处理
Promise	            处理异步操作
GeneratorFunction	生成器函数（少用）
AsyncFunction	    异步函数（少用）

//示例
const promise = new Promise((resolve, reject) = > {
    setTimeout(() = > resolve("成功"), 1000);
});
promise.then(console.log);  // 1 秒后打印 "成功"


/************************************************************/
//7. 国际化 API
Intl.Collator	        比较字符串（本地化排序）
Intl.DateTimeFormat	    本地化日期格式化
Intl.NumberFormat	    本地化数字格式化

//示例
const dateFormatter = new Intl.DateTimeFormat("zh-CN", { dateStyle: "long" });
console.log(dateFormatter.format(new Date())); // "2025年3月25日"

const numberFormatter = new Intl.NumberFormat("en-US", { style: "currency", currency : "USD" });
console.log(numberFormatter.format(1234.56)); // "$1,234.56"


