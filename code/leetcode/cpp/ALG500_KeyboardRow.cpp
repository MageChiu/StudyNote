/*
 * =====================================================================================
 *
 *       Filename:  ALG500_KeyboardRow.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年09月05日 01时15分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Charles Chiu (), charles.r.chiu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <set>
#include <string>

#include <vector>

using namespace std;

class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        set<char> tmp[3];
        tmp[0] = {'q','w','e','r','t','y','u','i','o','p','Q','W','E','R','T','Y','U','I','O','P'};
        tmp[1] = {'a','s','d','f','g','h','j','k','l','A','S','D','F','G','H','J','K','L'};
        tmp[2] = {'z','x','c','v','b','n','m','Z','X','C','V','B','N','M'};
        int flag = -1;
        int sel = 0;
        vector<string> ret;
        ret.reserve(words.size());
        for(int i = 0; i<words.size(); ++i)
        {
            sel = 1;
            for(flag = 0; flag <3; flag++)
            {
                if(tmp[flag].find(words[i][0])!=tmp[flag].end())
                {
                    break;
                }
            }
            if(flag == 3)
            {
                continue;
            }
            for(int j = 1; j<words[i].size(); j++)
            {
                if(tmp[flag].find(words[i][j])==tmp[flag].end())
                {
                    sel = 0;
                    break;
                }
            }
            if(sel ==1)
            {
                ret.push_back(words[i]);
            }
        }
        return ret;
    }
};


int main()
{
    vector<string> test = {"Hello", "Alaska", "Dad", "Peace"};
    Solution so;
    vector<string> res = so.findWords(test);
    for(int i = 0 ; i < res.size(); ++i)
    {
        cout << res[i].c_str() << endl;
    }
    return 0;
}