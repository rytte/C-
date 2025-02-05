<!--计算属性-->
计算属性值会基于其响应式依赖被缓存，只有当依赖值更新时才重新计算。而普通方法每一次渲染时都需要重新计算。

<script setup>
    import { ref, computed } from 'vue'

    const author = reactive({
        name: 'John Doe',
        books: [
            'Vue 2 - Advanced Guide',
            'Vue 3 - Basic Guide',
            'Vue 4 - The Mystery'
        ]
    })

    const publishedBooksMessage = computed(() => {
        return author.books.length > 0 ? 'Yes' : 'No'
    })

    function calculateBooksMessage() {
        return author.books.length > 0 ? 'Yes' : 'No'
    }
</script>

<template>
    <p>Has published books:</p>
    <span>{{ author.books.length > 0 ? 'Yes' : 'No' }}</span>       //不使用computed()
    <span>{{ publishedBooksMessage }}</span>                        //使用computed()
    <p>{{ calculateBooksMessage() }}</p>                            //使用普通方法
</template>


<!--可写计算属性-->
计算属性默认是只读的，即无法在函数中改变依赖值。你可以通过同时提供 getter 和 setter 来创建可写计算属性。
<script setup>
    import { ref, computed } from 'vue'

    const firstName = ref('John')
    const lastName = ref('Doe')

    const fullName = computed({
        // getter
        get() {
            return firstName.value + ' ' + lastName.value
        },
        // setter
        set(newValue) {
            // 注意：我们这里使用的是解构赋值语法
            [firstName.value, lastName.value] = newValue.split(' ')
        }
    })

    fullName.value = 'John Doe'     //此时 setter 会被调用而 firstName 和 lastName 会随之更新。
</script>


<!--获取上一个计算值（仅 3.4+ 支持）-->
<script setup>
    import { ref, computed } from 'vue'

    const count = ref(2)

    // 这个计算属性在 count 的值小于或等于 3 时，将返回 count 的值。
    // 当 count 的值大于等于 4 时，将会返回满足我们条件的最后一个值
    // 直到 count 的值再次小于或等于 3 为止。
    const alwaysSmall = computed((previous) => {
        if (count.value <= 3) {
            return count.value
        }

        return previous
    })
</script>
