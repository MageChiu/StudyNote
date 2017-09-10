这里主要是介绍一下C++的新特性，包括C++11、C++14、C++17等

____

<!-- TOC -->

- [C++的特性](#c的特性)
    - [常用的关键字](#常用的关键字)
        - [static](#static)
            - [首先是熟悉的面向过程：](#首先是熟悉的面向过程)
            - [static在面向对象过程中的使用](#static在面向对象过程中的使用)
        - [virtual关键字](#virtual关键字)
        - [register关键字关键字](#register关键字关键字)
        - [extern关键字](#extern关键字)
    - [深拷贝浅拷贝](#深拷贝浅拷贝)
    - [多态](#多态)
    - [四种类型转换](#四种类型转换)
        - [static_cast:](#static_cast)
        - [const_cast](#const_cast)
        - [dynamic_cast](#dynamic_cast)
        - [reinterpret_cast](#reinterpret_cast)
    - [友元函数](#友元函数)
- [C++11的新特性](#c11的新特性)
    - [智能指针](#智能指针)
        - [shared_ptr](#shared_ptr)
        - [weak_ptr](#weak_ptr)
    - [右值引用以及移动语义](#右值引用以及移动语义)
        - [什么是右值](#什么是右值)
        - [右值使用的折叠规则](#右值使用的折叠规则)
        - [move语义](#move语义)
            - [Rvalue和Lvalue Reference的重载规则](#rvalue和lvalue-reference的重载规则)
            - [返回Rvalue Reference](#返回rvalue-reference)
    - [async](#async)
    - [多线程](#多线程)
    - [lambda函数](#lambda函数)
- [C++14](#c14)
- [C++17](#c17)
    - [`fold expression`](#fold-expression)
    - [`structured binding`](#structured-binding)

<!-- /TOC -->
____


# C++的特性
## 常用的关键字

本篇文章是对C++中常见关键字的含义进行了详细的分析介绍，需要的朋友参考下，先笼统的介绍下，后面会详细介绍：
- inline：定义内联函数，该关键字是基于定义，如果只在函数声明时给出inline，则函数不会被认为是内联函数，所以必须在函数定义的地方也加上inline，同时inline只是向编译器建议函数以内联函数处理，不是强制的。
- const：定义常成员，包括const数据成员和const成员函数，const数据成员必须，也只能通过构造函数的初始化列表进行初始化，const成员函数只能访问类的成员，不能进行修改，如果需要修改，则引入下面的mutable关键字。
- mutable：这个关键字的引入是解决const成员函数要修改成员变量，通常而言，const成员函数只能访问成员变量，不能修改，但是如果成员变量被mutable修饰了，则在const成员函数中可以修改该变量。mutable和const不能同时用于修饰成员变量。
- static：声明静态成员，包括静态数据成员和静态成员函数，它们被类的所有对象共享，静态数据成员在使用前必须初始化，而静态成员函数只能访问静态数据成员，不能访问非静态数据成员，因为该函数不含有this指针。
- virtual：声明虚函数，用于实现多态，该关键字是基于声明的。
- friend：声明友元函数和友元类，该关键字也是基于声明的。
- volatile：被该关键字修饰的变量是指其值可能在编译器认识的范围外被修改，因此编译器不要对该变量进行的操作进行优化。可以与const同时修饰一个变量。
- explicit：修饰的构造函数不能在隐式转换中使用
- register：

下面详细介绍几个关键字。

### static
这里我们首先分析常用的static。  

由于C++兼顾两种编程思想：面向过程和面向对象，因此在关键字的应用上我们也要区分在这两种情况下的不同。
#### 首先是熟悉的面向过程：
	
1. 定义全局静态变量：这个定义静态全局变量和全局变量区别不是很大，但是可以显示该变量只能在本文件中使用。总结下来静态全局变量有以下的特点：

	- 该变量在全局数据区分配内存；
	- 未经初始化的静态全局变量会被程序自动初始化为0（自动变量的值是随机的，除非它被显式初始化）；
	- 静态全局变量在声明它的整个文件都是可见的，而在文件之外是不可见的；

	已经初始化的静态变量会放在.data，没有初始化的放在.bss段，其实也可以把他们统称为数据段
2. 定义静态局部变量

	静态局部变量与全局变量一样都是放在数据段的，已经初始化的放在.data段，没有初始化的放在.bss段，用来分配一定的空间。既然是放在数据段，那么生命周期就是整个程序运行结束，其实可以说是从局部变量所在的域（包括函数内部）第一次被使用，到最后一次被使用结束
	
	- 该变量在全局数据区分配内存；
	- 静态局部变量在程序执行到该对象的声明处时被首次初始化，即以后的函数调用不再进行初始化；
	- 静态局部变量一般在声明处初始化，如果没有显式初始化，会被程序自动初始化为0；
	- 它始终驻留在全局数据区，直到程序运行结束。但其作用域为局部作用域，当定义它的函数或语句块结束时，其作用域随之结束；
静态变量主要用来解决分配在栈里面的局部变量会被释放，没有办法继续使用的问题。
3. 静态函数
主要是限制不能再其他文件中被访问。
定义静态函数的好处：
静态函数不能被其它文件所用；
其它文件中可以定义相同名字的函数，不会发生冲突；


#### static在面向对象过程中的使用
static在面向对象中的应用，不外乎是修饰两个，一个是类的成员变量，一个是类的成员函数

1. 静态数据成员静态数据成员有以下的特点：

	- 首先静态数据成员是类共享的，在整个程序中只有一份拷贝。
	- 储存区域仍然是全局数据区
	- 初始化的时候采用如下的格式
	- 如果权限允许，使用的时候可以直接用类名利用作用域运算符调用，或者是使用点的形式

2. 静态成员函数

静态成员函数，可以总结为以下几点：
- 出现在类体外的函数定义不能指定关键字static；
- 静态成员之间可以相互访问，包括静态成员函数访问静态数据成员和访问静态成员函数；
- 非静态成员函数可以任意地访问静态成员函数和静态数据成员；
- 静态成员函数不能访问非静态成员函数和非静态数据成员；
- 由于没有this指针的额外开销，因此静态成员函数与类的全局函数相比速度上会有少许的增长；
- 调用静态成员函数，可以用成员访问操作符(.)和(->)为一个类的对象或指向类对象的指针调用静态成员函数，也可以直接使用如下格式：

``` cpp
 ＜类名＞::＜静态成员函数名＞（＜参数表＞）
```

调用类的静态成员函数。
上面就是简单的总结下static接下来是virtual。

### virtual关键字
virtual关键字是C++ OO机制中很重要的一个关键字，主要是用于在基类中表明该函数是虚函数，以实现在派生类中可以继承。

virtual在基类中修饰函数时，表示该函数是虚函数，在该基类的子类中将继承这一个属性

virtual在继承的环节中还可以修饰基类，表示该继承为虚继承，这是为了解决C++所有特有的多重继承带来的麻烦。

C++的隐藏规则：
1. 如果派生类的函数与基类的函数同名，但是参数不同。此时，不论有无virtual关键字，基类的函数将被隐藏（注意别与重载混淆）。
2. 如果派生类的函数与基类的函数同名，并且参数也相同，但是基类函数没有virtual关键字。此时，基类的函数被隐藏（注意别与覆盖混淆）。



### register关键字关键字
register告诉编译器“尽可能快地访问这个变量”。但是加快访问速度取决于实现，不过，register经常是通过寄存器中放置变量实现的。如上文所言，register并不能保证将变量放在寄存器里，甚至不能保证提高访问速度，register只是对编译器的一个暗示，是否优化，或者如何优化，完全在编译器的实现上。被register修饰的变量会有一些限制，不能得到或者计算register变量的地址；register变量只能在一个块中声明（不可能有全局或者静态的register变量），然而可以在一个函数中，也就是参数表中，使用register变量作为一个形式参数。
> 最好避免使用register。

### extern关键字
关键字extern告诉编译器存在一个变量和函数，即使编译器不能在当前编译的文件中没有看到它。这个变量或函数可能在拎一个文件中或者在当前文件的后面定义： 

``` cpp
#include <iostream>
using namespace std;
​extern int i;
extern int func();
​int main()
{
	i = func();    
	cout << i << endl;    
	system("pause");    
	return 0;
}
​int i;  //定义
int func() 
{    
	return 421;
}
```

> 当编译器遇到extern int i时，他知道i肯定作为全局变量存在于某处。


## 深拷贝浅拷贝


## 多态

C++的多态是C++最基本的一个性质之一。简而言之，多态分为静态多态和动态多态。

## 四种类型转换
C++引入了4种类型转化操作符（cast operator）：static_cast，const_cast，dynamic_cast和reinterpret_cast，使用方法与C语言中略有不同：
``` cpp
 (type)expression;   //这是C语言的
```
然后引入C++的：
``` cpp
 static_cast<type>(expression);//这是C++的
```
然后分别介绍一下：

### static_cast:
static_cast：static_cast基本上拥有与C旧式转型相同的威力和意义，以及相同的限制。但是，该类型转换操作符不能移除常量性，因为有一个专门的操作符用来移除常量性。

### const_cast
const_cast：用来改变表达式中的常量性（constness）或者易变形（volatileness），只能用于此功能。
使用方式如下：
``` cpp
const_cast<type_id> (expression)
```
其中type_id和expression的类型是一样的。
1. 常亮纸质被转化成非常量指针，并且仍然指向原来的对象。
2. 常亮引用被转换成非常量引用，并且仍然指向原来的对象；
3. const_cast一般用于修改底指针，如const char* p的形式。

### dynamic_cast
dynamic_cast：将指向基类basic class object的pointer或者reference转型为指向派生类derived（或这sibling base）class object的pointer或者reference中，并且可以获知是否转型成功：如果转型失败，当转型对象是指针的时候会返回一个null指针；当转型对象是reference会抛出一个异常exception。dynamic_cast无法应用在缺乏虚函数的类型上，也不能改变类型的常量性。此外，dynamic_cast还有一个用途就是找出被对象占用的内存的起始点。



### reinterpret_cast
reinterpret_cast：这个操作符的转换结果几乎总是和编译器平台相关，所以不具有移植性。reinterpret_cast的最常用用途是转换“函数指针”类型，如下： 
``` cpp
typedef void(*FuncPtr)();
int doSomething();
int main()
{    
	FuncPtr funcPtrArray[10];    
	funcPtrArray[0] = reinterpret_cast<FuncPtr>(&doSomething);    
	return 0;
}
```
通过reinterpret_cast强迫编译器了，并成功的将不同的类型的函数&doSomething转换为需要的类型。不过这个操作符进行的转换动作不具有移植性（C++不保证所有的函数指针都能以此方式重新呈现），某些情况下这样的转型可能会导致不正确的结果，所以这种操作不到万不得已不要使用。




## 友元函数

友元机制，允许一个类将对其非公有成员的访问权授予指定的函数或类。友元的声明以关键字 friend 开始。它只能出现在类定义的内部。友元声明可以出现在类中的任何地方：友元不是授予友元关系的那个类的成员，所以它们不受声明出现部分的访问控制影响。



# C++11的新特性

## 智能指针
### shared_ptr

> 注意：
>1. 不使用相同的内置指针初始化多个智能指针
>2. 
>3. 

### weak_ptr


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

### 右值使用的折叠规则



### move语义

`std::move()` 声明在```<utility>```

> 一般而言，C++标准库保证了，在一次move操作以后，对象出于有效但不确定的状态。也就是说，在执行

>  https://www.zhihu.com/question/22111546  
>  http://blog.csdn.net/booirror/article/details/45057689    
>  http://blog.csdn.net/yapian8/article/details/42341307   
____
#### Rvalue和Lvalue Reference的重载规则
- 如果只实现 `void foo(X&);` 而没有实现 `void foo(X&&);`，行为如同C++98：`foo()`可因lvalue但不能因Rvalue被调用。
- 如果实现`void foo(const X&);`而没有实现`void foo(X&&);`,
- 如果实现了
	``` cpp
	void foo(X&);
	void foo(X&&);
	```
	or
	``` cpp
	void foo(const)
	```
	就可以区分 “为Rvalue服务”和“为lvalue服务”。“为Rvalue服务”部分需要提供move语义。
- 如果实现
	``` cpp
	void foo(X&&);
	```
	但是没有实现`void foo(X&)`和`void foo(const X&)`,foo()可因Rvalue被调用，但是如果尝试使用lvalue调用它的时候，会触发编译报错。

也就是说，如果class没有提供move语义，只提供惯用的copy构造函数和copy assignment操作符，Rvalue reference可以调用他们，意味着在`std::move()`使用中，如果有提供move语义就调用move语义，否则使用copy语义。


#### 返回Rvalue Reference



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

> *首先，为什么要增加lambda这个东西呢？主要是为了**面向函数编程***






____

# C++14  



____

# C++17

## `fold expression`


## `structured binding`

____