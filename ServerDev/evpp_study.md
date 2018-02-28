
@brief:
A modern C++ network library for developing high performance network services in TCP/UPD/HTTP protocols

evpp是360开源的一个时间驱动的框架，采用的设计模式是reactor模式。
github地址为https://github.com/Qihoo360/evpp
是一个基于libevent开发的基于C++11开发的高性能网络库，自带TCP/UDP/HTTP等协议

特性：
1. 现代版的C++11接口
2. 非阻塞异步接口都是C++11的functional/bind形式的回调仿函数
3. 非阻塞纯异步多线程TCP服务器/客户端
4. 非阻塞纯异步多线程HTTP
5. UDP
6. 支持多进程模式
7. 跨平台和高性能

除此之外还

<!-- TOC -->

- [http模块](#http%E6%A8%A1%E5%9D%97)
    - [http::Server类](#httpserver%E7%B1%BB)
    - [http::Service类](#httpservice%E7%B1%BB)
- [httpc模块](#httpc%E6%A8%A1%E5%9D%97)
    - [httpc::ConnPool类](#httpcconnpool%E7%B1%BB)
- [upd模块](#upd%E6%A8%A1%E5%9D%97)
- [基础模块](#%E5%9F%BA%E7%A1%80%E6%A8%A1%E5%9D%97)
    - [事件线程池](#%E4%BA%8B%E4%BB%B6%E7%BA%BF%E7%A8%8B%E6%B1%A0)
    - [buffer](#buffer)
    - [http](#http)

<!-- /TOC -->



# http模块

## http::Server类
这是一个http服务器类，自带线程池，他的时间循环和工作线程调度，完全是线程安全的，业务层不用关心跨线程调度问题，同事，还将http服务的核心功能单独抽取出来形成。

## http::Service类
可嵌入型的服务器类，可以嵌入到已有的libevent事件循环中，参考了golang的设计，网络地址表达就仅仅使用“ip:port”这种形式的字符串来表示。

# httpc模块

## httpc::ConnPool类
http的客户端连接池，

# upd模块


# 基础模块

## 事件线程池
这里首先是EventLoopThreadPool
```cpp
class EVPP_EXPORT EventLoopThreadPool : public ServerStatus {
public:
    typedef std::function<void()> DoneCallback;

    EventLoopThreadPool(EventLoop* base_loop, uint32_t thread_num);
    ~EventLoopThreadPool();

    bool Start(bool wait_thread_started = false);

    void Stop(bool wait_thread_exited = false);
    void Stop(DoneCallback fn);

    // @brief Join all the working thread. If you forget to call this method,
    // it will be invoked automatically in the destruct method ~EventLoopThreadPool().
    // @note DO NOT call this method from any of the working thread.
    void Join();

    // @brief Reinitialize some data fields after a fork
    void AfterFork();
public:
    EventLoop* GetNextLoop();
    EventLoop* GetNextLoopWithHash(uint64_t hash);

    uint32_t thread_num() const;

private:
    void Stop(bool wait_thread_exit, DoneCallback fn);
    void OnThreadStarted(uint32_t count);
    void OnThreadExited(uint32_t count);

private:
    EventLoop* base_loop_;

    uint32_t thread_num_ = 0;
    std::atomic<int64_t> next_ = { 0 };

    DoneCallback stopped_cb_;

    typedef std::shared_ptr<EventLoopThread> EventLoopThreadPtr;
    std::vector<EventLoopThreadPtr> threads_;
};
```


## buffer
> 构造函数前面增加了explicit修饰，可以阻止不应该允许的经过转换构造函数进行的隐式转换的发生

定义在namespace evpp下的Buffer，下面是简单的定义：
```cpp
class EVPP_EXPORT Buffer {
public:
    static const size_t kCheapPrependSize;      //在buffer.cc的实现中，该值为8
    static const size_t kInitialSize;           //在buffer.cc的实现中，该值为1024
    /* 构造函数，不支持隐式转换 */
    explicit Buffer(size_t initial_size = kInitialSize, size_t reserved_prepend_size = kCheapPrependSize)
        : capacity_(reserved_prepend_size + initial_size)
        , read_index_(reserved_prepend_size)
        , write_index_(reserved_prepend_size)
        , reserved_prepend_size_(reserved_prepend_size) {
        buffer_ = new char[capacity_];
        assert(length() == 0);
        assert(WritableBytes() == initial_size);
        assert(PrependableBytes() == reserved_prepend_size);
    }

    ~Buffer() {
        delete[] buffer_;
        buffer_ = nullptr;
        capacity_ = 0;
    }

    void Swap(Buffer& rhs) {
        std::swap(buffer_, rhs.buffer_);
        std::swap(capacity_, rhs.capacity_);
        std::swap(read_index_, rhs.read_index_);
        std::swap(write_index_, rhs.write_index_);
        std::swap(reserved_prepend_size_, rhs.reserved_prepend_size_);
    }

    // Skip advances the reading index of the buffer
    void Skip(size_t len) {
        if (len < length()) {
            read_index_ += len;
        } else {
            Reset();
        }
    }

    // Retrieve advances the reading index of the buffer
    // Retrieve it the same as Skip.
    void Retrieve(size_t len) {
        Skip(len);
    }

    // Truncate discards all but the first n unread bytes from the buffer
    // but continues to use the same allocated storage.
    // It does nothing if n is greater than the length of the buffer.
    void Truncate(size_t n) {
        if (n == 0) {
            read_index_ = reserved_prepend_size_;
            write_index_ = reserved_prepend_size_;
        } else if (write_index_ > read_index_ + n) {
            write_index_ = read_index_ + n;
        }
    }

    void Reset() {
        Truncate(0);
    }

    // Increase the capacity of the container to a value that's greater
    // or equal to len. If len is greater than the current capacity(),
    // new storage is allocated, otherwise the method does nothing.
    void Reserve(size_t len) {
        if (capacity_ >= len + reserved_prepend_size_) {
            return;
        }

        // TODO add the implementation logic here
        grow(len + reserved_prepend_size_);
    }

    // Make sure there is enough memory space to append more data with length len
    void EnsureWritableBytes(size_t len) {
        if (WritableBytes() < len) {
            grow(len);
        }

        assert(WritableBytes() >= len);
    }

    // ToText appends char '\0' to buffer to convert the underlying data to a c-style string text.
    // It will not change the length of buffer.
    void ToText() {
        AppendInt8('\0');
        UnwriteBytes(1);
    }

    // TODO XXX Little-Endian/Big-Endian problem.
#define evppbswap_64(x)                          \
    ((((x) & 0xff00000000000000ull) >> 56)       \
     | (((x) & 0x00ff000000000000ull) >> 40)     \
     | (((x) & 0x0000ff0000000000ull) >> 24)     \
     | (((x) & 0x000000ff00000000ull) >> 8)      \
     | (((x) & 0x00000000ff000000ull) << 8)      \
     | (((x) & 0x0000000000ff0000ull) << 24)     \
     | (((x) & 0x000000000000ff00ull) << 40)     \
     | (((x) & 0x00000000000000ffull) << 56))

    // Write
public:
    void Write(const void* /*restrict*/ d, size_t len) {
        EnsureWritableBytes(len);
        memcpy(WriteBegin(), d, len);
        assert(write_index_ + len <= capacity_);
        write_index_ += len;
    }

    void Append(const Slice& str) {
        Write(str.data(), str.size());
    }

    void Append(const char* /*restrict*/ d, size_t len) {
        Write(d, len);
    }

    void Append(const void* /*restrict*/ d, size_t len) {
        Write(d, len);
    }

    // Append int64_t/int32_t/int16_t with network endian
    void AppendInt64(int64_t x) {
        int64_t be = evppbswap_64(x);
        Write(&be, sizeof be);
    }

    void AppendInt32(int32_t x) {
        int32_t be32 = htonl(x);
        Write(&be32, sizeof be32);
    }

    void AppendInt16(int16_t x) {
        int16_t be16 = htons(x);
        Write(&be16, sizeof be16);
    }

    void AppendInt8(int8_t x) {
        Write(&x, sizeof x);
    }

    // Prepend int64_t/int32_t/int16_t with network endian
    void PrependInt64(int64_t x) {
        int64_t be = evppbswap_64(x);
        Prepend(&be, sizeof be);
    }

    void PrependInt32(int32_t x) {
        int32_t be32 = htonl(x);
        Prepend(&be32, sizeof be32);
    }

    void PrependInt16(int16_t x) {
        int16_t be16 = htons(x);
        Prepend(&be16, sizeof be16);
    }

    void PrependInt8(int8_t x) {
        Prepend(&x, sizeof x);
    }

    // Insert content, specified by the parameter, into the front of reading index
    void Prepend(const void* /*restrict*/ d, size_t len) {
        assert(len <= PrependableBytes());
        read_index_ -= len;
        const char* p = static_cast<const char*>(d);
        memcpy(begin() + read_index_, p, len);
    }

    void UnwriteBytes(size_t n) {
        assert(n <= length());
        write_index_ -= n;
    }

    void WriteBytes(size_t n) {
        assert(n <= WritableBytes());
        write_index_ += n;
    }

    //Read
public:
    // Peek int64_t/int32_t/int16_t/int8_t with network endian
    int64_t ReadInt64() {
        int64_t result = PeekInt64();
        Skip(sizeof result);
        return result;
    }

    int32_t ReadInt32() {
        int32_t result = PeekInt32();
        Skip(sizeof result);
        return result;
    }

    int16_t ReadInt16() {
        int16_t result = PeekInt16();
        Skip(sizeof result);
        return result;
    }

    int8_t ReadInt8() {
        int8_t result = PeekInt8();
        Skip(sizeof result);
        return result;
    }

    Slice ToSlice() const {
        return Slice(data(), length());
    }

    std::string ToString() const {
        return std::string(data(), length());
    }

    void Shrink(size_t reserve) {
        Buffer other(length() + reserve);
        other.Append(ToSlice());
        Swap(other);
    }

    // ReadFromFD reads data from a fd directly into buffer,
    // and return result of readv, errno is saved into saved_errno
    ssize_t ReadFromFD(evpp_socket_t fd, int* saved_errno);

    // Next returns a slice containing the next n bytes from the buffer,
    // advancing the buffer as if the bytes had been returned by Read.
    // If there are fewer than n bytes in the buffer, Next returns the entire buffer.
    // The slice is only valid until the next call to a read or write method.
    Slice Next(size_t len) {
        if (len < length()) {
            Slice result(data(), len);
            read_index_ += len;
            return result;
        }

        return NextAll();
    }

    // NextAll returns a slice containing all the unread portion of the buffer,
    // advancing the buffer as if the bytes had been returned by Read.
    Slice NextAll() {
        Slice result(data(), length());
        Reset();
        return result;
    }

    std::string NextString(size_t len) {
        Slice s = Next(len);
        return std::string(s.data(), s.size());
    }

    std::string NextAllString() {
        Slice s = NextAll();
        return std::string(s.data(), s.size());
    }

    // ReadByte reads and returns the next byte from the buffer.
    // If no byte is available, it returns '\0'.
    char ReadByte() {
        assert(length() >= 1);

        if (length() == 0) {
            return '\0';
        }

        return buffer_[read_index_++];
    }

    // UnreadBytes unreads the last n bytes returned
    // by the most recent read operation.
    void UnreadBytes(size_t n) {
        assert(n < read_index_);
        read_index_ -= n;
    }

    // Peek
public:
    // Peek int64_t/int32_t/int16_t/int8_t with network endian

    int64_t PeekInt64() const {
        assert(length() >= sizeof(int64_t));
        int64_t be64 = 0;
        ::memcpy(&be64, data(), sizeof be64);
        return evppbswap_64(be64);
    }

    int32_t PeekInt32() const {
        assert(length() >= sizeof(int32_t));
        int32_t be32 = 0;
        ::memcpy(&be32, data(), sizeof be32);
        return ntohl(be32);
    }

    int16_t PeekInt16() const {
        assert(length() >= sizeof(int16_t));
        int16_t be16 = 0;
        ::memcpy(&be16, data(), sizeof be16);
        return ntohs(be16);
    }

    int8_t PeekInt8() const {
        assert(length() >= sizeof(int8_t));
        int8_t x = *data();
        return x;
    }

public:
    // data returns a pointer of length Buffer.length() holding the unread portion of the buffer.
    // The data is valid for use only until the next buffer modification (that is,
    // only until the next call to a method like Read, Write, Reset, or Truncate).
    // The data aliases the buffer content at least until the next buffer modification,
    // so immediate changes to the slice will affect the result of future reads.
    const char* data() const {
        return buffer_ + read_index_;
    }

    char* WriteBegin() {
        return begin() + write_index_;
    }

    const char* WriteBegin() const {
        return begin() + write_index_;
    }

    // length returns the number of bytes of the unread portion of the buffer
    size_t length() const {
        assert(write_index_ >= read_index_);
        return write_index_ - read_index_;
    }

    // size returns the number of bytes of the unread portion of the buffer.
    // It is the same as length().
    size_t size() const {
        return length();
    }

    // capacity returns the capacity of the buffer's underlying byte slice, that is, the
    // total space allocated for the buffer's data.
    size_t capacity() const {
        return capacity_;
    }

    size_t WritableBytes() const {
        assert(capacity_ >= write_index_);
        return capacity_ - write_index_;
    }

    size_t PrependableBytes() const {
        return read_index_;
    }

    // Helpers
public:
    const char* FindCRLF() const {
        const char* crlf = std::search(data(), WriteBegin(), kCRLF, kCRLF + 2);
        return crlf == WriteBegin() ? nullptr : crlf;
    }

    const char* FindCRLF(const char* start) const {
        assert(data() <= start);
        assert(start <= WriteBegin());
        const char* crlf = std::search(start, WriteBegin(), kCRLF, kCRLF + 2);
        return crlf == WriteBegin() ? nullptr : crlf;
    }

    const char* FindEOL() const {
        const void* eol = memchr(data(), '\n', length());
        return static_cast<const char*>(eol);
    }

    const char* FindEOL(const char* start) const {
        assert(data() <= start);
        assert(start <= WriteBegin());
        const void* eol = memchr(start, '\n', WriteBegin() - start);
        return static_cast<const char*>(eol);
    }
private:

    char* begin() {
        return buffer_;
    }

    const char* begin() const {
        return buffer_;
    }

    void grow(size_t len) {
        if (WritableBytes() + PrependableBytes() < len + reserved_prepend_size_) {
            //grow the capacity
            size_t n = (capacity_ << 1) + len;
            size_t m = length();
            char* d = new char[n];
            memcpy(d + reserved_prepend_size_, begin() + read_index_, m);
            write_index_ = m + reserved_prepend_size_;
            read_index_ = reserved_prepend_size_;
            capacity_ = n;
            delete[] buffer_;
            buffer_ = d;
        } else {
            // move readable data to the front, make space inside buffer
            assert(reserved_prepend_size_ < read_index_);
            size_t readable = length();
            memmove(begin() + reserved_prepend_size_, begin() + read_index_, length());
            read_index_ = reserved_prepend_size_;
            write_index_ = read_index_ + readable;
            assert(readable == length());
            assert(WritableBytes() >= len);
        }
    }
private:
    char* buffer_;
    size_t capacity_;
    size_t read_index_;
    size_t write_index_;
    size_t reserved_prepend_size_;
    static const char kCRLF[];
};
```
上面是Buffer的构造，但是，这里只需要先了解Buffer是一个支持右值引用的char型数组类。


## http
