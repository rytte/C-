<!DOCTYPE html>								//<!DOCTYPE html> 是一个声明，表示该文档是由 HTML5 进行编写的
<html>										//<html>用于告诉告诉浏览器其自身是一个 HTML 文档
	<head>									//<head>标签用于定义文档的头部，它是所有头部元素的容器
		<base href = "../img/" target = "_blank">	//<base> 标签用于设置相对 URL 的解析基准，让 HTML 文档中的相对链接在此基础上进行解析
		<meta name = "viewport" content = "width=device-width, initial-scale=1.0">	//<meta> 标签用于描述页面内容，关键词，作者，最新修订时间以及其它元信息。永远位于<head>内部。
		<title>第一个程序</title>				//<title>指定网页标题
	</head>
	<body>									//<body> 标签定义文档的主体，包含文档的所有内容（比如文本、超链接、图像、表格和列表等等）
		<h1>Hello World</h1>					//<h1>~<h6>表示标题，从大到小
		<p>I love myself!</p>					//<p>定义一个段落，会自动在前后创建一些空白
		<p>abcd<br>efg</p>					//<br>标签用于插入一个简单的换行符
		<hr>								//<hr> 标签用于在 HTML 页面中创建一条水平分隔线
		<p dir = "ltr">hijklmn</p>				//dir 属性规定元素内容的文本方向。dir 属性在以下标签中无效：<base>, <br>, <frame>, <frameset>, <hr>, <iframe> 以及 <script>。
		<!--在此处写注释-->					//<!--...--> 用来在源文档中插入注释。注释不会在浏览器中显示
		<style type = "text/css">				//<style> 标签用于为 HTML 文档定义样式信息。
	h1{ color: red; background: black }					//h1标签内容将被设置为红色，背景为黑色
			p{ color: blue }							//p标签内容将被设置为蓝色
		</style>
		</body>
</html>




<base>标签
属性		值									描述
href		URL									指定该 HTML 文档中所有相对链接的基准 URL。
target	_blank、_parent、_self、_top、framename	指定在何处打开超链接。
											_blank：在新窗口中打开
											_parent：在当前的父窗口中打开，如果不存在父窗口，此选项的行为方式与 _self 等同
											_self：当前窗口打开（默认）
											_top：在整个窗口中打开
											framename：在指定的框架中打开


<meta>标签
属性			值									描述
charset		character_set							指定 HTML 文档的编码。
content		text									指定与 http - equiv 或 name 属性相关的值。
http - equiv	content - type、default - style、refresh		content - type：另一种声明 HTML 文档作用字符编码的方法（<meta http - equiv = "content-type" content = "text/html charset=UTF-8">）。
												default - style：指定页面优先使用的样式表。
												refresh：以秒为单位指定一个时间间隔，在此时间过去之后将从服务器重新载入当前页面。也可以另行指定一个 URL 让浏览器载入。
name		application - name、author、description、generator、keywords、viewport		
												application - name：当前页所属 Web 应用系统的名称。
												author：当前页的作者名。
												description：当前页的内容描述。
												generator：用来生成 HTML 的软件名称。
												keywords：当前页的关键词。
												viewport：网页尺寸自适应。
实例：
实例一：指定网页编码
<meta charset = "UTF-8">
实例二：为搜索引擎提供关键词
<meta name = "keywords" content = "小甲鱼,Web开发,HTML5,CSS3,Web编程教学">
实例三：描述网页内容
<meta name = "description" content = "《零基础入门学习Web开发》案例演示">
实例四：定义网页的作者
<meta name = "author" content = "小甲鱼">
实例五：设置网页尺寸自适应
<meta name = "viewport" content = "width=device-width, initial-scale=1.0">
实例六：每 5 秒刷新一下浏览器并跳转到指定页面
<meta http - equiv = "refresh" content = "5;http://bbs.fishc.com">


<title>标签
属性	值	描述
lang	language_code	规定元素中内容的语言代码。


dir属性值
值		描述
auto		让浏览器根据内容来判断文本方向。仅在文本方向未知时推荐使用。
ltr		默认。从左向右的文本方向。
rtl		从右向左的文本方向。


<style>标签 
属性		值														描述
media	screen、tty、tv、projection、handheld、print、braille、aural、all	指定样式适用的媒体。
scoped	scoped													指定样式的作用范围（如果使用该属性，则样式仅仅应用到 style 元素的父元素及其子元素）。
type		text / css													指定样式的类型。


