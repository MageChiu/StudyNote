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



