('''********************'''pykakasi'''************************************************************'''

pykakasi库：将平假名、片假名和汉字（日语文本）音译为罗马字


#安装
pip install pykakasi



('''********************'''实例'''************************************************************'''
import pykakasi  
  
kks = pykakasi.kakasi()  
text = "かな漢字"  
result = kks.convert(text)  
for item in result:  
    print("{}: kana '{}', hiragana '{}', romaji: '{}'".format(  
        item['orig'], item['kana'], item['hira'], item['hepburn']))
    #输出结果将显示原始文本、平假名、片假名和罗马字（使用Hepburn罗马化系统）的对应关系。
