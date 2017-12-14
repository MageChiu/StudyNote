<!-- TOC -->

- [threading模块](#threading模块)
- [Thread类](#thread类)
    - [1）创建一个Thread的实例，传给他一个函数](#1创建一个thread的实例传给他一个函数)
    - [2）创建一个Thread的实例，传给它一个可调用的类对象](#2创建一个thread的实例传给它一个可调用的类对象)
    - [3）从Thread派生出一个子类，创建这个子类的实例。](#3从thread派生出一个子类创建这个子类的实例)

<!-- /TOC -->

Python的多线程要比C++的多线程简单一些，虽然C++11的多线程已经实现了跨平台。但是相对还是比较麻烦。

Python代码是的执行是通过Python虚拟机来控制的。对Python虚拟机的访问由全局解释器锁（global interpreter lock，GIL）来控制，这个锁能够保证当前只能有一个线程在被运行，在多线程环境下，Python虚拟机按照如下的方法进行执行：
1）设置GIL
2）、切换到一个线程去执行
3）、运行：
            a）、指定数量的字节码的指令
            b）、线程主动让出控制（可以调用time.sleep（0））。
4）、把线程设置为睡眠状态
5）、解锁GIL
6）再次重复以上所有步骤
在调用外部代码（如C++扩展函数）的时候，GIL将会被锁定，直到这个函数结束为止（由于在这个期间没有Python的字节码被运行，多益不会做线程切换）。编写扩展的程序员可以主动解锁GIL

# threading模块

Python提供了几个用于管理线程的模块，包括thread、threading和Queue等。thread和threading模块允许程序员创建和关系线程，Queue场用来创建一个可以在多个线程之间共享数据的队列数据结构。
这里建议使用threading而不是使用thread，thread模块在主线程退出的时候，其他线程没有清理就被退出了，而threading模块这会保留所有“重要”的主线程。
threading不仅提供了Thread类，还提供了各种非常好用的同步机制。

# Thread类

threading的Thread类是在Python中主要的运行对象。具有很多thread模块中没有的函数，通过Thread创建线程的方法有三种：

## 1）创建一个Thread的实例，传给他一个函数

``` python
"""
@author: Charles Chiu
@contact: charles.r.chiu@gmail.com
@software: PyCharm Community Edition
@project name: ExThreading
@file: mtsleep3.py
@time: 2016/4/20 2:50
"""
import threading
from  time import  sleep,ctime
loops = [4,2]
def loop(nloop, nsec):
    print('start loop ',nloop,' at: ',ctime())
    sleep(nsec)
    print('loop ',nloop,' done at: ',ctime())
    return None
def main():
    print('main start at: ', ctime())
    threads = []
    nloops = range(len(loops))
    for i in nloops:
        t = threading.Thread(target=loop,
                             args=(i, loops[i]))
        threads.append(t)
    print(""" 调用各个线程的start函数 at """, ctime())
    for i in nloops:
        threads[i].start()
    ''' 后面 中使用了join函数进行自等待，因此这里可以完成一些在主函数中需要完成的事情'''
    print('*'*40, ctime(), '*'*40)
    """ 这里使用join函数，会等到线程结束或者在给了timeout参数的时候，等到超时位置 """
    for i in nloops:
        threads[i].join()
    print('all done at: ', ctime())
if __name__ == '__main__':
    main()
```

这里通过将函数传入给threading模块的Thread类

## 2）创建一个Thread的实例，传给它一个可调用的类对象

``` python
"""
@author: Charles Chiu
@contact: charles.r.chiu@gmail.com
@software: PyCharm Community Edition
@project name: ExThreading
@file: mtsleep4.py
@time: 2016/4/20 15:42
"""
import threading
from time import sleep,ctime
loops = [4,2]
class ThreadFunc(object):
    def __init__(self, func, args, name = ''):
        self.name = name
        self.func = func
        self.args = args
    def __call__(self):
        self.res = self.func(*self.args)
def loop(nloop, nsec):
    print('start loop ',nloop,' at: ',ctime())
    sleep(nsec)
    print('loop ',nloop,' done at: ',ctime())
    return None
def main():
    print('main start at: ', ctime())
    threads = []
    nloops = range(len(loops))
    for i in nloops:
        t = threading.Thread(target=ThreadFunc(loop,(i,loops[i]),loop.__name__))
        threads.append(t)
    print(""" 调用各个线程的start函数 at """, ctime())
    for i in nloops:
        threads[i].start()
    ''' 后面 中使用了join函数进行自等待，因此这里可以完成一些在主函数中需要完成的事情'''
    print('*' * 40, ctime(), '*' * 40)
    """ 这里使用join函数，会等到线程结束或者在给了timeout参数的时候，等到超时位置 """
    for i in nloops:
        threads[i].join()
    print('all done at: ', ctime())
if __name__ == '__main__':
    main()
```

上面

## 3）从Thread派生出一个子类，创建这个子类的实例。

``` python
"""
@author: Charles Chiu
@contact: charles.r.chiu@gmail.com
@software: PyCharm Community Edition
@project name: ExThreading
@file: mtsleep5.py
@time: 2016/4/20 15:53
"""
import threading
from  time import ctime,sleep
loops = [4,2]
class MyThread(threading.Thread):
    def __init__(self, func, args, name=''):
        threading.Thread.__init__(self)
        self.name = name
        self.func = func
        self.args = args
    def run(self):
        self.res = self.func(*self.args)
    def getResult(self):
        return self.res
def loop(nloop, nsec):
    print('start loop ', nloop, ' at: ', ctime())
    sleep(nsec)
    print('loop ', nloop, ' done at: ', ctime())
    return None
def main():
    print('main start at: ', ctime())
    threads = []
    nloops = range(len(loops))
    for i in nloops:
        t = MyThread(loop, (i, loops[i]), loop.__name__)
        threads.append(t)
    print(""" 调用各个线程的start函数 at """, ctime())
    for i in nloops:
        threads[i].start()
    ''' 后面 中使用了join函数进行自等待，因此这里可以完成一些在主函数中需要完成的事情'''
    print('*' * 40, ctime(), '*' * 40)
    """ 这里使用join函数，会等到线程结束或者在给了timeout参数的时候，等到超时位置 """
    for i in nloops:
        threads[i].join()
        print(threads[i].getResult())
    print('all done at: ', ctime())
if __name__ == '__main__':
    main()
```

上面是三种不同线程启动方式









