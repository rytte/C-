('''********************'''openai'''************************************************************'''

#安装openai模块
pip install openai


#认证
OpenAI API 使用 API 密钥进行身份验证。所有 API 请求都应在 HTTP 标头中包含您的 API 密钥，如下所示：
Authorization: Bearer OPENAI_API_KEY


#请求组织
对于属于多个组织的用户，您可以传递标头以指定用于 API 请求的组织。这些 API 请求的使用量将计入指定组织的订阅配额。

示例 curl 命令：
curl https://api.openai.com/v1/models \
  -H "Authorization: Bearer $OPENAI_API_KEY" \
  -H "OpenAI-Organization: org-feIswv7vrPlelwcPgPw2xRZ1"

Python 包的示例：
import os
import openai
openai.organization = "org-feIswv7vrPlelwcPgPw2xRZ1"
openai.api_key = os.getenv("OPENAI_API_KEY")
openai.Model.list()

可以在组织设置页面上找到组织 ID。


#提出请求
您可以将以下命令粘贴到终端中以运行您的第一个 API 请求。确保替换为您的私有 API 密钥。
curl https://api.openai.com/v1/chat/completions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer $OPENAI_API_KEY" \
  -d '{
     "model": "gpt-3.5-turbo",
     "messages": [{"role": "user", "content": "Say this is a test!"}],
     "temperature": 0.7
   }'

(此请求查询模型以完成以提示“说这是一个测试”开头的文本。您应该收到类似于以下内容的回复：
 {
   "id":"chatcmpl-abc123",
   "object":"chat.completion",
   "created":1677858242,
   "model":"gpt-3.5-turbo-0301",
   "usage":{
      "prompt_tokens":13,
      "completion_tokens":7,
      "total_tokens":20
   },
   "choices":[
      {
         "message":{
            "role":"assistant",
            "content":"\n\nThis is a test!"
         },
         "finish_reason":"stop",
         "index":0
      }
   ]
}

现在，您已经生成了第一个聊天completion。我们可以看到这意味着 API 返回了模型生成的整个completion。
在上面的请求中，我们只生成了一条消息，但您可以设置参数以生成多条消息选项。


'''************************************************************'''
# models 模型
列出并描述 API 中可用的各种模型。
示例请求：
import os
import openai
openai.api_key = os.getenv("OPENAI_API_KEY")
openai.Model.list()

响应：
{
  "data": [
    {
      "id": "model-id-0",
      "object": "model",
      "owned_by": "organization-owner",
      "permission": [...]
    },
    {
      "id": "model-id-1",
      "object": "model",
      "owned_by": "organization-owner",
      "permission": [...]
    },
    {
      "id": "model-id-2",
      "object": "model",
      "owned_by": "openai",
      "permission": [...]
    },
  ],
  "object": "list"
}


#检索模型
检索模型实例，提供有关模型的基本信息，例如所有者和权限。
示例请求：
import os
import openai
openai.api_key = os.getenv("OPENAI_API_KEY")
openai.Model.retrieve("text-davinci-003")           #模型字符串，用于此请求的模型的 ID

响应：
{
  "id": "text-davinci-003",
  "object": "model",
  "owned_by": "openai",
  "permission": [...]
}


'''************************************************************'''
#聊天
给定包含会话的消息列表，模型将返回响应。


#创建聊天completion（beta版）
为给定的聊天对话创建模型响应。

#请求正文
示例请求：
import os
import openai
openai.api_key = os.getenv("OPENAI_API_KEY")

completion = openai.ChatCompletion.create(
  model="gpt-3.5-turbo",
  messages=[   
    {"role": "system", "content": "You are a helpful assistant."},
    {"role": "user", "content": "Hello!"}
  ]
)

print(completion.choices[0].message)

响应：{a:1,b:{c:1,d:2}}
{
  "id": "chatcmpl-123",
  "object": "chat.completion",
  "created": 1677652288,
  "choices": [{
    "index": 0,
    "message": {
      "role": "assistant",
      "content": "\n\nHello there, how may I assist you today?",
    },
    "finish_reason": "stop"
  }],
  "usage": {
    "prompt_tokens": 9,
    "completion_tokens": 12,
    "total_tokens": 21
  }
}

参数：    #openai.ChatCompletion.create() 函数参数，返回值赋给completion
model    字符串 必填：使用的模型名称
messages 数组   必填：包含到目前为止的对话的一个消息列表，包含以下参数：
{
    role        字符串 必填：消息作者这个角色（或之一），也就是你
    content     字符串 选填：消息的内容。对于除具有函数调用的助手assistant消息之外的所有消息都是必需的。
    name        字符串 选填：此消息的作者的姓名。 如果定义了 role 则必填，并且它应该是它响应在 中的函数的名称。可以包含 a-z、A-Z、0-9 和下划线，最大长度为 64 个字符。
  function_call 对象   选填：应调用的函数的名称和参数，由模型生成。
}
functions 数组  选填：模型可能为其生成 JSON 输入的函数列表，包含以下参数：
{
    name        字符串 必填：要调用的函数的名称。必须为 a-z、A-Z、0-9，或包含下划线和短划线，最大长度为 64。
    description 字符串 选填：函数功能的说明。
    parameters  对象   选填：函数接受的参数，描述为 JSON 架构对象。
}
function_call  字符串或对象 可选：控制模型如何响应函数调用。“none”表示模型不调用函数，并响应最终用户。“auto”表示模型可以在最终用户或调用函数之间进行选择。
                                  通过指定特定函数会强制模型调用该函数。“none”是不存在函数时的默认值。如果存在函数，则“auto”是默认值。例如：{"name":\ "my_function"}          (
temperature     数字 可选 默认为1：设置采样温度，介于 0 和 2 之间。
                                     较高的值（如 0.8）将使输出更加随机，而较低的值（如 0.2）将使其更加集中和确定。不要同时更改两者temperature和top_p。
top_p           数字 可选 默认为1：使用温度采样的替代方法称为核心采样，其中模型考虑具有top_p概率质量的令牌的结果。
                                     因此，0.1 意味着只考虑包含前 10% 概率质量的代币。
n               整数 可选 默认为1：要为每个输入消息生成的聊天完成completion选项数。
stream          布尔 可选 默认为 false：如果设置，将发送部分消息增量，就像在 ChatGPT 中一样。tokens将在可用时作为纯数据服务器发送的事件发送，stream由消息终止。
stop    字符串或数组 可选 默认为 null：最多 4 个序列，其中 API 将停止生成更多tokens。
max_tokens      整数 可选 默认为 inf：要在聊天completion中生成的最大tokens数。输入tokens和生成的tokens的总长度受模型上下文长度的限制。
presence_penalty数字 可选 默认为0：介于 -2.0 和 2.0 之间的数字。正值会根据新标记到目前为止是否出现在文本中来惩罚它们，从而增加模型讨论新主题的可能性。
frequency_penalty数字 可选 默认为0：介于 -2.0 和 2.0 之间的数字。正值会根据新标记到目前为止在文本中的现有频率来惩罚新标记，从而降低模型逐字重复同一行的可能性。
logit_bias      map  可选 默认为0：修改completion中出现指定tokens的可能性。接受将token（由其在分词器中的token ID 指定）映射到 -100 到 100 之间的关联偏差值的 json 对象。
                                    在数学上，偏差在采样之前被添加到模型生成的对数中。确切的效果因模型而异，但介于 -1 和 1 之间的值应降低或增加选择的可能性;
                                    像 -100 或 100 这样的值应该会导致禁止或排他性选择相关token。
user            字符串 可选：代表最终用户的唯一标识符，可帮助 OpenAI 监控和检测滥用行为。


'''************************************************************'''
#创建completion
低配版聊天，参数详解略过
示例请求：
import os
import openai
openai.api_key = os.getenv("OPENAI_API_KEY")
openai.Completion.create(
  model="text-davinci-003",
  prompt="Say this is a test",
  max_tokens=7,
  temperature=0
)

示例参数：
{
  "model": "text-davinci-003",
  "prompt": "Say this is a test",
  "max_tokens": 7,
  "temperature": 0,
  "top_p": 1,
  "n": 1,
  "stream": false,
  "logprobs": null,
  "stop": "\n"
}

响应：
{
  "id": "cmpl-uqkvlQyYK7bGYrRHQ0eXlWi7",
  "object": "text_completion",
  "created": 1589478378,
  "model": "text-davinci-003",
  "choices": [
    {
      "text": "\n\nThis is indeed a test",
      "index": 0,
      "logprobs": null,
      "finish_reason": "length"
    }
  ],
  "usage": {
    "prompt_tokens": 5,
    "completion_tokens": 7,
    "total_tokens": 12
  }
}


'''************************************************************'''
#编辑edits
给定提示prompt和指令，模型将返回prompt的编辑版本。


#创建编辑
为提供的输入、指令和参数创建新的编辑。

示例请求：
import os
import openai
openai.api_key = os.getenv("OPENAI_API_KEY")
openai.Edit.create(
  model="text-davinci-edit-001",
  input="What day of the wek is it?",
  instruction="Fix the spelling mistakes"
)

响应：
{
  "object": "edit",
  "created": 1589478378,
  "choices": [
    {
      "text": "What day of the week is it?",
      "index": 0,
    }
  ],
  "usage": {
    "prompt_tokens": 25,
    "completion_tokens": 32,
    "total_tokens": 57
  }
}

参数详解略过


'''************************************************************'''



import openai

openai.ChatCompletion.create(
  model="gpt-3.5-turbo",
  messages=[
        {"role": "system", "content": "You are a helpful assistant."},
        {"role": "user", "content": "Who won the world series in 2020?"},
        {"role": "assistant", "content": "The Los Angeles Dodgers won the World Series in 2020."},
        {"role": "user", "content": "Where was it played?"}
    ]
)





