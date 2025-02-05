<!--表单绑定--> 同时绑定状态与函数
同时使用 v-bind 和 v-on 来在表单的输入元素上创建双向绑定
<script setup>
    <input: value="text" @input="onInput" >
        function onInput(e) {
            // v-on 处理函数会接收原生 DOM 事件作为其参数。
            text.value = e.target.value
        }

        < input v - model="text" >       //上面的简写
</script>

实例：
<script setup>
                import { ref } from 'vue'
        const text = ref('')
</script>

<template>
    <input v-model="text" placeholder="Type here">
    <p>{{ text }}</p>
</template>


<!--v-show-->
用法和v-if基本一样，但v-show 会在 DOM 渲染中保留该元素，仅切换了该元素上名为 display 的 CSS 属性（也就是进行隐藏）
并且v-show不支持在template标签上使用
<h1 v-show="ok">Hello!</h1>


<!--模板引用和生命周期-->
<script setup>
    //script setup执行时，template还未执行，因此 DOM 元素还不存在。模板引用 ref 只能在组件挂载后访问。
    import { ref, onMounted } from 'vue'

    const pElementRef = ref(null)       //模板引用——也就是指向模板中一个 DOM 元素的 ref

    onMounted(() => {               //生命周期钩子函数
        // 此时组件已经挂载。模板引用 ref 只能在组件挂载后访问。
        pElementRef.value.textContent = 'mounted!'
    })
</script>

<template>
    <p ref="pElementRef">Hello</p>
</template>


<!--侦听器-->
watch(对象，函数)
当对象发生变化时，执行函数
<script setup>
    import { ref, watch } from 'vue'

    const todoId = ref(1)
    const todoData = ref(null)

    async function fetchData() {
        todoData.value = null
        const res = await fetch(
            `https://jsonplaceholder.typicode.com/todos/${todoId.value}`
        )
        todoData.value = await res.json()
    }

    fetchData()

    watch(todoId, fetchData)
</script>

<template>
    <p>Todo id: {{ todoId }}</p>
    <button @click="todoId++" :disabled="!todoData">Fetch next todo</button>
    <p v-if="!todoData">Loading...</p>
    <pre v-else>{{ todoData }}</pre>
</template>


<!--组件-->
导入：import ChildComp from './ChildComp.vue'
使用：
<ChildComp />


<!--props-->
子组件可以通过 defineProps 从父组件接受动态数据
<script setup>
    import { ref } from 'vue'
    import ChildComp from './ChildComp.vue'

    const greeting = ref('Hello from parent')
</script>

<template>
    <ChildComp :msg="greeting" />
</template>


【ChildComp.vue】
<script setup>
    const props = defineProps({
        msg: String
    })
</script>

<template>
    <h2>{{ msg || 'No props passed yet' }}</h2>
</template>


<!--Emits-->
子组件可以通过 defineEmits 和 emit 向父组件触发事件
父组件通过v-on监听事件
<script setup>
    import { ref } from 'vue'
    import ChildComp from './ChildComp.vue'

    const childMsg = ref('No child msg yet')
</script>

<template>
    <ChildComp @response="(msg) => childMsg = msg" />
    <p>{{ childMsg }}</p>
</template>


【ChildComp.vue】
<script setup>
    const emit = defineEmits(['response'])      // 声明触发的事件

    emit('response', 'hello from child')        // 带参数触发
</script>

<template>
    <h2>Child component</h2>
</template>


<!--插槽-->
除了通过 props 传递数据外，父组件还可以通过插槽 (slots) 将模板片段传递给子组件
<script setup>
    import { ref } from 'vue'
    import ChildComp from './ChildComp.vue'

    const msg = ref('from parent')
</script>

<template>
    <ChildComp>Message: {{ msg }}</ChildComp>
</template>


【ChildComp.vue】
<template>
    <slot>Fallback content</slot>
</template>


