
---

###### （Item 1 是第一章的开始，因此第一章的开始部分翻译就写到这里）

C++98 

---
当一个复杂系统的用户不知道它是如何工作时，用它做什么，可是很快乐，说了很多关于系统的设计。



如果你会忽视这一小撮伪码,我们思考如下的一个函数：
```cpp
template<typename T>
void f(ParamType param);
```
上面函数的调用过程如下：
```cpp
f(expr);        //调用函数f，该函数的参数是expression
```
通过编译，编译器利用expr进行了两个类型推导：分别是对于T和对于ParamType。这两个类型通常是不同的，因为ParamType通常会包括一些修饰符，例如const或者引用限定符。举一个例子，如果模板的如下所声明：
```cpp
template<typename T>
void f(const T& param);   //参数类型是const T&
```
然后我们可以这样调用：
```cpp
int x = 0;
f(x);    //传递一个整形参数调用f
```
T会被推导为int类型，但是ParamType（参数类型）会被推导为 “const int&” 。  
这里很容想到T的类型推导和传入参数的类型推导一样，在上面的例子中，T就是expr的类型。在上面的例子中，情况是这样的：x是int类型的，然后T被推到为int类型。但是并不是所有情况都是这样。T的类型推导不仅依靠expr的类型，而且和ParamType的组成有关系。这里有三个例子：
* 参数类型（ParamType）是指针或者引用类型，但不是universal reference（universal reference 会在Item 24中详细讲述，当前只需要知道这种引用存在，切不同于左值引用或右值引用）
* 参数类型是universal reference
* 参数类型既不是指针也不是引用  

因此，后面有三个类型推导方案进行仔细分析。其中给每一个都是来自于普通的模板，然后调用它：
```cpp
template<typename T>
void f(ParamType param);
...
...
f(expr);    // 通过expr推导T和ParamType
```


---

## Case 1： 参数类型是引用或者指针，而非Universal Reference

当参数类型是引用类型或者指针类型，且不是universal reference的时候，是最简单的方案。在这种情况下，类型推导如下进行实现：
* 如果exper（表达式）的类型是一个引用，忽略引用部分
* 然后

举个例子，如果下面是我们的模板：
```cpp
template<typename T>
void f(T& param);    //参数是一个引用
```
然后我们有下面的参数定义，
```cpp
int x = 27;             // x 是一个int类型
const int cx = x;       // cx 是整型常数
const int& rx = x;      // rx 是一个指向x的引用，作为一个常数使用
```
在使用这些值调用函数时的参数和T的类型推导如下所示：
```cpp
f(x);   //T是int类型，参数类型是int&

f(cx);  //T是const int类型，
        //参数类型是const int&

f(rx);  //T是const int类型
        //参数类型是const int&
        
```





























