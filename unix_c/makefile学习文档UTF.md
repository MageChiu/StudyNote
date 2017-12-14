##增加头文件搜索目录

```makfile
# 指令编译器和选项  
CC=gcc  
CFLAGS=-Wall -std=gnu99  
  
# 目标文件  
TARGET=test  
SRCS = test.c \  
  ./test-add/test-add.c \  
  ./test-sub/test-sub.c  
  
INC = -I./includefilepath -I./includefilepath  
  
OBJS = $(SRCS:.c=.o)  
  
$(TARGET):$(OBJS)  
#   @echo TARGET:$@  
#   @echo OBJECTS:$^  
[tab]$(CC) -o $@ $^  
  
clean:  
[tab]rm -rf $(TARGET) $(OBJS)  
  
%.o:%.c  
[tab]$(CC) $(CFLAGS) $(INC) -o $@ -c $<

```

具体说明：
1 在gcc中，通过-I前缀来制定头文件的路径，其中"./"表示当前文件夹；"../"表示上一级目录  
这里INC中保存的就是当前需要引用的头文件的位置，头文件的路径之间通过空格隔开  

2 编译规则"%.o:%.c"中加入了头文件参数"$(CC) $(CFLAGS) $(INC) -o $@ -c $<"


## makefile增加宏定义
在gcc中，宏定义使用的前缀-D，在编译过程中，可以把宏定义追加到CFLAGS中，
下面是实例代码：

```makefile
# 指令编译器和选项  
CC=gcc  
CFLAGS=-Wall -std=gnu99  
# 宏定义  
DEFS = -DTEST_ADD -DTEST_SUB=1  
CFLAGS += $(DEFS)  
# 目标文件  
      
TARGET=test  
# 源文件  
SRCS = test.c \  
  ./test-add/test-add.c \  
  ./test-sub/test-sub.c  
# 头文件查找路径  
INC = -I./test-add -I./test-sub  
# 目标文件  
OBJS = $(SRCS:.c=.o)  
# 链接为可执行文件  
$(TARGET):$(OBJS)  
#   @echo TARGET:$@  
#   @echo OBJECTS:$^  
[tab]$(CC) -o $@ $^  
clean:  
[tab]rm -rf $(TARGET) $(OBJS)  
# 连续动作，请清除再编译链接，最后执行  
exec:clean $(TARGET)  
[tab]@echo 开始执行  
[tab]./$(TARGET)  
[tab]@echo 执行结束  
# 编译规则 $@代表目标文件 $< 代表第一个依赖文件  
%.o:%.c  
[tab]$(CC) $(CFLAGS) $(INC) -o $@ -c $<
```
具体说明：
1 在makefile定义头文件的方法有两种  
  1 -D DEFINES  
  2 -D DEFINES=CONDITION
  分别对应宏定义中的#ifdef和#if

2 "CFLAGS += $(DEFS)"将宏定义追加到CFLAG中，此处强调CFLAGS只是一个变量，可以命名为任何合法的名称，只要在编译过程中引用该参数即可


## 增加系统共享库
在gcc 中，增加共享库使用-l前缀（这里注意，必须是小写）。
1 一定情况下，系统默认只搜索库目录位于"/usr/lib"和"lib"
2 若共享库不爱系统默认库中，可以通过-L参数指定目录，该参数只有在链接过程中有效

下面的例子中，是使用了m库
```makefile
# 指令编译器和选项  
CC = gcc  
CFLAGS = -Wall -std=gnu99  
  
# 可执行文件  
TARGET=test  
# C文件  
SRCS = test.c  
# 目标文件  
OBJS = $(SRCS:.c=.o)  
  
# 库文件  
DLIBS = -lm  
  
# 链接为可执行文件  
$(TARGET):$(OBJS)  
#   @echo TARGET:$@  
#   @echo OBJECTS:$^  
[tab]$(CC) -o $@ $^ $(DLIBS)  
  
clean:  
[tab]rm -rf $(TARGET) $(OBJS)  
  
# 连续动作，请清除再编译链接，最后执行  
exec:clean $(TARGET)  
[tab]@echo 开始执行  
[tab]./$(TARGET)  
[tab]@echo 执行结束  
  
# 编译规则 $@代表目标文件 $< 代表第一个依赖文件  
%.o:%.c  
[tab]$(CC) $(CFLAGS) -o $@ -c $< 
```
具体说明：
1 "DLIBS = -lm"增加共享库，这里请注意，实际的库全名为"libm.so"
2 "$(CC) -o $@ $^ $(DLIBS)"编译时增加共享库。这里注意，共享库增加在链接过程即可，不需要再编译过程中添加
3 由于libm.so为系统库，所以并不需要指定路径。


## 增加自定义共享库

下面是makefile的示例代码：
```makefile
# 指令编译器和选项  
CC = gcc  
CFLAGS = -Wall -std=gnu99  
  
# 目标文件  
TARGET = libtest.so  
# C文件  
SRCS = test-add.c test-sub.c  
# 目标文件  
OBJS = $(SRCS:.c=.o)  
  
# 链接为可执行文件  
$(TARGET):$(OBJS)  
[tab]$(CC) -shared -o $@ $^  
[tab]mv $(TARGET) ../lib  
  
clean:  
[tab]rm -rf $(TARGET) $(OBJS)  
  
# 编译规则 $@代表目标文件 $< 代表第一个依赖文件  
%.o:%.c  
[tab]$(CC) $(CFLAGS) -o $@ -fPIC -c $<  
```
具体说明：
1 DLIBS = -ltest 指定共享库，请注意共享库的名称为libtest.so，而-l参数只取test部分，去掉前缀lib和后缀.so。
2 LDFLAGS = -L./lib 指定共享库路径，请注意上一步中已经把共享库复制到lib目录中。
3 INC = -I./lib  指定libtest.h目录，也可把libtest.h复制到test.c所在的目录。
4 $(CC) -o $@ $^ $(LDFLAGS) $(DLIBS) 链接过程指定共享库查找路径，指定共享库名称。
5 第【1】和第【2】点只在链接过程有效，在执行过程中需要通过-Wl,-rpath=<path>指定共享库路径。
