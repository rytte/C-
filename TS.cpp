/*************************/TS/***************************************************************************/
JavaScript(JS) 是一种 动态类型语言（Dynamic Typed Language），变量的类型是在运行时决定的
TypeScript(TS) 是一种 静态类型语言（Statically Typed Language），类型的检查发生在编译时，而不是运行时。


//安装TS编译器
npm i - g  typescript		//i，即install。-g，即global。全局安装
tsc - v						//查看是否安装成功


//类型注解
即给变量添加类型约束，可以显示标记出代码中的意外行为，从而降低了发生错误的可能性
let 变量名 : 类型 = 初始值
let age : number = 18


//ts 的类型
ts 的常用基础类型分为两种： js 已有类型
原始类型：number / string / boolean / null / undefined / symbol
对象类型：object（包括，数组、对象、函数等对象）

ts 新增类型
* 联合类型
* 自定义类型(类型别名)
* 接口
* 元组
* 字面量类型
* 枚举
* void
* any
* 等等


//类型推导
有些情况下 TS 的类型推导机制会自动提供类型
1、声明变量并初始化时		let a = 1;	//number类型
2、决定函数返回值时		已知函数的两个参数都是number类型，那么该函数的返回值也是 number 类型。


//联合类型（即变量同时含多种类型）
let 变量 : 类型1 | 类型2 | 类型3 .... = 初始值
let arr1 : number | string = 1 // 可以写两个类型 


//类型别名（通常首字母大写）
type 别名 = 类型

type NewType = string | number

let a : NewType = 1
let b : NewType = '1'


//数组类型
let 变量 : 类型[] = [值1，...]
let numbers : number[] = [1, 3, 5]			//numbers必须是数组，每个元素都必须是数字

let 变量 : Array<类型> = [值1，...]
let strings : Array<string> = ['a', 'b', 'c']	//strings必须是数组，每个元素都必须是字符串 


//函数
函数涉及的类型实际上指的是：函数参数和返回值的类型


//定义单个函数
function 函数名(形参1： 类型 = 默认值， 形参2：类型 = 默认值, ...) : 返回值类型{ }   // 普通函数
function add(num1 : number, num2 : number) : number
{
    return num1 + num2
}

const 函数名（形参1： 类型 = 默认值， 形参2：类型 = 默认值, ...):返回值类型 = > { }   // 箭头函数
const add2 = (a: number = 100, b : number = 100) : number = > 
{
    return a + b
}

add（1, '1') // 报错


//统一定义函数格式
当函数的类型一致时，写多个就会显得代码冗余，所以需要统一定义函数的格式，如下所示：
const add2 = (a: number = 100, b : number = 100) : number = > 
{
    return a + b
}
function add1(a: number = 100, b : number = 200) : number
{
    return a + b
}

type Fn = (n1 : number, n2 : number) = > number // add1 和 add2 的参数类型和返回值一致，那么就可以统一定义一个函数类型
const add3 : Fn = (a, b) = > {return a + b }


//函数返回值类型void
在 ts 中，如果一个函数没有返回值，应该使用 void 类型

function greet(name: string) : void 
{
    console.log('Hello', name)  
}

返回 void 有以下几种情况：
1、没写 return
2、只写 return ，无具体的返回值
3、 return undefined


//函数可选参数
使用函数实现某个功能时，参数可以传也可以不传。
例如：数组的 slice 方法，可以 slice() 也可以 slice(1) 还可以 slice(1, 3) 那么就可以定义可选参数
语法：在可选参数名的后面添加 ? （问号）
function slice(a ? : number, b ? : number)      // 注意：可选参数只能在 必须参数的后面
{
    console.log(111);
}
slice()
slice(1)
slice(1, 2)


//对象类型 - 单独使用
格式： 方法有两种写法： 普通函数 和 箭头函数
const 对象名 : 
{
    属性名1：类型1，
        属性名2 ? ：类型2，
        方法名1(形参1 : 类型1，形参2 : 类型2)： 返回值类型,
        方法名2 : (形参1 : 类型1，形参2 : 类型2) = > 返回值类型
} = { 属性名1: 值1，属性名2：值2 }


//对象类型 - 类型别名
type Person = 
{
    name: string，
    age : number
    sayHi() : void
}

let person : Person =       // 使用类型别名作为对象的类型
{
    name: '小花',
    age : 18
    sayHi() {}
}


//接口
当一个对象类型被多次使用时，有如下两种方式来来描述对象的类型，以达到复用的目的

1、类型别名，type
2、接口，interface

interface 接口名 { 属性1: 类型1, 属性2 : 类型2 }
interface IGoodItem             // 接口名称推荐以 `I` 开头
{
    name: string, 
    price : number, 
    func : () = > string
}

const good1 : IGoodItem = {     // 声明接口后，直接使用接口名称作为变量的类型
    name: '手表',
    price : 200,
    func : function() 
    {
        return '看时间'
    }
}
const good2 : IGoodItem = {
    name: '手机',
    price : 2000,
    func : function() {
        return '打电话'
    }
}


//interface（接口）和 type（类型别名）的对比
相同点：都可以给对象指定类型
不同点 :
1、接口，只能为对象指定类型。它可以继承。
2、类型别名，不仅可以为对象指定类型，实际上可以为任意类型指定别名
3、先有的 interface，后有的 type, 推荐使用 type


//接口继承（extends关键字）
如果两个接口之间有相同的属性或方法，可以将公共的属性或方法抽离出来，通过继承来实现复用

interface 接口2 extends 接口1 
{
    属性1：类型1， // 接口2中特有的类型 
}

interface a { x: number; y: number }
interface b extends a 
{
    z: number
}


//元组
元组是一种特殊的数组。有两点特殊之处，符号[]

1、它约定了的元素个数
2、它约定了特定索引对应的数据类型

举个例子： 就拿 react 里面的 useState来举例：
function useState(n: number) : [number, (number) = > void] 
{
    const setN = (n1) = > 
    {
        n = n1
    }
    return[n, setN]
}

const [num, setNum] = useState(10)


//字面量类型
let str1 = 'hello TS'           //String类型
const str2 = 'hello TS'         //hello TS类型

用法：字面量类型一般是配合联合类型一起使用的， 用来表示一组明确的可选值列表（类似枚举），如下：

type Gender = 'girl' | 'boy'    // 声明一个类型，他的值 是 'girl' 或者是 'boy'
let g1 : Gender = 'girl' // 正确
let g2 : Gender = 'boy'  // 正确
let g3 : Gender = 'man'  // 错误 


//枚举（enum）
enum 枚举名 { 可取值1, 可取值2, .. }
枚举名.可取值

enum Dir { up, down, left, right }  //默认为数值类型
Dir.up
Dir.left

enum Direction      //字符串枚举，没有值，也没有自增长行为，因此，字符串枚举的每个成员必须有初始值
{
    Up = 'UP',
    Down = 'DOWN',
    Left = 'LEFT',
    Right = 'RIGHT'
}


//any 类型
不推荐使用，这会让 TypeScript 变为 “AnyScript”(失去 TS 类型保护的优势)
any : 任意的。当类型设置为 any 时，就取消了类型的限制。 例如：

let obj : any = { x: 0 }
obj.bar = 100
obj()

const n : number = obj      // obj 可以是任意类型

使用any的场景
1、函数就是不挑类型。 例如，console.log() ； 定义一个函数，输入任意类型的数据，返回该数据类型
2、临时使用 any 来"避免"书写很长、很复杂的类型

还有一种隐式 any，有下面两种情况会触发
1、声明变量不提供类型也不提供默认值
2、定义函数时，参数不给类型

