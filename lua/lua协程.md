<!-- TOC -->

- [协程](#协程)
- [lua协程](#lua协程)

<!-- /TOC -->

# 协程
协程是一种用户态的轻量级线程
> IO密集型应用: 多进程->多线程->事件驱动->协程
> CPU密集型应用:多进程-->多线程 
事件驱动和协程则是在充分挖掘不断提供的性能的单核CPU的潜力

# lua协程
协程(coroutine)技术是一种程序控制机制，用它可以很方便实现协作式多任务。Lua语言实现的协程是一种非对称式(asymmetric)协程，或者称为半对称式(semi-coroutine)。这种协程机制之所以被称为非对称的，是因为它提供了两种传递程序控制权的操作：一种是(重)调用协程(通过coroutine.resume)；另一种是挂起协程并将程序控制权返回给协程的调用者(通过coroutine.yield)。一个非对称协程可以看做是从属于它的调用者的，二者的关系非常类似于例程(routine)与其调用者之间的关系。既然有非对称式协程，当然也就有对称式(symmetric)协程了，它的特点是只有一种传递程序控制权的操作，即将控制权直接传递给指定的协程。曾经有这么一种说法，对称式和非对称式协程机制的能力并不等价，但事实上很容易根据前者来实现后者。接下来我们就用代码来证明这个事实。

``` lua
#!/bin/lua
coro = {}
coro.main = function() end

coro.current = coro.main

function coro.create(f)
    return coroutine.wrap(function(val)
                                return nil,f(val)
                           end)
end

function coro.transfer(k,val)
    print("zhaopeng test")
    if coro.current ~= coro.main then
        return coroutine.yield(k,val)
    else
        while k do
            coro.current = k
            if k == coro.main then
                return val
            end
            k,val = k(val)
        end
        error("coroutine ended without transfering control...")
    end
end
```


``` lua 
#!/bin/lua
require("coro")

function foo1(n)
   print("1: foo1 received value "..n)
   n = coro.transfer(foo2,n + 10)
   print("2: foo1 received value "..n)
   n = coro.transfer(coro.main,n + 10)
   print("3: foo1 received value "..n)
   coro.transfer(coro.main,n + 10)
end

function foo2(n)
   print("1: foo2 received value "..n)
   n = coro.transfer(coro.main,n + 10)
   print("2: foo2 received value "..n)
   coro.transfer(foo1,n + 10)
end


function main()
    foo1 = coro.create(foo1)
    foo2 = coro.create(foo2)
    local n = coro.transfer(foo1,0)
    print("1: main received value "..n)
    n = coro.transfer(foo2,n + 10)
    print("2: main received value "..n)
    n = coro.transfer(foo1,n + 10)
    print("3: main received value "..n)
end

coro.main = main
coro.current = coro.main
coro.main()
```

coro.transfer(k,val)函数中k是将要接收程序控制权的协程，而val是传递给k的数据。如果当前协程不是主协程，tansfer(k,val)就简单地利用coroutine.yield(k,val)将当前协程挂起并传回两项数据，即程序控制权的下一站和传递给它的数据；否则进入一个控制权分派(dispatch)循环，该循环(重)启动(resume)k协程，等待它执行到挂起(suspend)，并根据此时协程传回的数据来决定下一个要(重)启动的协程。从应用示例来看，协程与协程之间似乎是用transfer直接传递控制权的，但实际上这个传递还是通过了主协程。每一个在主协程里被调用(比较coro.current和coro.main是否相同即可判断出)的transfer都相当于一个协程管理器，它不断地(重)启动一个协程，将控制权交出去，然后等那个协程挂起时又将控制权收回，然后再(重)启动下一个协程...，这个动作不会停止，除非<1>将(重)启动的协程是主协程；<2>某个协程没有提供控制权的下一个目的地。很显然，每一轮分派循环开始时都由主协程把握控制权，在循环过程中如果控制权的下一站又是主协程的话就意味着这个当初把控制权交出去的主协程transfer操作应该结束了，所以函数直接返回val从而结束这轮循环。对于情况<2>，因为coro.create(f)创建的协程的体函数(body function)实际是function(val) return nil,f(val) end，所以当函数f的最后一条指令不是transfer时，这个协程终将执行完毕并把nil和函数f的返回值一起返回。如果k是这样的协程，transfer执行完k,val = k(val)语句后k值就成了nil，这被视为一个错误，因为程序此时没法确定下一个应该(重)启动的协程到底是谁。所以在对称式模型下，每一个协程(当然主协程出外)最后都必须显式地将控制权传递给其它的协程。根据以上分析，应用示例的控制权的分派应为：

第一轮分派: main->foo1->main->foo2->main->main(结束)
第二轮分派: main->foo2->main->foo1->main->main(结束)
第三轮分派: main->foo1->main->main(结束)

由于可以直接指定控制权传递的目标，对称式协程机制拥有极大的自由，但得到这种自由的代价却是牺牲程序结构。如果程序稍微复杂一点，那么即使是非常有经验的程序员也很难对程序流程有全面而清晰的把握。这非常类似goto语句，它能让程序跳转到任何想去的地方，但人们却很难理解充斥着goto的程序。非对称式协程具有良好的层次化结构关系，(重)启动这些协程与调用一个函数非常类似：被(重)启动的协程得到控制权开始执行，然后挂起(或结束)并将控制权返回给协程调用者，这与计算机先哲们倡导的结构化编程风格完全一致。

综上所述，Lua提供的非对称式协程不但具有与对称式协程一样强大的能力，而且还能避免程序员滥用机制写出结构混乱的程序。

