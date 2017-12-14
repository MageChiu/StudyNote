IPC是进程间通信的简称，这里是阅读《Unix网络编程 卷2 进程间通信》的读书笔记



______
______


# 简介

IPC对象的持续性
IPC类型|持续性|用于打开或者创建IPC的名字空间|IPC打开后的标识|Posix.1 1996| Unix 98
|:---:|:---:|:--:|:--:|:--:|:--:
|管道|随进程| 没有名字 | 描述符| · | ·
|FIFO|随进程|路径名| 描述符| · | ·
|
|Posix互斥锁|随进程|
|POSIX条件变量|随进程|
| Posix读写锁|随进程|
|fcntl记录上锁|随进程|
|
|Posix消息队列|随内核|
|Posix有名信号量|随内核|
|Posix基于内存的信号量|随进程|
|Posix共享内存区|随内核|
|
|System V消息队列|随内核|
|System V信号量|随内核|
|System V共享内存区| 随内核|
|
|TCP套接字|随进程|
|UDP套接字|随进程|
|Unix域套接字|随进程|



## Posix IPC简介

`Posix IPC`函数总汇
|      |  头文件  |  创建、打开或删除IPC的函数  |  控制IPC操作的函数  | IPC操作函数 |
|:----:|:-------:|:-------:|:----:|:------:|
|消息队列|<mqueue.h> | mq_open\mq_close\mq_unlink | mq_getattr\mq_setattr | mq_send\mq_receive\mq_notify|
|信号量|<semaphore.h> |sem_open\sem_close\sem_unlink  sem_init\sem_destroy |/ | sem_wait\sem_trywait\sem_post\sem_getvalue|
|共享内存|<sys/mman.h> | shm_open/shm_unlink | ftruncate/fstat | mmap/munmap |

Posix IPC名字必须符合已有的路径命名规则（必须最多由PATH_MAX个字节构成，包括结尾的空字节）


mq_open、sem_open、shm_open是创建或者打开一个IPC对象的函数。通过man手册可以查到：
- `man mq_open`
``` cpp
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>

mqd_t mq_open(const char *name, int oflag);
mqd_t mq_open(const char *name, int oflag, mode_t mode,
                struct mq_attr *attr);
Link with -lrt.
```
- `man sem_open`
``` cpp
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

sem_t *sem_open(const char *name, int oflag);
sem_t *sem_open(const char *name, int oflag,
                mode_t mode, unsigned int value);
Link with -pthread.
```
- `man shm_open`
``` cpp
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

int shm_open(const char *name, int oflag, mode_t mode);

int shm_unlink(const char *name);
Link with -lrt.
```
下面是三个函数oflag的取值：
说明 | 只读 | 只写 | 读写 | 若不存在则创建 | 排他性创建 | 非阻塞模式 | 若已存在则截短
:---:| :---:| :-: | :-: | :------------: | :-------:| :------: | :------:
mq_open | O_RDONLY | O_WRONLY | O_RDWR | O_CREAT | O_EXCL |    O_NONBLOCK| --
sem_open | ---     | ----     |  ---    | O_CREAT | O_EXCL |     |    
shm_open | O_RDONLY | --- |  O_RDWR | O_CREAT | O_EXCL|         | O_TRUNC
除了需要指定oflag的值以外，还需要指定mode的值，该值定义在`sys/stat.h`中：
常值 | 说明
:-----: | :-----:
S_IRUSR | 用户（属主）读
S_IWUSR | 用户（属主）写
S_IRGRP | （属）组成员读
S_IWGRP | （属）组成员写
S_IROTH | 其他用户读
S_IWOTH | 其他用户写

其中：   
- O_CREAT：如果不存在，则创建有函数第一个参数所指定的消息队列、信号量或者共享内存

mode所指定的权限位受当前进程的文件模式创建掩码（file mode creation mask）修正，而该掩码可以通过调用umask函数或者使用shell的umask命来来设置



# 信号量
