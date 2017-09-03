/*
 * =====================================================================================
 *
 *       Filename:  ALG575_DistributeCandies.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年09月03日 16时50分22秒
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
#include <set>

using namespace std;


class Solution {
public:
    int distributeCandies(vector<int>& candies) {
        int nLen = candies.size();
        set<int> tmp;
        for(int i = 0; i < nLen; i++)
        {
            tmp.insert(candies[i]);
        }
        if(tmp.size()<nLen/2)
        {
            return tmp.size();
        }
        else
        {
            return nLen/2;
        }
    }
};





int main()
{
    vector<int> test = {1,1,2,3 };
    Solution so;
    cout << so.distributeCandies(test) << endl;
    return 0;
}
