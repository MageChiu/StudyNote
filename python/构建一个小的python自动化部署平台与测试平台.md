#准备部分
首先要明确功能是要干什么，这里主要是想构建一个能够自动化部署版本的工具，以及进行一些简单的测试。
## 明确功能
1. 能够部署版本到制定的目标机
2. 能够远程执行脚本，获取并处理返回值

## 辅助功能
1. 能够通过配置文件获取目标机配置
2. 能够在本地输出日志

# 代码构建

## 代码架构规划

### 总体规划
1. 读取配置文件部分
2. 记录日志部分
3. 远程连接目标机，传输文件
4. 远程执行命令

### 读取配置文件
读取配置文件采用模块


### 日志记录部分
日志部分需要分级进行记录日志

### 远程控制部分
这部分主要有两个功能，一个是将本地的文件传输到远程目标机上，另一个功能是在远程的目标机上执行需要的脚本，用以安装版本
方案有两个：
1. 通过ssh模块进行
    优点：对目标机要求低，不需要提前部署服务
    缺点：功能性扩展少
2. 用python在目标机上构建一个服务
    优点：可以扩展功能
    缺点：需要在目标机部署服务、

这里决定使用方案二，通过socket进行版本传输。这里会构建一个类似ftp的服务器，采用

### 测试部分
提供服务层的测试工具。主要是整合测试库的相关的功能，提供针对服务层的脚本化测试。


## 构筑代码

## README
这部分主要是该模块的使用手册

本次设计为了方便更多的人使用，采用python2.7 进行开发，后面会相应的进行python 3 升级





