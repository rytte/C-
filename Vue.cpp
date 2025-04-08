/*************************/虚拟DOM/***************************************************************************/
{
    tag: 'div',
    attributes: { class: 'container' },
    children: [
        {
            tag: 'p',
            children: ['Hello, world!']
        }
    ]
}

<div class='container'>
    <p>Hello, world!</p>
< / div>

1、虚拟 DOM 是通过 JavaScript 对象模拟 DOM 结构。如上。
2、在页面变化时，框架会创建一个新的虚拟 DOM，并与之前的虚拟 DOM 进行对比，运用diff算法找出差异。
3、然后，框架只会更新那些发生变化的部分，从而避免了直接操作真实 DOM 的性能瓶颈。



/*************************/vue/***************************************************************************/

//简介
Vue通过MVVM模式, 能够实现视图与模型的双向绑定。
简单来说，就是数据变化的时候, 页面会自动刷新, 页面变化的时候，数据也会自动变化.

响应式：使用特定语法绑定页面状态，当绑定的数据发生变化时，Vue 会检测到变化并自动更新视图。

//渐进式的特点
1、可以从简单到复杂：Vue 既可以像 jQuery 那样直接在 HTML 里用，也可以构建复杂的单页应用（SPA）。
2、核心功能小，按需扩展：Vue 的核心功能很轻量，只有响应式数据和模板渲染，其他功能（如路由、状态管理）是可选的。
3、兼容已有项目，逐步引入：Vue 可以渐进式地整合到已有项目，无需推翻原有代码。

//使用方式
1、小型项目：直接用 <script src = "https://unpkg.com/vue@3/dist/vue.global.js">< / script> 引入
2、中等项目：组件化开发
3、大型项目：Vue CLI / Vite 搭建完整工程

//单文件组件
单文件组件(Single - File Component，缩写为 SFC)是一种可复用的代码组织形式，
它将从属于同一个组件的 HTML、CSS 和 JavaScript 封装在使用.vue 后缀的文件中。
以下语法为 SFC（单文件组件）特有的语法，仅在 Vue 文件中有效：
1、<script setup>
2、<template>
3、<style scoped>                //scoped：只作用于当前组件
4、defineProps 和 defineEmits
5、<script> 部分的 name 属性
6、<suspense>
7、<slot>
8、<component> 动态组件
9、"v-bind" 和 "v-on" 的简写

特性	        export default 写法	                            <script setup> 写法
代码结构	    使用 setup() 函数内部封装逻辑，返回值暴露给模板	    不需要显式定义 setup()，直接编写逻辑代码
简洁性	    需要显式书写 return，将变量暴露给模板	            自动暴露到模板中，省略了 return
模板绑定	    需要通过 return 将数据和方法暴露到模板	            任何声明的变量都可以直接在模板中使用
使用限制	    支持普通的 <script>，但无法直接访问模板上下文	    只能用于 <script setup>，更适合组合式 API
性能优化	    Vue 会在运行时处理返回的对象	                    Vue 会在编译阶段优化变量和方法的使用
引入组件	    需要手动引入组件并注册到 components 对象中	        直接引入组件即可，组件自动可用
文件大小	    代码稍长，因为需要手动暴露数据和方法	            代码更短，适合现代开发


//export default 写法如下
import { ref } from 'vue'

export default {
    setup() {
        const count = ref(0)

        function increment() {
            // 在 JavaScript 中需要 .value
            count.value++
        }

        // 不要忘记同时暴露 increment 函数
        return {
          count,
          increment
        }
    }
}

//VS Code 插件
Volar



/*************************/创建项目/***************************************************************************/
//vite模板搭建-快速开发（esbuild 支持热重载）
1、创建并手动配置选项："npm create vue@latest <project-name>"
2、进入目录："cd <project-name>"
3、安装依赖："npm install"
4、启动开发服务器："npm run dev"

//vue-cli搭建-功能丰富（webpack 包含GUI）
1、创建命令行工具："npm install -g @vue/cli"
2、创建项目："vue create <project-name>
3、进入目录："cd <project-name>"
4、启动服务器："npm run serve"


//通过CDN方式可以在HTML中使用Vue
<script src = "https://unpkg.com/vue@3/dist/vue.global.js">< / script>
CDN方式无法使用单文件组件(SFC) 语法。


//创建应用（工程入口：main.js）
import { createApp } from 'vue'
import App from './App.vue'     // 从一个单文件组件中导入根组件
const app = createApp(App)
app.mount('#app')           //将 Vue 应用实例挂载到 HTML 页面中的 #app 这个元素上，并让 Vue 负责管理这个元素及其内部的内容

< div id = "app" > < / div>

//应用配置
app.config 对象允许我们配置一些应用级的选项，例如定义一个应用级的错误处理器，用来捕获所有子组件上的错误：
app.config.errorHandler = (err) = > {
    /* 处理错误 */
}
注册应用范围内可用的资源，例如注册一个组件：
app.component('TodoDeleteButton', TodoDeleteButton)
这使得 TodoDeleteButton 在应用的任何地方都是可用的。