
#





# 负载均衡配置

Nginx支持四种负载均衡配置:
1. 轮训(默认)
    每个请求按时间顺序逐一分配哦
2. weight
3. ip_hash
    采用这种方式
4. fair
5. url_hash

在http端加入下面的配置
```
upstream servers.chiu.com {
    server ip1:port1;
    server ip2:port2;
    server ip3:port3;
}
```
然后在
