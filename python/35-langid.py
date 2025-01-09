('''********************'''langid'''************************************************************'''

langid是一个用于语言识别的库。支持多种语言识别，模型小但精度高，过滤速度快。


#安装
pip install langid



langid.classify()函数进行语言识别。该函数返回一个包含两个元素的元组：
第一个元素是识别出的语言代码（如'zh'表示中文，'en'表示英文），
第二个元素是该识别的可信度（一个介于0和1之间的浮点数，值越接近1表示可信度越高）。



('''********************'''语言识别'''************************************************************'''
import langid  
  
# 待检测的文本  
text = "这是一个测试文本，用中文写成。"  
  
# 使用langid.classify()函数进行语言识别  
lang, confidence = langid.classify(text)  
  
# 打印识别出的语言代码和可信度  
print(f"The language of the text is {lang} with a confidence of {confidence:.2f}.")  
  
# 如果需要，可以添加更多文本进行测试  
text_en = "This is a test text in English."  
lang_en, confidence_en = langid.classify(text_en)  
print(f"The language of the English text is {lang_en} with a confidence of {confidence_en:.2f}.")




