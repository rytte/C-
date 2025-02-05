<!--条件渲染-->
<h1 v-if="awesome">Vue is awesome!</h1>
<h1 v-else-if="test">Test</h1>
<h1 v-else>Oh no</h1>
awesome 的值为真值 (Truthy) 时渲染"Vue is awesome!",否则test值为真时渲染Test，否则渲染"Oh no"

实例：
<script setup>
    import { ref } from 'vue'

    const awesome = ref(true)

    function toggle() {
        awesome.value = !awesome.value
    }
</script>

<template>
    <button @click="toggle">Toggle</button>
    <h1 v-if="awesome">Vue is awesome!</h1>
    <h1 v-else>Oh no</h1>
</template>


<!--<template> 上的 v-if-->
v-if可以用在template标签上，可以同时决定多个元素是否显示
<template v-if="ok">
    <h1>Title</h1>
    <p>Paragraph 1</p>
    <p>Paragraph 2</p>
</template>


<!--列表渲染-->
<script>
    const parentMessage = ref('Parent')
    const items = ref([{ message: 'Foo' }, { message: 'Bar' }])
    const myObject = reactive({
        title: 'How to do lists in Vue',
        author: 'Jane Doe',
        publishedAt: '2016-04-10'
    })
</script>
<template>
    <li v-for="item in items">
        {{ item.message }}
    </li>

    <!--v-for 也支持使用可选的第二个参数表示当前项的位置索引。-->
    <li v-for="(item, index) in items">
        {{ parentMessage }} - {{ index }} - {{ item.message }}
    </li>

    <!--遍历对象所有属性，遍历的顺序会基于对该对象调用 Object.values() 的返回值来决定-->
    <ul>
        <li v-for="value in myObject">
            {{ value }}
        </li>
    </ul>

    <!--可以通过提供第二个参数表示属性名-->
    <li v-for="(value, key) in myObject">
        {{ key }}: {{ value }}
    </li>

    <!--第三个参数表示位置索引-->
    <li v-for="(value, key, index) in myObject">
        {{ index }}. {{ key }}: {{ value }}
    </li>
</template>

也可以使用 of 作为分隔符来替代 in，如：<div v-for="item of items"></div>


<!--在 v-for 里使用范围值-->
v-for 可以直接接受一个整数值。在这种用例中，会将该模板基于 1...n 的取值范围重复多次，注意此处 n 的初值是从 1 开始而非 0。
<span v-for="n in 10">{{ n }}</span>


<!--<template> 上的 v-for​-->
与模板上的 v-if 类似，你也可以在 template 标签上使用 v-for 来渲染一个包含多个元素的块。例如：
<ul>
    <template v-for="item in items">
        <li>{{ item.msg }}</li>
        <li class="divider" role="presentation"></li>
    </template>
</ul>


<!--v-for 与 v-if-->
同时使用 v-if 和 v-for 是不推荐的，因为这样二者的优先级不明显。
当 v-if 和 v-for 同时存在于一个元素上的时候，v-if 会首先被执行。
这意味着 v-if 的条件将无法访问到 v-for 作用域内定义的变量别名。
<li v-for="todo in todos" v-if="!todo.isComplete">
    {{ todo.name }}             <!--这会抛出一个错误，因为属性 todo 此时没有在该实例上定义-->
</li>
在外先包装一层 template 再在其上使用 v-for 可以解决这个问题
<template v-for="todo in todos">
    <li v-if="!todo.isComplete">
        {{ todo.name }}
    </li>
</template>


<!--key attribute-->
就地更新策略：当v-for 渲染的元素列表，数据项的顺序改变时，Vue 不会随之移动 DOM 元素的顺序，
而是就地更新每个元素，确保它们在原本指定的索引位置上渲染。
为每个元素对应的块提供一个唯一的 key 属性（值为字符串或number类型），可以使他跟踪每个节点，解决上述问题。
<div v-for="item in items" :key="item.id">
    <!-- 内容 -->
</div>

