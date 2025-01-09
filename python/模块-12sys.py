('''********************'''sys 模块'''************************************************************'''
sys模块提供了与Python解释器和运行环境相关的功能。
通过sys模块，我们可以获取和操作系统相关的信息，控制程序的执行，管理模块和包，以及处理异常等。


#1. 获取命令行参数
sys.argv：这是一个包含命令行参数的列表，其中第一个元素是脚本的名称，其余元素是传递给脚本的参数。

#2. 退出程序
sys.exit([arg])：用于退出程序，可选地指定一个整数参数作为退出状态码。正常退出时通常使用sys.exit(0)，错误退出时可以使用非零值。

#3. 获取Python解释器和环境信息
sys.version：表示当前Python解释器的版本信息。
sys.platform：表示当前运行的操作系统平台名称。
sys.executable：Python解释程序路径。
sys.version_info：返回一个包含Python版本信息的元组，例如(major, minor, micro, releaselevel, serial)。

#4. 管理模块和包
sys.modules：这是一个字典，包含了当前已导入的所有模块。
sys.path：这是一个列表，包含了Python解释器在搜索模块时要查找的路径。可以通过修改这个列表来添加自定义模块的搜索路径。
sys.meta_path：这是一个列表，包含了当前已注册的所有导入钩子。

#5. 标准输入输出和错误
sys.stdin、sys.stdout、sys.stderr：分别表示标准输入、标准输出和标准错误流。可以重定向这些流到文件或其他设备上，从而改变输入来源和输出目标。

#6. 异常处理
sys.exc_info()：返回当前异常的相关信息，包括异常类型、异常值和异常追踪信息。
sys.exc_clear()：清除当前异常。
sys.exc_type、sys.exc_value、sys.exc_traceback：分别保存了当前异常的类型、值和追踪信息。

#7. 其他功能
sys.getrecursionlimit()和sys.setrecursionlimit()：分别用于获取和设置Python解释器的递归调用深度限制。
sys.getdefaultencoding()：获取当前默认的字符编码）。
sys.getwindowsversion()：获取Windows的版本信息（仅Windows平台可用）。



('''********************'''实例'''************************************************************'''
import sys  
  
# 获取命令行参数  
print("脚本名称:", sys.argv[0])  
print("传递的参数:", sys.argv[1:])  
  
# 退出程序  
sys.exit(0)  
  
# 获取Python解释器和环境信息  
print("Python版本:", sys.version)  
print("操作系统平台:", sys.platform)  
  
# 管理模块和包  
print("已导入的模块:", sys.modules.keys())  
print("模块搜索路径:", sys.path)  
  
# 重定向标准输出  
with open('output.txt', 'w') as f:  
    sys.stdout = f  
    print('This is redirected to a file.')  
    sys.stdout = sys.__stdout__  # 恢复标准输出  
  
# 异常处理  
try:  
    raise ValueError("发生了一个错误")  
except:  
    exc_type, exc_value, exc_traceback = sys.exc_info()  
    print("异常类型:", exc_type)  
    print("异常值:", exc_value)  
    print("异常追踪信息:", exc_traceback)  
    sys.exc_clear()
    
