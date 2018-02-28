
<!-- TOC -->

- [epoll例子](#epoll%E4%BE%8B%E5%AD%90)
    - [这里主要写一写函数的使用](#%E8%BF%99%E9%87%8C%E4%B8%BB%E8%A6%81%E5%86%99%E4%B8%80%E5%86%99%E5%87%BD%E6%95%B0%E7%9A%84%E4%BD%BF%E7%94%A8)
- [在面试中被问道问题](#%E5%9C%A8%E9%9D%A2%E8%AF%95%E4%B8%AD%E8%A2%AB%E9%97%AE%E9%81%93%E9%97%AE%E9%A2%98)
    - [epoll两种方式的区别](#epoll%E4%B8%A4%E7%A7%8D%E6%96%B9%E5%BC%8F%E7%9A%84%E5%8C%BA%E5%88%AB)
    - [如何确定对端客户端已经关闭链接](#%E5%A6%82%E4%BD%95%E7%A1%AE%E5%AE%9A%E5%AF%B9%E7%AB%AF%E5%AE%A2%E6%88%B7%E7%AB%AF%E5%B7%B2%E7%BB%8F%E5%85%B3%E9%97%AD%E9%93%BE%E6%8E%A5)

<!-- /TOC -->

# epoll例子
下午研究了一下epoll，参考了以下的博客综合写了一个例子。

http://blog.csdn.net/ljx0305/article/details/4065058

这篇文章中有一些和我从man上面查到的不相符合的地方，特此指出。

1)关于epoll_create

这个函数的size参数已经器用。更推荐使用的是epoll_create1(0)来代替普通的用法。另外epoll_create1(EPOLLCLOEXEC)表示生成的epoll fd具有“执行后关闭”特性。

2) epoll_ctl

这个函数在指定EPOLL_CTL_DEL时，为了与linux内核2.6.9之前相兼容，还是要让最后的参数指向一个非null变量。

另外，events.EPOLLONESHOT确实表示只监听一次事件，但是当我们监听完这次事件之后，如果还需要继续监听这个fd的话，只需要使用EPOLL_CTL_MOD修改event。

 

3) 关于实例代码

实例代码我运行了一下，感觉有点问题。后来参考了这篇文章（http://blog.chinaunix.net/uid-20583479-id-1920065.html）的说法，发现修改之后就可以实行了。关键点有这么几点，

1. EPOLLET其实比EPOLLLT高级，所以优先用。

2. 用EPOLLET的时候，按照man的讲法，是必须要使用非阻塞fd，另外，必须要考虑EAGAIN。

服务器代码：
``` cpp
#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

using namespace std;

#define MAXLINE 5
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 5000
#define INFTIM 1000

void setnonblocking(int sock)
{
    int opts;
    opts=fcntl(sock,F_GETFL);
    if(opts<0)
    {
        perror("fcntl(sock,GETFL)");
        return;
    }
    opts = opts|O_NONBLOCK;
    if(fcntl(sock,F_SETFL,opts)<0)
    {
        perror("fcntl(sock,SETFL,opts)");
        return;
    }
}

void CloseAndDisable(int sockid, epoll_event ee)
{
    close(sockid);
    ee.data.fd = -1;
}

int main()
{
    int i, maxi, listenfd, connfd, sockfd,epfd,nfds, portnumber;
    char line[MAXLINE];
    socklen_t clilen;

    portnumber = 5000;

    //声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件

    struct epoll_event ev,events[20];
    //生成用于处理accept的epoll专用的文件描述符

    epfd=epoll_create(256);
    struct sockaddr_in clientaddr;
    struct sockaddr_in serveraddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port=htons(portnumber);

    // bind and listen
    bind(listenfd,(sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(listenfd, LISTENQ);

    //设置与要处理的事件相关的文件描述符
    ev.data.fd=listenfd;
    //设置要处理的事件类型
    ev.events=EPOLLIN|EPOLLET;
    //ev.events=EPOLLIN;

    //注册epoll事件
    epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);

    maxi = 0;

    int bOut = 0;
    for ( ; ; )
    {
        if (bOut == 1)
            break;
        //等待epoll事件的发生

        nfds=epoll_wait(epfd,events,20,-1);
        //处理所发生的所有事件
        cout << "\nepoll_wait returns\n";

        for(i=0;i<nfds;++i)
        {
            if(events[i].data.fd==listenfd)//如果新监测到一个SOCKET用户连接到了绑定的SOCKET端口，建立新的连接。
            {
                connfd = accept(listenfd,(sockaddr *)&clientaddr, &clilen);
                if(connfd<0){
                    perror("connfd<0");
                    return (1);
                }
                

                char *str = inet_ntoa(clientaddr.sin_addr);
                cout << "accapt a connection from " << str << endl;
                //设置用于读操作的文件描述符

                setnonblocking(connfd);
                ev.data.fd=connfd;
                //设置用于注测的读操作事件

                ev.events=EPOLLIN | EPOLLET;
                //ev.events=EPOLLIN;

                //注册ev
                epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
            }
            else if(events[i].events & EPOLLIN)//如果是已经连接的用户，并且收到数据，那么进行读入。
            {
                cout << "EPOLLIN" << endl;
                if ( (sockfd = events[i].data.fd) < 0)
                    continue;

                char * head = line;
                int recvNum = 0;
                int count = 0;
                bool bReadOk = false;
                while(1)
                {
                    // 确保sockfd是nonblocking的
                    recvNum = recv(sockfd, head + count, MAXLINE, 0);
                    if(recvNum < 0)
                    {
                        if(errno == EAGAIN)
                        {
                            // 由于是非阻塞的模式,所以当errno为EAGAIN时,表示当前缓冲区已无数据可读
                            // 在这里就当作是该次事件已处理处.
                            bReadOk = true;
                            break;
                        }
                        else if (errno == ECONNRESET)
                        {
                                // 对方发送了RST
                                CloseAndDisable(sockfd, events[i]);
                                cout << "counterpart send out RST\n";
                                break;
                         }
                        else if (errno == EINTR)
                        {
                            // 被信号中断
                            continue;
                        }
                        else
                        {
                            //其他不可弥补的错误
                            CloseAndDisable(sockfd, events[i]);
                            cout << "unrecovable error\n";
                            break;
                        }
                   }
                   else if( recvNum == 0)
                   {
                        // 这里表示对端的socket已正常关闭.发送过FIN了。
                        CloseAndDisable(sockfd, events[i]);
                        cout << "counterpart has shut off\n";
                        break;
                   }

                   // recvNum > 0
                    count += recvNum;
                   if ( recvNum == MAXLINE)
                   {
                       continue;   // 需要再次读取
                   }
                   else // 0 < recvNum < MAXLINE
                   {
                       // 安全读完
                       bReadOk = true;
                       break; // 退出while(1),表示已经全部读完数据
                   }
                }

                if (bReadOk == true)
                {
                    // 安全读完了数据
                    line[count] = '\0';

                    cout << "we have read from the client : " << line;
                    //设置用于写操作的文件描述符

                    ev.data.fd=sockfd;
                    //设置用于注测的写操作事件

                    ev.events = EPOLLOUT | EPOLLET;
                    //修改sockfd上要处理的事件为EPOLLOUT

                    epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
                }
            }
            else if(events[i].events & EPOLLOUT) // 如果有数据发送
            {
                const char str[] = "hello from epoll : this is a long string which may be cut by the net\n";
                memcpy(line, str, sizeof(str));
                cout << "Write " << line << endl;
                sockfd = events[i].data.fd;

                bool bWritten = false;
                int writenLen = 0;
                int count = 0;
                char * head = line;
                while(1)
                {
                        // 确保sockfd是非阻塞的
                        writenLen = send(sockfd, head + count, MAXLINE, 0);
                        if (writenLen == -1)
                        {
                            if (errno == EAGAIN)
                            {
                                // 对于nonblocking 的socket而言，这里说明了已经全部发送成功了
                                bWritten = true;
                                break;
                            }
                            else if(errno == ECONNRESET)
                            {
                                // 对端重置,对方发送了RST
                                CloseAndDisable(sockfd, events[i]);
                                cout << "counterpart send out RST\n";
                                break;
                            }
                            else if (errno == EINTR)
                            {
                                // 被信号中断
                                continue;
                            }
                            else
                            {
                                // 其他错误
                            }
                        }

                        if (writenLen == 0)
                        {
                            // 这里表示对端的socket已正常关闭.
                            CloseAndDisable(sockfd, events[i]);
                            cout << "counterpart has shut off\n";
                            break;
                        }

                        // 以下的情况是writenLen > 0
                        count += writenLen;
                        if (writenLen == MAXLINE)
                        {
                            // 可能还没有写完
                            continue;
                        }
                        else // 0 < writenLen < MAXLINE
                        {
                            // 已经写完了
                            bWritten = true;
                            break; // 退出while(1)
                        }
                }

                if (bWritten == true)
                {
                    //设置用于读操作的文件描述符
                    ev.data.fd=sockfd;

                    //设置用于注测的读操作事件
                    ev.events=EPOLLIN | EPOLLET;

                    epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
                }
            }
        }
    }
    return 0;
}
```

注意以下几点：

1. #14设定为5是故意的，为了测试后续的输入和输出

2. 整个服务器的功能是先读取字符串，然后向对方写内容。

3. #110处设置通信socket为非阻塞。

4. 注意#130~#183的读干净缓冲区的read。

5. 注意#213~#264的完全写完所需要传送内容的write。

6. 关于EPOLLET，epoll_wait只有在socket状态发生变化的时候才会返回。所以要对fd进行循环accept,read, write;知直到socket的缓冲区空（read, accept)或者填满(write)为止。

 7. 下面是客户端实验代码

``` cpp
int main(int argc, char **argv)
{
    int                    sockfd;
    char                recvline[MAXLINE + 1];
    struct sockaddr_in    servaddr;

    if (argc != 2)
        err_quit("usage: a.out <IPaddress>");

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(5000);   
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        err_quit("inet_pton error for %s", argv[1]);

    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");

    char input[100];
    while (fgets(input, 100, stdin) != EOF)
    {
        write(sockfd, input, strlen(input));

        int n = 0;
        int count = 0;
        while (1)
        {
            n = read(sockfd, recvline + count, MAXLINE);
            if (n == MAXLINE)
            {
                count += n;
                continue;
            }
            else 
                break;
        }
        printf("%s\n", recvline);
    }
    exit(0);
}
```



#epoll的例子

epoll是linux下高并发服务器的完美方案，因为是基于事件触发的，所以比select快的不只是一个数量级。
单线程epoll，触发量可达到15000，但是加上业务后，因为大多数业务都与数据库打交道，所以就会存在阻塞的情况，这个时候就必须用多线程来提速。
 
下面是来一个网络连接创建一个线程处理业务，业务处理完，线程销毁。实际测试结果不是很理想，在没有业务的时候的测试结果是2000个/s
 
测试工具：stressmark
因为加了适用与ab的代码，所以也可以适用ab进行压力测试。
```cpp
char buf[1000] = {0};
sprintf(buf,"HTTP/1.0 200 OK\r\nContent-type: text/plain\r\n\r\n%s","Hello world!\n");
send(socketfd,buf, strlen(buf),0);
```

``` cpp
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>

#define MAXBUF 1024 
#define MAXEPOLLSIZE 10000

void* pthread_handle_message(void* para);
/* 
setnonblocking - 设置句柄为非阻塞方式 
*/ 
int setnonblocking(int sockfd) 
{ 
    if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1) { 
        return -1; 
    } 
    return 0; 
}

static int count111 = 0;
static time_t oldtime = 0, nowtime = 0;

//------------------------------------------------------------
int main(int argc, char **argv) 
{ 
    int listener, new_fd, nfds, n, ret; 
    struct epoll_event ev; 
    int kdpfd, curfds; 
    socklen_t len; 
    struct sockaddr_in my_addr, their_addr; 
    unsigned int myport, lisnum; 
    struct epoll_event events[MAXEPOLLSIZE]; 
    struct rlimit rt;

    if (argc>1) 
        myport = atoi(argv[1]); 
    else 
        myport = 8006;

    if (argc>2) 
        lisnum = atoi(argv[2]); 
    else 
        lisnum = 10;

    /* 设置每个进程允许打开的最大文件数 */ 
    rt.rlim_max = rt.rlim_cur = MAXEPOLLSIZE; 
    if (setrlimit(RLIMIT_NOFILE, &rt) == -1) { 
        perror("setrlimit"); 
        exit(1); 
    } 
    else printf("设置系统资源参数成功！/n");

    /* 开启 socket 监听 */ 
    if ((listener = socket(PF_INET, SOCK_STREAM, 0)) == -1) { 
        perror("socket"); 
        exit(1); 
    } else 
        printf("socket 创建成功！/n");

    /*设置socket属性，端口可以重用*/ 
    int opt=SO_REUSEADDR; 
    setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    /*设置socket为非阻塞模式*/ 
    setnonblocking(listener);

    bzero(&my_addr, sizeof(my_addr)); 
    my_addr.sin_family = PF_INET; 
    my_addr.sin_port = htons(myport); 
    if (argc>3) 
        my_addr.sin_addr.s_addr = inet_addr(argv[3]); 
    else 
        my_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind 
        (listener, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) 
        == -1) { 
            perror("bind"); 
            exit(1); 
    } else 
        printf("IP 地址和端口绑定成功/n");

    if (listen(listener, lisnum) == -1) { 
        perror("listen"); 
        exit(1); 
    } else 
        printf("开启服务成功！/n");

    /* 创建 epoll 句柄，把监听 socket 加入到 epoll 集合里 */ 
    kdpfd = epoll_create(MAXEPOLLSIZE); 
    len = sizeof(struct sockaddr_in); 
    ev.events = EPOLLIN | EPOLLET; 
    ev.data.fd = listener; 
    if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, listener, &ev) < 0) { 
        fprintf(stderr, "epoll set insertion error: fd=%d/n", listener); 
        return -1; 
    } else 
        printf("监听 socket 加入 epoll 成功！/n"); 
    curfds = 1; 
    while (1) { 
        /* 等待有事件发生 */ 
        nfds = epoll_wait(kdpfd, events, curfds, -1); 
        if (nfds == -1) { 
            perror("epoll_wait"); 
            continue; 
        } 
        /* 处理所有事件 */ 
        for (n = 0; n < nfds; ++n) { 
            if (events[n].data.fd == listener) { 
                new_fd = accept(listener, (struct sockaddr *) &their_addr, 
                    &len); 
                if (new_fd < 0) { 
                    perror("accept"); 
                    continue; 
                } else 
                {
                    //printf("有连接来自于： %s:%d， 分配的 socket 为:%d/n", inet_ntoa(their_addr.sin_addr), ntohs(their_addr.sin_port), new_fd);

                }
                setnonblocking(new_fd); 
                ev.events = EPOLLIN | EPOLLET; 
                ev.data.fd = new_fd; 
                if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, new_fd, &ev) < 0) { 
                    fprintf(stderr, "把 socket '%d' 加入 epoll 失败！%s/n", 
                        new_fd, strerror(errno)); 
                    return -1; 
                } 
                curfds++; 
            } else { 
                pthread_attr_t attr;
                pthread_t threadId;
                

                /*初始化属性值，均设为默认值*/ 
                pthread_attr_init(&attr); 
                pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM); 
                /* 设置线程为分离属性*/ 
                pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
                if(pthread_create(&threadId,&attr,pthread_handle_message,(void*)&(events[n].data.fd)))
                { 
                    perror("pthread_creat error!"); 
                    exit(-1); 
                } 
            } 
        } 
    } 
    close(listener); 
    return 0; 
}


void* pthread_handle_message(void* para)
{
    char recvBuf[1024] = {0}; 
    int ret = 999;
    int rs = 1;
    int socketfd = *(int *)para;

    while(rs)
    {
        ret = recv(socketfd,recvBuf,1024,0);// 接受客户端消息

        if(ret < 0)
        {
            //由于是非阻塞的模式,所以当errno为EAGAIN时,表示当前缓冲区已无数据可//读在这里就当作是该次事件已处理过。

            if(errno == EAGAIN)
            {
                printf("EAGAIN\n");
                break;
            }
            else{
                printf("recv error! errno:%d\n", errno);
        
                close(socketfd);
                break;
            }
        }
        else if(ret == 0)
        {
            // 这里表示对端的socket已正常关闭. 
            rs = 0;
        }
        if(ret == sizeof(recvBuf))
            rs = 1; // 需要再次读取
        else
            rs = 0;
    }

    if(ret>0){
        count111 ++;
        struct tm *today;
        time_t ltime;
        time( &nowtime );

        if(nowtime != oldtime){
            printf("%d\n", count111);
            oldtime = nowtime;
            count111 = 0;
        }


        char buf[1000] = {0};
        sprintf(buf,"HTTP/1.0 200 OK\r\nContent-type: text/plain\r\n\r\n%s","Hello world!\n");
        send(socketfd,buf, strlen(buf),0);
    }
    close(socketfd);
}
```


## 这里主要写一写函数的使用
在终端中使用man epoll_wait可以看到如下用法：
``` cpp
#include <sys/epoll.h>
int epoll_wait(int epfd, struct epoll_event *events,
                      int maxevents, int timeout);
int epoll_pwait(int epfd, struct epoll_event *events,
                      int maxevents, int timeout,
                      const sigset_t *sigmask);
```
`epoll_wait()`函数主要是用于
其中几个参数分别是：
epfd:
events:

`epoll_pwait`相对于`epoll_wait`增加了：
``` cpp
sigset_t origmask;

sigprocmask(SIG_SETMASK, &sigmask, &origmask);
ready = epoll_wait(epfd, &events, maxevents, timeout);
sigprocmask(SIG_SETMASK, &origmask, NULL);
```

其中`sigprocmask`函数是用于检测或者改变目前的信号屏蔽字

``` cpp
#include <signal.h>            
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);       
int sigsuspend(const sigset_t*sigmask);
```

参数的含义：
how：用于指定信号修改的方式，可能选择有三种：
SIG_BLOCK//将set所指向的信号集中包含的信号加到当前的信号掩码中。即信号掩码和set信号集进行或操作。
SIG_UNBLOCK//将set所指向的信号集中包含的信号从当前的信号掩码中删除。几心号掩码和set进行与操作。
SIG_SETMASK //将set的值设定为新的进程信号掩码。即set对信号掩码进行了赋值操作。
set：为执行信号集的指针，在此是新设的信号集，如果进项读取现在的屏蔽值，可将其设置为NULL
oldset：也是指向信号集的指针，这里是指向存放原来的信号集。可以用来检测信号掩码中存在什么信号。
返回值说明：
成功执行时，返回0，失败返回-1，errno被设定为EINVAL

回过头继续看epoll_wait函数，该函数主要是等待事件的产生，类似select调用。参数：- - 1). epfd：由epoll_create生成的，epoll专用的文件描述符
- 2). `events`：用于回传待处理的事件的数组
- 3). maxevents：每次能处理的事件数
- 4). timeout：等待I/O事件发生的超时事件，单位是milliseconds

返回值：
- 成功时返回已经准备好的描述符的数量
- 0 当超时间结束的时候，没有文件描述符准备好
- -1 error

ERRORS：
- EBADF：epfd不是一个有效的文件描述符
- EFAULT：
- EINTR： 
- EINVAL： epfd不是一个epoll文件描述符，或者maxevents的值小于等于0



epoll_wait的系统实现的调用栈
```cpp
epoll_wait
    ep_poll
        ep_events_transfer
            ep_collect_ready_items
            ep_send_events
```
简单的分析：
- 1). ep_collect_ready_items可以看出，事件之前是挂在一个列表`ep->rdlist`上的，这个函数就是把指定数量（该数量就是epoll_wait的参数maxevents）的事件挂到另一个列表txlist，也就是没有取出来的事件仍然挂在`ep->rdlist`上，不会丢失，下一个epoll_wait再通知用户。
- 2). `ep_send_events`执行的动作就是把列表txlist的内容放到缓冲区，然后复制到用户缓冲区

maxevents是epoll_wait可以处理的连接事件的最大限度值，这个值一般要小于等于epoll_create的size，当然如果设置成比size大的话，也无所谓，size是epoll可以监听的最大fd的数量。maxevents的意义是防止epoll的API在填写我们传进去的指针events的时候，超过指针指向的内存的大小从而导致内存溢出。

# 在面试中被问道问题


## epoll两种方式的区别


## 如何确定对端客户端已经关闭链接
首先回来以后百度了一些答案，大概是如下几种方式：
1. TCP recv返回0 ，说明对端已经关闭
2. 注册EPOLLERR，收到事件是关闭
3. recv/send返回-1时，如果错误不是EWOULDBLOCK或者EINTR，也主动关闭连接。
[这里关注了一个讨论http://bbs.csdn.net/topics/370255833]然后根据他们的讨论，我也实验了一下：











