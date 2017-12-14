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

这里的prime256v1

## 生成RSA算法证书
首先是一个脚本的示例
``` shell
#########################################################################
# File Name: CreateCA.sh
# Author: Charles Chiu
# mail: charles.r.chiu@gmail.com
# Created Time: 2017年02月17日 星期五 15时31分52秒
#########################################################################
#!/bin/bash

CA_Name=$1
Client=$2
CAName=${CA_Name}CA
CName=$Client
SUBJECT="/C=CN/ST=BJ/L=BJ/O=bky"
mkdir -p demoCA/newcerts
touch ./demoCA/index.txt
echo 01 > ./demoCA/serial
openssl genrsa -des3 -out ${CAName}.key 2048
openssl req -new -x509 -key ${CAName}.key -out ${CAName}.crt

# 生成client证书
openssl genrsa -des3 -out ${CName}.key 2048
openssl req -new -key ${CName}.key -out ${CName}.csr

# 
openssl ca -in ${CName}.csr -out ${CName}.crt -cert ${CAName}.crt -keyfile ${CAName}.key 

openssl pkcs12 -export -in ${CName}.crt -inkey ${CName}.key -out ${CName}.pfx
openssl pkcs12 -in ${CName}.pfx -out ${CName}.pem 
openssl x509 -outform der -in ${CName}.pem -out ${CName}.der

openssl pkcs12 -export -in ${CAName}.crt -inkey ${CAName}.key -out ${CAName}.pfx
openssl pkcs12 -in ${CAName}.pfx -out ${CAName}.pem
openssl x509 -outform der -in ${CAName}.pem -out ${CAName}.der


```

下面是详细的单步步骤：

``` shell
SUBJECT="/C=CN/ST=BJ/L=BJ/O=bky"
# 生成CA证书
mkdir -p demoCA/newcerts
touch ./demoCA/index.txt
echo 01 > ./demoCA/serial
openssl genrsa -des3 -out serverCA.key 2048
openssl req -new -x509 -key serverCA.key -out serverCA.crt

# 生成client证书
openssl genrsa -des3 -out serverssl.key 2048
openssl req -new -key serverssl.key -out serverssl.csr


# 签发证书
openssl ca -in serverssl.csr -out serverssl.crt -cert serverCA.crt -keyfile serverCA.key 

# 格式转化
# serverssl格式转化
openssl pkcs12 -export -in serverssl.crt -inkey serverssl.key -out serverssl.pfx
openssl pkcs12 -in serverssl.pfx -out serverssl.pem 
openssl x509 -outform der -in serverssl.pem -out serverssl.der
# servereCA格式转换
openssl pkcs12 -export -in serverCA.crt -inkey serverCA.key -out serverCA.pfx
openssl pkcs12 -in serverCA.pfx -out serverCA.pem
openssl x509 -outform der -in serverCA.pem -out serverCA.der
```

