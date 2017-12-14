这里主要是在新浪微博出了问题以后，微博说是改成了gRPC的模式，所以从网上找来一些内容进行学习。githu地址为：
> https://github.com/grpc/grpc

我主要是学习C++版的。同样，检出代码：
``` shell
git clone https://github.com/grpc/grpc.git
```

____

<!-- TOC -->

- [1. 框架](#1-%E6%A1%86%E6%9E%B6)

<!-- /TOC -->
____



# 1. 框架

gRPC的特征：
- 基于 HTTP/2， 继而 提供了连接多路复用、Body 和 Header 压缩等机制。可以节省带宽、降低TCP链接次数、节省CPU使用和延长电池寿命等。
- 支持主流开发语言（C, C++, Python, PHP, Ruby, NodeJS, C#, Objective-C、Golang、Java）
- IDL (Interface Definition Language) 层使用了 Protocol Buffers, 非常适合团队的接口设计

