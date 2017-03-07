# 常用证书转化命令

## pem ==> der

```shell
openssl x509 -outform der -in client.pem -out client.der
```


# Other
## 查看证书命令
```shell
openssl x509 -in client.pem -noout -text
```

# 生成ecc证书

生成ecc CA证书
``` shell
openssl ecparam -out EccCA.key -name prime256v1 -genkey
openssl req -key EccCA.key -new -out EccCA.req
openssl x509 -req -in EccCA.req -signkey EccCA.key -out EccCA.pem
```

生成使用证书
``` shell
openssl ecparam -out EccSite.key -name prime256v1 -genkey
openssl req -config openssl.cnf -key EccSite.key -new -out EccSite.req
```

签发证书
``` shell
openssl x509 -req -in EccSite.req -CA EccCA.pem -CAkey EccCA.key -out EccSite.pem -CAcreateserial
```

