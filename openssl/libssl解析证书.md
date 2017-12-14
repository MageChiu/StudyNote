# C语言解析证书
主要函数
1、  DER编码转换为内部结构函数
X509 *d2i_X509(X509 **cert, unsigned char **d, int len);
函数功能：把一个DER编码的证书数据转化成OpenSSL内部结构体。
参数：cert：[OUT]X509结构体。 D：[IN]DER编码的证书数据指针地址。Len证书数据长度；
返回值：编码后的X509结构体数据
2、  获得证书版本函数X509_get_version
#define X509_get_version(x)  ASN1_INTEGER_get((x)->cert_info->version)
参数：x：[IN]X509*结构体数据结构。
返回值：证书版本，数据类型“LONG”
3、  获得证书序列号函数
ASN1_INTEGER *X509_get_serialNumber(X509 *x);
返回值：证书序列号，数据类型“ASN1_INTEGER”.
4、  获得证书颁发者信息函数
X509_NAME *X509_get_issuer_name(X509 *a);
注*：X509_NAME结构体包括多个X509_NAME_ENTRY结构体。X509_NAME_ENTRY保存了颁发者的信息，这些信息包括对象和值（object 和value）。对象的类型包括国家、通用名、单位、组织、地区、邮件等。
5、  获得证书拥有者信息函数
X509_NAME *X509_get_subject_name(X509 *a);
6、  获得证书有效期的起始日期函数
#define X509_get_notBefore(x)        ((x)->cert_info->validity->notBefore)
返回值：证书起始有效期，数据类型“ASN1_TIME”
7、  获得证书有效期的终止日期函数
#define X509_get_notAfter(x)           ((x)->cert_info->validity->notAfter)
8、  获得证书公钥函数
EVP_PKEY *X509_get_pubkey(X509 *x);
9、  创建和释放证书存储区
X509_STORE *X509_STORE_new(void);
Void X509_STORE_free(X509_STORE *v);
函数功能：创建和释放一个X509_STORE结构体，主要用于验证证书。
10、向证书存储区添加证书
Int X509_STORE_add_cert(X509_STORE *ctx, X509 *x);
函数功能：添加信任的根证书到证书存储区。
返回值：1成功，否则为0
11、向证书存储区添加证书吊销列表
Int X509_STORE_add_crl(X509_STORE *ctx, X509_CRL *x);
功能：添加CRL到证书存储区。
参数：x：证书吊销列表。Ctx：证书存储区。
返回值：1成功，否则为0。
12、创建证书存储区上下文环境函数
         X509_STORE_CTX *X509_STORE_CTX_new(void);
返回值：操作成功返回证书存储区上下文环境指针，否则返回NULL。
13、释放证书存储区上下文环境
         Void X509_STORE_CTX_free(X509_STORE_CTX *ctx);
14、初始化证书存储区上下文环境函数
         Int X509_STORE_CTX_init(X509_STORE_CTX *ctx, X509_STORE *store, X509 *x509, STACK_OF(X509) *chain);
函数功能：初始化证书存储区上下文环境，设置根证书、待验证的证书、CA证书链。
15、验证证书函数
         Int X509_verify_cert(X509_STORE_CTX *ctx);
返回值：验证成功返回1，否则返回0