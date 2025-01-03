'''********************'''整合包'''************************************************************'''
https://blog.csdn.net/weixin_44505135/article/details/136737915

1、官网下载window-embeddable-package
2、新建文件夹pack，解压，删除压缩包
3、进入解压出来的python-3.10.11-embed-amd64文件夹，找到python310._pth这一文件，将"#import site"注释去掉
4、在当前目录新建一个get-pip.py，然后去(bootstrap.pypa.io/get-pip.py)将三万多行复制到这个文件里
5、打开终端执行 .\python.exe get-pip.py
6、检验 .\python.exe -m pip
7、使用Scripts文件夹中的pip.exe安装包，如.\Scripts\pip.exe install openai
8、回到 pack 文件夹编写代码 test.py
9、使用python-3.10.11-embed-amd64文件夹下的python.exe执行
10、可以创建.bat文件来执行
python-3.10.11-embed-amd64\python.exe test.py
pause


'''********************'''docker打包'''************************************************************'''
1、运行docker服务
2、执行python -m pip freeze > requirements.txt 导出requirements.txt依赖列表
（该项目需要在虚拟环境中，否则导出会包含其它非依赖包）
3、新建目录src，将源码放入src目录
4、新建文件名为Dockerfile无后缀，添加以下内容：
'''
#基于python3.10的基础镜像
FROM python:3.10

#将当前目录添加到src文件夹下
ADD . /src
#设置src文件夹是工作目录
WORKDIR /src

#安装支持 -i 换国内pip源，速度更快
RUN pip install -r requirements.txt -i https://pypi.mirrors.ustc.edu.cn/simple/

CMD ["./python-3.10.11-embed-amd64/python.exe", "./chatbot.py"]


# FROM #基础镜像，一切从这里开始构建
# MAINTAINER #镜像是谁写的，姓名+邮箱
# RUN #镜像构建时需要运行的命令
# ADD #步骤，tomcat镜像，这个tomcat压缩包，添加内容
# WORKDIR #镜像工作目录
# VOLUME #挂载目录
# EXPOSE #暴露端口配置
# CMD #指定这个容器启动的时候要运行的命令，只有最后一个会生效，可被替代
# ENTRYPOINT #指定这个容器启动的时候要运行的命令，可以追加命令
# ONBUILD #当构建一个被继承DockerFile 这个时候就会运行 ONBUILD 的指令，触发指令
# COPY 类似ADD,将我们的文件拷贝至镜像中
# ENV 构建的时候设置环境变量
'''
5、运行命令构建镜像
docker build -t chatbot:v1 .
'''
-t参数指定构建成后，镜像的仓库、标签等,
chatbot 给镜像取的名字
v1 给镜像取的标签（默认标签为latest）
. 表示 Dockerfile 文件在当前目录下
'''
6、运行容器 docker run -it --name=chatbotCtn chatbot:v1    （需要加上标签）
'''
docker run [OPTIONS] IMAGE [COMMAND] [ARG...]

# [OPTIONS]参数
--name=“容器新名字” 为容器指定一个名称；
-d: 后台运行容器并返回容器ID，也即启动守护式容器(后台运行)；
-i：以交互模式运行容器，通常与 -t 同时使用；
-t：为容器重新分配一个伪输入终端，通常与 -i 同时使用；也即启动交互式容器(前台有伪终端，等待交互)；
# IMAGE：容器镜像名
# [COMMAND]参数：命令
# [ARG...]：传参
'''
7、退出容器终端命令：exit
8、docker相关命令
查看容器状态：docker ps -a
查看容器日志输出：docker logs -f chatbot
停止容器：docker stop chatbotCtn
删除容器：docker rm chatbotCtn

进入容器：docker exec -it chatbotCtn bash
进入容器后启动应用：python /code/src/chatbot.py
在外部启动应用：docker exec -it chatbotCtn python /code/src/chatbot.py


'''********************'''docker-compose'''************************************************************'''
9、创建docker-compose.yml
'''
version: "3"  # 文件格式版本
services:
  chatbot-compose:  # 服务名（docker-compose编排名称，一般同微服务名称，注意不要与其>他服务重名）
    image: "chatbot:v1"  # docker镜像名及版本，如果没有本地镜像，则需要在本文件中创建
    hostname: chatbot-host  # docker容器主机名
    container_name: chatbotCtn  # docker容器名
    volumes:  # 挂载目录
      - ./src:/src  # 将本地的src目录挂载到容器内的src目录
      #- ./docker:/docker
    ports:  # 端口映射
      - "5000:5000" # 外部端口:内部端口
    environment:  # 设置环境变量
      - TZ=Asia/Shanghai  # 设置时区
    command: python /src/chatbot.py  # 设置启动命令
    network_mode: bridge  # 网络模式：host、bridge、none等，我们使用bridge
    restart: unless-stopped  # 自动重启
'''
10、运行命令：docker-compose run chatbot-compose
11、相关命令 #docker与docker-compose多数命令和选项通用
启动所有服务：docker-compsoe up
-d              后台运行
--service-ports 启用服务定义中的端口映射
--rm            在容器退出后自动删除容器
查看容器的日志输出：docker-compose logs -f chatbot-compose    #-f表示跟随（follow）容器的日志输出，这样就可以实时看到新的日志条目。

