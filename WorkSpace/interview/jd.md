主要问题

# 后台开发相关
## TCP具体的调用流程，也就是在建立连接过程中使用的系统调用


## .bss和.data的区别？为什么要在.data放已经初始化的变量，两者有什么区别吗？
.bss中主要是存放没有初始化或者初始化为0的全局性质的变量（这里包含了静态变量和全局变量），具体体现是一个占位符，也就是说并未给该段分配空间，只是记录数据所需空间大小。不占用可执行程序的文件空间，其内容有操作系统初始化，

而.data主要是存放初始化的全局性质的变量，需要占用可执行程序的文件空间，其实也就是由程序进行初始化。数据保存在目标文件中。

这里还要说一下.rodata段，该段是进程间共享的。



## 函数的调用过程，函数时如何被调用的？如何通过寄存器进行调用的？

## 数据在程序中是如何被使用到的？


# 算法相关

## 洗牌算法
首先


## 稀疏向量求点积
主要是原有向量中含有大量的0，因此只需要考虑