记录一下在开发过程中使用的一些命令

___
<!-- TOC -->

- [强大的手册man](#强大的手册man)
- [查看一个进程中有多少个线程](#查看一个进程中有多少个线程)
    - [pstree](#pstree)
    - [通过进程的属性](#通过进程的属性)
- [用curl名利测试http](#用curl名利测试http)
- [清理共享内存](#清理共享内存)
- [查看网络IO](#查看网络io)
- [查看网络设备](#查看网络设备)
- [awk](#awk)
- [查看消息队列](#查看消息队列)
- [shell中的循环](#shell中的循环)
    - [`for`循环](#for循环)
    - [`while`循环](#while循环)

<!-- /TOC -->

___


# 强大的手册man
man是个很强大的手册工具，man的用法可以直接用man看一下
``` shell
SYNOPSIS
       man  [-c|-w|-tZ] [-H[browser]] [-T[device]] [-X[dpi]] [-adhu7V] [-i|-I] [-m system[,...]]
       [-L locale] [-p string] [-C file] [-M path] [-P pager] [-r prompt] [-S list]  [-e  exten-
       sion] [--warnings [warnings]] [[section] page ...] ...
       man -l [-7] [-tZ] [-H[browser]] [-T[device]] [-X[dpi]] [-p string] [-P pager] [-r prompt]
       [--warnings[warnings]] file ...
       man -k [apropos options] regexp ...
       man -f [whatis options] page ...

DESCRIPTION
       man is the system's manual pager. Each page argument given to man is normally the name of
       a  program, utility or function.  The manual page associated with each of these arguments
       is then found and displayed. A section, if provided, will direct man to look only in that
       section of the manual.  The default action is to search in all of the available sections,
       following a pre-defined order and to show only the first page found, even if page  exists
       in several sections.

       The  table  below  shows the section numbers of the manual followed by the types of pages
       they contain.


       0   Header files (usually found in /usr/include)
       1   Executable programs or shell commands
       2   System calls (functions provided by the kernel)
       3   Library calls (functions within program libraries)
       4   Special files (usually found in /dev)
       5   File formats and conventions eg /etc/passwd
       6   Games
       7   Miscellaneous (including macro  packages  and  conven-
           tions), e.g. man(7), groff(7)
       8   System administration commands (usually only for root)
       9   Kernel routines [Non standard]
EXAMPLES
       man ls
           Display the manual page for the item (program) ls.

       man -a intro
           Display, in succession, all of the available intro manual pages contained within  the
           manual.  It is possible to quit between successive displays or skip any of them.

       man -t alias | lpr -Pps
           Format  the  manual page referenced by `alias', usually a shell manual page, into the
           default troff or groff format and pipe it to the printer named ps.  The default  out-
           put  for groff is usually PostScript.  man --help should advise as to which processor
           is bound to the -t option.

       man -l -Tdvi ./foo.1x.gz > ./foo.1x.dvi
           This command will decompress and format the nroff source manual page ./foo.1x.gz into
           a  device independent (dvi) file.  The redirection is necessary as the -T flag causes
           output to be directed to stdout with no pager.  The output could  be  viewed  with  a
           program  such  as  xdvi  or further processed into PostScript using a program such as
           dvips.

       man -k printf
           Search the short descriptions and manual page names for the keyword printf as regular
           expression.  Print out any matches.  Equivalent to apropos -r printf.

       man -f smail
           Lookup  the  manual pages referenced by smail and print out the short descriptions of
           any found.  Equivalent to whatis -r smail.
```
主要的参数
- `-c`：显式使用cat命令的手册信息
- `-t`：使用troff命令格式化手册信息
- `-k`：
- `-f`
- `-F`
- `-m`
- `-MPath`
- `-r`
- `a`

man后面的数字的含义：
- `1`：可执行命令或者shell命令
- `2`：系统调用
- `3`：C语言库函数
- `4`：设备或者特殊文件
- `5`：文件格式和规则
- `6`：游戏
- `7`：杂项
- `8`：系统管理员相关的命令
- `9`：跟Kernel有关的文件




# 查看一个进程中有多少个线程

## pstree
``` shell
pstree -p `ps -e | grep svrName | awk '{print $1}' `
pstree -p `ps -e | grep svrName | awk '{print $1}' ` | wc -l

```

## 通过进程的属性
``` shell
cat /porc/`ps -e | grep svrName | awk '{print $1}' `/status
```
从其中的`Threads`属性中可以获取进程的数目，但是该进程数目会有创建这些线程的主线程的数目



# 用curl名利测试http



# 清理共享内存



# 查看网络IO




# 查看网络设备


# awk


# 查看消息队列
这里主要使用的命令是`ipcs`，


# shell中的循环
## `for`循环


## `while`循环


