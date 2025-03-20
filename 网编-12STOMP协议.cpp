/********************/STOMP/************************************************************/
STOMP（Simple / Streaming Text Oriented Messaging Protocol，简单 / 流式面向文本的消息协议）
是一种轻量级、基于文本的消息传输协议，用于客户端与消息代理（Message Broker）之间的通信。

它类似于 AMQP（Advanced Message Queuing Protocol） 或 MQTT，但更简单，
主要用于 消息队列（Message Queue）和实时消息传输，适用于 WebSockets、微服务通信、分布式系统、即时聊天等场景。


//特点
1、基于文本协议：		STOMP 的消息是 纯文本格式，比二进制协议（如 AMQP）更易读和调试。
2、轻量级：			STOMP 仅定义了 简单的消息格式，不像 AMQP 那样涉及队列、路由等复杂概念。
3、面向消息代理：		STOMP 需要一个 消息代理（Message Broker），如 RabbitMQ、ActiveMQ、Apollo、Artemis 等。
4、支持 WebSockets：	STOMP 适用于 WebSocket + 消息队列的应用，适合 Web 应用进行 实时推送。
5、跨平台、跨语言：	STOMP 仅定义了协议，支持 Java、Python、C++、JavaScript、Go 等多种语言的客户端。


//命令
STOMP 的工作模式和 发布 / 订阅（Pub / Sub）模式 类似，包含以下核心概念：

操作				说明
CONNECT			连接到 STOMP 服务器
SEND			发送消息到某个目的地（Destination）
SUBSCRIBE		订阅一个目的地，接收消息
UNSUBSCRIBE		取消订阅
ACK / NACK		确认或拒绝消息
DISCONNECT		断开连接


//对比
🔥 STOMP vs.AMQP vs.MQTT
特性			STOMP							AMQP						MQTT
协议类型		文本协议							二进制协议					二进制协议
消息模型		仅提供消息传输					复杂消息队列系统				轻量级消息协议
支持	WS		✅								❌（需额外扩展）				✅
消息确认		仅支持 ACK / NACK				复杂的 QoS 机制				QoS 0、1、2
适用场景		WebSockets、微服务、实时推送		企业级消息队列、事务型消息		物联网（IoT）、移动设备通信



/********************/STOMP 消息示例/************************************************************/
字符：
"^@" 是 STOMP 协议 中的 控制字符，表示 空字符（NULL character，也称为 ASCII 码 0）。用于标识消息的结束或连接的结束信号。


 //客户端发送消息（假设 STOMP 代理运行在 localhost:61613）
R"(
CONNECT
accept-version:1.2
host:localhost

^@
)"

// 订阅某个队列（比如 /queue /chat）
R"(
SUBSCRIBE
id:sub-1
destination:/queue/chat

^@
)"

// 发送消息到队列 /queue /chat
R"(
SEND
destination:/queue/chat
content-type:text/plain

Hello STOMP!
^@
)"

// 收到消息（服务器返回的 STOMP 消息）
R"(
MESSAGE
destination:/queue/chat
message-id:12345
subscription:sub-1

Hello STOMP!
)"

