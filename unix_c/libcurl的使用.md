## libcurl的api
``` C
curl_easy_init() 
curl_easy_cleanup() 
curl_easy_setopt() 
curl_easy_perform() 
curl_easy_getinfo()
```
还有
``` C
curl_version()    //returns a pointer to the libcurl version string
curl_getdate()    //converts a date string to time_t
curl_formadd()    //build multipart form-data posts
curl_formfree()    //free a previously built form POST
curl_slist_append()    //builds a linked list
curl_slist_free_all()    //frees a whole curl_slist as made with curl_slist_append()
curl_easy_escape()    //URL encodes a string
curl_easy_unescape()    //URL decodes a string
```

### 主要函数`curl_easy_setopt`
``` C
#include <curl/curl.h>
CURLcode curl_easy_setopt(CURL *handle, CURLoption option, parameter);
```
该函数是curl中非常重要的函数，curl所有设置都是在该函数中完成，该函数的设置选项众多：
1. CURLOPT_URL
设置访问URL
2.       CURLOPT_WRITEFUNCTION，CURLOPT_WRITEDATA
回调函数原型为：size_t function( void *ptr, size_t size, size_t nmemb, void *stream); 函数将在libcurl接收到数据后被调用，因此函数多做数据保存的功能，如处理下载文件。CURLOPT_WRITEDATA 用于表明CURLOPT_WRITEFUNCTION函数中的stream指针的来源。
如果你没有通过CURLOPT_WRITEFUNCTION属性给easy handle设置回调函数，libcurl会提供一个默认的回调函数，它只是简单的将接收到的数据打印到标准输出。你也可以通过 CURLOPT_WRITEDATA属性给默认回调函数传递一个已经打开的文件指针，用于将数据输出到文件里。
 
3.      CURLOPT_HEADERFUNCTION，CURLOPT_HEADERDATA
回调函数原型为 size_t function( void *ptr, size_t size,size_t nmemb, void *stream); libcurl一旦接收到http 头部数据后将调用该函数。CURLOPT_WRITEDATA 传递指针给libcurl，该指针表明CURLOPT_HEADERFUNCTION 函数的stream指针的来源。
 
4.       CURLOPT_READFUNCTION CURLOPT_READDATA
libCurl需要读取数据传递给远程主机时将调用CURLOPT_READFUNCTION指定的函数，函数原型是：size_t function(void *ptr, size_t size, size_t nmemb,void *stream). CURLOPT_READDATA 表明CURLOPT_READFUNCTION函数原型中的stream指针来源。
 
5.       CURLOPT_NOPROGRESS，CURLOPT_PROGRESSFUNCTION，CURLOPT_PROGRESSDATA
跟数据传输进度相关的参数。CURLOPT_PROGRESSFUNCTION 指定的函数正常情况下每秒被libcurl调用一次，为了使CURLOPT_PROGRESSFUNCTION被调用，CURLOPT_NOPROGRESS必须被设置为false，CURLOPT_PROGRESSDATA指定的参数将作为CURLOPT_PROGRESSFUNCTION指定函数的第一个参数
 
6.       CURLOPT_TIMEOUT，CURLOPT_CONNECTIONTIMEOUT:
CURLOPT_TIMEOUT 由于设置传输时间，CURLOPT_CONNECTIONTIMEOUT 设置连接等待时间
 
7.       CURLOPT_FOLLOWLOCATION
设置重定位URL
 
8.       CURLOPT_RANGE: CURLOPT_RESUME_FROM:
断点续传相关设置。CURLOPT_RANGE 指定char *参数传递给libcurl，用于指明http域的RANGE头域，例如：
表示头500个字节：bytes=0-499
表示第二个500字节：bytes=500-999
表示最后500个字节：bytes=-500
表示500字节以后的范围：bytes=500-
第一个和最后一个字节：bytes=0-0,-1
同时指定几个范围：bytes=500-600,601-999
CURLOPT_RESUME_FROM 传递一个long参数给libcurl，指定你希望开始传递的 偏移量。

9. CURLOPT_POSTFIELDS
设置post的内容

### 函数`curl_easy_getinfo`
参考`https://curl.haxx.se/libcurl/c/curl_easy_getinfo.html`
发出http请求后，服务器会返回应答头信息和应答数据，如果仅仅是打印应答头的所有内容，则直接可以通过curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, 打印函数)的方式来完成，这里需要获取的是应答头中特定的信息，比如应答码、cookies列表等，则需要通过下面这个函数：

``` C
#include <curl/curl.h>
CURLcode curl_easy_getinfo(CURL *curl, CURLINFO info, ... );
```

获取时间

| 字段名 | 功能 | 获取 |
|:----:|:---:|:---:|
|CURLINFO_APPCONNECT_TIME | ssl握手时间|double|
| CURLINFO_CONNECT_TIME | 连接时间 |double|
| CURLINFO_TOTAL_TIME | |double|
|CURLINFO_RESPONSE_CODE|获取应答码|long|
|CURLINFO_HTTP_CONNECTCODE|||
|CURLINFO_HTTP_VERSION|||
|CURLINFO_EFFECTIVE_URL|||
|CURLINFO_HEADER_SIZE|头大小||
|CURLINFO_COOKIELIST|cookies列表||

### 函数` curl_easy_perform`
该函数是完成curl_easy_setopt指定的所有选项，本节重点介绍curl_easy_perform的返回值。返回0意味一切ok，非0代表错误发生。主要错误码说明：

``` C
1.    CURLE_OK
    任务完成一切都好
2     CURLE_UNSUPPORTED_PROTOCOL
    不支持的协议，由URL的头部指定
3     CURLE_COULDNT_CONNECT
    不能连接到remote 主机或者代理
4     CURLE_REMOTE_ACCESS_DENIED
    访问被拒绝
5     CURLE_HTTP_RETURNED_ERROR
    Http返回错误
6     CURLE_READ_ERROR
读本地文件错误
要获取详细的错误描述字符串，可以通过const char *curl_easy_strerror(CURLcode errornum ) 这个函数取得.
```

这个函数

## 长连接和短连接
====什么是长连接？
HTTP1.1规定了默认保持长连接（HTTP persistent connection ，也有翻译为持久连接），数据传输完成了保持TCP连接不断开（不发RST包、不四次握手），等待在同域名下继续用这个通道传输数据；相反的就是短连接。
 
HTTP首部的Connection: Keep-alive是HTTP1.0浏览器和服务器的实验性扩展，当前的HTTP1.1 RFC2616文档没有对它做说明，因为它所需要的功能已经默认开启，无须带着它，但是实践中可以发现，浏览器的报文请求都会带上它。如果HTTP1.1版本的HTTP请求报文不希望使用长连接，则要在HTTP请求报文首部加上Connection: close。《HTTP权威指南》提到，有部分古老的HTTP1.0 代理不理解Keep-alive，而导致长连接失效：客户端–>代理–>服务端，客户端带有Keep-alive，而代理不认识，于是将报文原封不动转给了服务端，服务端响应了Keep-alive，也被代理转发给了客户端，于是保持了“客户端–>代理”连接和“代理–>服务端”连接不关闭，但是，当客户端第发送第二次请求时，代理会认为当前连接不会有请求了，于是忽略了它，长连接失效。书上也介绍了解决方案：当发现HTTP版本为1.0时，就忽略Keep-alive，客户端就知道当前不该使用长连接。其实，在实际使用中不需要考虑这么多，很多时候代理是我们自己控制的，如Nginx代理，代理服务器有长连接处理逻辑，服务端无需做patch处理，常见的是客户端跟Nginx代理服务器使用HTTP1.1协议&长连接，而Nginx代理服务器跟后端服务器使用HTTP1.0协议&短连接。
 
在实际使用中，HTTP头部有了Keep-Alive这个值并不代表一定会使用长连接，客户端和服务器端都可以无视这个值，也就是不按标准来，譬如我自己写的HTTP客户端多线程去下载文件，就可以不遵循这个标准，并发的或者连续的多次GET请求，都分开在多个TCP通道中，每一条TCP通道，只有一次GET，GET完之后，立即有TCP关闭的四次握手，这样写代码更简单，这时候虽然HTTP头有Connection: Keep-alive，但不能说是长连接。正常情况下客户端浏览器、web服务端都有实现这个标准，因为它们的文件又小又多，保持长连接减少重新开TCP连接的开销很有价值。
 
以前使用libcurl做的上传/下载，就是短连接，抓包可以看到：1、每一条TCP通道只有一个POST；2、在数据传输完毕可以看到四次握手包。只要不调用curl_easy_cleanup，curl的handle就可能一直有效，可复用。这里说可能，因为连接是双方的，如果服务器那边关掉了，那么我客户端这边保留着也不能实现长连接。
 
如果是使用windows的WinHTTP库，则在POST/GET数据的时候，虽然我关闭了句柄，但这时候TCP连接并不会立即关闭，而是等一小会儿，这时候是WinHTTP库底层支持了跟Keep-alive所需要的功能：即便没有Keep-alive，WinHTTP库也可能会加上这种TCP通道复用的功能，而其它的网络库像libcurl则不会这么做。以前观察过WinHTTP库不会及时断开TCP连接。

## 多线程问题
首先，线程之间不应该共享同一个libcurl handle(CURL *对象)
libcurl依赖其他库支持SSL/STL，所以用多线程访问HTTPS或者FTPS的URL时，应该满足这些库对多线程的一些要求。详细可以参考：
|参考||
|:--:|:--:|
| OpenSSL| http://www.openssl.org/docs/crypto/threads.html#DESCRIPTION|
|GnuTLS | http://www.gnu.org/software/gnutls/manual/html_node/Multi_002dthreaded-applications.html |
NSS：宣称是多线程安全的

## libcurl调试方法

       传输失败总是有原因的。你可能错误的设置了一些libcurl的属性或者没有正确的理解某些属性的含义，或者是远程主机返回一些无法被正确解析的内容。
       这里有一个黄金法则来处理这些问题：将CURLOPT_VERBOSE属性设置为1，libcurl会输出通信过程中的一些细节。如果使用的是http协 议，请求头/响应头也会被输出。将CURLOPT_HEADER设为1，这些头信息将出现在消息的内容中。
    当然不可否认的是，libcurl还存在bug。
    如果你对相关的协议了解越多，在使用libcurl时，就越不容易犯错。


## 使用libcurl是需要注意的地方
1. 线程使用libcurl访问时，设置了超时时间，而libcurl库不会为这个超时信号做任何处理，信号产生而没有禁止访问超时的时候抛出超时的信号
``` C
curl_setopt(curl, CURLOPT_NOSIGNAL,1L);
```

2. 正常使用流程是先调用curl_global_init初始化资源，而这个函数不是线程安全的。curl_easy_init发现没有做初始化时会自动初始化，多个线程同时进行curl_easy_init时会导致异常。curl官方建议在主线程中先做初始化。
``` C
curl_global_init(CURL_GLOBAL_ALL); 
```

3. multithread
官方网站提供的multithread实例：

``` C
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
*
* Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
*
* This software is licensed as described in the file COPYING, which
* you should have received as part of this distribution. The terms
* are also available at https://curl.haxx.se/docs/copyright.html.
*
* You may opt to use, copy, modify, merge, publish, distribute and/or sell
* copies of the Software, and permit persons to whom the Software is
* furnished to do so, under the terms of the COPYING file.
*
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
* KIND, either express or implied.
*
***************************************************************************/
/* <DESC>
* A multi-threaded example that uses pthreads to fetch several files at once
* </DESC>
*/
 
#include <stdio.h>
#include <pthread.h>
#include <curl/curl.h>
 
#define NUMT 4
 
/*
  List of URLs to fetch.
  If you intend to use a SSL-based protocol here you MUST setup the OpenSSL
  callback functions as described here: 
  https://www.openssl.org/docs/crypto/threads.html#DESCRIPTION 
*/
const char * const urls[NUMT]= {
  "https://curl.haxx.se/",
  "ftp://cool.haxx.se/",
  "http://www.contactor.se/",
  "www.haxx.se"
};
 
static void *pull_one_url(void *url)
{
  CURL *curl;
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_perform(curl); /* ignores error */
  curl_easy_cleanup(curl);
  return NULL;
}
/*
   int pthread_create(pthread_t *new_thread_ID,
   const pthread_attr_t *attr,
   void * (*start_func)(void *), void *arg);
*/
int main(int argc, char **argv)
{
  pthread_t tid[NUMT];
  int i;
  int error;
  /* Must initialize libcurl before any threads are started */
  curl_global_init(CURL_GLOBAL_ALL);
 
  for(i=0; i< NUMT; i++) {
    error = pthread_create(&tid[i],
                           NULL, /* default attributes please */
                           pull_one_url,
                           (void *)urls[i]);
    if(0 != error)
      fprintf(stderr, "Couldn't run thread number %d, errno %d\n", i, error);
    else
      fprintf(stderr, "Thread %d, gets %s\n", i, urls[i]);
  }
 
  /* now wait for all threads to terminate */
  for(i=0; i< NUMT; i++) {
    error = pthread_join(tid[i], NULL);
    fprintf(stderr, "Thread %d terminated\n", i);
  }
  return 0;
}
```

openssl不是线程安全的，需要实现相关的锁设置才行。
系统提供的demo

``` C
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
*
* Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
*
* This software is licensed as described in the file COPYING, which
* you should have received as part of this distribution. The terms
* are also available at https://curl.haxx.se/docs/copyright.html.
*
* You may opt to use, copy, modify, merge, publish, distribute and/or sell
* copies of the Software, and permit persons to whom the Software is
* furnished to do so, under the terms of the COPYING file.
*
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
* KIND, either express or implied.
*
***************************************************************************/
/* <DESC>
* Show the required mutex callback setups for GnuTLS and OpenSSL when using
* libcurl multi-threaded.
* </DESC>
*/
/* A multi-threaded example that uses pthreads and fetches 4 remote files at
* once over HTTPS. The lock callbacks and stuff assume OpenSSL or GnuTLS
* (libgcrypt) so far.
*
* OpenSSL docs for this:
 *   https://www.openssl.org/docs/crypto/threads.html
* gcrypt docs for this:
 *   https://gnupg.org/documentation/manuals/gcrypt/Multi_002dThreading.html
*/
 
#define USE_OPENSSL 
 
#include <stdio.h>
#include <pthread.h>
#include <curl/curl.h>
 
#define NUMT 4
 
/* we have this global to let the callback get easy access to it */
static pthread_mutex_t *lockarray;
 
#ifdef USE_OPENSSL
#include <openssl/crypto.h>
static void lock_callback(int mode, int type, char *file, int line)
{
  (void)file;
  (void)line;
  if(mode & CRYPTO_LOCK) {
    pthread_mutex_lock(&(lockarray[type]));
  }
  else {
    pthread_mutex_unlock(&(lockarray[type]));
  }
}
 
static unsigned long thread_id(void)
{
  unsigned long ret;
 
  ret=(unsigned long)pthread_self();
  return ret;
}
 
static void init_locks(void)
{
  int i;
 
  lockarray=(pthread_mutex_t *)OPENSSL_malloc(CRYPTO_num_locks() *
                                            sizeof(pthread_mutex_t));
  for(i=0; i<CRYPTO_num_locks(); i++) {
    pthread_mutex_init(&(lockarray[i]), NULL);
  }
 
  CRYPTO_set_id_callback((unsigned long (*)())thread_id);
  CRYPTO_set_locking_callback((void (*)())lock_callback);
}
 
static void kill_locks(void)
{
  int i;
 
  CRYPTO_set_locking_callback(NULL);
  for(i=0; i<CRYPTO_num_locks(); i++)
    pthread_mutex_destroy(&(lockarray[i]));
 
  OPENSSL_free(lockarray);
}
#endif
 
#ifdef USE_GNUTLS
#include <gcrypt.h>
#include <errno.h>
 
GCRY_THREAD_OPTION_PTHREAD_IMPL;
 
void init_locks(void)
{
  gcry_control(GCRYCTL_SET_THREAD_CBS);
}
 
#define kill_locks()
#endif
 
/* List of URLs to fetch.*/
const char * const urls[]= {
  "https://www.example.com/",
  "https://www2.example.com/",
  "https://www3.example.com/",
  "https://www4.example.com/",
};
 
static void *pull_one_url(void *url)
{
  CURL *curl;
 
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, url);
  /* this example doesn't verify the server's certificate, which means we
     might be downloading stuff from an impostor */
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
  curl_easy_perform(curl); /* ignores error */
  curl_easy_cleanup(curl);
 
  return NULL;
}
 
int main(int argc, char **argv)
{
  pthread_t tid[NUMT];
  int i;
  int error;
  (void)argc; /* we don't use any arguments in this example */
  (void)argv;
 
  /* Must initialize libcurl before any threads are started */
  curl_global_init(CURL_GLOBAL_ALL);
 
  init_locks();
 
  for(i=0; i< NUMT; i++) {
    error = pthread_create(&tid[i],
                           NULL, /* default attributes please */
                           pull_one_url,
                           (void *)urls[i]);
    if(0 != error)
      fprintf(stderr, "Couldn't run thread number %d, errno %d\n", i, error);
    else
      fprintf(stderr, "Thread %d, gets %s\n", i, urls[i]);
  }
 
  /* now wait for all threads to terminate */
  for(i=0; i< NUMT; i++) {
    error = pthread_join(tid[i], NULL);
    fprintf(stderr, "Thread %d terminated\n", i);
  }
 
  kill_locks();
 
  return 0;
}
```


例子opensslthreadlock.c

``` C
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
*
* Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
*
* This software is licensed as described in the file COPYING, which
* you should have received as part of this distribution. The terms
* are also available at https://curl.haxx.se/docs/copyright.html.
*
* You may opt to use, copy, modify, merge, publish, distribute and/or sell
* copies of the Software, and permit persons to whom the Software is
* furnished to do so, under the terms of the COPYING file.
*
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
* KIND, either express or implied.
*
***************************************************************************/
/* <DESC>
* one way to set the necessary OpenSSL locking callbacks if you want to do
* multi-threaded transfers with HTTPS/FTPS with libcurl built to use OpenSSL.
* </DESC>
*/
/*
* This is not a complete stand-alone example.
*
* Author: Jeremy Brown
*/
#include <stdio.h>
#include <pthread.h>
#include <openssl/err.h>

#define MUTEX_TYPE       pthread_mutex_t
#define MUTEX_SETUP(x)   pthread_mutex_init(&(x), NULL)
#define MUTEX_CLEANUP(x) pthread_mutex_destroy(&(x))
#define MUTEX_LOCK(x)    pthread_mutex_lock(&(x))
#define MUTEX_UNLOCK(x)  pthread_mutex_unlock(&(x))
#define THREAD_ID        pthread_self()

void handle_error(const char *file, int lineno, const char *msg)
{
  fprintf(stderr, "** %s:%d %s\n", file, lineno, msg);
  ERR_print_errors_fp(stderr);
  /* exit(-1); */
}
 
/* This array will store all of the mutexes available to OpenSSL. */
static MUTEX_TYPE *mutex_buf= NULL;

static void locking_function(int mode, int n, const char *file, int line)
{
  if(mode & CRYPTO_LOCK)
    MUTEX_LOCK(mutex_buf[n]);
  else
    MUTEX_UNLOCK(mutex_buf[n]);
}
 
static unsigned long id_function(void)
{
  return ((unsigned long)THREAD_ID);
}
 
int thread_setup(void)
{
  int i;
  mutex_buf = malloc(CRYPTO_num_locks() * sizeof(MUTEX_TYPE));
  if(!mutex_buf)
    return 0;
  for(i = 0;  i < CRYPTO_num_locks();  i++)
    MUTEX_SETUP(mutex_buf[i]);
  CRYPTO_set_id_callback(id_function);
  CRYPTO_set_locking_callback(locking_function);
  return 1;
}
 
int thread_cleanup(void)
{
  int i;
 
  if(!mutex_buf)
    return 0;
  CRYPTO_set_id_callback(NULL);
  CRYPTO_set_locking_callback(NULL);
  for(i = 0;  i < CRYPTO_num_locks();  i++)
    MUTEX_CLEANUP(mutex_buf[i]);
  free(mutex_buf);
  mutex_buf = NULL;
  return 1;
}
```

















