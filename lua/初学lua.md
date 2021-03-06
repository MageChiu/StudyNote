<!-- TOC -->

- [快速学习`lua`](#快速学习lua)
    - [1 `lua`初级入门](#1-lua初级入门)
        - [1.1 控制语句](#11-控制语句)
            - [1.1.1 `for`循环](#111-for循环)
        - [1.2 函数](#12-函数)
            - [1.2.1 冒号(:)和点(.)的区别](#121-冒号和点的区别)
    - [2. 字符串操作](#2-字符串操作)
    - [pair和ipair的区别](#pair和ipair的区别)

<!-- /TOC -->

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

## 2. 字符串操作

通过使用string库，lua可以很容易地操作字符串。string库中所有的字符索引从前往后是`1,2,...`，从后往前是`-1,-2,...`。string库中所有的function都不会直接操作字符串，而是返回一个结果：
``` lua
s = "[abc]"
string.len(s)        <==返回5
string.rep("abc", 2) <==返回"abcabc"
string.lower("ABC") <==返回"abc"
string.upper("abc") <==返回"ABC"
string.sub(s, 2)     <==返回"abc]"
string.sub(s, -2)    <==返回"c]"
string.sub(s, 2, -2) <==返回"abc"
string.format(fmt, ...)返回一个类似printf的格式化字符串
string.find(s, pattern, pos)
```
第1个参数：源字符串

第2个参数：待搜索之模式串

第3个参数：A hint, 从pos位置开始搜索

找到匹配返回：匹配串开始和结束的位置，否则返回nil

简单的模式串
``` lua
s = "hello world"
i, j = string.find(s, "hello")
print(i, j) --> 1 5
print(string.sub(s, i, j)) --> hello
print(string.find(s, "world")) --> 7 11
i, j = string.find(s, "l")
print(i, j) --> 3 3
print(string.find(s, "lll")) --> nil
```

格式化的模式串
``` lua
s = "Deadline is 30/05/1999, firm"
date = "%d%d/%d%d/%d%d%d%d"
print(string.sub(s, string.find(s, date))) --> 30/05/1999
```
下面的表列出了Lua支持的所有字符类：

- . 任意字符
- %s 空白符
- %p 标点字符
- %c 控制字符
- %d 数字
- %x 十六进制数字
- %z 代表0的字符
- %a 字母
- %l 小写字母
- %u 大写字母
- %w 字母和数字

上面字符类的大写形式表示小写所代表的集合的补集。例如，'%A'非字母的字符：

模式串中的特殊字符

( ) . % + - * ? [ ^ $

- '%' 用作特殊字符的转义字符
- '%.' 匹配点；
- '%%' 匹配字符 '%'。

转义字符 '%'不仅可以用来转义特殊字符，还可以用于所有的非字母的字符。当对一个字符有疑问的时候，为安全起见请使用转义字符转义他。

用'[]'创建字符集

- '[%w_]' 匹配字母数字和下划线
- '[01]' 匹配二进制数字
- '[%[%]]'匹配一对方括号

在'[]'中使用连字符'-'

'%d'    表示 '[0-9]'；

'%x'    表示 '[0-9a-fA-F]'

'[0-7]' 表示 '[01234567]'

在'[]'开始处使用 '^' 表示其补集：

'[^0-7]' 匹配任何不是八进制数字的字符；

'[^\n]' 匹配任何非换行符户的字符。

'[^%s]' == '%S'

模式修饰符

+ 匹配前一字符1次或多次

* 匹配前一字符0次或多次;最长匹配

- 匹配前一字符0次或多次;最短匹配

? 匹配前一字符0次或1次

^ 匹配字符串开头

$ 匹配字符串结尾

捕获：用()将要捕获的部分包围起来
``` lua
pair = "name = Anna"
firstidx, lastidx, key, value = string.find(pair, "(%a+)%s*=%s*(%a+)")
print(key, value) <== name Anna
```
拷贝捕获(%1-%9)

``` lua
s = "abc \"it\'s a cat\""
_,_,_,q = string.find(s, "([\"'])(.-)%1"))
print(q) <== it's a cat 如果%d代表第几个捕获的拷贝。
string.gsub(s, pattern, reps)
```
- 第1个参数：源字符串
- 第2个参数：待替换之模式串
- 第3个参数：替换为reps

将s中所有符合pattern的字串替换为reps，返回结果串+匹配数
``` lua
print(string.gsub("hello, world", "o", "a"))       <== hella, warld        2
gsub也可以用拷贝捕获技巧
print(string.gsub("hello, world", "(o)", "%1-%1")) <== hello-o, wo-orld    2
print(string.gsub("hello Lua", "(.)(.)", "%2%1")) <== ehll ouLa           4
function trim (s) return (string.gsub(s, "^%s*(.-)%s*$", "%1")) end <== 注意匹配数用括号丢弃
string.gsub(s, pattern, func)
``` 
第3个参数：自定义函数，对找到的匹配操作，并传出替换值
``` lua
s, n = string.gsub("hello world", "l+", function(s) return "xxx" end)
print(s, n) <== hexxxo worxxxd 2
string.gfind(s, pattern)
``` 
返回一个迭代器，迭代器每执行一次，返回下一个匹配串；
``` lua
iter = string.gfind("a=b c=d", "[^%s+]=[^%s+]")
print(iter()) <== a=b
print(iter()) <== c=d
```
通常用于泛性for循环,下面的例子结果同上
``` lua
for s in string.gfind("a=b c=d", "[^%s+]=[^%s+]") do
print(s)
end
```


## pair和ipair的区别
区别其实很简单，但是是一个很基本的区别。主要是在做基本循环的时候的会遇到










