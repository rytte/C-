/*************************/BOM/***************************************************************************/

浏览器对象模型（Browser Object Model(BOM)）可以使我们通过JS来操作浏览器，常见的BOM对象如下：

Window：代表的是整个浏览器的窗口，同时window也是网页中的全局对象
Navigator：代表当前浏览器的信息，通过该对象可以来识别不同的浏览器
Location：代表当前浏览器的地址栏信息，通过Location可以获取地址栏信息，或者操作浏览器跳转页面
History：代表浏览器的历史记录，通过该对象来操作浏览器的历史记录，由于隐私原因，该对象不能获取到具体的历史记录，只能操作浏览器向前或向后翻页，而且该操作只在当次访问时有效
Screen：代表用户的屏幕的信息，通过该对象可以获取到用户的显示器的相关的信息



/*************************/Window对象/***************************************************************************/
window对象的方法可以不带window前缀直接使用

//弹出框：警告框
window.alert("我是一个警告框！");

//弹出框：确认框
window.confirm("sometext");		//单击“确定”，该框返回 true。如果用户单击“取消”，该框返回 false。

var r = confirm("请按按钮");
if (r == true)
    x = "您按了确认！";
else
    x = "您按了取消！";

//弹出框：提示框
window.prompt("sometext", "defaultText");

//定时事件
setTimeout(function, milliseconds)      //在等待指定的毫秒数后执行函数，只执行一次
setInterval(function, milliseconds)     //每隔指定毫秒数后执行

//窗口属性
window.innerHeight - 浏览器窗口的内高度（以像素计）
window.innerWidth - 浏览器窗口的内宽度（以像素计）

//操作窗口
window.open(URL, name, specs, replace);     //打开新窗口
window.close();                             //关闭当前窗口
window.moveTo(x, y);                        //移动当前窗口
window.resizeTo(width, height);             //调整当前窗口



/*************************/Navigator对象/***************************************************************************/
Navigator代表的当前浏览器的信息，通过该对象可以来识别不同的浏览器，
由于历史原因，Navigator对象中的大部分属性都已经不能帮助我们识别浏览器了，一般我们只会使用userAgent来判断浏览器的信息，
userAgent是一个字符串，这个字符串中包含有用来描述浏览器信息的内容，不同的浏览器会有不同的userAgent，如下代码：

var ua = navigator.userAgent;
if (/ firefox / i.test(ua)) {
    alert("你是火狐浏览器");
}
else if (/ chrome / i.test(ua)) {
    alert("你是谷歌浏览器");
}
else if (/ msie / i.test(ua)) {
    alert("你是IE5-IE10浏览器");
}
else if ("ActiveXObject" in window) {
    alert("你是IE11浏览器");
}



/*************************/Location对象/***************************************************************************/
Location对象中封装了浏览器的地址栏的信息，如果直接打印location，则可以获取到地址栏的信息（当前页面的完整路径）

console.log(location);          //输出location对象
console.log(location.href);     //输出当前地址的全路径地址
console.log(location.origin);   //输出当前地址的来源
console.log(location.protocol); //输出当前地址的协议
console.log(location.hostname); //输出当前地址的主机名
console.log(location.host);     //输出当前地址的主机
console.log(location.port);     //输出当前地址的端口号
console.log(location.pathname); //输出当前地址的路径部分
console.log(location.search);   //输出当前地址的?后边的参数部分


//修改地址
location = "https://www.baidu.com";
location.href = "https://www.baidu.com";

//常用方法
location.assign("https://www.baidu.com");   //跳转到其它的页面，作用和直接修改location一样
location.reload(true);                      //重新加载当前页面，作用和刷新按钮一样，如果传入true作为参数，则会强制清空缓存刷新页面
location.replace("https://www.baidu.com");  //使用一个新的页面替换当前页面，调用完毕也会跳转页面，它不会生成历史记录，不能使用回退按钮回退



/*************************/History对象/***************************************************************************/
History对象可以用来操作浏览器向前或向后翻页

console.log(history);           //输出history对象
console.log(history.length);    //可以获取到当成访问的链接数量


//常用方法
history.back();                 //回退到上一个页面，作用和浏览器的回退按钮一样
history.forward();              //跳转到下一个页面，作用和浏览器的前进按钮一样
history.go(-2);                 //跳转N个页面，整数表示向前跳转，负数表示向后跳转



/*************************/Screen对象/***************************************************************************/
Screen 对象包含有关客户端显示屏幕的信息。每个 Window 对象的 screen 属性都引用一个 Screen 对象。

属性	                    描述
availHeight	            返回显示屏幕的高度(除 Windows 任务栏之外)。
availWidth	            返回显示屏幕的宽度(除 Windows 任务栏之外)。
bufferDepth	            设置或返回调色板的比特深度。
colorDepth	            返回目标设备或缓冲器上的调色板的比特深度。
deviceXDPI	            返回显示屏幕的每英寸水平点数。
deviceYDPI	            返回显示屏幕的每英寸垂直点数。
fontSmoothingEnabled	返回用户是否在显示控制面板中启用了字体平滑。
height	                返回显示屏幕的高度。
logicalXDPI	            返回显示屏幕每英寸的水平方向的常规点数。
logicalYDPI	            返回显示屏幕每英寸的垂直方向的常规点数。
pixelDepth	            返回显示屏幕的颜色分辨率（比特每像素）。
updateInterval	        设置或返回屏幕的刷新率。
width	                返回显示器屏幕的宽度。



