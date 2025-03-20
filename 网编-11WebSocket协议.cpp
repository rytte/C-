/********************/WebSocket协议/************************************************************/

//WebSocket
WebSocket 是一种 全双工通信协议，它建立在 TCP 连接 之上，允许 客户端 和 服务器 之间进行 实时双向数据传输。
相比于传统的 HTTP 轮询方式，WebSocket 具有 低延迟、高效率 的特点，广泛应用于在线聊天、股票推送、在线游戏、实时通知等场景。


//1. WebSocket 特点
✅ 全双工通信（Full - Duplex）//客户端和服务器都可以主动发送数据
✅ 基于 TCP 连接				 //WebSocket 连接建立后，会保持 TCP 连接，无需每次请求都建立新的连接，减少了连接握手的开销
✅ 减少 HTTP 头部开销		 //WebSocket 只在握手阶段使用 HTTP 头部，之后数据传输是 轻量级帧，减少了不必要的流量消耗。
✅ 支持跨域					 //WebSocket 遵循 同源策略，但可以通过服务器配置"Access-Control-Allow-Origin"来允许跨域访问，比 Ajax 跨域更灵活。
✅ 支持心跳机制				 //WebSocket 允许客户端或服务器定期发送 Ping/Pong 帧，保持连接活跃，避免因长时间无数据传输导致连接断开。


//2. WebSocket 连接建立过程
WebSocket 连接建立需要经过 HTTP 握手（Upgrade 请求），然后升级为 WebSocket 协议。

📌 连接流程
1、客户端发送 WebSocket 连接请求
采用 HTTP GET 请求，头部包含 Upgrade : websocket 和 Connection : Upgrade 来表示升级为 WebSocket。示例请求如下：
R"(
GET /chat HTTP/1.1
Host: example.com
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==
Sec-WebSocket-Version: 13
)"

2、服务器响应 WebSocket 连接
服务器检查 Upgrade 头部，如果支持 WebSocket，则返回 101 Switching Protocols 状态码，表示协议升级成功。示例响应如下：
R"(
HTTP/1.1 101 Switching Protocols
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo=
)"

3、连接建立，开始数据传输
WebSocket 连接建立后，客户端和服务器可以通过 帧（Frame） 进行数据传输，不需要每次发送请求。

4、连接关闭
WebSocket 连接可以由客户端或服务器主动关闭，使用 Close 帧来通知对方断开连接。


//3. WebSocket 数据格式
WebSocket 采用 帧（Frame） 进行数据传输，每个帧的结构如下：

字段				长度						说明
FIN				1bit					是否为消息的最后一帧
Opcode			4bit					操作码（文本、二进制、Ping、Pong 等）
Mask			1bit					是否对数据进行掩码（客户端必须为 1，服务器可以为 0）
Payload Length	7bit / 16bit / 64bit	负载数据的长度
Masking Key		32bit					掩码键（仅客户端发送数据时使用）
Payload Data	可变						具体传输的数据

//常见操作码（Opcode）
0x1 - 文本数据（Text Frame）
0x2 - 二进制数据（Binary Frame）
0x8 - 关闭连接（Close Frame）
0x9 - Ping（心跳检测）
0xA - Pong（响应心跳）


//4. WebSocket 与 HTTP 长轮询的区别
特性	WebSocket	HTTP 长轮询
连接方式	一次握手，长连接	每次请求创建新的 HTTP 连接
服务器推送	支持，服务器可以主动推送数据	服务器无法主动推送，需等待客户端请求
开销	低，仅初次建立时有开销	高，每次轮询都要建立 HTTP 连接
数据传输	轻量级帧格式	传统 HTTP 头部，冗余较大
延迟	低，实时性高	高，受请求间隔限制


//WebSocket 相关协议
RFC 6455：WebSocket 标准协议
WS（"ws://"）：WebSocket 非加密连接
WSS（"wss://"）：WebSocket 加密连接（类似 HTTPS）



/********************/WebSocket 实例/************************************************************/
📌 JavaScript（客户端）

// 创建 WebSocket 连接
let socket = new WebSocket("ws://localhost.com:8080");

// 监听连接打开
socket.onopen = function(event) {
    console.log("WebSocket 连接已建立");
    socket.send("Hello Server!"); // 发送消息
};

// 监听服务器消息
socket.onmessage = function(event) {
    console.log("收到消息:", event.data);
};

// 监听错误
socket.onerror = function(error) {
    console.log("WebSocket 错误:", error);
};

// 监听连接关闭
socket.onclose = function(event) {
    console.log("WebSocket 连接已关闭");
};


/************************************************************/
📌 Python（服务器端）

import asyncio
import websockets

async def handle_message(websocket, path) :
    async for message in websocket :
        print(f"收到客户端消息: {message}")
        await websocket.send(f"服务器回复: {message}")

// 启动 WebSocket 服务器
start_server = websockets.serve(handle_message, "localhost", 8080)

asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()



/********************/WebSocket实践优化/************************************************************/
[技巧]	        [关键点]
连接管理	        断线重连、指数退避、心跳检测
数据优化	        使用 JSON / 二进制，消息分片
服务器优化	    连接数限制、负载均衡
安全性	        认证（JWT）、使用 WSS、防止 DoS


/************************************************************/
//连接重试
WebSocket 连接可能会因为网络波动、服务器崩溃等原因断开，因此客户端应该支持自动重连
📌 技巧：
1、指数退避（Exponential Backoff）可以减少短时间内的高频重试，防止服务崩溃。
2、最大重试时间可避免指数增长无限延长等待时间。
3、结合随机抖动（Jitter），防止多个客户端同步重试导致雪崩效应。

//实例
let socket;
let reconnectAttempts = 0; // 记录重连次数
const maxDelay = 30000; // 最大等待时间 30s

function connectWebSocket() {
    socket = new WebSocket("ws://localhost:8080");

    socket.onopen = () = > {
        console.log("WebSocket 连接成功");
        reconnectAttempts = 0; // 连接成功后重置重连次数
    };

    socket.onmessage = (event) = > {
        console.log("收到消息:", event.data);
    };

    socket.onclose = () = > {
        console.log("WebSocket 连接关闭，尝试重连...");
        reconnectWithBackoff();
    };

    socket.onerror = (error) = > {
        console.log("WebSocket 错误:", error);
        socket.close(); // 关闭连接，触发 onclose
    };
}

function reconnectWithBackoff() {
    let delay = Math.min(Math.pow(2, reconnectAttempts) * 1000, maxDelay);  // 应用指数退避与最大重试时间
    console.log(`将在 ${ delay / 1000 } 秒后重试连接...`);

    setTimeout(() = > {
        reconnectAttempts++;
        connectWebSocket();
    }, delay);
}

connectWebSocket();


/************************************************************/
//心跳检测（Ping - Pong）
WebSocket 连接可能会因为长时间无数据传输而被中间网络设备（如防火墙、代理）断开，因此使用 心跳检测 保持连接：
1、客户端定期发送 "ping" 消息，如果服务器响应，则连接正常。
2、服务器定期发送数据，防止连接被断开。

📌 技巧：
1、设置超时机制，如果 3 次没有收到响应，主动关闭连接并尝试重连。
2、WebSocket 的 ping / pong 机制可以代替手动的 ping 消息，但不同库的支持情况不同。


//手动 ping / pong 示例
📌 JavaScript（客户端）

let heartbeatInterval;

function startHeartbeat() {
    heartbeatInterval = setInterval(() = > {
        if (socket.readyState == = WebSocket.OPEN) {
            socket.send("ping");
            console.log("发送心跳包");
        }
    }, 5000); // 每5秒发送一次
}


📌 Python（服务器端）

import asyncio
import websockets

async def handle_client(websocket, path) :
    async for message in websocket :
        if message == "ping" :
            await websocket.send("pong")  // 服务器回应 pong
        else :
            print(f"收到消息: {message}")
            await websocket.send(f"服务器回复: {message}")

start_server = websockets.serve(handle_client, "localhost", 8080)
asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()


/************************************************************/
//数据优化：使用 JSON 还是二进制（WebSocket Binary）
文本消息（JSON / Plain Text）：适合结构化数据，但 JSON 体积大。
二进制消息（ArrayBuffer / Blob）：适合图片、音频、视频等数据传输，减少带宽占用。

📌 技巧：
如果数据量大，建议使用二进制格式，如 Protocol Buffers（protobuf）。
WebRTC 适用于大规模流媒体数据传输。

//发送二进制数据示例
let buffer = new Uint8Array([1, 2, 3, 4]).buffer;
socket.send(buffer);


/************************************************************/
//消息分片
WebSocket 发送的数据量太大时，可能导致延迟或丢包。
解决方案：拆分数据包，逐块发送，服务器端再合并数据。

技巧：使用 WebSocket 流式传输，逐块发送，而不是一次性传输大数据包。

//示例（大数据分片传输）
function sendLargeData(data) {
    const chunkSize = 1024; // 每次发送 1KB
    for (let i = 0; i < data.length; i += chunkSize) {
        let chunk = data.slice(i, i + chunkSize);
        socket.send(chunk);
    }
}


/************************************************************/
//限制 WebSocket 连接数
WebSocket 是持久连接，过多的连接会占用服务器资源，影响性能。
解决方案：
1、限制每个 IP 的最大连接数，防止 DoS 攻击。
2、使用 Nginx 进行 WebSocket 负载均衡。

// 示例（Nginx 配置 WebSocket 代理）
server{
    listen 80;
    location / ws / {
        proxy_pass http ://localhost:8080;
        proxy_http_version 1.1;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection "Upgrade";
    }
}


/************************************************************/
//WebSocket 负载均衡
WebSocket 连接是长连接，传统的 HTTP 负载均衡（轮询）方式不适用。
解决方案：
1、使用 Nginx + Sticky Session 或 Redis 存储连接信息。
2、使用 WebSocket 服务器集群（如 socket.io + Redis）。

//示例（Socket.io + Redis 共享连接）
const io = require("socket.io")(server);
const redis = require("socket.io-redis");

io.adapter(redis({ host: "localhost", port : 6379 }));


/************************************************************/
//WebSocket 认证
WebSocket 连接建立后，没有像 HTTP 一样的 Cookie 认证，建议：
1、使用 JWT（JSON Web Token） 或 自定义 Token 进行身份认证。
2、在 URL 传递 Token（不推荐） 或 使用 Sec - WebSocket - Protocol 头部传递。

📌 技巧：
1、WebSocket 不支持 Same - Origin Policy，因此要使用 CORS 限制访问。
2、强制使用 WSS（WebSocket Secure），防止流量被劫持。

//示例（前端携带 Token）
let socket = new WebSocket("ws://localhost:8080", ["authToken", "your-token-value"]);

//示例（Python 服务器端认证）
async def authenticate(websocket, path) :
    token = websocket.request_headers.get("Sec-WebSocket-Protocol")
    if token != "your-token-value" :
        await websocket.close(reason = "Unauthorized")
    else :
        await websocket.send("认证成功")

