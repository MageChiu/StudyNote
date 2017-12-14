/*
 * =====================================================================================
 *
 *       Filename:  ALG476_NumberComplement.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年09月02日 23时39分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Charles Chiu (), charles.r.chiu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include<iostream>

using namespace std;

class Solution {
public:
    int findComplement(int num) {
        int a = 1;
        int ret=0;
        while(a<num)
        {
            a=(a<<1 | 1);
        }
        ret = a ^ num;
        return ret;
    }
};



int main()
{
    int test;
    Solution so;
    while(cin>>test)
    {
        cout << "test: input[" << test << "] output [" << so.findComplement(test) << "]"<< endl;
    }
    return 0;
}