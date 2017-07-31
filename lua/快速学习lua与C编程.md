这里主要是学习如何使用C和lua的编程

____

<!-- TOC -->

- [lua与C之间的交互](#lua与c之间的交互)
    - [虚拟栈](#虚拟栈)
    - [元素的入栈和出栈](#元素的入栈和出栈)
    - [虚拟栈内元素的管理](#虚拟栈内元素的管理)
- [编写提供给Lua使用的C库函数](#编写提供给lua使用的c库函数)
    - [第一个例子](#第一个例子)

<!-- /TOC -->
____


# lua与C之间的交互

## 虚拟栈

C与lua通信的关键内容在于一个虚拟的栈。几乎所有的调用都是对栈上的值进行操作，所有C与lua之间的数据交换也都是通过这个栈完成的。另外，也可以通过栈来保存临时变量。

栈的使用解决了C和lua之间的两个不协调的问题：第一，Lua会自动回收垃圾，而C要求显式地分配存储单元，二者


- 正索引：正索引的顺序为元素入栈的顺序，栈中的第一个元素索引为1
- 负索引：负索引以栈顶为参照来存取元素，栈顶为-1，依次类推



简单的例子：
``` cpp
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
int main(int argc, char const *argv[])
{	
	char buff[256]={0};
	int 	error = 0;
	lua_State	*L = luaL_newstate();
	luaL_openlibs(L);

	while(fgets(buff, sizeof(buff), stdin) != NULL )
	{
		error = luaL_loadbuffer(L, buff, strlen(buff), "line") || lua_pcall(L, 0, 0, 0);
		if(error)
		{
			fprintf(stderr, "%s", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
	}
	lua_close(L);
	return 0;
}
```


## 元素的入栈和出栈
Lua中的数据类型和C中的数据类型不一一对应，对于不同的数据类型，需要不同的入栈函数
Lua中用于入栈的函数
``` cpp
// 将"b"作为一个布尔值入栈。
void lua_pushboolean(lua_State *L, int b)

/* 将C函数"fn"以及其在虚拟栈上关联的"n"个值作为"Closure"入栈。
 * "n"最大为255，第一个被关联的值首先入栈，栈顶是最后一个被关联的值，
 * 这些值会在函数调用成功后被出栈。
 */
void lua_pushcclosure(lua_State *L, lua_CFunction fn, int n)

// 将C函数"f"作为函数入栈。内部实际调用"lua_pushcclosure(L, f, 0)"。
void lua_pushcfunction(lua_State *L, lua_CFunction f)

/* 将一个被格式化后的字符串入栈。函数返回这个字符串的指针。
 * 与C语言中的"sprintf()"类似，其区别在于：
 * 1、不需要为结果分配空间。
 *    其结果是一个Lua字符串，由Lua来关心其内存分配（同时通过垃圾收集来释放内存）。
 * 2、"fmt"不支持符号、宽度、精度。只支持：
 *    "%%": 字符'%'。
 *    "%s": 带零终止符的字符串，没有长度限制。
 *    "%f": "lua_Number"（Lua中的浮点数类型）。
 *    "%L": "lua_Integer"（Lua中的整数类型）。
 *    "%p": 指针或是一个十六进制数。
 *    "%d": "int"。
 *    "%c": "char"。
 *    "%U": 用"long int"表示的UTF-8字。
 */
const char *lua_pushfstring(lua_State *L, const char *fmt, ...)

/* 将长度为"len"，非字面形式的字符串"s"入栈。
 * Lua对这个字符串做一个内部副本（或是复用一个副本），
 * 因此"s"处的内存在函数返回后，可以释放掉或是立刻重用于其它用途。
 * 字符串内可以是任意二进制数据，包括'\0'。函数返回内部副本的指针。
 */
const char *lua_pushlstring(lua_State *L, const char *s, size_t len)

// 将字面形式的字符串"s"入栈，函数自动给出字符串的长度。返回内部副本的指针。
const char *lua_pushliteral(lua_State *L, const char *s)

/* 将以'\0'结尾的字符串"s"入栈。
 * Lua对这个字符串做一个内部副本（或是复用一个副本），
 * 因此"s"处的内存在函数返回后，可以释放掉或是立刻重用于其它用途。
 * 函数返回内部副本的指针。如果"s"为"NULL"，将"nil"入栈并返回"NULL"。
 */
const char *lua_pushstring(lua_State *L, const char *s)

// 等价于"lua_pushfstring()"。不过是用"va_list"接收参数，而不是用可变数量的实际参数。
const char *lua_pushvfstring(lua_State *L, const char *fmt, va_list argp)

// 将全局环境入栈。
void lua_pushglobaltable(lua_State *L)

// 将值为"n"的整数入栈。
void lua_pushinteger(lua_State *L, lua_Integer n)

/* 将一个轻量用户数据"p"入栈。
 * 用户数据是保留在Lua中的C值。轻量用户数据表示一个指针"void*"。
 * 它像一个数值，你不需要专门创建它，它也没有独立的元表，
 * 而且也不会被收集（因为从来不需要创建）。只要表示的C地址相同，两个轻量用户数据就相等。
 */
void lua_pushlightuserdata(lua_State *L, void *p)

// 将空值入栈。
void lua_pushnil(lua_State *L)

// 将一个值为"n"的浮点数入栈。
void lua_pushnumber(lua_State *L, lua_Number n)

// "L"表示的线程入栈。如果这个线程是当前状态机的主线程的话，返回1。
int lua_pushthread(lua_State *L)

// 将虚拟栈上索引"index"处的元素的副本入栈。
void lua_pushvalue(lua_State *L, int index)
```

用于出栈的函数很简单：
``` cpp
// 从虚拟栈中弹出"n"个元素。
void lua_pop(lua_State *L, int n)
```


## 虚拟栈内元素的管理
检查虚拟栈中的元素的类型
``` cpp
// 如果栈中索引"index"处的元素为"bool"类型，则返回1，否则返回0。
int lua_isboolean(lua_State *L, int index)

// 如果栈中索引"index"处的元素是一个C函数，则返回1，否则返回0。
int lua_iscfunction(lua_State *L, int index)

// 如果栈中索引"index"处的元素是一个C函数或是一个Lua函数，则返回1，否则返回0。
int lua_isfunction(lua_State *L, int index)

// 如果栈中索引"index"处的元素是一个整数，则返回1，否则返回0。
int lua_isinteger(lua_State *L, int index)

// 如果栈中索引"index"处的元素是一个轻量级的"userdata"，则返回1，否则返回0。
int lua_islightuserdata(lua_State *L, int index)

// 如果栈中索引"index"处的元素是一个"nil"，则返回1，否则返回0。
int lua_isnil(lua_State *L, int index

// 如果"index"是一个无效索引时，返回1，否则返回0。
int lua_isnone(lua_State *L, int index)

// 如果"index"是一个无效索引或者"index"处的元素是一个"nil"，则返回1，否则返回0。
int lua_isnoneornil(lua_State *L, int index)

/* 如果栈中索引"index"处的元素是一个数值或者是一个可以转换为数值的字符串，
 * 则返回1，否则返回0。
 */
int lua_isnumber(lua_State *L, int index)

/* 如果栈中索引"index"处的元素是一个字符串或者是一个可以转换为字符串的数值，
 * 则返回1，否则返回0。
 */
int lua_isstring(lua_State *L, int index)

// 如果栈中索引"index"处的元素是一个"table"，则返回1，否则返回0。
int lua_istable(lua_State *L, int index)

// 如果栈中索引"index"处的元素是一个线程，则返回1，否则返回0。
int lua_isthread(lua_State *L, int index)

// 如果栈中索引"index"处的元素是一个"userdata"，则返回1，否则返回0。
int lua_isuserdata (lua_State *L, int index)

// 如果栈中的"coroutine"可以被挂起，则返回1，否则返回0。
int lua_isyieldable(lua_State *L)

/* 返回栈中索引"index"处元素的类型。这些类型在"lua.h"中定义，如下：
 * #define LUA_TNONE       (-1)    // 无效
 * #define LUA_TNIL        0    // "nil"
 * #define LUA_TBOOLEAN        1    // "bool"
 * #define LUA_TLIGHTUSERDATA  2    // 轻量级"userdata"
 * #define LUA_TNUMBER     3    // 数值
 * #define LUA_TSTRING     4    // 字符串
 * #define LUA_TTABLE      5    // "table"
 * #define LUA_TFUNCTION       6    // 函数
 * #define LUA_TUSERDATA       7    // "userdata"
 * #define LUA_TTHREAD     8    // 线程
 */
int lua_type(lua_State *L, int index)

// 返回"tp"表示的类型的名字。"tp"是"lua_type()"的返回值之一。
const char *lua_typename(lua_State *L, int tp)
```

如何转换虚拟站中的元素类型：
``` cpp
// 将栈中"index"处的元素转换为C中的"bool"值返回。
int lua_toboolean(lua_State *L, int index)

// 将栈中"index"处的元素转换为一个C函数返回。指定的元素必须是一个C函数，否则返回"NULL"。
lua_CFunction lua_tocfunction(lua_State *L, int index)

/* 将栈中"index"处的元素转换为一个整数返回。
 * 指定的元素必须是一个整数或是一个可以被转换为整数的数字或字符串，否则返回0。
 * 如果"isnum"非"NULL"，"*isnum"会被赋值为操作是否成功的"bool"值。
 */
lua_Integer lua_tointegerx(lua_State *L, int index, int *isnum)

// 内部调用"lua_tointegerx(L, index, NULL)"。
lua_Integer lua_tointeger(lua_State *L, int index)

/* 将栈中"index"处的元素转换为一个C字符串并将其指针返回。
 * 如果"len"非"NULL"，"*len"将获得字符串的长度。
 * 指定元素必须是一个字符串或是一个数字，否则返回返回"NULL"。
 * 如果指定元素是一个数字，函数会将元素的类型转换为字符串。
 * 返回的字符串结尾包含'\0'，而在字符串中允许包含多个'\0'。
 * 函数返回的字符串应立即转存，否则有可能被Lua垃圾回收器回收。
 */
const char *lua_tolstring(lua_State *L, int index, size_t *len)

/* 将栈中"index"处的元素转换为一个浮点数返回。
 * 指定的元素必须是一个数字或是一个可被转换为数字的字符串，否则返回0。
 * 如果"isnum"非"NULL"，"*isnum"会被赋值为操作是否成功的"bool"值。
 */
lua_Number lua_tonumberx(lua_State *L, int index, int *isnum)

// 内部调用"lua_tonumberx(L, index, NULL)"。
lua_Number lua_tonumber(lua_State *L, int index)

/* 将栈中"index"处的元素转换为一个C指针返回。
 * 指定的元素必须是一个"userdata"，"table"，线程或是一个函数，否则返回"NULL"。
 */
const void *lua_topointer(lua_State *L, int index)

// 内部调用"lua_tolstring(L, index, NULL)"。
const char *lua_tostring(lua_State *L, int index)

/* 将栈中"index"处的元素转换为一个Lua线程返回。
 * 指定的元素必须是一个线程，否则返回"NULL"。
 */
lua_State *lua_tothread(lua_State *L, int index)

/* 栈中"index"处的元素如果是一个完全"userdata"，则返回其内存地址的指针；
 * 如果是一个轻量级"userdata"，则返回其存储的指针。
 */
void *lua_touserdata(lua_State *L, int index)
```

维护虚拟栈的方法
``` cpp
/* int lua_gettop(lua_State *L)
 * 返回栈顶元素的索引。
 * 因为栈中元素的索引是从1开始编号的，所以函数的返回值相当于栈中元素的个数。
 * 返回值为0表示栈为空。
 */
lua_gettop(L);    // 返回栈中元素的个数。

/* void lua_settop(lua_State *L, int index)
 * 设置栈顶为索引"index"指向处。
 * 如果"index"比"lua_gettop()"的值大，那么多出的新元素将被赋值为"nil"。
 */
lua_settop(L, 0);    // 清空栈。

/* void lua_remove(lua_State *L, int index)
 * 移除栈中索引"index"处的元素，该元素之上的所有元素下移。
 */

/* void lua_insert(lua_State *L, int index)
 * 将栈顶元素移动到索引"index"处，索引"index"（含）之上的所有元素上移。
 */

/* void lua_replace(lua_State *L, int index)
 * 将栈顶元素移动到索引"index"处。（相当于覆盖了索引"index"处的元素）
 */
```

一个简答的例子

如果在C++中使用lua，就需要增加：
``` cpp
extern "C" {
    #include <lua.h>
}
```


# 编写提供给Lua使用的C库函数



## 第一个例子

``` cpp
#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
int l_map(lua_State *L)
{
    int i = 0 , n =0;
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TFUNCTION);

    n = lua_rawlen(L, 1);
    for(i = 1; i <= n; ++i)
    {
        lua_pushvalue(L, 2);
        lua_rawgeti(L, 1, i);
        lua_call(L, 1, 1);

        lua_rawseti(L, 1, i);
    }
    return 0;
}
static const struct luaL_Reg mylib[] = {
    {"mymap", l_map },
    {NULL, NULL}
};

extern int luaopen_mylib(lua_State* L)
{
    luaL_newlib(L, mylib);

    return 1;
}
```
下面是Lua的代码
``` lua
local mylib = require "mylib"
local t = {1, 3, 5}
local f = function(n)
    return n*n
end

mylib.mymap(t,f)
for k,v in pairs(t) do
    print(k, v)
end
```



