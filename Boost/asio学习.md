asio是boost库中一个

asio库基于Proactor模式封装了操作系统的select，kqueue，poll/epool、overlapped I/O等机制，实现了异步IO模型。核心是io_service，相当于前摄器模式中的Proactor角色，asio的任何操作都需要有io_service的参与。

> 与evpp的区别，evpp是采用reactor模式设计的

我阅读的源码是boost_1_66_0的，此时已经使用io_context替代io_service了，通过下面的代码：
```cpp
namespace boost {
namespace asio {
#if !defined(BOOST_ASIO_NO_DEPRECATED)
/// Typedef for backwards compatibility.
typedef io_context io_service;
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)
} // namespace asio
}
```




## 一些概念
**handler**
他是符合某种函数签名的回调函数

handler 并不一定是函数指针，函数对象、function对象、bind/lambda表达式等可以调用物也都可以作为handler用于io_service调用。asio库里的handler主要有如下三种：
- 只有一个error_code参数，标志某个异步事件完成了，是最基本的handler；
- error_code和signal_number两个参数，标志发生了一个Unix信号事件
- error_code和bytes_transferred两个参数，标志某个读写操作已经完成了，可读写的数据字节数是bytes_transferred，通常用于socket回调。

```cpp

void handler(const error_code& ec); //

void handler(const error_code& ec, // 操作的错误码
                int signal_number); //引发操作的信号值

void handler(const error_code& ec,  // 操作的错误码
                std::size_t bytes_transferred); //传输的字节数
```


**strand**


**work**

```cpp
class io_context::work
{
public:
  explicit work(boost::asio::io_context& io_context); //构造函数启动工作
  work(const work& other);      //复制构造函数
  ~work();      //析构函数 停止工作

  /// Get the io_context associated with the work.
  boost::asio::io_context& get_io_context();    //从work中获取io_context
  boost::asio::io_context& get_io_service();    //
private:
  // Prevent assignment.
  void operator=(const work& other);    //限制赋值操作
  // The io_context implementation.
  detail::io_context_impl& io_context_impl_;    //
};
```
如果想要work停止工作，可以显式地调用work的析构函数，或者使用智能指针持有他，通过reset智能指针进行析构。



**错误处理**
asio的错误处理是使用system库的error_code和system_error俩表示程序运行的错误。



**跟踪日志**

```cpp
#define BOOST_ASIO_ENABLE_HANDLER_TRACKING
```



## 网络通信中涉及的类

asio库支持TCP，UDP，ICMP通信协议，命名空间boost::asio::ip中提供了大量的网络通信方面的函数的类
### tcp

```cpp
class tcp
{
public:
  /// The type of a TCP endpoint.
  typedef basic_endpoint<tcp> endpoint;

  /// Construct to represent the IPv4 TCP protocol.
  static tcp v4()
  {
    return tcp(BOOST_ASIO_OS_DEF(AF_INET));
  }

  /// Construct to represent the IPv6 TCP protocol.
  static tcp v6()
  {
    return tcp(BOOST_ASIO_OS_DEF(AF_INET6));
  }

  /// Obtain an identifier for the type of the protocol.
  int type() const
  {
    return BOOST_ASIO_OS_DEF(SOCK_STREAM);
  }

  /// Obtain an identifier for the protocol.
  int protocol() const
  {
    return BOOST_ASIO_OS_DEF(IPPROTO_TCP);
  }

  /// Obtain an identifier for the protocol family.
  int family() const
  {
    return family_;
  }

  typedef basic_stream_socket<tcp> socket;/// The TCP socket type.
  typedef basic_socket_acceptor<tcp> acceptor; /// The TCP acceptor type.
  typedef basic_resolver<tcp> resolver;

#if !defined(BOOST_ASIO_NO_IOSTREAM)
  typedef basic_socket_iostream<tcp> iostream;
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined no_delay;
#else
  typedef boost::asio::detail::socket_option::boolean<
    BOOST_ASIO_OS_DEF(IPPROTO_TCP), BOOST_ASIO_OS_DEF(TCP_NODELAY)> no_delay;
#endif

  /// Compare two protocols for equality.
  friend bool operator==(const tcp& p1, const tcp& p2)
  {
    return p1.family_ == p2.family_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const tcp& p1, const tcp& p2)
  {
    return p1.family_ != p2.family_;
  }

private:
  // Construct with a specific family.
  explicit tcp(int protocol_family)
    : family_(protocol_family)
  {
  }

  int family_;
};
```

### address



### endpoint
将IP地址和端口构成一个端点，
```cpp
ip::address addr;
addr = addr.from_string("127.0.0.1");
ip::tcp::endpoint ep(addr, 6886); //创建端点对象，端口为6886
```


### socket
TCP通信的基本类，basic_stream_socket的tcp协议特例化




### 


### 简单的实例
这里是使用Clion去开发的，需要修改下CMakefile.txt
完整的CMakeList.txt的写法如下：
``` makefile
cmake_minimum_required(VERSION 3.9)
project(basio_server)

set(CMAKE_CXX_STANDARD 11)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.66.0 COMPONENTS log thread system regex context REQUIRED)

add_executable(basio_server main.cpp)
#链接该boost库
target_link_libraries(basio_server ${Boost_LIBRARIES} pthread)
#添加
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_system -lpthread")
add_definitions(${CMAKE_CXX_FLAGS})
```

