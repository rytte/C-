('''********************'''bilibili_api'''************************************************************'''

#安装
pip3 install bilibili-api-python

#仓库
https://github.com/nemo2011/bilibili-api

#api介绍
https://nemo2011.github.io/bilibili-api/#/



('''********************'''获取视频信息'''************************************************************'''

import asyncio
from bilibili_api import video


async def main() -> None:
    # 实例化 Video 类
    v = video.Video(bvid="BV1uv411q7Mv")
    # 获取信息
    info = await v.get_info()
    # 打印信息
    print(info)


if __name__ == "__main__":
    asyncio.get_event_loop().run_until_complete(main())



('''********************'''给视频点赞'''************************************************************'''
import asyncio
from bilibili_api import video, Credential

async def main() -> None:
    # 实例化 Credential 类
    credential = Credential(sessdata=SESSDATA, bili_jct=BILI_JCT, buvid3=BUVID3)
    # 实例化 Video 类
    v = video.Video(bvid="BVxxxxxxxx", credential=credential)
    info = await v.get_info()
    print(info)
    # 给视频点赞
    await v.like(True)

if __name__ == '__main__':
    asyncio.get_event_loop().run_until_complete(main())


('''********************'''直播间机器人'''************************************************************'''
import subprocess  # 导入子进程模块
from chatterbot import ChatBot  # 导入聊天机器人库
from bilibili_api import live, sync, Credential, login  # 导入bilibili直播API库


SESSDATA = "5e0cb7bb%2C1737905558%2C71837%2A71CjANGEUNjOA7EkuT6wjNxwW4DeezkqhbMDew2Sf5uWobx4vB3eTX2P_mTEa3MzAQIxMSVmo0MV9FR3pyYUpkZ1hSYjRHdlhlUTVyTkZVNEdJVmVYR2RSbkd2amxwRE5PTjJ3bEY1RlhoZUhSOWN3bEZDYjlQOVNNV3ZZR0YxZXdfdzFyV21laUpRIIEC"
BILI_JCT = "45ead0913fd58a2c32118b2e19e1f5e5"
AC_TIME_VALUE = "0117d2e09c027ee3ed7877823be3dd71"

# 生成一个 Credential 对象
credential = Credential(sessdata=SESSDATA, bili_jct=BILI_JCT, ac_time_value=AC_TIME_VALUE, buvid3="123") 

# 检查是否成功获取 sessdata  
if credential.sessdata:  
    # 使用 credential 进行后续操作  
    print("登录成功，sessdata 已获取")  
else:  
    print("登录失败或未获取到 sessdata")


bot = ChatBot(
    'xixi',  # 聊天机器人名字
    database_uri='sqlite:///db.sqlite3'  # 数据库URI，数据库用于存储对话历史
)

# room_id = int(input("请输入直播间编号: "))  # 输入直播间编号
room = live.LiveDanmaku(23712360, credential=credential)  # 连接弹幕服务器

@room.on('DANMU_MSG')  # 弹幕消息事件回调函数
async def on_danmaku(event):
    """
    处理弹幕消息
    :param event: 弹幕消息事件
    """
    content = event["data"]["info"][1]  # 获取弹幕内容
    user_name = event["data"]["info"][2][1]  # 获取用户昵称
    print(f"[{user_name}]: {content}")  # 打印弹幕信息

    prompt = f"{content}"  # 设置观众提问
    response = bot.get_response(prompt)  # 生成回复

    print(f"[AI回复{user_name}]：{response}")  # 打印AI回复信息

    command = f'edge-tts --voice zh-CN-XiaoyiNeural --text "{response.text}" --write-media output.mp3'  # 将 AI 生成的文本传递给 edge-tts 命令
    subprocess.run(command, shell=True)  # 执行命令行指令

    with open("./output.txt", "a", encoding="utf-8") as f:
        f.write(f"[AI回复{user_name}]：{response}\n")  # 将回复写入文件

    command = 'mpv.exe -vo null output.mp3'  # 播放音频文件
    subprocess.run(command, shell=True)  # 执行命令行指令

sync(room.connect())  # 开始监听弹幕流


