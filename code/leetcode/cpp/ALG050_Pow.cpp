/*
 * =====================================================================================
 *
 *       Filename:  ALG050_Pow.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年09月13日 16时21分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Charles Chiu (), charles.r.chiu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>


using namespace std;
class Solution {
public:
    double myPow(double x, int n) {
        return _myPow(x,n);
    }
    double _myPow(double x, long long n) {
        if(x == 0) return 0;
        if(n<0) return _myPow(1.0/x, 0-n);
        if(n==0) return 1;
        else if(n == 1) return x;
        if((n&1)>0){
            return x*_myPow(x*x,n>>1);
        }
        else
        {
            return _myPow(x*x,n>>1);
        }
    }
};

int main()
{
    double x = 1.00000;
    int n = -2147483648;
    Solution so;
    cout << so.myPow(x,n) << endl;
}

