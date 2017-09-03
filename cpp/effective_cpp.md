包含了effective C++和more effective C++中一些常用到的点

_____

<!-- TOC -->

- [09 绝不在构造和析构过程中调用virtual函数](#09-绝不在构造和析构过程中调用virtual函数)

<!-- /TOC -->
_____



# 09 绝不在构造和析构过程中调用virtual函数

在base class构造期间，virtual函数不是virtual函数



如何在
1. 在class Base中，将vfunc改成non-virtual