<!-- TOC -->

- [Python 与C 的相互调用](#python-%E4%B8%8Ec-%E7%9A%84%E7%9B%B8%E4%BA%92%E8%B0%83%E7%94%A8)
- [Python调C](#python%E8%B0%83c)
    - [获取参数](#%E8%8E%B7%E5%8F%96%E5%8F%82%E6%95%B0)
        - [API Function](#api-function)
        - [参数类型](#%E5%8F%82%E6%95%B0%E7%B1%BB%E5%9E%8B)
        - [字典获取并读取](#%E5%AD%97%E5%85%B8%E8%8E%B7%E5%8F%96%E5%B9%B6%E8%AF%BB%E5%8F%96)
    - [返回结果](#%E8%BF%94%E5%9B%9E%E7%BB%93%E6%9E%9C)
        - [返回一个字典对象](#%E8%BF%94%E5%9B%9E%E4%B8%80%E4%B8%AA%E5%AD%97%E5%85%B8%E5%AF%B9%E8%B1%A1)
- [参考资料](#%E5%8F%82%E8%80%83%E8%B5%84%E6%96%99)
    - [python3](#python3)
    - [python2](#python2)
- [C调Python](#c%E8%B0%83python)
    - [C语言调用Python3函数](#c%E8%AF%AD%E8%A8%80%E8%B0%83%E7%94%A8python3%E5%87%BD%E6%95%B0)

<!-- /TOC -->
# Python 与C 的相互调用




# Python调C
这里主要是参考python3的做法，python2的做法类似，只是相关的函数可能有所差别

首先是一个简单的python3的例子
``` cpp
/*
 * =====================================================================================
 *
 *       Filename:  chiuLib.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年12月11日 16时24分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Charles Chiu (), charles.r.chiu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <Python.h>

int greater_func(int a)
{
    return a+1;
}

static PyObject *_greater(PyObject *self, PyObject *args)
{
    int _a;
    int res;
    if ( !PyArg_ParseTuple( args, "i", &_a) )
    {
        return NULL;
    }
    res = greater_func(_a);
    return PyLong_FromLong(res);
}

static PyMethodDef ChiuLibMethods[] = {
    {
        "greater",
        _greater,
        METH_VARARGS,
        "add 1 for raw data"
    },
    {
        NULL,
        NULL,
        0,
        NULL
    }
};

static struct PyModuleDef chiulibmodule = {
    PyModuleDef_HEAD_INIT,
    "chiuLib",
    NULL,
    -1,
    ChiuLibMethods
};

PyMODINIT_FUNC  PyInit_chiuLib(void)
{
    return PyModule_Create(&chiulibmodule);
}
```
## 获取参数
### API Function

function | usage
:---: | :---:
int PyArg_ParseTuple(PyObject *args, const char *format, ...)| 分析函数的传入参数，成功返回true，失败返回false，并抛出异常
int PyArg_VaParse(PyObject *args, const char *format, va_list vargs) | 和PyArg_ParseTuple完全一样除了增加增加了一个参数接收列表

在python官方提供的教程说明里面[官方介绍](https://docs.python.org/3/c-api/arg.html#c.PyArg_ParseTuple)
- `int PyArg_ParseTupleAndKeywords(PyObject *args, PyObject *kw, const char *format, char *keywords[], ...)`  
    Parse the parameters of a function that takes both positional and keyword parameters into local variables. The keywords argument is a NULL-terminated array of keyword parameter names. Empty names denote positional-only parameters. Returns true on success; on failure, it returns false and raises the appropriate exception.

    Changed in version 3.6: Added support for positional-only parameters.

- `int PyArg_VaParseTupleAndKeywords(PyObject *args, PyObject *kw, const char *format, char *keywords[], va_list vargs)`
Identical to PyArg_ParseTupleAndKeywords(), except that it accepts a va_list rather than a variable number of arguments.

- `int PyArg_ValidateKeywordArguments(PyObject *)`
    Ensure that the keys in the keywords argument dictionary are strings. This is only needed if PyArg_ParseTupleAndKeywords() is not used, since the latter already does this check.


### 参数类型
在上面的函数中有一些format参数类型，下面详细说一些。对于这样的类型`#`，例如`s#`,`y#`,等，这些类型是参数的长度（int or Py_ssize_t）是由定义的宏（PY_SSIZE_T_CLEAN）控制的（定义在Python.h?<看了源码，我在Python3.5的头文件里面没有找到PY_SSIZE_T_CLEAN的定义>）。如果定义了PY_SSIZE_T_CLEAN的话，那么长度就应该是Py_ssize_t类型而不是int。Python的官网上说后面会仅支持Py_ssize_t，不支持使用int表示这些类型的长度，并且建议定义PY_SSIZE_T_CLEAN这个宏。

format | Python中的类型 | C中的类型 | 说明
:--:|:--:|:--:|:--:
s   |   str  | const char*  | 把python中Unicode编码的object转换为C中指向字符串的指针。这个
-|-|-|-
b   | int | unsigned char | 把Python中的非负整型转换为一个字节的非负整型, 也就是 C 中的 `unsigned char`
B   | int | unsigned char | 把Python中的整型转换为一个字节的整型，但是没有溢出检查，存放在 C 中的`unsigned char`
h   | int | short int | 把python中的整型转为`short int`
H   | int | unsigned short int  |  without overflow checking.
i   |int |int | Convert a Python integer to a plain C int.
I   | int   | unsigned int | without overflow checking.
l   | int   | long int |Convert a Python integer to a C long int.
k   | int   | unsigned long | without overflow checking.
L   | int   | long long | 
K   | int   | unsigned long long |  without overflow checking.
n   | int   | Py_ssize_t | 把Python中的整型转换为 C中的 Py_ssize_t.
c   | bytes or bytearray of length 1 | char | 把Python byte(represented as a bytes or bytearray object of length 1)转换为 C 中的char [Changed in version 3.3: Allow bytearray objects.]
C | str of length 1 | int | Convert a Python character, represented as a str object of length 1, to a C int.
f |float |float | Convert a Python floating point number to a C float.
d | float | double |Convert a Python floating point number to a C double.
D |complex| |Py_complex | 把Python中的复数(complex number)转换为C 中的Py_complex结构

### 字典获取并读取
这里的获取方式分为两种，一般来说可以是从输入的参数列表中，获取dict这个对象，也可以是从参数中使用`key_list`进行解析。其实获取字典，可以认为是获取PyObject对象。从官网的说明(https://docs.python.org/3/c-api/arg.html#other-objects)中可以了解到基本的获取方式。
1. `O (object) [PyObject *]`
    把一个Python的object（没有转换）存放到一个C指针中。C指针接收到这个对象，但是这个对象的引用计数并不会增加。存放的指针也不会为空。
2. `O! (object) [typeobject, PyObject *]`
    把一个Python的object存放大一个指针中，和`O`类似，但是第一个参数是Python类型对象的地址，第二个参数是用于存放具体的值的C指针，如果Python obejct没有需要的类型，那么就会抛出异常。
3. `O& (object) [converter, anything]`
    通过一个转换函数，转换一个Python对象到一个C变量中。第一个变量是转换用的function，第二个是转换后存放的C指针的值(of arbitrary type)，转换后是`void *`。转换函数按照如下调用：
    ``` cpp
    status = converter(object, address);
    ```
    这里，obejct是指Python的obejct，address是被`void *`类型的参数，被传递给了函数`PyArg_Parse*()`。函数返回值为1表示成功，返回0表示转换失败。如果失败，转换函数应该抛出异常，并保持传入地址的的内容不变，也就是不会修改address中的内容。
    如果转换函数返回`Py_CLEANUP_SUPPORTED`,则当参数解析最终失败时，他可能会再次调用，从而使得转换函数有机会释放已经分配的任何内存。在第二次调用中，obejct这个参数为NULL，address会和原始调用使用相同的值。`Py_CLEANUP_SUPPORTED`是在version 3.1中加入的。


## 返回结果

返回值
format | python中的类型 | C语言类型 | 说明
:---:|:--:|:--:|:--:
s    | str or None | char *         | 把一个带有结束符的字符串转换成python中的str，采用utf-8编码，如果C的字符串指针为空，那么返回None
s#   | str or None  | char* , int   | 

例子：
``` cpp
int str_len;
const char* c_ptr;
if(!PyArg_ParseTuple(args, "s#", &c_ptr, &str_len))
{
    return NULL;
}
```

### 返回一个字典对象

# 参考资料
## python3
> https://docs.python.org/3/extending/extending.html   
>

## python2 
> https://docs.python.org/2/extending/extending.html  
> 
这里先以python2为例，下面是简单的例子：
``` cpp
#include <Python.h>
int greate_function(int a)
{
    return a+1;
}
static PyObject * _great_function(PyObject *self, PyObject *args)
{
    int _a;
    int res;
    if(!PyArg_ParseTuple(args,"i",&_a))
    {
        return NULL;
    }
    res = greate_function(_a);
    return PyLong_FromLong(res);
}

static PyMethodDef GreateModuleMethods[]= {
    {
        "greate_function",
        _great_function,
        METH_VARARGS,
        ""
    },
    {
        NULL,
        NULL,
        0,
        NULL
    }
};
PyMODINIT_FUNC initpyTestLib(void)
{
    (void) Py_InitModule("pyTestLib",GreateModuleMethods);
}
```
这里


# C调Python
如同上面的python能够调用c的函数，c也可以调用python的函数，这里依然是先以python3为例。

## C语言调用Python3函数

这里可以通过参数传递获取由Python传递过来的函数。




