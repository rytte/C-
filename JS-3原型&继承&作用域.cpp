/*************************/原型/***************************************************************************/
//原型（prototype）对象
相当于对象的基类(事实上JavaScript中没有类的概念)，在基类中定义的属性或方法，直接继承到每一个派生对象。
也就是说，我们可以将对象中共有的内容，统一设置到原型对象中。
1、类可以通过 prototype 访问其原型
2、类对象可以通过 _proto_ 访问其原型
3、Object对象是所有对象的基类，Object的原型对象指向为null，也就是没有原型对象

console.log(mc.__proto__.hasOwnProperty("hasOwnProperty"));



/*************************/继承/***************************************************************************/
//继承方式：原型链继承
function SupperType()           //父类构造
{
    this.supProp = 'Supper property';
}

function SubType()              //子类构造
{
    this.subProp = 'Sub property';
}

SubType.prototype = new SupperType();      //SubType将SupperType设为父类
SubType.prototype.constructor = SubType;   //SubType将构造函数设为SubType（也就是替换掉父类的构造函数）

//缺点
1、原型链继承多个实例的引用类型属性指向相同，一个实例修改了原型属性，另一个实例的原型属性也会被修改
2、不能传递参数
3、不能多继承



//继承方式：借用构造函数继承
function SuperType(name)            //父类构造
{
    this.name = name;
    this.showSupperName = function()
    {
        console.log(this.name);
    };
}

function SubType(name, age)         //子类构造
{
    // 在子类型中调用call方法继承自SuperType。他会将SuperType中的所有属性复制到SubType中（不包括方法）
    SuperType.call(this, name);
    this.age = age;
}

//缺点
1、只能继承父类的实例属性和方法，不能继承原型属性和方法
2、无法实现构造函数的复用，每个子类都有父类实例函数的副本，影响性能，代码会臃肿



//继承方式：组合继承（原型链 + 借用构造函数）（最常用的继承方式）
function Person(name, age)
{
    this.name = name;
    this.age = age;
}

Person.prototype.setName = function(name)
{
    this.name = name;
};

function Student(name, age, price)
{
    Person.call(this, name, age);   // 为了得到父类型的实例属性和方法
    this.price = price;             // 添加子类型私有的属性
}

Student.prototype = new Person();               // 为了得到父类型的原型属性和方法
Student.prototype.constructor = Student;        // 修正constructor属性指向
Student.prototype.setPrice = function(price)    // 添加子类型私有的方法 
{
    this.price = price;
};

//缺点
父类中的实例属性和方法既存在于子类的实例中，又存在于子类的原型中，不过仅是内存占用，因此，在使用子类创建实例对象时，其原型中会存在两份相同的属性和方法 。



/*************************/作用域/***************************************************************************/
//全局作用域
1、在 script 标签中的 JavaScript 代码属于全局作用域。
2、全局作用域在页面打开时创建，页面关闭时销毁。
3、全局作用域中有一个全局对象 window，它代表浏览器窗口。
在全局作用域中：
{
变量作为 window 对象的属性。
函数作为 window 对象的方法。
全局变量在页面的任意部分都可访问。
}

//函数作用域
每次调用函数时创建一个新的作用域，函数执行完毕后销毁。
函数作用域和全局作用域是独立的。
函数作用域可以访问全局变量，但全局作用域不能访问函数作用域中的变量。
可以通过 window 对象访问全局变量。

//作用域链（即变量查找顺序）
当前作用域 >> 上一级作用域 >> 一直到全局作用域，若找不到则抛出 ReferenceError 异常。


