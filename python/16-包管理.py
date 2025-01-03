'''********************'''pip 工具'''************************************************************'''
#换源
pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
pip config unset global.index-url

#python库文件编译
下载库文件
解压并进入文件夹
python setup.py build  
python setup.py install



#命令
pip 是 Python 包管理工具，该工具提供了对 Python 包的查找、下载、安装、卸载的功能。

pip --version/-V               #查看已安装的 pip 版本

pip install package-name       #下载安装包

pip uninstall package-name     #移除软件包

pip list                       #查看已经安装的软件包



'''********************'''conda 工具'''************************************************************'''
conda --version                 #查看conda版本

conda config --show         #查看conda的环境配置

conda update conda          #更新conda版本

conda update Anaconda   #更新Anaconda整体

conda create --help           #查询某个命令的帮助 

#设置清华镜像
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/conda-forge/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/bioconda/
#设置bioconda
conda config --add channels bioconda
conda config --add channels conda-forge
#设置搜索时显示通道地址
conda config --set show_channel_urls yes



'''********************'''conda 包管理'''************************************************************'''
conda list                                      #查询看当前环境中安装了哪些包

conda list pkgname                      #查询是否安装了指定包

conda search package_name       #查询当前Anaconda repository中是否有你想要安装的包

conda install package_name        #在当前（虚拟）环境中安装一个包

conda install numpy=0.20.3         #安装指定版本的包

conda update numpy                  #将包更新到最新版本

conda uninstall package_name    #卸载指定包（及依赖其的包）

conda uninstall package_name --force        #仅删除指定包

#清理anaconda缓存
conda clean -p                   # 删除没有用的包 --packages
conda clean -t                    # 删除tar打包 --tarballs
conda clean -y -all             # 删除所有的安装包及cache(索引缓存、锁定文件、未使用过的包和tar包)




'''********************'''conda 虚拟环境'''************************************************************'''
虚拟环境（Virtual Environment）：为不同项目所需的不同版本的包创建的独立环境。

conda create -n env_name python=3.8     #创建虚拟环境

conda activate env_name         #激活虚拟环境

#查看有哪些虚拟环境
conda env list
conda info -e
conda info --envs

#退出虚拟环境
conda activate
conda deactivate

conda remove --name env_name --all                         #删除虚拟环境及其所有包

conda remove --name env_name  package_name      #删除虚拟环境中的指定包

conda env export --name myenv > myenv.yml           #获得环境中的所有配置

conda env create -f  myenv.yml                                  #重新还原环境


