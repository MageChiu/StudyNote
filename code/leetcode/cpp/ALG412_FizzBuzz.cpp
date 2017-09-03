/*
 * =====================================================================================
 *
 *       Filename:  ALG412_FizzBuzz.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年09月03日 17时02分18秒
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
#include <string>
#include <sstream>

using namespace std;


class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> ret;
        string str="";
        stringstream ss_stream;
        ret.reserve(n);
        for(int i=1;i<=n;++i)
        {
            if(i%15==0)
            {
                ret.push_back("FizzBuzz");
            }
            else
            {
                if(i%3==0)
                {
                    ret.push_back("Fizz");
                }
                else if(i%5==0)
                {
                    ret.push_back("Buzz");
                }
                else
                {
                    //cout << i << endl;
                    ss_stream.clear();
                    ss_stream << i;
                    ss_stream >> str;
                    ret.push_back(str);
                }
            }
        }
        return ret;
    }
};

int main()
{
    Solution so;
    int n =15;
    vector<string> res = so.fizzBuzz(n);
    for(int i =0 ;i<res.size();++i)
    {
        cout << res[i].c_str() << endl;
    }
    return 0;
}

