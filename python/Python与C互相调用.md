<!-- TOC -->

- [Python 与C 的相互调用](#python-与c-的相互调用)
- [Python调C](#python调c)
    - [获取参数](#获取参数)
        - [API Function](#api-function)
- [参考资料](#参考资料)
    - [python3](#python3)
    - [python2](#python2)
- [C调Python](#c调python)
    - [C语言调用Python3函数](#c语言调用python3函数)

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

这里
