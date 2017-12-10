<!-- TOC -->

- [Python 与C 的相互调用](#python-与c-的相互调用)
- [C调Python](#c调python)
- [Python调C](#python调c)
    - [获取参数](#获取参数)
        - [API Function](#api-function)
- [参考资料](#参考资料)
    - [python3](#python3)
    - [python2](#python2)

<!-- /TOC -->
# Python 与C 的相互调用

# C调Python


# Python调C
这里主要是参考python3的做法，python2的做法类似，只是相关的函数可能有所差别
## 获取参数
### API Function

function | usage
:---: | :---:
int PyArg_ParseTuple(PyObject *args, const char *format, ...)| 分析函数的传入参数，成功返回true，失败返回false，并抛出异常
int PyArg_VaParse(PyObject *args, const char *format, va_list vargs)|




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


