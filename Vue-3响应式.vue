<!--深层响应与浅层响应-->
深层响应：会递归地将所有嵌套的属性（包括对象和数组）都转换为响应式对象，从而确保任何嵌套属性的变化都会触发视图更新。
浅层响应：它只会追踪对象的第一层属性，可以用于避免对大型数据的响应性开销来优化性能、或者有外部库管理其内部状态的情况

ref()               可以接受任何值类型，并将其包裹在一个带有 .value 属性的对象中返回，具有深层响应性。
reactive()          只适用于对象，具有深层响应性。
shallowRef()        浅层响应的ref()。
shallowReactive()   浅层响应的reactive()

如下当"nested"的值改变时，不会自动触发视图更新。
<script>
    const obj = shallowReactive({
        a: 1,
        b: { nested: 2 }
    })
</script>


<!--ref和reactive的区别-->
特性	            reactive()	                            ref()
适用数据类型	    用于对象、数组等复杂类型	                用于原始数据类型（如 string、number、boolean）或对象
数据存取方式	    直接访问属性：obj.property	            需要通过 .value 访问：ref.value
创建的响应式类型	创建 响应式对象，可以直接访问属性	        创建 响应式引用，需要 .value 来访问数据
深度响应	        对象内的嵌套属性也会变成响应式         	只有 ref 本身是响应式的，嵌套的属性需要显式转换为响应式


<!--ref和reactive 注意事项-->
1、reactive() 只能用于对象类型 (对象、数组和如 Map、Set 这样的集合类型)。不能持有如 string、number 或 boolean 这样的原始类型。
2、ref() 在模板渲染上下文中，只有顶级属性才会被解包。但如果是文本插值的最终计算值 (即 {{ }} 标签)，那么它将被解包。
<script>
    const count = ref(0)
    const object = { id: ref(1) }
</script>
<template>
    {{ count + 1 }}         // 1
    {{ object.id + 1 }}     // 不会被解包：返回[object Object]1
    {{ object.id }}         // 2
</template>


<!--代理对象和原始对象-->
ref()和reactive() 返回的是一个原始对象的 Proxy，它和原始对象是不全等的。
代理对象是响应式的，更改原始对象不会触发更新。

<script>
    const raw = {}
    const proxy = reactive(raw)

    // 代理对象和原始对象不是全等的
    console.log(proxy === raw) // false

    // 在同一个对象上调用 reactive() 会返回相同的代理
    console.log(reactive(raw) === proxy) // true

    // 在一个代理上调用 reactive() 会返回它自己
    console.log(reactive(proxy) === proxy) // true

    // 不能替换整个对象
    let state = reactive({ count: 0 })
    state = reactive({ count: 1 })      // 上面的 ({ count: 0 }) 引用将不再被追踪。(响应性连接已丢失！)
</script>
