# OAuth 运行流程

``` sequence
Client --> User: (A)Authorization Request
User ->> Client: (B)Authorization Grant 

Client -->> Authorization Server: (C)Authorization Grant 
Authorization Server -->> Client: (D)Access Token

Client -->> Resource Server: (E)Access Token
Resource Server --> Client: (F)Protected Resource

```

- （A）用户打开客户端以后，客户端要求用户给予授权。
- （B）用户同意给予客户端授权。
- （C）客户端使用上一步获得的授权，向认证服务器申请令牌。
- （D）认证服务器对客户端进行认证以后，确认无误，同意发放令牌。
- （E）客户端使用令牌，向资源服务器申请获取资源。
- （F）资源服务器确认令牌无误，同意向客户端开放资源。

OAuth 2.0有四种模式：
- 授权码模式（authorization code）
- 简化模式（implicit）
- 密码模式（resource owner password credentials）
- 客户端模式（client credentials）

## 授权码模式
授权码模式（authorization code）是功能最完整、流程最严密的授权模式。它的特点就是通过客户端的后台服务器，与"服务提供商"的认证服务器进行互动。
``` sequence
User->>Client:  
User-->
Client-->app: 获取机构的成功失败次数
app-->redis: 记录机构情况
redis-->conllectorsvr: 获取机构当前信息
```




> http://www.ruanyifeng.com/blog/2014/05/oauth_2_0.html   
> https://oauth.net/2/