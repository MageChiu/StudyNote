这里主要是学习如何使用C和lua的编程

____

<!-- TOC -->

- [lua与C之间的交互](#lua与c之间的交互)
    - [虚拟栈](#虚拟栈)
    - [元素的入栈和出栈](#元素的入栈和出栈)
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



