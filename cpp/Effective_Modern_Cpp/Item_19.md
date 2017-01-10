这里要提及的首先有三点：

 - shared_ptr是原始指针大小的两倍。 
 - 引用计数的内存必须被动态分配   
 - 引用计数的改变（increments and decrements）必须是原子的

使用如下代码：

```cpp
#include <memory>
#include <iostream>
using namespace std;
int main()
{
	int *rpw = new int(12);
	{
		shared_ptr<int> isptr1(rpw);
		cout << sizeof(rpw) << endl;
		cout << sizeof(isptr1) << endl;
	}
	system("pause");
    return 0;
}
```

在32bit的电脑上可以得到结果：

![sizeof(shared_ptr)](http://img.blog.csdn.net/20150905175639467)

明显看到验证了第一条。为什么会是两倍具体原因后面会分析

与unique_ptr类似，shared_ptr使用delete作为默认的资源析构函数，但是也可以使用用户自己提供的删除函数(deleter)。不过与unique_ptr不同的是，（unique_ptr的deleter是unique_ptr的类型的一部分）shared_ptr的deleter的类型不再是shared_ptr的类型的一部分。如下示例：

```cpp
	auto del1 = [](int *p) {
		cout << "del1" << endl;
		delete p;
	};
	auto del2 = [](int *p) {
		cout << "del2" << endl;
		delete p;
	};
	shared_ptr<int> isptr1(new int(12), del1);
	shared_ptr<int> isptr2(new int(10), del2);
	vector<shared_ptr<int>> vsptr{ isptr1,isptr2 };
```

这里的isptr1和isptr2的类型是一样的，而对于unique_ptr则不同：

```cpp
	auto del1 = [](int *p) {
		cout << "del1" << endl;
		delete p;
	};
	auto del2 = [](int *p) {
		cout << "del2" << endl;
		delete p;
	};
	unique_ptr<int, decltype(del1)> iuptr1(new int(12), del1);
	unique_ptr<int, decltype(del2)> iuptr2(new int(10), del2);
```
   这里的iuptr1和iuptr2是两种不同的类型。
       回到上面的分析中，为什么shared_ptr的大小是raw pointer的两倍的呢？原因主要是在shared_ptr的内部不只有一个类似原始指针的指向object的指针，还有一个指向Control Block的指针：
![Control Block](http://img.blog.csdn.net/20150905175541964)
如上所示，清晰的看到shared_ptr的sizeof返回值应该是2个指针的大小，其中一个指针指向需要指向的object，另外一个指针指向Control Block。Control Block中包含了对这个shared_ptr控制所必需的一些信息，包括引用计数Reference Count、Weak Count、以及在Other Data中会存放用户指定的deleter函数，分配器（allocator）等。所以从shared_ptr的开销角度来说，接下主要是讨论Control Block的创建已经创建带来的问题和Control Block的开销。
一般来说在三种情况下会创建Control Block

 - 通过raw pointer创建shared_ptr的时候 
 - 通过make_shared创建shared_ptr的时候
 - 通过unique_ptr转化创建shared_ptr的时候

上面三种情况都会创建Control Block，但是问题就出在这个Control Block上，稍后讨论该部分的开销。如果使用同一个raw pointer创建shared_ptr就会出现两个不同的shared_ptr指向同一个raw pointer指向的资源，但是有两个不同的Control Block，当一个的引用计数为0的时候，就会调用deleter释放该资源，那么当另一个shared_ptr也要释放该资源的时候就会发生释放已经被释放的资源的错误，如下所示：

```cpp
	int *rpw = new int(12);
	{
		shared_ptr<int> isptr1(rpw);
		shared_ptr<int> isptr2(rpw);
	}
```

显然这种错误是致命的，因为有可能是发生在析构函数中，接下来还会导致资源泄漏，原本我们是为了防止资源泄漏的。所以，这里建议尽我们在使用shared_ptr的时候应当避免使用raw pointer创建shared_ptr，也就是尽量避免。