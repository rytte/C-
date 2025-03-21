/********************/Protobuf/************************************************************/

Protocol Buffers（简称 Protobuf）是 Google 开发的一种高效、可扩展的序列化协议。
它主要用于结构化数据的序列化（类似于 XML 和 JSON），但相比它们更小、更快、更适合网络传输和存储。


//Protobuf 主要特点
1、跨语言、跨平台
* 支持 C++、Java、Python、Go、C#、Rust 等多种语言。
* 适用于不同的操作系统和架构。

2、高效的二进制格式
* 比 JSON、XML 更小，解析速度更快，占用带宽更少。

3、结构化数据
* 通过.proto 文件定义数据结构，自动生成代码。
* 适用于 RPC（远程过程调用）、数据存储、消息传递等场景。

4、前向兼容 & 后向兼容
* 旧版本客户端可以读取新版本的数据，反之亦然。
* 支持字段的新增、删除而不影响解析。


//适用场景
RPC 通信：gRPC 采用 Protobuf 作为默认数据格式。
数据存储：用于高效存储结构化数据。
消息队列：Kafka、MQTT 也可以使用 Protobuf。
配置文件：某些应用使用 Protobuf 代替 JSON / XML 作为配置格式。


//与 JSON、XML 对比
特性		Protobuf		JSON			XML
体积		最小				中等				最大
解析速度	最快				较快				最慢
可读性	差（二进制）		好（文本）		好（文本）
扩展性	强（编号兼容）	较强（Key 兼容）	强（Schema 兼容）



/********************/Protobuf基本使用/************************************************************/
//1、定义.proto 文件
syntax = "proto3"; // 版本声明，代表使用 Protobuf 3 语法。

message Person{				// message Person 定义一个数据结构（类似于 C++ 结构体、JSON 对象）。
  int32 id = 1;				// 其中 1 是字段编号，必须唯一。
  string name = 2;
  repeated string phone_numbers = 3; // 可重复字段，代表一个列表，可以存多个值。
}

//2、生成代码
protoc --cpp_out = .person.proto		// 生成 C++ 代码
protoc --python_out = .person.proto		// 生成 Python 代码

//3、在 C++ 中使用
#include "person.pb.h"

Person p;
p.set_id(1);
p.set_name("Alice");
p.add_phone_numbers("123456789");

std::string data;
p.SerializeToString(&data); // 序列化

Person p2;
p2.ParseFromString(data); // 反序列化
std::cout << "Name: " << p2.name() << std::endl;

