# 信号处理机制



信号 |  SIG_NO    |功能
:---:|:--:|:---:
SIGHUP       |  1 |
SIGINT       |  2 | 程序终止(interrupt)信号, 在用户键入INTR字符(通常是Ctrl-C)时发出，用于通知前台进程组终止进程。
SIGQUIT      |  3 | 和SIGINT类似, 但由QUIT字符(通常是Ctrl-/)来控制. 进程在因收到IGQUIT退出时会产生core文件, 在这个意义上类似于一个程序错误信号。
SIGILL       |  4   |
SIGTRAP      |  5   |
SIGABRT      |  6   |
SIGBUS       |  7   |
SIGFPE       |  8   |
SIGKILL      |  9   |  用来立即结束程序的运行. 本信号不能被阻塞、处理和忽略。如果管理员发现某个进程终止不了，可尝试发送这个信号。
SIGUSR1      |  10   |  留给用户使用
SIGSEGV      |  11   |
SIGUSR2      |  12   |
SIGPIPE      |  13   |
SIGALRM      |  14   |  时钟定时信号, 计算的是实际的时间或时钟时间. alarm函数使用该信号
SIGTERM      |  15   |  程序结束(terminate)信号, 与SIGKILL不同的是该信号可以被阻塞和处理。通常用来要求程序自己正常退出，shell命令kill缺省产生这个信号。如果进程终止不了，我们才会尝试SIGKILL。
SIGSTKFLT    |  16   | 
SIGCHLD      |  17   |
SIGCONT      |  18   |
SIGSTOP      |  19   |
SIGTSTP      |  20   |
SIGTTIN      |  21   |
SIGTTOU      |  22   |
SIGURG       |  23   |
SIGXCPU      |  24   |
SIGXFSZ      |  25   |
SIGVTALRM    |  26   |
SIGPROF      |  27   |
SIGWINCH     |  28   | 窗口大小改变时发出.
SIGIO        |  29   |
SIGPWR       |     |
SIGSYS       |     |
SIGRTMIN     |     |
SIGRTMIN+1   |     |
SIGRTMIN+2   |     |
SIGRTMIN+3   |     |
SIGRTMIN+4   |     |
SIGRTMIN+5   |     |
SIGRTMIN+6   |     |
SIGRTMIN+7   |     |
SIGRTMIN+8   |     |
SIGRTMIN+9   |     |
SIGRTMIN+10  |     |
SIGRTMIN+11  |     |
SIGRTMIN+12  |     |
SIGRTMIN+13  |     |
SIGRTMIN+14  |     |
SIGRTMIN+15  |     |
SIGRTMAX-14  |     |
SIGRTMAX-13  |     |
SIGRTMAX-12  |     |
SIGRTMAX-11  |     |
SIGRTMAX-10  |     |
SIGRTMAX-9   |     |
SIGRTMAX-8   |     |
SIGRTMAX-7   |     |
SIGRTMAX-6   |     |
SIGRTMAX-5   |     |
SIGRTMAX-4   |     |
SIGRTMAX-3   |     |
SIGRTMAX-2   |     |
SIGRTMAX-1   |     |
SIGRTMAX     |     |