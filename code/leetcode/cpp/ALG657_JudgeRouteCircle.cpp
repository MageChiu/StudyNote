/*
 * =====================================================================================
 *
 *       Filename:  ALG657_JudgeRouteCircle.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年09月03日 00时51分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Charles Chiu (), charles.r.chiu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


/**************************
 *
 *
 *
 *
 * ******************************/


#include <iostream>

#include <string>
using namespace std;



class Solution {
public:
    bool judgeCircle(string moves) {
        int x=0,y=0;
        int n = moves.size();
        for(int i =0 ;i < n; i++)
        {
            if(abs(x)> n /2 || abs(y)>n/2)
            {
                return false;
            }
            if(moves[i]=='U')
            {
                y++;
            }
            else if(moves[i]=='D')
            {
                y--;
            }
            else if(moves[i]=='L')
            {
                x--;
            }
            else if(moves[i]=='R')
            {
                x++;
            }

        }
        if(x==0&&y==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};






int main()
{
    return 0;
}
