# 快速学习`lua`
## 1 `lua`初级入门
lua中常用的语法有：table，function，
### 1.1 控制语句
#### 1.1.1 `for`循环
lua中的for循环有两种，一种是基于整数的for循环，如下所示：
``` lua
for var = from, end, step do
    --
    print(var)
end
```
另一种则是泛型for循环，这里的for很像C++11 中的基于范围的for循环。lua库为for循环提供了几个迭代器：io.lines（用于遍历每一行）；pairs（用于迭代table）；ipairs（用来迭代数组）；string.gmatch（用来迭代字符串中的单词）
这里简单区分一下pairs和ipairs：
1. pairs会一直迭代table中的每一个元素，包括table自己
2. ipairs则是从下标为1的元素开始循环，遇到下标i所指向的tbl[i]为空时，则会停止，并返回
``` lua
test = {
 [0] = "test0",
 [1] = "test1",
 [2] = "test2",
 [4] = "test4",
}
for i,v in ipairs(test) do
    print(test[i].."===>"..v)
end
```
这里输出结果只有：
``` shell
test1===>test1
test2===>test2
```

### 1.2 函数
#### 1.2.1 冒号(:)和点(.)的区别
在lua脚本中，常

这里简单理解，就是通过：定义的函数












