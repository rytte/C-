('''********************'''pypinyin'''************************************************************'''

pypinyin库：将汉字转换为拼音。它支持多种拼音风格，包括全拼、首字母、声调以及不带声调的拼音等。


#安装
pip install pypinyin



('''********************'''实例'''************************************************************'''
from pypinyin import pinyin, Style  
  
# 将汉字转换为全拼  
text = "你好，世界"  
pinyin_list = pinyin(text)  
print(pinyin_list)  # 输出: [['nǐ'], ['hǎo'], ['，'], ['shì'], ['jiè']]  
  
# 转换为不带声调的拼音  
pinyin_list_no_tone = pinyin(text, style=Style.NORMAL)  
print(pinyin_list_no_tone)  # 输出: [['ni3'], ['hao3'], ['，'], ['shi4'], ['jie4']]  
  
# 转换为首字母  
initials = pinyin(text, style=Style.INITIALS)  
print(initials)  # 输出: [['n'], ['h'], ['，'], ['s'], ['j']]  
  
# 转换为首字母且不带声调  
initials_no_tone = pinyin(text, style=Style.FIRST_LETTER)  
print(initials_no_tone)  # 输出同上，因为首字母默认不带声调

# 还支持一次性转换多个汉字字符串
texts = ["苹果", "香蕉", "橙子"]  
pinyin_list = pinyin(texts, style=Style.NORMAL)  
print(pinyin_list)  # 输出: [['ping2', 'guo3'], ['xiang1', 'jiao'], ['cheng2', 'zi']]

