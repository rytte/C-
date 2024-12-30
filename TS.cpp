/*************************/TS/***************************************************************************/

JavaScript(JS) 是一种 动态类型语言（Dynamic Typed Language），变量的类型是在运行时决定的
TypeScript(TS) 是一种 静态类型语言（Statically Typed Language），类型的检查发生在编译时，而不是运行时。


//安装TS编译器
npm i - g  typescript		//i，即install。-g，即global。全局安装
tsc -v						//查看是否安装成功


//类型注解
即给变量添加类型约束，可以显示标记出代码中的意外行为，从而降低了发生错误的可能性
let 变量名 : 类型 = 初始值
let age : number = 18

