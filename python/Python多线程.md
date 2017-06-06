<!-- TOC -->

- [threadingģ��](#threadingģ��)
- [Thread��](#thread��)
    - [1������һ��Thread��ʵ����������һ������](#1����һ��thread��ʵ��������һ������)
    - [2������һ��Thread��ʵ����������һ���ɵ��õ������](#2����һ��thread��ʵ��������һ���ɵ��õ������)
    - [3����Thread������һ�����࣬������������ʵ����](#3��thread������һ�����ഴ����������ʵ��)

<!-- /TOC -->

Python�Ķ��߳�Ҫ��C++�Ķ��̼߳�һЩ����ȻC++11�Ķ��߳��Ѿ�ʵ���˿�ƽ̨��������Ի��ǱȽ��鷳��

Python�����ǵ�ִ����ͨ��Python����������Ƶġ���Python������ķ�����ȫ�ֽ���������global interpreter lock��GIL�������ƣ�������ܹ���֤��ǰֻ����һ���߳��ڱ����У��ڶ��̻߳����£�Python������������µķ�������ִ�У�
1������GIL
2�����л���һ���߳�ȥִ��
3�������У�
            a����ָ���������ֽ����ָ��
            b�����߳������ó����ƣ����Ե���time.sleep��0������
4�������߳�����Ϊ˯��״̬
5��������GIL
6���ٴ��ظ��������в���
�ڵ����ⲿ���루��C++��չ��������ʱ��GIL���ᱻ������ֱ�������������Ϊֹ������������ڼ�û��Python���ֽ��뱻���У����治�����߳��л�������д��չ�ĳ���Ա������������GIL

# threadingģ��

Python�ṩ�˼������ڹ����̵߳�ģ�飬����thread��threading��Queue�ȡ�thread��threadingģ���������Ա�����͹�ϵ�̣߳�Queue����������һ�������ڶ���߳�֮�乲�����ݵĶ������ݽṹ��
���ｨ��ʹ��threading������ʹ��thread��threadģ�������߳��˳���ʱ�������߳�û������ͱ��˳��ˣ���threadingģ����ᱣ�����С���Ҫ�������̡߳�
threading�����ṩ��Thread�࣬���ṩ�˸��ַǳ����õ�ͬ�����ơ�

# Thread��

threading��Thread������Python����Ҫ�����ж��󡣾��кܶ�threadģ����û�еĺ�����ͨ��Thread�����̵߳ķ��������֣�

## 1������һ��Thread��ʵ����������һ������

``` python
"""
@author: Charles Chiu
@contact: charles.r.chiu@gmail.com
@software: PyCharm Community Edition
@project name: ExThreading
@file: mtsleep3.py
@time: 2016/4/20 2:50
"""
import threading
from  time import  sleep,ctime
loops = [4,2]
def loop(nloop, nsec):
    print('start loop ',nloop,' at: ',ctime())
    sleep(nsec)
    print('loop ',nloop,' done at: ',ctime())
    return None
def main():
    print('main start at: ', ctime())
    threads = []
    nloops = range(len(loops))
    for i in nloops:
        t = threading.Thread(target=loop,
                             args=(i, loops[i]))
        threads.append(t)
    print(""" ���ø����̵߳�start���� at """, ctime())
    for i in nloops:
        threads[i].start()
    ''' ���� ��ʹ����join���������Եȴ����������������һЩ������������Ҫ��ɵ�����'''
    print('*'*40, ctime(), '*'*40)
    """ ����ʹ��join��������ȵ��߳̽��������ڸ���timeout������ʱ�򣬵ȵ���ʱλ�� """
    for i in nloops:
        threads[i].join()
    print('all done at: ', ctime())
if __name__ == '__main__':
    main()
```

����ͨ�������������threadingģ���Thread��

## 2������һ��Thread��ʵ����������һ���ɵ��õ������

``` python
"""
@author: Charles Chiu
@contact: charles.r.chiu@gmail.com
@software: PyCharm Community Edition
@project name: ExThreading
@file: mtsleep4.py
@time: 2016/4/20 15:42
"""
import threading
from time import sleep,ctime
loops = [4,2]
class ThreadFunc(object):
    def __init__(self, func, args, name = ''):
        self.name = name
        self.func = func
        self.args = args
    def __call__(self):
        self.res = self.func(*self.args)
def loop(nloop, nsec):
    print('start loop ',nloop,' at: ',ctime())
    sleep(nsec)
    print('loop ',nloop,' done at: ',ctime())
    return None
def main():
    print('main start at: ', ctime())
    threads = []
    nloops = range(len(loops))
    for i in nloops:
        t = threading.Thread(target=ThreadFunc(loop,(i,loops[i]),loop.__name__))
        threads.append(t)
    print(""" ���ø����̵߳�start���� at """, ctime())
    for i in nloops:
        threads[i].start()
    ''' ���� ��ʹ����join���������Եȴ����������������һЩ������������Ҫ��ɵ�����'''
    print('*' * 40, ctime(), '*' * 40)
    """ ����ʹ��join��������ȵ��߳̽��������ڸ���timeout������ʱ�򣬵ȵ���ʱλ�� """
    for i in nloops:
        threads[i].join()
    print('all done at: ', ctime())
if __name__ == '__main__':
    main()
```

����

## 3����Thread������һ�����࣬������������ʵ����

``` python
"""
@author: Charles Chiu
@contact: charles.r.chiu@gmail.com
@software: PyCharm Community Edition
@project name: ExThreading
@file: mtsleep5.py
@time: 2016/4/20 15:53
"""
import threading
from  time import ctime,sleep
loops = [4,2]
class MyThread(threading.Thread):
    def __init__(self, func, args, name=''):
        threading.Thread.__init__(self)
        self.name = name
        self.func = func
        self.args = args
    def run(self):
        self.res = self.func(*self.args)
    def getResult(self):
        return self.res
def loop(nloop, nsec):
    print('start loop ', nloop, ' at: ', ctime())
    sleep(nsec)
    print('loop ', nloop, ' done at: ', ctime())
    return None
def main():
    print('main start at: ', ctime())
    threads = []
    nloops = range(len(loops))
    for i in nloops:
        t = MyThread(loop, (i, loops[i]), loop.__name__)
        threads.append(t)
    print(""" ���ø����̵߳�start���� at """, ctime())
    for i in nloops:
        threads[i].start()
    ''' ���� ��ʹ����join���������Եȴ����������������һЩ������������Ҫ��ɵ�����'''
    print('*' * 40, ctime(), '*' * 40)
    """ ����ʹ��join��������ȵ��߳̽��������ڸ���timeout������ʱ�򣬵ȵ���ʱλ�� """
    for i in nloops:
        threads[i].join()
        print(threads[i].getResult())
    print('all done at: ', ctime())
if __name__ == '__main__':
    main()
```

���������ֲ�ͬ�߳�������ʽ









