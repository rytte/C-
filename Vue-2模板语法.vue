<!--声明式渲染-->
<script setup>
    import { reactive, ref } from 'vue'

    const counter = reactive({ count: 0 })
    const message = ref('<u>Hello World!</u>')
</script>

<template>
    <h1>{{ message }}</h1>                      // {{}} 双大括号用于渲染原始文本
    <h1 v-html="message"></h1>                  // v-html可以渲染为HTML
    <p>Count is : {{ counter.count }}</p>       // 在模板中使用 ref 时，不需要附加 .value
</template>


<!--指令语法-->
v-on:submit.prevent="onSubmit"
指令名:参数.修饰符="值"


<!--Attribute 绑定--> 绑定状态
<div v-bind:id="dynamicId"></div>
<div :id="dynamicId"></div>         //简写

实例：
<script setup>
    import { ref } from 'vue'
    const titleClass = ref('title')
    const isDisabled = ref(false)
    const objectOfAttrs = {
        id: 'container',
        class: 'wrapper',
        style: 'background-color:green'
    }
</script>

<template>
    <h1 :class="titleClass">Make me red</h1>          // 绑定为titleClass的属性
    <button :disabled="isDisabled">Button</button>    // 根据isDisabled判断disabled属性是否生效
    <div v-bind="objectOfAttrs"></div>                // 动态绑定多个值

</template>

<style>
    .title {
        color: red;
    }
</style>


<!--支持JS表达式-->
仅支持单一表达式，即可以写在return后面的那种，如下
{{ message.split('').reverse().join('') }}
<div :id="`list-${id}`"></div>


<!--调用函数-->
可以在绑定的表达式中使用一个组件暴露的方法，绑定在表达式中的方法在组件每次更新时都会被重新调用
<time :title="toTitleDate(date)" :datetime="date">
    {{ formatDate(date) }}
</time>


<!--事件监听--> 绑定函数
<button v-on:click="increment">{{ count }}</button>
<button @click="increment">{{ count }}</button>     //简写

实例：
<script setup>
    import { ref } from 'vue'

    const count = ref(0)

    function increment() {
        count.value++
    }
</script>

<template>
    <button @click="increment">Count is: {{ count }}</button>
</template>


<!--动态参数-->
指令的参数也可以使用JS表达式，需要包含在一对方括号内
<a :[attributeName]="url"> ... </a>         //如果有一个数据属性 attributeName，其值为 "href"，那么就等价于 v-bind:href
<a @[eventName]="doSomething"> ... </a>
JS表达式的限制：不能含有空格和引号，避免使用大写字母


<!--修饰符-->
修饰符是以点开头的特殊后缀，表明指令需要以一些特殊的方式被绑定。
例如 .prevent 修饰符会告知 v-on 指令对触发的事件调用 event.preventDefault()：
<form @submit.prevent="onSubmit">...</form>

