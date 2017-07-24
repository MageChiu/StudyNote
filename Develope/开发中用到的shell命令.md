记录一下在开发过程中使用的一些命令

___
<!-- TOC -->

- [查看一个进程中有多少个线程](#查看一个进程中有多少个线程)
    - [pstree](#pstree)
    - [通过进程的属性](#通过进程的属性)
- [用curl名利测试http](#用curl名利测试http)
- [清理共享内存](#清理共享内存)
- [查看网络IO](#查看网络io)
- [查看网络设备](#查看网络设备)
- [awk](#awk)
- [查看消息队列](#查看消息队列)
- [shell中的循环](#shell中的循环)
    - [`for`循环](#for循环)
    - [`while`循环](#while循环)

<!-- /TOC -->

___




# 查看一个进程中有多少个线程

## pstree
``` shell
pstree -p `ps -e | grep svrName | awk '{print $1}' `
pstree -p `ps -e | grep svrName | awk '{print $1}' ` | wc -l

```

## 通过进程的属性
``` shell
cat /porc/`ps -e | grep svrName | awk '{print $1}' `/status
```
从其中的`Threads`属性中可以获取进程的数目，但是该进程数目会有创建这些线程的主线程的数目



# 用curl名利测试http



# 清理共享内存



# 查看网络IO




# 查看网络设备


# awk


# 查看消息队列
这里主要使用的命令是`ipcs`，


# shell中的循环
## `for`循环


## `while`循环


