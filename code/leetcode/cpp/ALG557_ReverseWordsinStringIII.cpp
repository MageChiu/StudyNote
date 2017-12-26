/*
 * =====================================================================================
 *
 *       Filename:  ALG557_ReverseWordsinStringIII.cpp
 *
 *    Description:  ALG557_ReverseWordsinStringIII.cpp
 *
 *        Version:  1.0
 *        Created:  2017年12月19日 15时37分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Charles Chiu (), charles.r.chiu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        int len = s.length();
        if (len <= 1)
        {
            return s;
        }
        string ret(s);
        int i = 0;
        while(i<len)
        {
            int k = i;
            while(s[i] !=0 && s[i]!= ' ')
            {
                ++i;
            }
            int j = i-1;
            int w = k;
            while(j>=k)
            {
                ret[w] = s[j];
                w++;
                j--; 
            }
            ret [i] = s[i];
            i++;
        }
        return ret;
    }
};

int main()
{
    string test_str = "Let's take LeetCode contest";
    Solution so;
    string ret = so.reverseWords(test_str);
    cout << ret << endl;
    return 0;
}

