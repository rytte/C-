/********************/HTTP协议/************************************************************/
//HTTP介绍
HTTP（HyperText Transfer Protocol，超文本传输协议）是一种 无状态、基于请求 - 响应模型 的应用层协议，
用于在 客户端（浏览器等）和 服务器 之间传输网页、图片、视频等资源。

//HTTPS介绍
HTTPS（HyperText Transfer Protocol Secure，超文本传输安全协议）是一种通过计算机网络进行安全通信的传输协议。
HTTPS 经由 HTTP 进行通信，但利用 SSL / TLS 来加密数据包，HTTPS 开发的主要目的，是提供对网站服务器的身份认证，保护交换资料的隐私与完整性。

//默认端口
HTTP:80
HTTPS:443。

//HTTP工作原理
HTTP使用 URI 来传输数据和建立连接。
浏览器通过 URL 向 WEB 服务器发送请求，Web 服务器根据接收到的请求后，向客户端发送响应信息。

//URL和URI
URI（统一资源标识符）和 URL（统一资源定位符）都用于标识互联网上的资源（URL属于URI）
URI示例：ftp://ftp.example.com/resource        //仅标识了一个资源的位置
URL示例：https://www.example.com/index.html    //不仅标识了资源，还指定了使用 https 协议和 www.example.com 主机来获取资源的位置



//HTTP 请求/响应流程
1. 客户端连接到 Web 服务器：客户端（如浏览器）与 Web 服务器的 HTTP 端口（默认 80，HTTPS 为 443）建立 TCP 连接。
2. 发送 HTTP 请求：客户端通过 TCP 连接 发送 HTTP 请求   //包含4部分：请求行、请求头部、空行、请求数据
3. 服务器处理请求并返回 HTTP 响应：Web 服务器 解析请求，定位所请求的资源，并返回 HTTP 响应 //包含4部分：状态行、响应头部、空行、响应数据
4. 释放 TCP 连接
短连接（Connection : close）：服务器返回响应后，主动关闭 TCP 连接，客户端被动关闭。
长连接（Connection : keep - alive）：TCP 连接会 保持一段时间，允许多个请求复用该连接，提高效率。
5. 客户端解析 HTTP 响应
客户端 解析状态行，检查状态码是否为 200 OK（请求成功）。
解析 响应头，获取数据类型、编码格式等信息。
读取并解析 HTML、CSS、JS、图片等资源，渲染网页并展示给用户。


//实例：在浏览器地址栏键入URL，按下回车之后会经历以下流程：
1. 浏览器向 DNS 服务器请求解析该 URL 中的域名所对应的 IP 地址;
2. 解析出 IP 地址后，根据该 IP 地址和服务器的默认端口 80，和服务器建立TCP连接;
3. 浏览器发出读取文件(URL 中域名后面部分对应的文件)的HTTP 请求，该请求报文作为 TCP 三次握手的第三个报文的数据发送给服务器;
4. 服务器对浏览器请求作出响应，并把对应的 html 文本发送给浏览器;
5. 释放 TCP连接;
6. 浏览器将该 html 文本并显示内容;


//特点
1、基于 请求 - 响应 的模式：请求从客户端发出, 最后服务器端响应该请求并 返回。
2、无状态保存：不对请求和响应之间的通信状态进行保存。
3、无连接：无连接的含义是限制每次连接只处理一个请求。
4、服务器处理完客户的请求，并收到客户的应答后，即断开连接。采用这种方式可以节省传输时间，并且可以提高并发性能



————————————————————————————————————————————————————
//报文示例
HTTP1.1 Request
R"(
GET /index.html HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:98.0) Gecko/20100101 Firefox/98.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
)"

HTTP1.1 Response
R"(
HTTP/1.1 200 OK
Date: Wed, 19 Mar 2025 12:00:00 GMT
Server: Apache/2.4.41 (Ubuntu)
Content-Type: text/html; charset=UTF-8
Content-Length: 1234
Connection: keep-alive

<html>
<head><title>Example Page</title></head>
<body>
    <h1>Hello, World!</h1>
</body>
</html>
)"


//HTTP八种请求方法
GET			请求指定的资源（如网页、图片等），不会修改服务器数据。
POST		向服务器提交数据，通常用于表单提交、上传文件等。
PUT			向服务器上传资源，通常用于更新已有数据。
PATCH		用于 部分更新 资源，与 PUT 不同，PUT 更新整个资源，而 PATCH 只修改部分字段。
DELETE		删除指定资源
HEAD		类似 GET 请求，但 只返回响应头，不返回响应体。
OPTIONS		用于获取服务器支持的 HTTP 方法，常用于 CORS 预检请求。
TRACE		服务器会返回 请求的原始内容，用于调试或诊断网络问题。


//注意事项
1、方法名称区分大小写。
2、当某个请求所针对的资源不支持对应的请求方法的时候，服务器应当返回状态码405（Method Not Allowed），
3、当服务器不认识或者不支持对应的请求方法的时候，应当返回状态码501（Not Implemented）。
4、HTTP服务器至少应该实现 GET 和 HEAD 方法，其他方法都是可选的。


//HTTP 响应头信息
应答头	            说明

Allow	            服务器支持哪些请求方法（如GET、POST等）。
Content - Encoding	文档的编码（Encode）方法。
Content - Length	    表示内容长度。
Content - Type	    表示后面的文档属于什么MIME类型。
Date	            当前的GMT时间。
Expires	            应该在什么时候认为文档已经过期，从而不再缓存它。
Last - Modified	    文档的最后改动时间。
Location	        表示客户应当到哪里去提取文档。
Refresh	            表示浏览器应该在多少时间之后刷新文档，以秒计。
Server	            服务器名字。
Set - Cookie	        设置和页面关联的Cookie
WWW - Authenticate	客户应该在Authorization头中提供什么类型的授权信息。


//HTTP 状态码
当浏览者访问一个网页时，浏览者的浏览器会向网页所在服务器发出请求。
当浏览器接收并显示网页前，此网页所在的服务器会返回一个包含 HTTP 状态码（HTTP Status Code）的信息头（server header）用以响应浏览器的请求。

常见的 HTTP 状态码：
200 - 请求成功
301 - 资源（网页等）被永久转移到其它URL
404 - 请求的资源（网页等）不存在
500 - 内部服务器错误


//HTTP 状态码分类
HTTP 状态码由三个十进制数字组成，第一个十进制数字定义了状态码的类型。
响应分为五类：信息响应(100–199)，成功响应(200–299)，重定向(300–399)，客户端错误(400–499)和服务器错误(500–599)：

分类	    分类描述
1xx     信息，服务器收到请求，需要请求者继续执行操作
2xx     成功，操作被成功接收并处理
3xx     重定向，需要进一步的操作以完成请求
4xx     客户端错误，请求包含语法错误或无法完成请求
5xx     服务器错误，服务器在处理请求的过程中发生了错误



/********************/HTTP2.0/************************************************************/
//对比
特性          HTTP/1.1                           HTTP/2.0
协议格式      文本格式	                        二进制格式
连接复用	     不支持多路复用，每个请求需要一个连接	支持多路复用，所有请求通过一个连接
头部压缩	     无压缩，头部信息重复传输	            使用 HPACK 压缩头部信息
服务器推送	 不支持	                            支持服务器推送资源
优先级	     无优先级支持                        支持流的优先级
性能优化	     受到队头阻塞影响                    解决队头阻塞，提供更好的性能


//报文示例
HTTP2.0 Request
R"(
:method: GET
:scheme: https
:authority: www.example.com
:path: /index.html
user-agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:98.0) Gecko/20100101 Firefox/98.0
accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
accept-language: en-US,en;q=0.5
accept-encoding: gzip, deflate
)"


//报文格式
HTTP / 2.0 使用二进制帧结构，每个请求和响应都被分解成多个 帧（Frame）。这些帧可以有不同的类型，常见的类型包括：
1、数据帧（DATA）：包含实际的数据部分，如 HTML、图片、CSS 等。
2、头部帧（HEADERS）：包含请求或响应的头部信息。
3、设置帧（SETTINGS）：用于协商和配置客户端与服务器之间的连接设置。
4、优先级帧（PRIORITY）：指定流的优先级。
5、窗口更新帧（WINDOW_UPDATE）：用于流量控制。