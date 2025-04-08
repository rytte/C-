/********************/Element Plus/************************************************************/

//安装
"npm install element-plus --save"

//完整引入（打包后的文件较大）
import { createApp } from 'vue'
import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'
import App from './App.vue'

const app = createApp(App)

app.use(ElementPlus)
app.mount('#app')


//也可以CDN导入（分别导入Vue3，CSS，组件库）
R"(
<script src = "https://unpkg.com/vue@3" > </script>
<link rel = "stylesheet" href = "https://unpkg.com/element-plus/dist/index.css">
<script src = "https://unpkg.com/element-plus"></script>
)"



