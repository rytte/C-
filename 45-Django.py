from email.policy import default


('''********************'''Django'''************************************************************'''
 https://blog.csdn.net/Ans_min/article/details/123146335

#安装
pip install django

会在当前python环境下的lib/site-package中，另外会生成django-admin.exe在Scripts文件夹中。
django-admin.exe用于初始化Django项目，需要配置到环境变量中。


#创建项目
执行"django-admin startproject 项目名"

#创建APP
一个Django项目管理多个功能模块，这里的功能模块称为APP
执行"python manage.py startapp app名称(如index)"

#目录结构
django_study_demo
│  manage.py
├─django_study_demo
│     asgi.py
│     settings.py
│     urls.py
│     wsgi.py
│     __init__.py
└─index						【app名命名的文件夹】
    │  admin.py				【固定的不用动】django默认提供的后台管理，但实际开发不常用，创建超级管理员账户:"python manage.py createsuperuser"
    │  apps.py				【固定的不用动】app启动相关
    │  models.py			【☆很重要，对数据库进行操作】这里不用SQL写了，Django封装了ORM供调用
    │  tests.py				【固定的不用动】用来单元功能测试的，个人小项目可以不用管
    │  views.py				【☆很重要，撰写视图函数（得我们自己写的）】
    │  __init__.py
    └─migrations			【固定的不用动】数据库变更记录，会自动生成文件，我们不用动
            __init__.py

#注册APP
打开apps.py，复制类名(IndexConfig)
打开settings.py，在列表变量INSTALLED_APPS中，添加app配置路径'index.apps.IndexConfig'

#编写视图函数
打开views.py
from django.shortcuts import render, HttpResponse
def index(request):
	return HttpResponse("Hello World!")

注意：
1、视图函数必须带request这个参数
2、视图函数必须return，返回的都是要传给前端的数据

#URL和视图函数的映射
大家使用网站时，在网站内的页面跳转都会改变URL，不同的URL就需要后台调用不同的功能给用户使用。所以每个URL都得有函数来执行相应的代码。此过程需要修改urls.py
打开urls.py，导入 from index import views
在列表变量 urlpatterns 中，添 path('index/', views.index)，参数一为URL，参数二为触发的函数名。
这句的映射关系即为访问 http://www.xxxx.com/index 时，触发的函数是名为index的app下的views.py中的index函数。

#运行Django项目
执行"python manage.py runserver"
可访问 http://127.0.0.1:8000/index/

#热重载
项目运行时修改代码并保存，Django将会直接加载代码，无需重新运行。相关的客户端页面需要手动刷新。



('''********************'''模板与静态文件'''************************************************************'''
#模板文件
为了访问html网页（而非字符串），我们 return 后面就不用 HttpResponse() 了，而是用render()，如下。

from django.shortcuts import render     # 导入render，一般django默认
def user_list(request):
    return render(request, "user_list.html")    # 第一个位子是视图函数的request参数，第二个参数位是html文件路径

模版路径为：settings.py中TEMPLATES字典的DIRS的值。若该值为空，则默认的模板路径是当前app目录下的templates目录。

#静态文件
图片、css、js这些文件都称为静态文件，在django项目中必须放在"static"文件夹中。
static中，我们可以再分img、css、js、plugins来分类存放不同的东西。

Django中，html文件中的路径写法如下。
{% load static %}       #在文件头部添加，加载static路径
<img src="{% static 'img/default.png' %}" alt="">

#添加一个页面总结
【index/template/templates_learn.html】
{% load static %}
<!-- templates_learn.html -->
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <title>模板语法学习</title>
</head>
<body>
    <h1>模板语法学习</h1>

</body>
</html>

【views.py】
def temp_learn(request):
    return render(request, "templates_learn.html")

【urls.py】
path('temp_learn/', views.temp_learn),

运行并访问 http://localhost:8000/temp_learn/ 即可


#调用后端数据
render()第三个参数位可以提供给视图函数传递数据，但必须是字典。

def temp_learn(request):
    name = "John Doe"
    students = ["Alice", "Bob", "Charlie"]
    return render(request, "templates_learn.html", {"n1": name, "stu_list": students})

<body>
    <div>{{ n1 }}</div>
    <div>{{ stu_list }}</div>           #使用后端数据
    <div>{{ stu_list.0 }}</div>         #索引使用'.'
    <div>{{ stu_list.1 }}</div>         
    {% for stu in stu_list %}           #循环语句
        {% if stu == "Alice" %}         #条件语句
            <strong>{{ stu }}</strong>
        {% else %}
            <span>{{ stu }}</span>
        {% endif %}
    {% endfor %}
</body>


#模板语法原理
1、render()读取带有模板语法的html文件
2、django内部进行渲染（模板语法执行并替换成数据）
3、最终得到只包含html标签的字符串
4、将渲染完成的字符串传给用户浏览器。


#模板的继承
首先编写基础模板，也就是重复的部分。{% block xxx %}{% endblock %}是占位符，即子模板自行实现的部分，xxx是块名。

【base.html】
{% load static %}
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">

    <!-- 标题块，可以被子模板覆盖 -->
    {% block title %}{% endblock %}

    <link rel="stylesheet" href="{% static 'plugins/bootstrap-3.4.1-dist/css/bootstrap.css' %}">
</head>
<body>
    <!-- 导航栏 -->
    <nav class="navbar navbar-default">
        <!-- 导航栏内容 -->
    </nav>

    <!-- 主体部分，可以被子模板覆盖 -->
    {% block content %}{% endblock %}

    <!-- 引入 jQuery 和 Bootstrap JS 文件 -->
    <script rel="script" src="{% static 'js/jquery-3.6.0.min.js' %}"></script>
    <script rel="script" src="{% static 'plugins/bootstrap-3.4.1-dist/js/bootstrap.js' %}"></script>
</body>
</html>


然后使用{% extends 'base.html' %}继承，并实现{% block xxx %}{% endblock %}部分。
【derived.html】
<!-- 继承语法 -->
{% extends 'base.html' %}

<!-- 页面标题 -->
{% block title %}
    <title>【EmployeeManager】部门列表</title>
{% endblock %}

<!-- 页面主体 -->
{% block content %}
    <div class="container">
        <!-- 主体内容将在这里添加 -->
    </div>
{% endblock %}



('''********************'''请求与响应'''************************************************************'''
#Request
request.method：获取用户请求提交方式（GET/POST）
request.GET：获取通过URL传递的参数
request.POST：通过请求体中获得数据

def something(request):
	print(request.method)
	print(request.GET)
	print(request.POST)
	return render(request, "user_list.html")
得到输出
GET
<QueryDict: {}>
<QueryDict: {}>

如果想获取URL传递的数据，就在网址后面加上?，后面跟着键值对（k=v），以&隔开
http://localhost:8000/something/?uid=1&username=Alice
访问该url，后台输出如下
GET
<QueryDict: {'uid': ['1'], 'username': ['Alice']}>
<QueryDict: {}>


#Response
HttpResponse()：返回内容字符串给请求者；
render()：读取HTML，并渲染，最终以字符串的格式返回给用户浏览器；
redirect()：让浏览器重定向到其他页面，返回的是网址。

Q：重定向这个过程是怎么样的？
① 浏览器提交请求给 Django，Django 收到请求后再向重定向的网址发起请求，然后返回响应数据给浏览器。
② 浏览器提交请求给 Django，Django 收到请求后直接返回重定向的网址，浏览器重新向新的网址发送请求，然后新的网址返回响应数据。
A：②是对的。①行为实际上是 服务器代理请求 或 反向代理，而不是重定向。

#登录页面
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <title>登录界面</title>
</head>
<body>
    <h1>登录界面</h1>
    <form action="/login/" method="post">   #确保填写正确的action(提交后会向改地址发起请求)和method属性
        {% csrf_token %}                    #Django的安全机制，在表单中添加 CSRF（Cross-Site Request Forgery） 令牌，否则访问会报错
        <div>
            <label for="username">用户名：</label>
            <input type="text" id="username" name="user" placeholder="请输入用户名">
        </div>
        <div>
            <label for="password">密码：</label>
            <input type="password" id="password" name="pwd" placeholder="请输入密码">
        </div>
        <div>
            <input type="submit" value="提交">
        </div>
    </form>
</body>
</html>

def login(request):
	if request.method == "GET":
		return render(request, "login.html")
	elif request.method == "POST":
		post_data = request.POST
		print(post_data)
		return HttpResponse("登录成功！")

登录成功后，后台可见如下
<QueryDict: {'csrfmiddlewaretoken': ['7BpUkoWntXgkOYx1iHbP585uPKmXxiQVtQ6Y2ivxfrJ2AJ7r2Gjq93D0ZB0RBZgz'], 'user': [''], 'pwd': ['']}>
    

#CSRF介绍
CSRF 攻击是指攻击者通过欺骗用户浏览器提交恶意请求，通常是在用户已经登录的情况下，利用浏览器自动附带的凭证（如 cookies）伪造请求。
这种攻击可能会让用户在不知情的情况下执行一些不该执行的操作，例如修改密码、提交数据等。
例如，攻击者可以诱导已登录的用户点击一个恶意链接，提交一个带有不合法请求的表单，利用用户已登录的身份进行未授权的操作。

为什么要加 {% csrf_token %}
Django 使用 CSRF 保护来防止这种攻击。在每个需要提交表单的页面中，Django 会通过 {% csrf_token %} 插入一个 唯一的令牌（token），该令牌会在用户登录时与其会话关联。
在表单提交时，Django 会检查请求中是否包含这个 CSRF 令牌，并且令牌的值是否与当前用户会话中的值匹配。如果不匹配，Django 会拒绝请求并返回一个错误，防止恶意请求。



('''********************'''数据库操作 ORM'''************************************************************'''
 在Django开发中，我们不需要手动去写SQL了，Django给我们封装好并且增加了安全机制，让用户更简单更安全的操作数据库。这个封装好的东西就是ORM。

 Django默认使用sqlite3作为数据库，无需额外安装或配置，以下为MySQL的安装与配置。


#安装模块
pip install mysqlclient


#创建数据库
登录MySQL："mysql -u root -p"
创建数据库："CREATE DATABASE manager(数据库名);"

#django连接数据库
1、打开settings.py
2、找到DATABASES字典（Django默认配置的是sqlite）
DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.sqlite3',
        'NAME': BASE_DIR / 'db.sqlite3',
    }
}
3、我们按以下参数格式配置MySQL连接
'default': {
    'ENGINE': 'django.db.backends.mysql',	# Django的引擎，还可以用Oracle等
    'NAME': 'dbname',	# 数据库名
    'USER': 'root',		# 用户名
    'PASSWORD': 'xxx',	# 密码
    'HOST': '',			# 数据库服务器地址
    'PORT': 3306,		# 端口号（MySQL默认3306）
}
4、连接的是本地的MySQL，所以HOST是localhost或者127.0.0.1，数据库名和密码填自己的即可。


#增加表
在相应【app/models.py】中写一个继承于 models.Model 类就是创建一张表。

class UserInfo(models.Model):
    # 创建字段
    name = models.CharField(max_length=32)
    password = models.CharField(max_length=64)
    age = models.IntegerField()

ORM会帮我们把这个面向对象的代码转化成SQL（表名是app名称_类名），与上面代码对应的SQL大致为：

create table index_userinfo(
    id bigint auto_increment primary key,		【django创建表自带自增字段】
    name varchar(32),
    password varchar(64),
    age int,
);

到terminal界面下执行命令，通过manage.py来让ORM读取我们写好的models.py中的代码。
"python manage.py makemigrations"
"python manage.py migrate"

刷新一下数据库，就可以看到很多django创建出来的表了

生成表的原理是django去所有app的models.py中找需要创建的表，在settings.py中可以看到，
django有很多默认自带的app，所以除了index_userinfo表，其他表都是django自带app生成的表，暂先不用管。


#删除表
把models.py中类注释掉，然后再执行那两个指令即可删除表
"python manage.py makemigrations"
"python manage.py migrate"


#修改表
修改表就是增删或修改表中的字段，我们删除就直接注释，增加就直接加，修改就改代码中对应变量名。然后执行两个命令。

sex = models.CharField(max_length=2)                        #增加字段
nickname = models.CharField(max_length=64, default='-w-')   #增加字段，并给定默认值

"python manage.py makemigrations"
"python manage.py migrate"

在没有指定默认值的情况下，不可能向userinfo添加不可为空的字段“sex”。这是因为数据库需要一些东西来填充现有的行。
请选择一个修复:
1)现在提供一次性默认值(将在所有现有行上设置，并且此列为空值)
2)退出并在models.py中手动定义一个默认值。
选择（1）：Select an option: 1

请输入默认值作为有效的Python。
datetime和django.utils.timezone模块是可用的，因此可以提供例如timezone.now作为值。
键入“exit”退出该提示
输入默认值：>>> 1


#表内增删改查
如上，我们可以通过操作对象的方式，免去一大堆SQL语句，从而通过用django来操作表的结构。
同样的，django还给我们提供了方法来操作表中的数据。这些方法是写在视图函数中的，调用相应models.py中的类即可，最后我们演示。

增
    类名.objects.create()
    StudentInfo.objects.create(title="Alice")          # insert into index_studentinfo(title) values("Alice");
    UserInfo.objects.create(name="gzh", password="123", age=18) # insert into index_userinfo(name,password,age) values("gzh","123",18);

删
    类名.objects.filter().delete()：筛选内容，再删除
    类名.objects.all().delete()：删除表内全部内容
    UserInfo.objects.filter(id=2).delete()	# 删除表中id为2的删除
    StudentInfo.objects.all().delete()		# 删除表中所有内容

改
    类型.objects().all().update()：修改全部
    类型.objects().filter().update()：筛选内容，再修改
    UserInfo.objects().all().update(password="123")		    # 把表中password全改成123
    UserInfo.objects().filter(id=2).update(password="1")	# 把表中id为2的那行数据的password改成1

查
    类名.objects.all()：查询表中所有数据
    类名.objects.filter()：筛查相应的数据
    注意：返回的数据都是一个QuerySet类型数据，可以理解为List，只是每个元素是一个对象罢了。

    all_data = UserInfo.objects.all()
    for obj in all_data:
        print(obj.id, obj.name, obj.password, obj.age)

    # UserInfo.objects.filter(id=1)		# 获得一行数据，但是也是QuerySet的一个列表，只是只有一个元素
    # 所以可以通过first()来取到第一个单独的元素
    data = UserInfo.objects.filter(id=1).first()
    print(data.id, data.name, data.password, data.age)


#显示数据表
【views.py】
def user_list(request):
    from index.models import UserInfo
    all_data = UserInfo.objects.all()
    return render(request, "user_list.html", {"user_list": all_data})

【user_list.html】
<table border="1">
    <thead>
        <tr>
            <td>ID</td>
            <td>姓名</td>
            <td>密码</td>
            <td>年龄</td>
        </tr>
    </thead>
    <tbody>
        {% for user in user_list %}
        <tr>
            <td>{{ user.id }}</td>
            <td>{{ user.name }}</td>
            <td>{{ user.password }}</td>
            <td>{{ user.age }}</td>
        </tr>
        {% endfor %}
    </tbody>
</table>

#增加记录
【views.py】
def user_add(request):
    if request.method == "GET":
        return render(request, "user_add.html", {"msg": ""})

    elif request.method == "POST":
        get_post = request.POST
        username = get_post.get("username")
        pwd = get_post.get("password")
        age = get_post.get("age")

        from index.models import UserInfo
        UserInfo.objects.create(name=username, password=pwd, age=int(age))

        if UserInfo.objects.filter(name=username):
            return redirect("http://127.0.0.1:8000/user/list/")
        else:
            msg = "提交失败"
            return render(request, "user_add.html", {"msg": msg})

【user_add.html】
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>用户添加</title>
</head>
<body>
    <h1>用户添加</h1>
    <form method="post" action="/user/add/">
        {% csrf_token %}
        <label>用户名：
            <input type="text" name="username" placeholder="用户名">
        </label>
        <label>密码：
            <input type="password" name="password" placeholder="密码">
        </label>
        <label>年龄：
            <input type="text" name="age" placeholder="年龄">
        </label>
        <input type="submit" value="提交">{{ msg }}
    </form>
</body>
</html>


# model中字段对象常用的方法参数
max_length          一般是CharField()中用，字符的最大长度
verbose_name        用来注释字段名，方便别人知道该字段是什么意思。如果调用django的admin模块来后台管理的话，字段名会自动替换成verbose_name
primary_key         声明主键，主键是唯一且非空的，一般都是写primary_key=True，不写则默认为 False
default             默认值
max_digits          DecimalField()用，规定数字最长是多少（不包括正负号）
decimal_places      DecimalField()用，规定显示小数点后几位
null&blank          声明该字段可以为空，组合使用，一般都是写null=True, blank=True，不写则默认为 False
choices             添加django的约束，给这个参数赋值时得用元组


#设置表间关系：外键
每个员工有自己属于的部门，需要设置字段来表示，而且部门与员工之间是一对多的关系，需要在"多"的那个表设置外键

PS:一般表间联系都是用 id，而不是用名称这种的字段名。因为 id 字段存储消耗小，这样节省存储开销。
Q：不写外键行不行？直接声明一个整型字段，存部门 id。
A：这样是不行的。因为这个关系是有约束的，部门 id 必须是部门表内存在的 id，而不是乱填的。所以还是老老实实用外键。

在员工表中设置外键：
dep = models.ForeignKey(to="Department", to_field="id") #生成表后，django会自动在此字段名后加上_id，即dep_id。
假设部门表有部门被裁撤了，那么员工表中，原属于该部门的员工改怎么办？
不管？肯定是不行的，因为上面说到了，这个关系是有约束的，dep_id必须在部门表中存在此id，对此，有许多解决方法：

1、删除关联的员工：一般叫级联删除，相应参数为 on_delete=models.CASCADE
2、不删置为空：这样写，必须设置允许该字段可以为空，相应参数为 null=True, blank=True, on_delete=models.SET_NULL

这里我们就设置级联删除：dep = models.ForeignKey(to="Department", to_field="id", on_delete=models.CASCADE)


class Department(models.Model):
	"""部门表"""
	dep_name = models.CharField(verbose_name="部门名称", max_length=32)


class Employee(models.Model):
	"""员工表"""
	name = models.CharField(verbose_name="员工姓名", max_length=16)
	password = models.CharField(verbose_name="员工密码", max_length=64)
	age = models.IntegerField(verbose_name="员工年龄")
	account = models.DecimalField(verbose_name="账户余额", max_digits=10, decimal_places=2, default=0)
	create_time = models.DateTimeField(verbose_name="入职时间")

	# 添加Django中的约束
	gender_choices = (
		(1, "男"),
		(2, "女"),
	)
	gender = models.SmallInterField(verbose_name="员工性别", choices=gender_choices)

	#生成表时，Django会生成dep_id字段而不是dep字段
	dep = models.ForeignKey(to="Department", to_field="id", on_delete=models.CASCADE)



('''********************'''其它'''************************************************************'''
【setting.py】
LANGUAGE_CODE = 'zh-hans'       #中文


#ModelForm
常用的数据库模型表单


#切片（filter和all都可以）
Employee.objects.all()	        # 获取全部数据
Employee.objects.all()[0:10]	# 获取前10条数据



