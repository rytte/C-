/********************/Git/************************************************************/

//基础命令
git init					//初始化一个新的 Git 仓库
git clone <repo_url>		//克隆远程仓库到本地
git status					//查看当前工作区的状态，显示哪些文件被修改、哪些文件是未跟踪的
git add <file>				//将文件添加到暂存区，以准备提交。
git add .					//添加所有文件
git commit - m "message"	//提交暂存区的更改到本地仓库，并附上更新信息
git log						//查看提交历史
git diff					//查看文件差异
git reset					//撤销某次提交或修改，可以指定回退的提交

//分支操作
git branch					//查看所有分支
git branch <branch>			//创建新分支
git checkout <branch>		//切换分支
git checkout - b <branch>	//创建并切换到新分支。
git merge <branch>			//将指定的分支合并到当前分支
git branch - d <branch>		//删除本地分支

// 远程操作
git remote - v				// 查看远程仓库的 URL
git fetch					// 从远程仓库获取最新的提交信息，但不合并到当前分支
git pull					// 拉取远程仓库的最新提交，并自动合并到当前分支
git push					// 将本地的提交推送到远程仓库
git push - u origin <branch> // 推送并设置 upstream 分支（关联本地和远程分支）

// 其他常用命令
git stash					// 保存当前工作区的更改（暂存区和工作区），并恢复到最后一次提交的状态
git stash apply				// 恢复暂存的更改
git tag						// 列出所有标签
git tag v1.0				// 创建标签
git rm <file>				// 从工作区和暂存区删除文件
git revert <commit>			// 撤销某个提交的影响，并生成一个新的提交
git show <commit>			// 查看某个提交的详细信息
git config --global user.name "Your Name"				// 设置全局用户名
git config --global user.email "your-email@example.com" // 设置全局电子邮件


