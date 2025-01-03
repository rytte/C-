from gettext import find
from re import L


('''********************'''Linux'''************************************************************'''
 Linux系统启动过程：
·内核的引导。
·运行 init。
·系统初始化。
·建立终端 。
·用户登录系统。


七大文件类型
- 		普通文件
d		目录文件
l		链接文件（类似文件的快捷方式）
p		管道文件（进程通信）
s		套接字文件（网络通信）
b		块设备文件（存储）
c		字符设备文件（Linux驱动节点）


#终端启动配置文件，可以配置用户环境变量，可以在该文件内设置alias。
vim ~/.bashrc

修改完成后重新打开终端或使用 source .bashrc 命令使其生效

/etc/bash.bashrc：Ubuntu启动配置文件，可以配置系统环境变量，这是对整个系统所有用户生效的。
/etc/profile：此文件为系统的每个用户设置环境信息,当用户第一次登录时,该文件被执行,并从/etc/profile.d目录的配置文件中搜集shell的设置。

#共享文件夹
虚拟机---》设置---》选项---》共享文件夹----》总是启用
共享文件夹位置：/mnt/hgfs

#快捷键
打开命令终端          Ctrl + Alt + T
打开并列终端          Ctrl + Shift + T
终端放大                 Ctrl + Shift + =
终端缩小                 Ctrl + -
复制                  Ctrl + Shift + C
粘贴                  Ctrl + Shift + V
复制粘贴            选中并按下鼠标滚轮
清空命令行            Ctrl + U

产生SIGINT信号        Ctrl + C
产生SIGQUIT信号       Ctrl + \
产生SIGSTOP信号       Ctrl + Z    



#浏览类命令
cat /etc/issue.net      查看当前Ubuntu版本
getconf LONG_BIT    查看当前Ubuntu操作位数
man                     帮助手册
man man             查看所有man手册
man –f 函数名      查看所有包含该函数的手册
man 手册号 函数名     查看函数帮助
cd 路径                切换当前路径
cd -                   回到上一次操作过的路径
ls                     查看文件
ls -a                  查看所有文件（包括隐藏文件）
ls -l                  查看文件详细信息
pwd                    打印当前路径
cat + 文件名           打印文件内容
which + 文件名         打印可执行文件的路径（如：which ls）
whoami                 打印当前用户名字
env                    打印系统环境变量
history                打印历史命令
file + 文件名          查看文件属性
uname -a              查看系统信息
clear                  清屏
df -h                   查看磁盘信息， -h 选项为根据大小适当显示
du -sh                  获取当前目录大小
du -sh *                获取当前目录及其子项大小

#修改类命令
touch + 文件名         新建文件
mkdir + 目录名         新建目录
rm + 文件名            删除文件
rm -r 目录名           删除目录
rmdir + 目录名         删除空目录
cp 文件名 文件路径     复制文件
cp 目录名 文件路径     复制目录
mv 文件名 文件路径     移动文件
mv 文件名 新文件名     文件或目录重命名
alias 别名='命令'         给命令起别名
unalias 别名                取消别名
chmod 权限 文件名     修改文件权限
ln 文件 别名                 创建文件硬链接（硬链接相当于文件的副件，与原文件是同一个文件，指向同一地址）
ln 文件 别名 -s             创建文件软链接（软链接相当于文件的快捷方式，是一个链接文件）
export 属性=路径        添加环境变量
export -p                    列出所有shell赋予的环境变量
export -n 变量名称      删除指定环境变量
date -s "01/31/2010 23:59:53"    设置系统时间
gedit 文件名               gedit文本编辑器
vim 文件名                  vim文本编辑器
source 文件名             运行可执行文件

#用户类命令
sudo useradd 新用户名       新建用户（可选参数-m：自动建立用户的登录目录） 
sudo userdel 用户名           删除用户（可选参数-r：删除用户登录目录及目录中所有文件）
sudo passwd 用户名          修改用户密码
su + 用户名                        切换用户
sudo -s/sudo -i/sudo su             获取超级用户权限
exit                                            退出超级用户模式

#查找类命令
sudo find 路径名 -name 文件名     寻找文件或目录，打印其路径
grep "匹配内容" 文件名 参数       在文档中匹配相应内容，按参数要求打印（可选参数-H：打印文件名字 -n：打印文件的行号 -w：全字匹配）

#输出命令
echo + 输出内容             输出字符串，使用""引用输出内容则表示输出的是一个整体（可选参数-e：使用转义字符）
>>                          表示追加写入到文件中

#系统类命令
poweroff                         立刻关机
shutdown now                立刻关机
shutdown -h 数字            在几分钟后关机
reboot                             立刻重启
shutdown -r now            立刻重启
shutdown -r 数字             在几分钟后重启

#系编网编相关
ps -ef                      查看linux下所有进程之间的关系
pstree                     树形结构查看进程间关系
top                         动态显示进程列表信息
ulimit -a                   查看无名管道信息
kill -l                     查看系统中所有已经定义好的信号
kill -9 PID                 杀死进程。
kill -SIGKILL PID           同上。
killall -2 进程名           杀死进程。会杀死所有同名进程。
killall -SIGINT 进程名      同上。

ipcs -a                     查看所有IPC对象
ipcs -q                     查看消息队列
ipcs -m                     查看共享内存
ipcs -s                     查看信号量
ipcrm -q MSG_ID             删除指定的消息队列
ipcrm -Q msg_key            同上
ipcrm -m SHM_ID             删除指定共享内存
ipcrm -M shm_key            同上
ipcrm -s SEM_ID             删除指定信号量
ipcrm -S sem_key            同上
ps -Lf 线程号               查看指定线程信息

#tar 压缩解压
压缩格式：tar  压缩参数  压缩文件名.bz2/.gz  文件1  文件2
如：tar -jcvf CC.bz2 AA BB

解压格式：tar  解压参数  压缩文件名.bz2/.gz  解压位置(默认当前目录)
如：tar -zxvf DD.gz -C /

常见的参数格式：
j 处理以.bz2结尾的压缩文件
z 处理以.gz结尾的压缩文件
c 压缩命令
x 解压命令
v 详细列出已处理的文件
f 文件，不可忽略的参数
C 指定解压的位置

查看压缩文件里面的内容：tar –tf 压缩包的名字


#嵌入式linux系统
     uboot ---》相当于windows是BIOS (本质是用C语言+汇编写的一段代码)，做内存，cpu初始化
     kernel ---》操作系统的内核(内存管理，网络管理)
     rootfs ---》根文件系统




'''********************'''网络配置'''************************************************************'''
查看网络配置        ifconfig
查看网卡名字        cd /proc/sys/net/ipv4/conf  ls
打开网卡            sudo ifconfig 网卡名 up
关闭网卡            sudo ifconfig 网卡名 down
设置ip地址配置文件  sudo vim /etc/network/interfaces                                           #16.04
设置ip地址配置文件  sudo vim /etc/netplan/01-network-manager-all.yaml           #18.04+
测试网络连接        ping + ip地址/网址



'''********************'''apt 工具'''************************************************************'''
apt（Advanced Packaging Tool）是一个在 Debian 和 Ubuntu 中的 Shell 前端软件包管理器。

sudo apt upgrade                    #更新apt工具

sudo apt update                     #更新包索引

sudo apt list                       #列出可更新软件包清单

sudo apt install package-name       #安装软件包

sudo apt remove package-name        #卸载软件包      参数-r，不保留配置文件

sudo apt clean package-name         #清除安装包

sudo apt source package-name        #下载源码包

sudo apt clean                                  #清除安装包（即/var/cache/apt/archives/下的deb文件）

dpkg -l                                             #显示已安装的软件列表



'''********************'''磁盘管理'''************************************************************'''

df -h：检查文件系统的磁盘空间占用情况。
du -ah：查看文件和目录磁盘使用的空间。
fdisk -l：磁盘分区。

mkfs [-t 文件系统格式] 装置文件名：磁盘格式化。
      -t ：可以接文件系统格式，例如 ext3, ext2, vfat 等(系统有支持才会生效)
fsck [-t 文件系统] [-ACay] 装置名称：磁盘检验。

mount [-t 文件系统] [-L Label名] [-o 额外选项] [-n]  装置文件名  挂载点：磁盘挂载。
umount [-fn] 装置文件名或挂载点：磁盘卸除。



'''********************'''源码编译'''************************************************************'''
#1.进入源码目录，执行configure文件。运行./configure -h可查看参数说明
$ ./configure  参数列表

#2.执行make，参数-j4表示同时执行的命令数目为4
$ make -j4

#3.执行make install，安装
$ make install

#其它。make uninstall，卸载
$ make uninstall



'''********************'''man手册中文包'''************************************************************'''
sudo apt-get install manpages-zh
sudo vi /etc/manpath.config     将所有的/usr/share/man替换为/usr/share/man/zh_CN保存即可。
#可使用替换命令，按下 ESC 进入命令行模式，输入
#:%s//usr/share/man//usr/share/man/zh_CN/g



'''********************'''Ubuntu16.04网络配置'''************************************************************'''
#查看网卡名                   
/proc/sys/net/ipv4/conf             ens33（16.04的网卡）eth0（开发板的网卡）

#网卡的激活与关闭
格式：sudo ifconfig ens33 up（打开网卡）      Windows（ipconfig）
格式：sudo ifconfig ens33 down（关闭网卡）

#查看网络的ip地址
格式：sudo ifconfig ens33
lo 回环链路
回环地址：127.0.0.1

#在Ubuntu中，打开设置ip地址的配置文件
sudo vi /etc/network/interfaces
如果想让系统自动获取ip
auto lo
iface lo inet loopback

auto ens33
iface ens33 inet dhcp

如果想指定ip
auto lo
iface lo inet loopback

auto eth0
iface eth0 inet ststic
address 192.168.12.xxx
gateway 192.168.12.1
netmask 255.255.255.0

#虚拟机网络设置
桥接模式：Ubuntu能访问外网，外网也能找到Ubuntu
仅主机模式：Ubuntu能访问外网，外网无法访问Ubuntu，只与Windows主机相互通信

#网络调试
1，检查电脑网线是否插好，确保 虚拟机---设置---网络适配器---已连接，桥接模式

2，检查网络是否通畅，如果没返回信息出来，往下面看。
   ping www.baidu.com

3，使用ifconfig查看当前活跃网络接口，是否有eth0（有线网卡）
   ifconfig

4，配置IP地址、子网掩码、网关地址
   sudo vi /etc/network/interfaces

	a.)确保此文件中有以下信息：（固定IP地址为192.168.12.xxx）
	auto lo
	iface lo inet loopback

	auto eth0
	iface eth0 inet static
	address 192.168.12.xxx
	gateway 192.168.12.1
	netmask 255.255.255.0

	b.)或者：（动态IP地址，就是系统自动获取IP）
	auto lo
	iface lo inet loopback

	auto eth0
	iface eth0 inet dhcp

5，重启网络服务（ubuntu-14.04以上）
   sudo service networking force-reload
   sudo service networking restart

6，配置DNS服务
   sudo vi /etc/resolvconf/resolv.conf.d/base
	确保此文件中有以下信息：
	nameserver 113.57.184.2
	nameserver 114.114.114.114
	nameserver 202.114.176.10

7，重启DNS服务
   sudo /etc/init.d/resolvconf restart（ubuntu-12.04）
   sudo service resolvconf restart（ubuntu-14.04以上）

8，重新启停以下虚拟网卡
   sudo ifconfig eth0 down
   sudo ifconfig eth0 up

9，手工添加默认网关
   sudo route add default gw 192.168.11.1

10，终极大招：重启电脑

11，如果还是不行，选择VM虚拟机---编辑---虚拟网络编辑器---还原默认设置。



'''********************'''安装搜狗输入法'''************************************************************'''
#安装
sudo dpkg -i sogoupinyin_x.x.x.xxxx_x86_64.deb
如果出错，下载依赖，再执行上句     sudo apt-get install –f
安装fcitx                                         sudo apt-get install fcitx
打开系统设置中的语言支持，并修改键盘输入方式为fcitx
重启电脑
这时，在右上方会出现一个键盘图标，按下图依次点击Configure
按下方的“+”
把打勾去掉，选择sogou Pinyin，点击OK，再点击close!
按“shift”键切换到搜狗输入法，即可输入中文



'''********************'''安装交叉工具链'''************************************************************'''
#编译命令
           arm-linux-as            编译ARM 汇编程序 
           arm-linux-ar            把多个.o 合并成一个.o 或静态库(.a) 
           arm-linux-ranlib        为库文件建立索引，相当于arm-linux-ar 
           arm-linux-ld            连接器(Linker), 把多个.o 或库文件连接成一个可执行文件 
           arm-linux-objdump       查看目标文件(.o)和库(.a)的信息    
           arm-linux-objcopy       转换可执行文件的格式 
           arm-linux-strip         去掉elf 可执行文件的信息. 使可执行文件变小 
           arm-linux-readelf       读elf 可执行文件的信息 
           arm-linux-gcc           编译.c 或.S 开头的C 程序或汇编程序 
           arm-linux-g++           编译c++程序 
         开发板上不允许编译程序的
         交叉编译：程序编写，编译在PC端进行，但是程序的运行是在开发板上执行

#编译步骤
    步骤：
            1.将压缩包拷贝到家目录(纯粹的linux环境中)，然后解压
            2.设置环境变量(如果不设置，每次要写arm-linux-gcc的绝对路径，很麻烦)
                 环境变量：系统默认的一个路径
                 export PATH=/home/gec/arm-2009q3/bin:$PATH
				 
	步骤：
  a.将arm-linux-gcc-4.4.3.tar.gz解压到Ubuntu
	cd /mnt/hgfs
	sudo tar zxvf arm-linux-gcc-4.4.3.tar.gz -C /
  b.将交叉编译工具拷贝到用户目录
	cd /opt/FriendlyARM/toolschain
	sudo cp 4.4.3 /usr/local/arm -rf
  c.配置环境变量
	vi ~/.bashrc
	修改最后两行的环境变量
	export PATH=/usr/local/arm/4.4.3/bin:$PATH
	export LD_LIBRARY_PATH=/usr/local/arm/4.4.3/lib:$LD_LIBRARY_PATH 



'''********************'''换源'''************************************************************'''

sudo vim /etc/apt/sources.list

替换为如下
# 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse

# 以下安全更新软件源包含了官方源与镜像站配置，如有需要可自行修改注释切换
deb http://security.ubuntu.com/ubuntu/ jammy-security main restricted universe multiverse
# deb-src http://security.ubuntu.com/ubuntu/ jammy-security main restricted universe multiverse

# 预发布软件源，不建议启用
# deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-proposed main restricted universe multiverse
# # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ jammy-proposed main restricted universe multiverse
