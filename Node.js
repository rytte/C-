/*************************/Node.js/***************************************************************************/
Node.js 不是一种编程语言，而是一个基于 Chrome V8 引擎 的 JavaScript 运行环境。
它允许你在服务器端运行 JavaScript 代码，打破了 JavaScript 仅限于浏览器端执行的传统限制。


//Node.js 特性
1、事件驱动：Node.js 采用事件驱动架构，使得它非常适合处理并发连接。
2、异步 I/O：Node.js 使用非阻塞的异步 I/O 操作，可以提高性能，特别是用于 I/O 密集型任务时（如数据库查询、文件读写等）。
3、跨平台：Node.js 可以在多个操作系统上运行，如 Windows、Linux 和 macOS。
4、npm（Node.js 包管理器）：Node.js 提供了一个庞大的模块生态系统，你可以通过 npm 安装和管理各种模块，极大地提升开发效率。


//TS
当你运行 tsc（TypeScript 编译器）时，它会自动查找当前工作目录中的 tsconfig.json 文件，并根据该文件中的配置选项来编译 TypeScript 代码。
也可以指定其它名称(路径)：tsc --project myconfig.json

tsconfig.json文件结构示例：
{
  "compilerOptions": {
    "target": "ES6",             // 编译目标语言标准
    "module": "CommonJS",        // 使用的模块系统
    "outDir": "./dist",          // 输出目录
    "esModuleInterop": true,     // 启用与 ES 模块的互操作性
    "strict": true               // 启用严格模式
  },
  "include": ["src/**/*.ts"],    // 包含的文件
  "exclude": ["node_modules"]    // 排除的文件
}

说明：
compilerOptions：
{
    target：指定 JavaScript 编译的目标版本（例如，ES5、ES6、ES2018 等）。
    module：指定模块系统，通常使用 CommonJS（Node.js）、ESNext（ES模块）等。
    outDir：指定编译后的 JavaScript 文件的输出目录。
    esModuleInterop：启用对 CommonJS 模块的兼容性，通常与 import 语句一起使用。
    strict：启用 TypeScript 的严格模式，开启严格的类型检查。
    sourceMap：生成.map 文件，方便调试。
    noImplicitAny：禁止隐式的 any 类型，要求显式声明类型。
}
include：指定包含的文件或文件夹。例如，src/**/ *.ts 表示编译 src 文件夹下的所有.ts 文件。
exclude：指定排除的文件或文件夹，通常会排除 node_modules 和 build 目录。
files：列出明确指定要包含的文件，而不是通过 include 模式来匹配。


//package.json
很多常见的 npm 命令会读取 package.json 这个文件来获取依赖、脚本、版本信息等。
可以由 npm init - y 命令生成
{
    "name": "simple-demo",
    "version": "1.0.0",
    "main": "index.js",
    "scripts": {
        "test": "echo \"Error: no test specified\" && exit 1"
    },
    "keywords": [],
    "author": "",
    "license": "ISC",
    "description": ""
}

会读取 package.json 的命令：
1、npm install
2、npm run 执行脚本
3、npm publish
4、npm init
5、npm update
6、npm install < package >
7、npm uninstall < package >
8、npm ls


//package-lock.json
由 npm install 命令生成，用于锁定项目中所有安装的依赖包的版本。

当其他开发者克隆该项目并运行 npm install 时，npm 会根据 package - lock.json 安装精确版本的依赖，确保安装的依赖版本与开发者的环境一致。
因此应该将 package - lock.json 纳入版本控制（Git）。


//npm配置修改
执行 "npm config edit"
添加 "python=C:\Users\13055\miniconda3\python.exe" 可解决python路径问题



/*************************/工程实例/***************************************************************************/
//创建工程
1、在新建工程文件夹下执行 "npm init -y"，快速初始化一个新的 Node.js 项目（-y可以跳过手动输入配置值），生成 package.json 文件。
2、安装依赖库 "npm install express"，会生成 package - lock.json 和 node_modules 文件夹 
3、编写网页 public/index.html
4、编写后端 server.js
5、启动Node.js服务器 node server.js
6、打开浏览器访问 http://localhost:3000



【index.html】
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Simple Demo</title>
</head>
<body>
    <h1>Hello from Node.js and HTML!</h1>
    <button id="btn">Click Me</button>
    <p id="response"></p> <!-- 用于显示后端返回的消息 -->

    <script>
        // 当按钮被点击时，向后端请求数据
        document.getElementById('btn').onclick = function () {
            fetch('/getMessage')  // 向后端请求数据
                .then(response => response.json())  // 解析响应为 JSON 格式
                .then(data => {
                    document.getElementById('response').innerText = data.message;  // 显示消息
                })
                .catch(error => console.error('Error:', error));
        };
    </script>
</body>
</html>



【server.js】
// 引入 express
const express = require('express');
const app = express();
const port = 3000;

// 提供静态文件服务
app.use(express.static('public'));

// 设置根路由
app.get('/', (req, res) => {
    res.sendFile(__dirname + '/public/index.html');
});

// 新增的路由，返回一条简单的消息
app.get('/getMessage', (req, res) => {
    res.json({ message: 'Hello from the backend!' });
});

// 启动服务器
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});

