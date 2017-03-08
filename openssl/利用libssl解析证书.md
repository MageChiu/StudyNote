# C语言 利用openssl解析证书
最近在完成一个利用openssl对证书进行解析的工作，因此总结一些需要注意的问题，和一些流程上的问题。

## 注意的地方
1. 之前在做pem和cer证书解析的时候时候都没有问题，但是在解析p12证书的时候一直生成的X509结构为空，在查询了资料以后，发现需在增加下面的代码：

```C
OpenSSL_add_all_algorithms();
ERR_load_crypto_strings();
```

上面的`OpenSSL_add_all_algorithms()`函数主要是用来加载算法函数和单向三列算法函数

``` C
void OpenSSL_add_all_algorithms(void)
{
    OpenSSL_add_all_ciphers();  /* 加载加密算法 */
    OpenSSL_add_all_digests(); /* 加载单向散列函数 */
}
```

其中void OpenSSL_add_all_ciphers(void)函数实现如下:

``` C

```


## 解析的流程

这里主要是针对证书进行解析，我的思路是将证书读入到X509结构中，通过解析X509结构，完成对证书的解析

### 从`cer/der`格式证书获取X509格式

这里我们思考两种方式，一种是从文件指针中直接获取，一种是从字符流中获取。

``` C
unsigned char derRootCert[4096];  
unsigned long derRooCertLen;  
X509 *rootCert = NULL;   
unsigned char *pTmp = NULL;
FILE *fp = fopen(certPath,"rb");
if(fp == NULL){  
    perror("open file failed\n");  
    return -1;  
} 
derRooCertLen = fread(derRootCert,1,4096,fp);  
pTmp =  derRootCert;  
rootCert = d2i_X509(NULL,(unsigned const char **)&pTmp,derRooCertLen); 
```
certPath为证书的路径



### 从`crt/pem`格式证书获取X509格式

### 从`p12/pfx`格式证书获取X509格式


### 解析X509结构

#### 获取version

#### 获取序列号

#### 获取有效时间


#### 获取公钥

这里常用的有四种加密算法，因此证书中的公钥也有四种形式进行存放形式：

1. RSA 结构rsa.h中，其中{n,e} 表示公钥，{n, d}表示私钥

``` C
struct rsa_st  
    {  
    .....  
    BIGNUM *n;  
    BIGNUM *e;  
    BIGNUM *d;  
    BIGNUM *p;  
    BIGNUM *q;  
    BIGNUM *dmp1;  
    BIGNUM *dmq1;  
    BIGNUM *iqmp;  
        .....  
    };  
```

2. DSA结构在dsa.h中

``` C
struct dsa_st  
    {  
    ......  
    BIGNUM *p;  
    BIGNUM *q;  /* == 20 */  
    BIGNUM *g;  
    BIGNUM *pub_key;  /* y public key */  
    BIGNUM *priv_key; /* x private key */  
        ......  
    }; 
```

3. ECC结构在ecc.h

``` C
struct ec_key_st {  
    EC_GROUP *group;  
    EC_POINT *pub_key;  
    BIGNUM   *priv_key;  
} /* EC_KEY */; 
```

4. DH结构体在dh.h中定义

``` C
struct dh_st  
    {
    BIGNUM *p;  
    BIGNUM *g;  
    long length; /* optional */  
    BIGNUM *pub_key;    /* g^x */  
    BIGNUM *priv_key;   /* x */  
    } 
```

5. EVP封装中的密钥结构EVP_PKEY

``` C
struct evp_pkey_st  
    {  
    int type;  
    int save_type;  
    int references;  
    const EVP_PKEY_ASN1_METHOD *ameth;  
    ENGINE *engine;  
    union   {  
        char *ptr;  
#ifndef OPENSSL_NO_RSA  
        struct rsa_st *rsa; /* RSA */  
#endif  
#ifndef OPENSSL_NO_DSA  
        struct dsa_st *dsa; /* DSA */  
#endif  
#ifndef OPENSSL_NO_DH  
        struct dh_st *dh;   /* DH */  
#endif  
#ifndef OPENSSL_NO_EC  
        struct ec_key_st *ec;   /* ECC */  
#endif  
        } pkey;  
    int save_parameters;  
    STACK_OF(X509_ATTRIBUTE) *attributes; /* [ 0 ] */  
    } /* EV  
```



``` C

```



``` C

```

## 常用的openssl证书解析函数

### `cer/der`常用解析函数




### `crt/pem`常用函数

### `p12/pfx`常用函数

