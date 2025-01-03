('''********************'''pygame'''************************************************************'''

pygame 库专为编写视频游戏而设计。它包含了许多用于创建游戏所需的模块，如图像和声音处理、事件处理、碰撞检测以及简单的 2D 图形绘制。


#安装
pip install pygame


#主要模块
pygame 包含了多个模块，每个模块都提供了不同的功能：

pygame.display：用于创建窗口和屏幕，并处理屏幕的绘制和更新。
pygame.event：用于处理事件，如按键、鼠标移动和点击等。
pygame.draw：提供了一些基本的图形绘制函数，如线条、矩形、圆形等。
pygame.font：用于加载和渲染字体。
pygame.image：用于加载和保存图像。
pygame.mixer：用于播放声音。
pygame.time：提供了控制游戏速度和定时器的功能。



('''********************'''实例'''************************************************************'''
import pygame  
import sys  
  
# 初始化 pygame  
pygame.init()  
  
# 设置屏幕大小  
screen_width, screen_height = 800, 600  
screen = pygame.display.set_mode((screen_width, screen_height))  
  
# 设置窗口标题  
pygame.display.set_caption("简单的 pygame 窗口")  
  
# 游戏主循环  
running = True  
while running:  
    # 处理事件（如按键、点击等）  
    for event in pygame.event.get():  
        if event.type == pygame.QUIT:  
            running = False  
  
    # 填充背景颜色  
    screen.fill((0, 0, 0))  
  
    # 更新整个屏幕显示  
    pygame.display.flip()  
  
# 退出 pygame  
pygame.quit()  
sys.exit()


