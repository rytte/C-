<!--CDN语法-->
<script src="https://unpkg.com/vue@3/dist/vue.global.js"></script>

<div id="app">{{ message }}</div>

<script>
    const { createApp, ref } = Vue

    createApp({
        setup() {
            const message = ref('Hello vue!')
            return {
                message
            }
        }
    }).mount('#app')
</script>


<!--或者使用ES模块语法-->
<div id="app">{{ message }}</div>

<script type="module">
    import { createApp, ref } from 'https://unpkg.com/vue@3/dist/vue.esm-browser.js'

    createApp({
        setup() {
            const message = ref('Hello Vue!')
            return {
                message
            }
        }
    }).mount('#app')
</script>
