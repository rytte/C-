('''********************''' 开发模式'''************************************************************'''
 在开发Web应用中，有两种应用模式：

 #1、前后端混合开发模式
 前后端混合项目是指前后端代码的混合，前端需要使用模版语法去获取后端的数据，后端需要使用locals在开放局部空间来让前端拿到数据。
 大体流程：前端编写静态页面 >> 发送给后端人员做二次处理，所有的html代码和数据在服务器拼接好 >> 前后端处理好模版之后再做整合 >> 一次性将所有内容发送到客户端，浏览器执行代码，将内容呈现给客户。

 #2、前后端分离开发模式
 前后端分离开发模式是指代码上的分离，前后端代码上面的数据传输和交互使用API接口的方式使用Json格式的数据进行交互，脱离了模版语法。
 大体流程：浏览器发送请求 >> 前端返回一个静态页面，静态页面中触发js事件 >> 通过Ajax向服务器端发送请求，索要数据 >> 将数据拿到之后再填充到浏览器的页面中。



('''********************''' Django REST Framework（DRF）'''************************************************************'''

 RESTful API 是一种基于 REST（Representational State Transfer，表述性状态转移） 架构风格的 Web API，用于客户端和服务器之间的数据通信。

REST 以 资源（数据）为核心，每个资源都有唯一的 URL 作为标识。
例如：
1、https://api.example.com/users/（用户列表）
2、https://api.example.com/users/1/（ID 为 1 的用户）

#RESTful API 和普通 API 的区别
比较项		RESTful API												普通 API
架构风格		遵循 REST（表述性状态转移）								没有固定的架构风格，通常基于自定义规则
数据组织		以资源（Resource）为中心，每个资源用 URL 唯一标识			通常以功能为中心，URL 可能包含动词
请求方法		使用 HTTP 方法（GET, POST, PUT, DELETE）表示 CRUD 操作	可能所有操作都用 POST，然后传递不同的参数来区分
无状态性		无状态（服务器不记录请求状态，每次请求都需携带完整信息）		可能使用 Session 存储状态
URL 设计		简洁、层级化，通常是 /资源名称/{id}/						可能是 /getUser?id=1 或 /api?action=getUser&id=1
数据格式		通常使用 JSON（有时 XML）									可以是 JSON、XML、表单数据等
适用场景		Web API、前后端分离、微服务								传统 Web 开发、RPC 调用



('''********************''' Django-Vue 前后端分离开发'''************************************************************'''
#项目结构
可以采用如下的目录结构，后端（Django）和前端（Vue）分别独立开发，后端提供 API，前端通过 API 获取数据并展示 UI。
project-root/
│── backend/            # Django 后端
│   ├── manage.py
│   ├── backend/        # Django 核心
│   ├── api/            # 业务逻辑（views, models, serializers）
│   ├── static/         # 存放静态文件
│   ├── media/          # 存放用户上传文件
│   ├── requirements.txt
│   ├── ...
│
│── frontend/           # Vue 前端
│   ├── node_modules/
│   ├── src/
│   ├── public/
│   ├── package.json
│   ├── vite.config.js
│   ├── ...

#Django 后端开发
后端主要使用 Django + Django REST Framework (DRF) 提供 API。
（1）创建 Django 项目
"django-admin startproject backend"
"cd backend"
"python manage.py startapp api"

（2）安装依赖
"pip install djangorestframework django-cors-headers"

（3）配置 Django
【settings.py】
INSTALLED_APPS = [
    ...
    'rest_framework',
    'corsheaders',  # 允许跨域请求
    'api',          # 业务应用
]

MIDDLEWARE = [
    ...
    'corsheaders.middleware.CorsMiddleware',
]

CORS_ALLOW_ALL_ORIGINS = True  # 允许所有跨域

（4）创建 API
【models.py】
from django.db import models

class Article(models.Model):
    title = models.CharField(max_length=200)
    content = models.TextField()
    created_at = models.DateTimeField(auto_now_add=True)

创建【serializers.py】
from rest_framework import serializers
from .models import Article

class ArticleSerializer(serializers.ModelSerializer):
    class Meta:
        model = Article
        fields = '__all__'

【views.py】
from rest_framework import viewsets
from .models import Article
from .serializers import ArticleSerializer

class ArticleViewSet(viewsets.ModelViewSet):
    queryset = Article.objects.all()
    serializer_class = ArticleSerializer

【urls.py】
from django.urls import path, include
from rest_framework.routers import DefaultRouter
from api.views import ArticleViewSet

router = DefaultRouter()
router.register(r'articles', ArticleViewSet)

urlpatterns = [
    path('api/', include(router.urls)),
]

运行数据库迁移：
"python manage.py makemigrations"
"python manage.py migrate"

运行 Django 服务器：
"python manage.py runserver"

访问 http://127.0.0.1:8000/api/articles/ 可查看 API。


#Vue 前端开发
前端使用 Vue 3 + Vite 进行开发，主要通过 Axios 请求后端 API。

（1）初始化 Vue 项目
"npm create vite@latest frontend --template vue"
"cd frontend"
"npm install"
"npm install axios"

（2）配置 Vue
【src/main.js】
import { createApp } from 'vue'
import App from './App.vue'
import axios from 'axios'

const app = createApp(App)

// 配置全局 axios
app.config.globalProperties.$axios = axios.create({
    baseURL: 'http://127.0.0.1:8000/api/'
})

app.mount('#app')

（3）创建 Vue 组件
【src/components/ArticleList.vue】
<template>
  <div>
    <h1>Article List</h1>
    <ul>
      <li v-for="article in articles" :key="article.id">
        {{ article.title }}
      </li>
    </ul>
  </div>
</template>

<script>
import axios from 'axios'

export default {
  data() {
    return {
      articles: []
    }
  },
  async mounted() {
    try {
      const response = await axios.get('http://127.0.0.1:8000/api/articles/')
      this.articles = response.data
    } catch (error) {
      console.error("Failed to get the article", error)
    }
  }
}
</script>

（4）修改 src/App.vue
【src/App.vue】
<template>
  <div>
    <h1>Welcome to the article management system</h1>
    <ArticleList />
  </div>
</template>

<script>
import ArticleList from './components/ArticleList.vue'

export default {
  components: {
    ArticleList
  }
}
</script>

（5）启动前端
npm run dev

访问 http://localhost:5173/，应该能看到后端返回的数据。

