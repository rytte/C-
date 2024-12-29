/*************************/CSS选择器/***************************************************************************/
CSS (Cascading Style Sheets, 即层叠样式表简称样式表) 

//css3的新特性
选择器、文字颜色特效，背景和边框、盒子模型、布局、过度、动画、2D/3D转换


选择器 {
    属性: 属性值;
    属性: 属性值;
}

//css三种引入方式
内联式: <p style="color: aqua;font-weight: bold;font-size: 12">你好</p>;
内部式: "<style> p { color: red;font-weight: bold;font-size: 16;} </style >; ";
外链式: <link rel="stylesheet" href="../css/1.css">;   (最常用)


/*基本选择器*/
* {
    选中所有元素
}

标签名 {
    选中对应的标签
}

.类名 {
    选中所有对应指定类名的元素
}

#id名 {
    选中对应的id名元素
}


//id和类的区别 
id名唯一: 同一个页面只能有一个相同的id, 同一个元素只能有一个id;
类名不唯一: 一个元素可以有多个类名，不同元素可以有相同的类名; 
设置多个类名的方式: class="类名1 类名2  类名3";


//层次选择器
1、后代选择器
e f{ }      代表选中e的后代f

2、子代选择器
e > f{ }    代表选中e的儿子f

3、并列选择器
e, f{ }     代表选中e和f


//伪类选择器
鼠标悬停
e:hover{ }  鼠标悬停在e上面的样式设置   //注意：e:hover是一个整体，不准有空格之类
p>a:hover{
    color:red;
}

鼠标的四种状态，只有a标签有其他三种状态，其他标签只有悬停状态
e : link     未访问的链接
e : visited  已访问的链接
e : hover    鼠标悬停状态
e : active   选定的激活状态



/*************************/继承与优先级/***************************************************************************/
//继承
下级元素继承上级元素的CSS样式
文本相关属性和列表相关属性可以被继承

//优先级
!important > 行内样式 > #id > .类名 > 标签名 > * > 继承 > 默认

如果用到层级选择器，判断权重之和：权重越大越优先，权重之和一致，后面的覆盖前面
层级         权值
行内样式     1000
#id         100
类名        10
标签名      1

例如：.wrap.box p    21
例如：.wrap #box.m    #test  p    221



/*************************/字体属性 Font/***************************************************************************/
/* 设置字体样式 */
p{
    font - family: '微软雅黑', 'Arial', sans - serif; /* 字体类型，先匹配微软雅黑，没有则使用Arial，最后使用默认字体 */
    font - size: 16px;                               /* 设置字体大小为16px */
    font - weight: 700;                              /* 设置字体加粗 */
    font - style: italic;                            /* 设置字体为斜体 */
    line - height: 1.5;                              /* 设置行高为1.5倍行距，适用于多行文本 */
    text - decoration: underline;                    /* 添加下划线 */
    text - transform: capitalize;                    /* 首字母大写 */
    color: #FF5733;                                  /* 设置字体颜色为红橙色（使用十六进制） */
}

/* 设置类名 .header 的字体 */
.header{
    font: italic bold 20px / 30px 'Times New Roman', serif; /* font复合属性：斜体、加粗、20px 字号、30px 行高、字体为 Times New Roman */
    color: rgb(0, 0, 255);                                  /* 设置字体颜色为蓝色（使用RGB） */
}

/* 设置段落字体 */
div{
    font - family: '宋体', 'Arial', sans - serif; /* 字体为宋体，如果没有则使用Arial */
    font - size: 18px;                            /* 设置字体大小为18px */
    font - weight: 100;                           /* 设置字体为正常粗细 */
    line - height: 25px;                          /* 行高为25px */
    text - decoration: line - through;            /* 添加删除线 */
    color: black;                                 /* 字体颜色为黑色 */
}

//说明
字体类型(font - family) : 通过多个字体来确保浏览器有适合的字体。如果前一个字体不可用，则会使用下一个字体。
字体大小(font - size) : 支持绝对单位（如 px）和相对单位（如 em、rem），在不同设备上有不同的表现。
粗细(font - weight) : 可以使用 normal、bold 或数值（100 到 900），数值越大表示越粗。
斜体(font - style) : 可以设置为 italic（斜体）、normal（正常字体）或 oblique（倾斜字体）。
行高(line - height) : 控制文本的垂直间距，尤其适用于多行文本，通常设置为一个单位的倍数，或者具体的像素值。
文本修饰线(text - decoration) : none 表示无修饰，underline 表示添加下划线，line - through 添加删除线。
英文大小写转换(text - transform) : 用于控制文本的大小写显示，capitalize 会将每个单词的首字母大写，uppercase 会将文本全部转换为大写，lowercase 会将文本全部转换为小写。

//字体大小详细说明
* px    px是一个绝对尺寸
* em    em是相对大小   代表是它基于父亲字体大小的 * 倍
* rem   rem是相对大小  大小基于根元素（HTML）的字体大小



/*************************/CSS3新增选择器/***************************************************************************/
结构伪类选择器（重点中的重点）

//child系列
e:first-child   选中第一个子元素e
e:last-child    选中最后一个子元素e
e:nth-child(n)  选中中间的第n个元素，n是一个乘法因子，
可以是数字，
可以是英文单词（odd奇数 even偶数），
可以是数学表达式（在表达式中n代表0 - 无穷的正整数）2n 0 2....

li:nth-last-child(n)  倒数第n个
p:only-child          选中唯一的子元素p

注意 : child系列的排序是在父元素的所有子元素里面的排列顺序, 与类型无关


//type系列
.wrap>p:first-of-type  选中p元素中的第一个元素

//type和child区别
child系列是强调在所有的孩子里面的排列顺序（建议）
type系列强调是在所有同类型元素里面的排列顺序


//否定伪类选择器
.ul1 > li:not(:first - child)  除了第一个元素不选其余的都选
前后都为选择器

//伪类和伪元素
E : after 和 E：before
配合content使用 在e元素前后插入内容

//伪类和伪元素的区别
伪类是一种临时状态，只有被出发才能生效
伪元素是一种虚拟的dom节点（标签）
伪类使用单冒号，伪元素使用双冒号
:after和::after都是伪元素，版本不同写法不一致。为方便兼容性，也会使用单冒号

//css3新增的其他伪元素选择器
e::first - letter{  }       选中第一个字符
p::first - line{   }        选中第一行
input::placeholder{   }     设置占位符的样式
p::selection{     }         选中效果，不能设置文字大小



/*************************/文本属性text /***************************************************************************/
/* 示例 1: 设置文本的水平对齐方式 */
p{
    text - align: justify; /* 两端对齐 */
    text - shadow:10px 10px 10px grey ; /* 文本阴影 */
    color: #333; /* 设置字体颜色 */
}

/* 示例 2: 设置文本的垂直对齐方式 */
img{
    vertical - align: middle; /* 图片与文本垂直居中对齐 */
}

/* 示例 3: 设置段落首行缩进 */
p{
    text - indent: 2em; /* 首行缩进 2em */
    font - size: 16px; /* 设置字体大小 */
    line - height: 1.5; /* 设置行高 */
}

/* 示例 4: 设置文本的自动换行行为 */
div{
    white - space: nowrap; /* 禁止文本换行 */
    overflow: hidden; /* 超出部分隐藏 */
    text - overflow: ellipsis; /* 显示省略号 */
    width: 200px; /* 设置固定宽度 */
}

/* 示例 5: 设置字间距和词间距 */
h1{
    letter - spacing: 2px; /* 设置字间距 */
    word - spacing: 5px; /* 设置词间距 */
}

/* 示例 6: 设置文本的两端对齐，且有省略号效果 */
p{
    width: 150px;
    white - space: nowrap;
    overflow: hidden;
    text - overflow: ellipsis; /* 超出部分显示省略号 */
    text - align: justify; /* 两端对齐 */
}



/*************************/背景/***************************************************************************/
div{
    /* 设置背景颜色 */
    background - color: bisque; /* 设置背景颜色为淡米色 */

    /* 设置背景图片 */
    background - image: url('1.jpg'); /* 设置背景图片 */

    /* 设置背景图的平铺方式（不重复） */
    background - repeat: no - repeat; /* 背景图不重复 */

    /* 设置背景图的起始位置 */
    background - position: center bottom; /* 背景图从中间水平和底部垂直位置开始 */

    /* 设置背景图的大小 */
    background - size: 100px 100px; /* 设置背景图的大小为100px宽和100px高 */

    /* 背景复合属性，覆盖上面的背景设置 */
    background: bisque url('1.jpg') no - repeat center bottom; /* 设置背景颜色、背景图、不重复并定位在中间底部 */

    /* 可选，设置容器尺寸以便查看效果 */
    width: 400px;
    height: 300px;
}



/*************************/盒子模型/***************************************************************************/
/* 示例：综合盒子模型和布局属性 */

/* 盒子1：设置宽高、内外边距及边框 */
.div1{
    width: 200px;               /* 设置宽度为200px */
    height: 300px;              /* 设置高度为300px */
    border: 1px solid black;    /* 设置边框为1px实线黑色 */
    background - color: aquamarine; /* 设置背景颜色为水绿色 */
    margin - bottom: 40px;        /* 设置底部外边距为40px */
    padding: 10px;              /* 设置内边距为10px */
    box - sizing: border - box;     /* 包含边框和内边距在内的总宽高计算 */
}

/* 盒子2：设置宽高、内外边距及边框 */
.div2{
    width: 300px;               /* 设置宽度为300px */
    height: 200px;              /* 设置高度为200px */
    border: 1px solid black;    /* 设置边框为1px实线黑色 */
    background - color: bisque;   /* 设置背景颜色为米色 */
    margin - top: 30px;           /* 设置顶部外边距为30px */
    padding: 15px;              /* 设置内边距为15px */
    box - sizing: border - box;     /* 包含边框和内边距在内的总宽高计算 */
}

/* 父元素，防止子元素外边距塌陷 */
.parent{
    overflow: hidden;          /* 使用 overflow: hidden 防止垂直外边距塌陷 */
    background - color: lightgray; /* 设置父元素的背景颜色 */
    padding: 20px;             /* 给父元素添加内边距 */
}

/* 盒子3：带阴影和圆角 */
.div3{
    width: 150px;               /* 设置宽度为150px */
    height: 150px;              /* 设置高度为150px */
    border: 2px solid gray;     /* 设置边框为2px实线灰色 */
    background - color: lavender; /* 设置背景颜色为薰衣草紫 */
    border - radius: 10px;        /* 设置圆角半径为10px */
    box - shadow: 10px 10px 15px greenyellow; /* 设置外部阴影，偏移10px，绿色黄色 */
}

/* 盒子4：内阴影效果 */
.div4{
    width: 200px;               /* 设置宽度为200px */
    height: 200px;              /* 设置高度为200px */
    background - color: lightblue; /* 设置背景颜色为淡蓝色 */
    border - radius: 20px;        /* 设置圆角半径为20px */
    box - shadow: inset 0px 0px 10px rgba(0, 0, 0, 0.5); /* 设置内阴影 */
}

/* 盒子5：垂直外边距塌陷问题 */
.div5{
    width: 100 %;                /* 设置宽度为父容器的100% */
    height: 100px;              /* 设置固定高度 */
    background - color: lightgreen; /* 设置背景颜色为浅绿色 */
    margin - bottom: 20px;        /* 设置底部外边距为20px */
    padding: 10px;              /* 设置内边距为10px */
}

/* 盒子6：最小高度和最大高度 */
.div6{
    width: 250px;               /* 设置宽度为250px */
    min - height: 100px;           /* 设置最小高度为100px */
    max - height: 300px;          /* 设置最大高度为300px */
    background - color: peachpuff; /* 设置背景颜色为桃色 */
    padding: 15px;              /* 设置内边距为15px */
}



/*************************/标准模式与怪异模式/***************************************************************************/
// 什么是标准模式与怪异模式？
概念：他们是盒子模型的不同模式
有文档声明的都是标准模式，没有文档声明的在IE6, 7, 8就会展示为怪异模式
语法：box - sizing: content - box border - box；前者为标准模式，后者为怪异模式

//标准模式和怪异模式的区别
元素实际占用的宽高计算方式不一致。
标准模式的元素实际占用的宽度：width + margin + border + padding
怪异模式的元素实际占用的宽度：width + margin
盒子模型：尺寸 + margin + padding + border



/*************************/布局/***************************************************************************/
//浮动布局
浮动是一种定位属性，主要用于布局，实现一行多列效果
float: left / right;    左右浮动成一行，从左到右，从右到左。浮动会让元素脱离文档流（代码按照从上到下的顺序显示效果）

//清除浮动（清除浮动带来的影响）
方式1：给浮动元素的父亲设置高度

方式2：
给浮动元素最后面添加空的兄弟元素（什么样式都没有，内容都没有）
给该元素类名设置clear，设置样式，clear：both

方式3：给浮动元素的父亲设置类名clearfix
.clearfix:after{
    content: "";
    height : 0;
    display: block;
    clear: both;
}

方式4：给浮动元素的父亲设置overflow : hidden;

//清除浮动小结
方式1  只适用高度固定的情况
方式2   添加很多没意义的结构，不推荐
方式4   会有作弊嫌疑，不建议
推荐方式3
注意：多个元素排列一行，必须保证元素的实际宽度小于父亲的元素的宽度

多个元素排在一行，多个元素都要浮动

//超出隐藏
overflow : hidden; 当元素的内容超出设置的元素宽高时候，隐藏内容

//显示与隐藏
display : inline none block inline - block;

none：不显示，隐藏
block：以块元素的样子显示
inline ：以行级元素的样子显示
inline - block:以块级行元素的样子显示（可以设置宽高，且显示在一行）

//设置鼠标形状
cursor : pointer; 鼠标形状设置手型（低版本支持hand高版本支持pointer）



/*************************/定位/***************************************************************************/
//图片和背景图片的区别
1，数据从数据库来，使用img
2，数据经常更改的，使用img（产品图，广告图），不经常改的用背景
3，想要作为页面结构的使用img
4，精灵图，使用背景图

//定位的概念
概念：将一个元素放在指定的位置上

//定位的语法
语法：position:relative static absolute fixed; (定位方式)
坐标：
left right : *px
top bottom : *px

static： 静态定位，元素按照默认位置显示
relative ：相对定位  基于元素本身的位置 会占据原来的位置
fixed：   固定定位，基于浏览器窗口的位置判定
absolute ：绝对定位  基于最近的被设置非静态定位（relative ，fixed，absolute ）的上级元素的位置定位

盒子完全居中于未知大小的盒子（应用场景广告，回到顶部，楼层跳转，顶部固定的导航）

div{
    width: 300px;
    height: 200px;
    background - color:pink;
    position: fixed;
    top: 50 %;
    margin - top: -100px;
    left: 50 %;
    margin - left: -150px;
}

div{
    width: 300px;
    height: 200px;
    background - color:pink;
    position: fixed;
    top: 0 %;
    bottom: 0 %;
    left: 0 %;
    right: 0 %;
    margin: auto;
}

//z - index属性
概念：设置元素在z轴上的堆叠层次
语法：z - index:数字;
说明：每个元素默认的z - index值大的会覆盖小的（默认的为0）
注意：元素如果要设置z - index，该元素必须被设置非静态定位，搭配position使用 否则无效果



/*************************/CSS hack以及CSS常用的样式/***************************************************************************/
//CSS hack
概念：针对不同的浏览器或者不同版本的浏览器，写不一样的css代码的过程


//CSS hack分类
1，css属性前缀法：针对不同浏览器添加特定浏览器能识别的属性前缀
div{
    color: red;
    *color:red;     //IE6
    +color: red;    //IE7
}

2，选择器前缀法：在特定浏览器前添加特定浏览器能识别的选择器
div{}
*div{}  //IE6
*+div{} //IE7

3，IE条件注释法：专门针对IE浏览器的hack方式


//css3添加私有前缀
添加的前缀        代表的浏览器         浏览器内核
- o -            欧朋                 presto
- ms -           IE                   trident
- moz -          火狐                 gecko
- webkit -       谷歌                 webkit


//css常用样式
三角形实现
div{
    width: 0px;
    height: 0px;
    border - top: 100px solid red;
    border - bottom: 100px solid transparent;
    border - left: 100px solid transparent;
    border - right: 100px solid transparent;
}

通过伪元素实现三角形
.wrap::after{
    content: "";
    display: block;
    width: 0px;
    height: 0px;
    border: 8px solid transparent;
    border - left: 8px solid pink;
}

//css精灵(sprites)图像拼合技术
精灵图又叫雪碧图

实现步骤
1，实现一个指定的盒子大小
2，将精灵图设置为该盒子的背景图
3，设置背景图的起始位置，以达到显示想要的图

精灵图的优缺点
优点：减少请求的次数，提升网站的性能，减少图片的文件数目
缺点：开发过程复杂，需要测量每个背景图的精确位置，进行定位，后期新加或者删除图标比较麻烦

//定位技巧（子绝父相：儿子绝对定位父亲相对定位）
给儿子元素设置相对定位，作为参照的父亲设置绝对定位

//一行两列
1，设置盒子的宽度
2，给盒子设置浮动
注意：两个盒子实际占用的宽度之和要小于等于父亲的宽度

//一行多列
1，设置盒子的宽度
2，除最后一个盒子右浮动外其余都左浮动

//设置元素透明度
透明度在0 - 1之间

img{
    opacity: 0.5;
}
img:hover{
    opacity : 1;
}

