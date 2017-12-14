这里我们需要从Python的角度了解一下协程的概念



# 生成器
利用生成器可以使用一个整数的内存即可便利数组列表，生成器通过yield实现：
``` python
def l_range(num):
    index = 0
    while index < num:
        yield index
        index += 1
```
访问这些数据，可以使用下面的方法：
``` python
# 方法1
l = l_range(5)
print(next(l))
print(next(l))
print(next(l))
print(next(l))
print(type(l))
# 方法2
for i in l_range(5):
    print(i)
    print(type(i))
```
这里我分别用type看了一下二者的不同，得到了：
``` shell
0
1
2
3
<class 'generator'>
0
<class 'int'>
1
<class 'int'>
2
<class 'int'>
3
<class 'int'>
4
<class 'int'>
```
上面的代码用到了yield index，配合next(l)的使用。这样在使用next的时候会调用生成器，在yield处返回，当再次调用next就会从下一行，也就是从`index+=1`这一行继续执行

> 1. http://www.cnblogs.com/lateink/p/7523011.html  
> 2. https://segmentfault.com/a/1190000001813992

## Python 协程
协程的调用来自用户，Python在3.4中引入了协程的概念，但是这个还是以生成器对象为基础的，3.5则确定了协程的语法。下面简单介绍asyncio的用法。

这里套用上面生成器的代码，只是略做改动：
``` python
def jumping_range(up_to):
    index = 0
    while index < up_to:
        jump = yield index
        if jump is None:
            jump = 1
        index += jump


iterator = jumping_range(20)
for i in range(3):
    print(next(iterator))
    print(iterator.send(2))
```
这里可以将`jump = yield index`看做是:
``` python
yield index
jump = yield
```
但是这么拆分会导致各种问题，但是我是这么理解的。测试可以发现yield会返回，并等待下一次调用，与生成器不同的是，yield会在函数内返回send传入的值。