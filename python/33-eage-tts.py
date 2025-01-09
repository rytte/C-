


#安装
pip install edge-tts


#命令行使用
edge-tts --text "hello, everyone!" --write-media hello.mp3


#实例
import edge_tts  
import asyncio  

text = "hello, everyone!"  
voice = 'zh-CN-shaanxi-XiaoniNeural'  
output_result = 'hello.mp3'  

async def my_function():  
    tts = edge_tts.Communicate(text=text, voice=voice)  
    await tts.save(output_result)  

if __name__ == "__main__":  
    asyncio.run(my_function())
    