'''********************'''PowerShell'''************************************************************'''

https://zhuanlan.zhihu.com/p/76708298

PowerShell 命令称为 cmdlet（读作 command-let）。
PowerShell 脚本文件的扩展名是 .ps1。

#外部命令
任何本机命令都可以从 PowerShell 命令行运行。如：在 Ubuntu 上的 PowerShell 可以运行 grep 命令，而在 Windows 中不行。

#基本命令
Get-Verb。 获取大多数命令遵循的谓词的列表。如果你要创建命令，这有助于选择适当的命令和命令名称。
Get-Command。 检索计算机上安装的所有命令的列表。
Get-Member。 它在基于对象的输出上运行，并且能够发现可用于命令的对象、属性和方法。
Get-Help。 以命令名称为参数调用此命令，将显示一个帮助页面，其中说明了命令的各个部分。

#常用命令
$PSVersionTable.PSVersion													查询当前powershell版本
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned		将 PowerShell 执行策略更改为远程签名

#PowerShell中运行 Windows 批处理脚本
如果在 PowerShell 中运行 Windows 批处理脚本（.cmd 文件），PowerShell 将运行 cmd.exe 并传入批处理文件以供执行。


#Winget
Windows 包管理器 Winget 是一种命令行工具，用户可以使用它在 Windows 客户端计算机上查找、安装、升级、删除和配置应用程序。 

格式：winget + 命令 + 目标

命令：
search		搜索最新版本的软件
install		安装软件


'''********************'''PowerShell脚本'''************************************************************'''
#注释
行注释: #
块注释: <# 和 #>


#定义变量（大小写不敏感）
$变量名=初值
${变量名}=初值

$变量名.GetType()          #查看变量类型
del variable:变量名         #删除变量


#转换为静态类型
可以在变量前添加类型限定符使该变量变为静态类型，可以确保变量的类型不会随着赋值而改变
[int]$num=123 #正确
[int]$num=ls <#错误



#转义字符
PowerShell的转义字符是 ` 而不是 \

