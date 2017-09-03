/*
 * =====================================================================================
 *
 *       Filename:  ALG461_HammingDistance.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年09月03日 15时23分50秒
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
    int hammingDistance(int x, int y) {
        int tmp = x^ y;
        int num = 0;
        while(tmp>0)
        {
            if((tmp & 1)==1)
                num++;
            tmp = tmp >> 1;
        }
        return num;
    }
};


int main(int argc,char* argv[])
{
    int x, y;
    Solution so;
    while(cin>>x>>y)
    {
        cout << "input x:[" << x<< "],y:["<< y<<"],output:["<<so.hammingDistance(x,y) << "]" << endl;
    }
    return 0;
}


