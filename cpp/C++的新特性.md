这里主要是介绍一下C++的新特性，包括C++11、C++14、C++17等

____

<!-- TOC -->

- [C++11的新特性](#c11的新特性)
    - [智能指针](#智能指针)
    - [右值引用以及移动语义](#右值引用以及移动语义)
        - [什么是右值](#什么是右值)
        - [move语义](#move语义)
    - [async](#async)
    - [多线程](#多线程)
    - [lambda函数](#lambda函数)
- [C++14](#c14)
- [C++17](#c17)

<!-- /TOC -->
____

# C++11的新特性

## 智能指针



## 右值引用以及移动语义
右值引用是C++11中最重要的特性之一。
### 什么是右值

首先这里需要区分左值和右值，左值对应变量的存储位置，右值对应变量本身。

``` cpp
int& foo();
foo() = 3; //ok, foo() is an lvalue

int bar();
int a = bar(); // ok, bar() is an rvalue
```

### move语义




>  https://www.zhihu.com/question/22111546  
>  http://blog.csdn.net/booirror/article/details/45057689  
____

## async

分析代码：
``` cpp
#include <future>
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>
using namespace std;
int doSomething(char c)
{
	std::default_random_engine dre(c);
	std::uniform_int_distribution<int> id(10, 1000);
	//
	for (int i = 0; i < 10; ++i)
	{
		this_thread::sleep_for(chrono::milliseconds(id(dre)));
		cout.put(c).flush();
	}
	return c;
}
int func1()
{
	return doSomething(',');
}
int func2()
{
	return doSomething('+');
}
int main()
{
	std::cout << "starting func1() in background"
		<< " and func2() in background:" << std::endl;
	//异步开始func1函数
	std::future<int> result1(std::async(func1));
	int result2 = func2();	//同步调用func2函数
	//等待func1结束，获取func1与func2的返回值之和
	int result = result1.get() + result2;
	std::cout << "\nresult of func1()+ func2():  " << result << std::endl;
	system("pause");
	return 0;
}
```
得到结果：

上面的代码中使用了随机数引擎，并且初始化了由参数传递进来的不同的种子，避免随机结果相同。通过随机数引擎参数均匀分布的随机数，利用到sleep_for中，使得时间上随机化。采用了：
``` cpp
	std::future<int> result1(std::async(func1));
	int result2 = func2();	
	int result = result1.get() + result2;
```
异步调用func1和func2而非以前的同步调用方式：
``` cpp
int result = func1()+func2();
```
在上面的实现代码中，通过使用async函数将func1运行在后台，并将结果分配给一个future类的对象。在对result1使用函数get的时候，如果此时func1还没有被调用，则在调用成员函数get时调用该函数，且只能被调用一次，然后该future对象就会失效，通过result1.valid()会获得状态值假的这个状态。
这里看一下future对象都有那些成员函数



## 多线程


## lambda函数






____

# C++14  



____

# C++17



____