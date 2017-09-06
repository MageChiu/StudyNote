/*
 * =====================================================================================
 *
 *       Filename:  ALG371_SumofTwoIntegers.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年09月07日 01时06分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Charles Chiu (), charles.r.chiu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

class Solution {
public:
    int getSum(int a, int b) {
        if (b == 0) return a;
        if( a ==0) return b;
        int x = a ^ b;
        int y = (a&b)<<1;

        return getSum(x,y);

    }
};


int main()
{
    int a = 13;
    int b = 14;
    Solution so;
    printf("[%d]+[%d]=[%d](ans is [%d])\n",a,b,so.getSum(a,b),a+b);
    return 0;
    

}