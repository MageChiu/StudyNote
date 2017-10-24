# 目录


_____
<!-- TOC -->

- [目录](#%E7%9B%AE%E5%BD%95)
- [内部优化](#%E5%86%85%E9%83%A8%E4%BC%98%E5%8C%96)

<!-- /TOC -->

____



# 内部优化
优化点：
1. 将libcurl全局初始化函数调用位置从线程初始化函数中修改至进程初始化中
1. 调整机构监控服务agent统计数据来源


agent优化：
现有系统主要是通过从日志中获取机构的运行信息，获取日志信息是通过shell脚本从日志中捞取：
``` flow
st=>start: Start
e=>end: End
op1=>operation: Agent
op2=>operation: Collect


st->e


```

collectorsvr部署在mon（master）主机上
agent部署在app服务器上
``` sequence
collectorsvr-->agent: 统计机构信息
Note right of agent: 统计日志
agent-->collectorsvr: 返回统计的信息
Note left of collectorsvr: 记录数据库
```

``` sequence
redis-->app: 获取机构的成功失败次数
app-->redis: 记录机构情况
redis-->conllectorsvr: 获取机构当前信息
```
