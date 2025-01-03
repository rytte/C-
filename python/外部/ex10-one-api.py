

本地 Docker Destop 安装运行 One - Api


#拉取 one - api 镜像
docker pull justsong / one - api


#使用 SQLite 的部署命令 启动容器（默认宿主机端口为 3000）
docker run --name one-api -d --restart always -p 3000:3000 -e TZ=Asia/Shanghai -v C:/LLM/OneApi-V-Data:/data justsong/one-api



浏览器打开http://localhost:3000/
one-api 提供了开箱即用的功能，有一个默认的root账号,密码是123456


配置渠道（模型）
申请令牌


#请求示例
请求地址: http://localhost:3000/v1/chat/completions
请求头:   Authorization：Bearer {OneApiToken}

接口入参:
{
  "model": "SparkDesk-v3.5",
  "messages": [
    {
      "role": "user",
      "content": "给我讲个笑话吧。"
    }
  ],
  "temperature": 0.7
}

接口回参:
{
  "id": "chatcmpl-04025f1484c54770a8d854de360fd06e",
  "object": "chat.completion",
  "created": 1715000959,
  "choices": [
    {
      "index": 0,
      "message": {
        "role": "assistant",
        "content": "当然可以，这是一个我最近听到的笑话：\n\n有一天，一只猫走进了一个酒吧，然后走到吧台前坐下，对酒保说：“我要一杯牛奶。”\n\n酒保惊讶地看着猫，然后说：“你是我见过的第一只会说话的猫。”\n\n猫看着酒保，回答说：“考虑到你的服务速度，我也没什么好惊讶的。”"
      },
      "finish_reason": "stop"
    }
  ],
  "usage": {
    "prompt_tokens": 6,
    "completion_tokens": 75,
    "total_tokens": 81
  }
}

