IPC是进程间通信的简称



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








