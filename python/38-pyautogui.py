('''********************'''pyautogui'''************************************************************'''


pyautogui库：允许你通过编写Python脚本来控制鼠标和键盘，从而实现自动化操作图形用户界面（GUI）的功能。

#安装
pip install pyautogui



('''********************'''实例'''************************************************************'''

import pyautogui  
import time  
  
# 假设表单的输入框位置已知，这里使用示例坐标  
# 填写姓名  
name_field_position = (100, 200)  # 假设姓名输入框的坐标为(100, 200)  
pyautogui.moveTo(name_field_position, duration=0.5)  # 移动鼠标到姓名输入框  
pyautogui.click()  # 点击输入框  
pyautogui.typewrite('张三', interval=0.1)  # 输入姓名“张三”  
  
# 填写电子邮件  
email_field_position = (100, 300)  # 假设电子邮件输入框的坐标为(100, 300)  
pyautogui.moveTo(email_field_position, duration=0.5)  # 移动鼠标到电子邮件输入框  
pyautogui.click()  # 点击输入框  
pyautogui.typewrite('zhangsan@example.com', interval=0.1)  # 输入电子邮件  
  
# 填写密码  
password_field_position = (100, 400)  # 假设密码输入框的坐标为(100, 400)  
pyautogui.moveTo(password_field_position, duration=0.5)  # 移动鼠标到密码输入框  
pyautogui.click()  # 点击输入框  
pyautogui.typewrite('password123', interval=0.1)  # 输入密码  
  
# 提交表单  
submit_button_position = (300, 500)  # 假设提交按钮的坐标为(300, 500)  
pyautogui.moveTo(submit_button_position, duration=0.5)  # 移动鼠标到提交按钮  
pyautogui.click()  # 点击提交按钮  
  
# 等待表单提交完成，这里简单使用time.sleep模拟等待时间  
time.sleep(5)  
  
print("表单填写并提交完成！")


