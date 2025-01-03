/*************************/NAPI/***************************************************************************/
N - API（Node API）是 Node.js 提供的一套 C / C++ 插件接口，用于开发原生模块（Native Modules）。
它提供了一个稳定的 API，使得开发者能够通过 C 或 C++ 语言为 Node.js 扩展功能，而无需依赖底层的 V8 引擎或 Node.js 版本。
N - API 的主要目的是提供跨版本的稳定性，避免每次 Node.js 更新时都需要重新编译原生模块。


//N-API 的主要特点：
1、跨版本兼容：N - API 模块不需要随着 V8 引擎的变化而重编译。
2、抽象底层实现：通过提供统一的接口，N - API 抽象了底层 JavaScript 引擎（如 V8）细节，减少了开发者的维护负担。
3、性能优化：相比传统的 Node.js 原生模块开发，N - API 提供了更高的性能优化。
4、多语言支持：N - API 模块可以用 C / C++ 语言编写，甚至可以用其他支持 C / C++ 接口的语言，如 Rust。


//使用 N-API 编写原生模块的步骤
1、在新建工程文件夹下执行 "npm init -y", 快速初始化项目
2、安装模块 
"npm install node-gyp"
"npm install node-addon-api"
3、创建一个 binding.gyp 文件，它是 node - gyp 的配置文件（node - gyp是生成构建配置的工具，相当于cmake）
{
  "targets": [
    {
      "target_name": "my_module",
      "sources" : ["src/my_module.cc"] ,
      "include_dirs" : [
        "./node_modules/node-addon-api"
      ] ,
      "defines" : [
        "NODE_ADDON_API_CPP_EXCEPTIONS"
      ]
    }
  ]
}
4、编写 C++ 代码
5、编译模块（编译成功后，生成的原生模块将会存放在 build / Release 目录下）
"node-gyp configure" 
"node-gyp build"
6、在 JavaScript（仅限Node.js） 中加载和使用模块
const myModule = require('./build/Release/my_module.node');
console.log(myModule.double(21)); // 输出：42


【src / my_module.cc】
#include <napi.h>

// 定义一个简单的函数，将传入的数字加倍
Napi::Number Double(const Napi::CallbackInfo & info) 
{
    Napi::Env env = info.Env();
    int arg = info[0].As<Napi::Number>().Int32Value();
    return Napi::Number::New(env, arg * 2);
}

// 定义一个模块，导出 Double 函数
Napi::Object Init(Napi::Env env, Napi::Object exports) 
{
    exports.Set("double", Napi::Function::New(env, Double));
    return exports;
}

// 注册模块
NODE_API_MODULE(addon, Init)




