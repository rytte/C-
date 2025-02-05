Vue 专门为 class 和 style 的 v-bind 用法提供了特殊的功能增强。除了字符串外，表达式的值也可以是对象或数组。

<!--绑定 HTML class-->
<div :class="{ active: isActive }"></div>     active 是否存在取决于数据属性 isActive 的真假值

<!--:class 指令也可以和一般的 class attribute 共存-->
const isActive = ref(true)
const hasError = ref(false)
<div class="static"
     :class="{ active: isActive, 'text-danger': hasError }"></div>
渲染结果：<div class="static active"></div>

<!--也可以绑定对象-->
const classObject = reactive({
  active: true,
  'text-danger': false
})
<div :class="classObject"></div>
渲染结果：<div class="active"></div>
也可以绑定一个返回对象的计算属性。

<!--绑定数组-->
const activeClass = ref('active')
const errorClass = ref('text-danger')
<div :class="[activeClass, errorClass]"></div>
渲染结果：<div class="active text-danger"></div>

<!--对于只有一个根元素的组件，class 会合并-->
<p class="foo bar">Hi!</p> <!-- 子组件模板 -->
<MyComponent class="baz boo" /> <!-- 在使用组件时 -->
渲染结果：<p class="foo bar baz boo">Hi!</p>

<!--对于有多个根元素的组件-->
你将需要指定哪个根元素来接收这个 class。你可以通过组件的 $attrs 属性来指定接收的元素：
【MyComponent.vue】
<p :class="$attrs.class">Hi!</p>
<span>This is a child component</span>
使用：
<MyComponent class="baz" />
这将被渲染为：
<p class="baz">Hi!</p>
<span>This is a child component</span>


<!--绑定样式-->
绑定style样式与绑定class基本相同

<!--样式多值-->
当你在 :style 中使用了需要浏览器特殊前缀的 CSS 属性时，Vue 会自动为他们加上相应的前缀。
Vue 是在运行时检查该属性是否支持在当前浏览器中使用。
如果浏览器不支持某个属性，那么将尝试加上各个浏览器特殊前缀，以找到哪一个是被支持的。
<div :style="{ display: ['-webkit-box', '-ms-flexbox', 'flex'] }"></div>
你可以对一个样式属性提供多个 (不同前缀的) 值，数组仅会渲染浏览器支持的最后一个值。
在这个示例中，在支持不需要特别前缀的浏览器中都会渲染为 display: flex








