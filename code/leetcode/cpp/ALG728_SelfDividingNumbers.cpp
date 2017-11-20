/*
 * =====================================================================================
 *
 *       Filename:  ALG728_SelfDividingNumbers.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年11月20日 15时57分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Charles Chiu (), charles.r.chiu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <vector>
#include <iostream>


using namespace std;

class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> ret ;
        if(right<left){
            return ret;
        }
        ret.reserve(right-left+1);
        for(int num = left; num <= right; ++num)
        {
            int flag = 1;
            int tag = num;
            while(tag>0)
            {
                int a = tag % 10;
                tag = tag /10;
                if(a==0 || num%a!=0)
                {
                    flag = 0;
                    break;
                }
            }
            if(flag == 1)
            {
                ret.push_back(num);
            }
        }
        return ret;
    }
};


int main()
{
    int l = 1;
    int r = 22;
    Solution so;
    vector<int> ret = so.selfDividingNumbers(l,r);
    for(int a : ret)
    {
        cout << a << " ";
    } 
    cout << endl;
    return 0;
}


