('''********************'''chatterbot'''************************************************************'''

#安装
pip intstall chatterbot

如果不能安装，下载源码手动安装
1、进入github仓库下载源码：https://github.com/gunthercox/ChatterBot
2、进入源码文件ChatterBot-master\chatterbot\tagging.py
3、将第26行的：self.nlp = spacy.load(self.language.ISO_639_1.lower())
替换为如下：
        if self.language.ISO_639_1.lower() == 'en':
            self.nlp = spacy.load('en_core_web_sm')
        else:
            self.nlp = spacy.load(self.language.ISO_639_1.lower())
4、回到源码主目录，运行：
python setup.py build
python setup.py install
5、运行：pip install spacy
5、运行：python -m spacy download en_core_web_sm
6、运行程序，补足库（部分需要clash）

异常：AttributeError: module ‘time’ has no attribute ‘clock’
解决：打开相关文件，将 time.clock 改为 time.perf_counter



('''********************'''数据训练'''************************************************************'''
 # 导入所需的依赖  
from chatterbot import ChatBot  
from chatterbot.trainers import ListTrainer  
  
# 创建机器人实例  
chatbot = ChatBot("SillyRobot")  
  
# # 定义训练数据集  
# conversation = [  
#     "Hello",  
#     "Hi there!",  
#     "How are you doing?",  
#     "I'm doing great.",  
#     "That is good to hear",  
#     "Thank you.",  
#     "You're welcome."  
# ]  


#导入语料库
file = open("./traintext.txt",'r',encoding='utf-8')
corpus = []
print('开始加载语料！')
while 1:
    try:
        line = file.readline()
        if not line:
         break
        if line == 'E\n':
            continue
        corpus.append(line.split('M ')[1].strip('\n'))
    except:
        pass
file.close()
print('语料加载完毕')
  

# 使用ListTrainer来训练  
trainer = ListTrainer(chatbot)  
trainer.train(corpus)  
  
# 响应用户请求  
response = chatbot.get_response("How are you?")  
print(response)



('''********************'''使用训练模型'''************************************************************'''
 from chatterbot import ChatBot  
  
# 设置ChatBot的database_uri为SQLite3数据库文件的路径  
chatbot = ChatBot("SillyRobot",  
                  database_uri='sqlite:///db.sqlite3')  
  
# 现在，chatbot已经加载了SQLite3数据库中的训练数据  
  
while 1:

    # 用户输入新的请求  
    user_input = input("请输入您的问题: ")  
      
    # 机器人响应  
    response = chatbot.get_response(user_input)  
      
    # 打印机器人的响应  
    print(response)











