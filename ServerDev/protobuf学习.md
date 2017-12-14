protoBuf是Google的一个用来做序列化和反序列化的东西


_____
<!-- TOC -->

- [1. 安装](#1-%E5%AE%89%E8%A3%85)
- [2. 语法简介（主要proto3）](#2-%E8%AF%AD%E6%B3%95%E7%AE%80%E4%BB%8B%EF%BC%88%E4%B8%BB%E8%A6%81proto3%EF%BC%89)
- [3. proto2和proto3的区别](#3-proto2%E5%92%8Cproto3%E7%9A%84%E5%8C%BA%E5%88%AB)

<!-- /TOC -->
____


# 1. 安装

- 从github上获取资源
```shell
git clone https://github.com/google/protobuf.git
```

然后按照上面readme进行安装
- 检查并安装依赖
依赖的其他工具有：autoconf automake libtool curl make g++ unzip
``` shell
$ sudo apt-get install autoconf automake libtool curl make g++ unzip
```
- 下载gmock资源
```shell
$ ./autogen.sh
```
- 安装
``` shell
$ ./configure
$ make
$ make check
$ sudo make install
$ sudo ldconfig # refresh shared library cache.
```
- 安装完成，简单检测一下：
proto2的example
```
syntax = "proto2";
package Im;
message Content
{
    required int32      id = 1;     //ID
    required string     str = 2;    //str
    optional int32      opt = 3;    //optional field
} 
```
其中第一行`syntax = "proto2";`是用来表示是使用的proto2，在新版的protobuf中一般是要求加上的，如果要使用proto3，这一行必须制定使用proto3。下面是proto3的例子：





# 2. 语法简介（主要proto3）



# 3. proto2和proto3的区别
proto3比proto2更加简洁，不过增加了一些改动，官方推荐使用proto3。



