--- 写在前面  

这里问题是之前有个人问我的，当子线程挂掉了以后，如何在主线程中将这个线程重新拉起来。

---

# 多线程pthread
## 常用函数


### 线程清理函数
``` cpp
#include <pthread.h>
void pthread_cleanup_push(void (*rtn)(void *), void *arg);
void pthread_cleanup_pop(int execute);
```
当遇到如下情况时，pthread_cleanup_push函数会调度清理函数rtn，调用时只有一个参数arg：
- 调用pthread_exit时
- 响应取消的时候
- 用非零execute参数调用pthread_cleanup_pop时





