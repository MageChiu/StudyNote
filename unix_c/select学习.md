在使用libcurl中的multi模型的时候用到了select，所以决定好好学习一下

-------

# select
通过man可以获得select的基本知识
``` cpp
#include <sys/select.h>
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int select(int nfds, fd_set *readfds, fd_set *writefds,
            fd_set *exceptfds, struct timeval *timeout);

void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);

#include <sys/select.h>

int pselect(int nfds, fd_set *readfds, fd_set *writefds,
            fd_set *exceptfds, const struct timespec *timeout,
            const sigset_t *sigmask);

```
> [其中pselect和select的区别应该与pepoll和epoll的区别类似]

- 参数的介绍：
    - `int nfds`:只集合内所有文件描述符的范围，几所有文件描述符的最大值加1，在Windows中这个参数没有意义
    - `fd_set *readfds`
    - `fd_set *writefds`
    - `fd_set *exceptfds`：用来监视文件错误异常
    - `struct timeval *timeout`：超时时间
- 返回值：
    - `-1`:失败返回-1
    - `0`：超时返回0
    - 正值：表示可读写或者错误的文件







