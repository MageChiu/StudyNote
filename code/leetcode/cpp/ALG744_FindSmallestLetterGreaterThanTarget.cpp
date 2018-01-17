/*
 * =====================================================================================
 *
 *       Filename:  ALG744_FindSmallestLetterGreaterThanTarget.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年01月17日 15时51分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Charles Chiu (), charles.r.chiu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include <iostream>
#include <vector>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



using namespace std;


class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        char ret = target;
        int min_dis = 26;
        int cur_dis = 0;
        for(int i = 0 ; i < letters.size(); i++)
        {
            //cur_dis = abs(letters[i]-target);
            cur_dis = (letters[i]-target +26 )%26;
            if(cur_dis !=0 && cur_dis<min_dis)
            {
                min_dis = cur_dis;
                ret = letters[i];
            }
        }
        return ret;
    }
};


int func(char ch)
{
    for(char c = 'a'; c <= 'z'; c++)
    {
        cout << c << " | " << (ch -c +26 +1)%26 << endl;
    }
    return 0;
}

int main()
{
    //func('c');
    vector<char> test = {'c', 'f', 'j'};
    Solution so;
    char ch ;
    while(cin>>ch)
    {
        cout << "Target:[" << ch << "] the return [" << so.nextGreatestLetter(test,ch) << "]" << endl;
    }
    return 0;
}

