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


//类继承（implements关键字）
implements关键字用于继承并实现接口。

            <extends>	                                        <implements>
用途	        用于类继承类和接口继承接口。	                        用于类实现接口。
继承关系	    子类继承父类的实现，或接口继承接口的定义。	            类需要实现接口定义的所有方法，不能只继承。
支持继承多个	一个类只能继承一个父类（单继承），但可以继承多个接口。	类可以实现多个接口。
方法实现	    子类继承父类的实现，可以重写父类的方法。	            类必须实现接口定义的所有方法，不可以只声明方法。


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


//函数签名重载（支持构造函数重载）
class C {
    foo(x: number) : void;            /* 第一个签名 */
    foo(x: string) : void;            /* 第二个签名 */
    foo(x: number | string) : void {  /* 实现签名 */
    }

    // 可见性修饰符
    public a : string = '';
    protected b: string = '';
    private getCount() : number {
        return 10
    }
}
let c = new C();
c.foo(123);     // OK，使用第一个签名
c.foo('aa');    // OK，使用第二个签名


//Record 定义一个字面量对象
type PersonAge = Record<'Tom' | 'Jerry' | 'Mickey', number>;

const ages : PersonAge = {
  Tom: 25,
  Jerry : 30,
  Mickey : 35,
};


//抽象类语法
抽象类不能被实例化，必须通过继承来使用。抽象方法没有实现，子类必须实现这些方法。
abstract class ClassName {
    abstract methodName() : void; // 抽象方法，没有实现，必须在子类中实现
    // 可以有非抽象方法
    regularMethod() {
        console.log("This is a regular method.");
    }
}



/*************************/泛型/***************************************************************************/

//泛型类与接口
class CustomStack<Element> {
    public push(e: Element) :void {
        // ...
    }
}

let s = new CustomStack<string>();
s.push('hello');


//约束
泛型类型的类型参数可以被限制只能取某些特定的值。例如，MyHashMap<Key, Value>这个类中的Key类型参数必须具有hash方法。

interface Hashable {
    hash() : number;
}
class MyHashMap<Key extends Hashable, Value> {
    public set(k: Key, v : Value) {
        let h = k.hash();
        // ...其他代码...
    }
}


//泛型函数
使用泛型函数可编写更通用的代码。比如返回数组最后一个元素的函数：
function last(x: number[]) : number{
  return x[x.length - 1];
}
last([1, 2, 3]); // 3

如果需要为任何数组定义相同的函数，使用类型参数将该函数定义为泛型：
function last<T>(x: T[]) : T{
  return x[x.length - 1];
}

在函数调用中，类型实参可以显式或隐式设置：

last<string>(['aa', 'bb']);     // 显式设置的类型实参
last<number>([1, 2, 3]);        // 显式设置的类型实参
last([1, 2, 3]);                // 隐式设置的类型实参。编译器根据调用参数的类型来确定类型实参


//泛型默认值
泛型类型的类型参数可以设置默认值。这样可以不指定实际的类型实参，而只使用泛型类型名称。下面的示例展示了类和函数的这一点。

class SomeType {}
interface Interface <T1 = SomeType> { }
class Base <T2 = SomeType> { }
class Derived1 extends Base implements Interface { }

class Derived2 extends Base<SomeType> implements Interface<SomeType> { }    // Derived1在语义上等价于Derived2

function foo<T = number>() : T {
    // ...
}
foo();
foo<number>();      // 此函数在语义上等价于上面的调用


//空安全
TypeScript有严格的空值检查模式，类型的值不能为空
let x : number = null;    // 编译时错误
let y : string = null;    // 编译时错误
let z : number[] = null;  // 编译时错误

可以为空值的变量定义为联合类型T | null。
let x : number | null = null;
x = 1;    // ok
x = null; // ok
if (x != null) { /* do something */ }


//非空断言运算符
后缀运算符!可用于断言其操作数为非空。
应用于可空类型的值时，它的编译时类型变为非空类型。例如，类型将从T | null更改为T：
class A {
value: number = 0;
}

function foo(a : A | null) {
    a.value;   // 编译时错误：无法访问可空值的属性
    a!.value;  // 编译通过，如果运行时a的值非空，可以访问到a的属性；如果运行时a的值为空，则发生运行时异常
}


//空值合并运算符
空值合并二元运算符 ? ? 用于检查左侧表达式的求值是否等于null或者undefined。如果是，则表达式的结果为右侧表达式；否则，结果为左侧表达式。

换句话说，a ? ? b等价于三元运算符(a != null && a != undefined) ? a : b。

在以下示例中，getNick方法如果设置了昵称，则返回昵称；否则，返回空字符串：

class Person {
    // ...
nick: string | null = null;
    getNick() : string{
      return this.nick ? ? '';
    }
}


//可选链
在访问对象属性时，如果该属性是undefined或者null，可选链运算符会返回undefined。

class Person {
nick: string | null = null;
    spouse ? : Person

        setSpouse(spouse : Person) : void {
        this.spouse = spouse;
    }

    getSpouseNick() : string | null | undefined{
      return this.spouse ? .nick;
    }

        constructor(nick : string) {
        this.nick = nick;
        this.spouse = undefined;
    }
}

说明：getSpouseNick的返回类型必须为string | null | undefined，因为该方法可能返回null或者undefined。

可选链可以任意长，可以包含任意数量的 ? .运算符。

在以下示例中，如果一个Person的实例有不为空的spouse属性，且spouse有不为空的nick属性，则输出spouse.nick。否则，输出undefined：

class Person {
nick: string | null = null;
    spouse ? : Person;

    constructor(nick: string) {
        this.nick = nick;
        this.spouse = undefined;
    }
}

let p : Person = new Person('Alice');
p.spouse ? .nick; // undefined



/*************************/模块/***************************************************************************/
模块
程序可划分为多组编译单元或模块。

每个模块都有其自己的作用域，即，在模块中创建的任何声明（变量、函数、类等）在该模块之外都不可见，除非它们被显式导出。

与此相对，从另一个模块导出的变量、函数、类、接口等必须首先导入到模块中。

导出
可以使用关键字export导出顶层的声明。

未导出的声明名称被视为私有名称，只能在声明该名称的模块中使用。

export class Point {
x: number = 0;
y: number = 0;
    constructor(x: number, y : number) {
        this.x = x;
        this.y = y;
    }
}
export let Origin = new Point(0, 0);
export function Distance(p1: Point, p2 : Point) : number{
  return Math.sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}
导入
静态导入

导入声明用于导入从其他模块导出的实体，并在当前模块中提供其绑定。导入声明由两部分组成：

导入路径，用于指定导入的模块；
导入绑定，用于定义导入的模块中的可用实体集和使用形式（限定或不限定使用）。
导入绑定可以有几种形式。

假设模块具有路径“. / utils”和导出实体“X”和“Y”。

导入绑定 * as A表示绑定名称“A”，通过A.name可访问从导入路径指定的模块导出的所有实体：

import * as Utils from './utils';
Utils.X // 表示来自Utils的X
Utils.Y // 表示来自Utils的Y
导入绑定{ ident1, ..., identN }表示将导出的实体与指定名称绑定，该名称可以用作简单名称：

import { X, Y } from './utils';
X // 表示来自utils的X
Y // 表示来自utils的Y
如果标识符列表定义了ident as alias，则实体ident将绑定在名称alias下：

import { X as Z, Y } from './utils';
Z // 表示来自Utils的X
Y // 表示来自Utils的Y
X // 编译时错误：'X'不可见
动态导入

应用开发的有些场景中，如果希望根据条件导入模块或者按需导入模块，可以使用动态导入代替静态导入。

import()语法通常称为动态导入（dynamic import），是一种类似函数的表达式，用来动态导入模块。以这种方式调用，将返回一个promise。

如下例所示，import(modulePath)可以加载模块并返回一个promise，该promise resolve为一个包含其所有导出的模块对象。该表达式可以在代码中的任意位置调用。

// Calc.ts
export function add(a:number, b : number) :number{
  let c = a + b;
  console.info('Dynamic import, %d + %d = %d', a, b, c);
  return c;
}

// Index.ts
import("./Calc").then((obj: ESObject) => {
console.info(obj.add(3, 5));
}).catch ((err: Error) = > {
    console.error("Module dynamic import error: ", err);
});
如果在异步函数中，可以使用let module = await import(modulePath)。

// say.ts
export function hi() {
    console.log('Hello');
}
export function bye() {
    console.log('Bye');
}
那么，可以像下面这样进行动态导入：

async function test() {
    let ns = await import('./say');
    let hi = ns.hi;
    let bye = ns.bye;
    hi();
    bye();
}


