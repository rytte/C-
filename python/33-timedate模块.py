


('''********************'''获取当前北京时间'''************************************************************'''
#使用系统时区（+8小时）
from datetime import datetime  
  
def get_beijing_time_system_tz():  
    # 直接获取当前时间（这里假设系统时区已经是UTC+8）  
    now = datetime.now()  
    # 格式化输出  
    formatted_time = now.strftime('%Y-%m-%d %H:%M:%S')  
    return formatted_time  
  
# 调用函数并打印结果  
print(get_beijing_time_system_tz())



#手动设置时区（+8小时）
from datetime import datetime, timedelta  
  
def get_beijing_time_manual_offset():  
    # 获取UTC时间  
    utc_now = datetime.utcnow()  
    # 手动添加8小时以转换为北京时间  
    beijing_time = utc_now + timedelta(hours=8)  
    # 格式化输出  
    formatted_time = beijing_time.strftime('%Y-%m-%d %H:%M:%S')  
    return formatted_time  
  
# 调用函数并打印结果  
print(get_beijing_time_manual_offset())

