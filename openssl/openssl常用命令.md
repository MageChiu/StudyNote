生成RSA密钥的方法

``` shell
openssl genrsa -des3 -out privkey.pem 2048
```

这个命令会生成一个2048位的密钥，同时有一个des3方法加密的密码，如果你不想要每次都输入密码，可以改成：

``` shell
openssl genrsa -out privkey.pem 2048
```

建议用2048位密钥，少于此可能会不安全或很快将不安全。

2、生成一个证书请求

``` shell
openssl req -new -key privkey.pem -out cert.csr
```

这个命令将会生成一个证书请求，当然，用到了前面生成的密钥privkey.pem文件 这里将生成一个新的文件cert.csr，即一个证书请求文件，你可以拿着这个文件去数字证书颁发机构（即CA）申请一个数字证书。CA会给你一个新的文件cacert.pem，那才是你的数字证书。

如果是自己做测试，那么证书的申请机构和颁发机构都是自己。就可以用下面这个命令来生成证书：

``` shell
openssl req -new -x509 -key privkey.pem -out cacert.pem -days 1095
```


这个命令将用上面生成的密钥privkey.pem生成一个数字证书cacert.pem

配置nginx

``` shell
server
{
	listen 443;
	ssl on;
	ssl_certificate /var/www/sslkey/cacert.pem;
	ssl_certificate_key /var/www/sslkey/privkey.pem;
	server_name 192.168.1.1;
	index index.html index.htm index.php;
	root /var/www/test;
}
```

下面是生成双向验证的例子，步骤和之前的差不多

一、服务器端证书生成

1、生成服务器端的私钥

openssl genrsa -des3 -out server.key 2048

 

命令完成后会提示让输入密码，这个密码是通过des3（也可以采用其他加密算法）加密此密钥文件的，如果其他程序需要读取这个文件，需要输入密码

openssl rsa -in server.key -out server.key

执行这个命令后，NGINX引用此文件不需要输入密码

2、通过server.key生成证书

openssl req -new -key server.key -out server.csr

 

按照相关提示，填入证书相关基本信息，生成的证书通过CA签名后形成服务端自己的证书

（Certificate Signing Request（CSR））

二、客户端证书生成

1、生成客户端私钥

 openssl genrsa -des3 -out client.key 2048

2、通过client.key生成客户端证书

openssl req -new -key client.key -out client.csr

三、自签名

生成的csr文件必须要经过CA签名才能形成自己的证书，我们可以通过第三方权威认证机构进行签名，但是这个需要收费，我们制作自签名根证书

1、制作ca key文件和ca根证书

openssl req -new -x509 -keyout ca.key -out ca.crt

2、签署证书配置文件

查看/etc/pki/tls/openssl.cnf文件 ，查看dir是不是指向dir= /etc/pki/CA 如果不是，请修改

 

touch /etc/pki/CA/{index.txt,serial}

这个是根据openssl.cnf中的配置,要求生成的文件

----------------------------------

 

dir             = /etc/pki/CA           # Where everything is kept

certs           = $dir/certs            # Where the issued certs are kept

crl_dir         = $dir/crl              # Where the issued crl are kept

database        = $dir/index.txt        # database index file.

-------------------------------

echo 01 > /etc/pki/CA/serial

3、用第一步制作的证书，对服务器证书和客户端证书进行签名

 openssl ca -in server.csr -out server.crt -cert ca.crt -keyfile ca.key

 

 openssl ca -in client.csr -out client.crt -cert ca.crt -keyfile ca.key

 至此证书签名已经全部完毕。

四、证书导出

        由于我们生成的客户端证书是需要用在各个地方的，例如在浏览器中，在IOS和Android中，需要做相应的转换才能安装

        1、导出浏览器可以安装的证书

        openssl pkcs12 -export -clcerts -in client.crt -inkey client.key -out client.p12

        2、导出Android可以安装的证书

        openssl pkcs12 -export -in client.crt -inkey client.key -out  client.pfx

        3、导出IOS可以安装的证书

        openssl x509 -in client.crt -out client.cer
        
        另外IE也可以安装.pfx格式的证书
        
        以上步骤有些需要输入密码，密码就是我们刚才在生成客户端和浏览器端证书时的密码，密码千万必要忘记，忘记了只能重新生成
        
        client使用的文件有：ca.crt,client.crt,client.key,client.pfx
        server使用的文件有：ca.crt, server.crt,server.key

五、nginx Https双向校验配置

    修改nginx.conf文件
``` shell
     server {
        listen       443 ssl;                                                    #https默认端口
        root /var/www/src;
        ssl on;                                                                                #开启https校验
        ssl_certificate ssl/server.crt;                                #服务端证书            
        ssl_certificate_key ssl/server.key;                        #服务端key
        #ssl_client_certificate ssl/client/client.crt;#客户端证书，不需要根证书的时候可以使用
        ssl_client_certificate ssl/ca.crt;                        #客户端签发的ca证书
        ssl_verify_client on;                                                    #开启对客户端的校验，这个地方是就是开启双向校验的地方

       ssl_session_cache    shared:SSL:1m;
        ssl_session_timeout  5m;

        ssl_ciphers  HIGH:!aNULL:!MD5;
        ssl_prefer_server_ciphers  on;
    }
```

配置完成以后    nginx -s reload 使之生效

六、使用

    把相关证书导入到相应的客户端，例如在IE下，需要把根证书ca.crt安装到受信任的证书颁发机构
client.crt(client.pfx) 安装到个人证书的位置
然后打开我们需要访问的地址https://xxx.xxx.xxx.xx能正确的打开页面即代表成功
在打开的时候，浏览器会询问，1、证书确认，2、需要凭据（是否允许此应用访问您的私钥）
以上点击确认和允许即可

 

(ps：接下来我会一些脚本直接把以上带颜色的命令进行生成)

七、自动化脚本

通过以上命令，我写了一个shell脚本，可以快速的生成我们需要的证书，由于不能上传附件，所以写的shell文件就不能上传上来了，贴上具体的脚本代码，还请读者复制到自己的文件中然后进行运行即可

1、脚本代码

``` shell
#!/bin/sh
# create self-signed server certificate:
read -p "请输入证书的域 例如[www.example.com or 192.168.1.52]: " DOMAIN

SUBJECT="/C=CN/ST=BJ/L=BJ/O=bky/CN=$DOMAIN"

echo "创建服务器证书..."

openssl genrsa -des3 -out server.key 2048
openssl rsa -in server.key -out server.key

openssl req -new -subj $SUBJECT -key server.key -out server.csr

echo "创建客户端证书..."
openssl genrsa -des3 -out client.key 2048
openssl req -new -subj $SUBJECT -key client.key -out client.csr

echo "创建根证书..."
openssl req -new -x509 -keyout ca.key -out ca.crt

rm -rf /etc/pki/CA/index.txt
rm -rf /etc/pki/CA/serial
touch /etc/pki/CA/{index.txt,serial}
echo 01 > /etc/pki/CA/serial

echo "用根证书对服务器证书和客户端证书签名"
openssl ca -in server.csr -out server.crt -cert ca.crt -keyfile ca.key
openssl ca -in client.csr -out client.crt -cert ca.crt -keyfile ca.key

echo "导出服务器证书和客户端证书"
openssl pkcs12 -export -clcerts -in client.crt -inkey client.key -out client.p12
openssl pkcs12 -export -in client.crt -inkey client.key -out  client.pfx
openssl x509 -in client.crt -out client.cer
openssl x509 -in server.crt -out server.cer


echo "把以上生成的文件copy到nginx conf文件的ssl目录下面，如果ssl目录不存在请创建"
echo "接下请配置nginx.conf操作:"
echo " server {																						"
echo " 			...                                           "
echo "     ssl on;                                        "
echo "     ssl_certificate ssl/server.crt;                "
echo "     ssl_certificate_key ssl/server.key;            "
echo "     ssl_client_certificate ssl/ca.crt;             "
echo "     ssl_verify_client on;                          "
echo "			...                                           "
echo "     }                                               "
echo "使用如下命令重新加载nginx配置"
echo "nginx -s reload"
```


## 第二个例子

一、准备证书

0. 前期准备工作

``` shell
cd ~/
mkdir ssl
cd ssl
mkdir demoCA
cd demoCA
mkdir newcerts
mkdir private
touch index.txt
echo '01' > serial
```

1. 制件 CA 证书

生成 CA 私钥: ca.key

`openssl genrsa -des3 -out ca.key 2048`
这样是生成 rsa 私钥，`des3` 算法，openssl 格式，2048 位强度。`ca.key` 是密钥文件名。为了生成这样的密钥，需要一个至少四位的密码。另外可以通过以下方法生成没有密码的key:

`openssl rsa -in ca.key -out ca_decrypted.key`
生成 CA 根证书的公钥 ca.crt：

`openssl req -new -x509 -days 3650 -key ca.key -out ca.crt`
2. 制作网站的 https 证书，并用 CA 签名认证

假设我们需要为 abc.com 域名制作证书

先生成 abc.com 的证书私钥 abc.com.pem

`openssl genrsa -des3 -out abc.com.pem 1024`
无密码的私钥

`openssl rsa -in abc.com.pem -out abc.com.key`
生成 csr 签名请求

`openssl req -new -key abc.com.pem -out abc.com.csr`
这里需要输入国家，地区，组织，email等。最重要的是 **common name**，可以写你的名字或者域名。如果为了 https 申请，这个必须和域名一样，即，这里要写 abc.com，否则会引发浏览器警报，这里可以用 *.abc.com 来做泛域名证书。

最后，需要用 CA 证书进行签名：

`openssl ca -policy policy_anything -days 1460 -cert ./demoCA/ca.crt -keyfile ./demoCA/ca.key -in abc.com.csr -out abc.com.crt`
这样网站的 https 证书就做完了。

还有一步就是把 ca.crt 的内容追加到 abc.com.crt 后面，因为有些浏览似乎不支持。

cat demoCA/ca.crt >> abc.com.crt
nginx 配置

加入配置内容：

``` shell
server {
	listen 443;
	server_name abc.com www.abc.com;

	root html;
	index index.html index.htm;

	ssl on; 
	ssl_certificate /PATH/TO/abc.com.crt;
	ssl_certificate_key /PATH/TO/abc.com.key;

	ssl_session_timeout 5m;

	ssl_protocols SSLv3 TLSv1 TLSv1.1 TLSv1.2;
	ssl_ciphers "HIGH:!aNULL:!MD5 or HIGH:!aNULL:!MD5:!3DES";
	ssl_prefer_server_ciphers on;

	location / {
		try_files $uri $uri/ =404;
	}       
}
```
其它

其实很多时候，并不需要加密的 key，所以像这面这么做就好了。

``` shell
cd ~/
mkdir ssl
cd ssl
mkdir demoCA
cd demoCA
mkdir newcerts
mkdir private
touch index.txt
echo '01' > serial
openssl genrsa -out ca.key 2048
openssl req -new -x509 -days 3650 -key ca.key -out ca.crt
cd ..
openssl genrsa -out abc.com.key 2048
openssl req -new -key abc.com.key -out abc.com.csr
openssl ca  -policy policy_anything  -days 1460 -in abc.com.csr -out abc.com.crt -cert ./demoCA/ca.crt -keyfile ./demoCA/ca.key
````





## 下面是一个简单的例子

``` shell
cd ~/
mkdir ssl
cd ssl
mkdir demoCA
cd demoCA
mkdir newcerts
mkdir private
touch index.txt
echo '01' > serial
openssl genrsa -out ca.key 2048
openssl req -new -x509 -days 3650 -key ca.key -out ca.crt
cd ..
openssl genrsa -out abc.com.key 2048
openssl req -new -key abc.com.key -out abc.com.csr
openssl ca  -policy policy_anything  -days 1460 -in abc.com.csr -out abc.com.crt -cert ./demoCA/ca.crt -keyfile ./demoCA/ca.key
```


