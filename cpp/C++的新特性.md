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
    - [`fold expression`](#fold-expression)
    - [`structured binding`](#structured-binding)

<!-- /TOC -->
____

# C++11的新特性

## 智能指针
shared_ptr

> 注意：
>1. 不使用相同的内置指针初始化多个智能指针
>2. 
>3. 



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

这里参考了别人的一个说法，左值和右值都是针对表达式而言的，左值是指表达式结束后依然存在的持久的对象，而右值是指表达式结束就不存在的临时对象。*一个区分左值和右值的简单方法是，看能不能对表达式取地址。*简而言之，如果能对表达式取地址，就是左值，否则为右值。
``` cpp
int a = 10;
int b = 20;
int *pFlag = &a;
vector<int> vctTemp;
vctTemp.push_back(1);
string str1 = "hello ";
string str2 = "world";
const int &m = 1;
```
其中，：
- `a`:
- `b`:
- `a+b`
- `++a`:
- `a++`:
- `pFlag`:
- `*pFlag`:
- `100`和`string("hello")`:
- `str1+str2`


右值引用之前，先看一下*左值引用*。左值引用，根据其修饰符不同，可以分为非常量左值引用和常量左值引用。
- 非常量左值只能绑定到非常量左值，不能绑定常量左值、非常量右值和常量右值。
	- 如果允许绑定到常量左值和常量右值，则非常量左值引用可以用于修改常量左值和常量右值，这明显违反的常量的定义
	- 如果允许绑定到非常量右值，则会导致危险的情况出现，因为非常量右值是一个临时对象，这样一来，非常量左值引用可能使用了一个已经被销毁的临时对象。
- 常量左值可以绑定到所有的类型上，包括非常量左值、常量左值、非常量右值、常量右值

右值引用根据其修饰符的不同，也可以分为非常量右值引用和常量右值引用。
- 非常量右值引用只能绑定到非常量右值。
	- 如果允许绑定到非常量左值，则会错误的窃取一个持久对象的数据。
	- 如果允许绑定到常量左值和常量右值，则非常量右值引用可以修改常量左值和常量右值，这违反了常量的定义。
- 常量右值可以绑定到非常量右值和常量右值。


当添加了move版本的构造函数和赋值函数的重载形式以后，执行绑定的优先级规制：
1. 常量值只能绑定到常量引用上，不能绑定到非常量引用上。
2. 左值优先绑定到左值引用上，右值优先绑定到右值引用上。
3. 非常量值优先绑定到非常量引用上。
> 注意：拷贝构造函数可以通过直接调用*this = s来实现，但是move构造函数却不能。这是因为在move构造函数中，s虽然是一个非常量右值，但是其本身确实一个左值，因此调用`*this =s`时，会使用拷贝赋值函数而不是move，这与move构造函数的语义不符。要使语义正确，这里需要将左值绑定到非常量右值上，C++11提供了move函数来实现这种转换，因此这里修改为`*this=move(s)`,这样move构造函数就会就会调用move赋值函数。



### move语义




>  https://www.zhihu.com/question/22111546  
>  http://blog.csdn.net/booirror/article/details/45057689    
>  http://blog.csdn.net/yapian8/article/details/42341307   
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

## `fold expression`


## `structured binding`

____