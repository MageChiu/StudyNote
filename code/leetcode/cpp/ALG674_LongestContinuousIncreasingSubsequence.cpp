/*
 * =====================================================================================
 *
 *       Filename:  ALG674_LongestContinuousIncreasingSubsequence.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年09月11日 17时09分31秒
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



using namespace std;


class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        vector<int> dp;
        int maxL = -1;
        int len = nums.size();
        if(len ==0) return 0;
        dp.resize(len+1,0);
        dp[0]=1;
        maxL = 1;
        for(int i = 1 ; i<len; ++i)
        {
            if(nums[i] > nums[i-1])
            {
                dp[i] = dp[i-1] +1 ;
            }
            else
            {
                dp[i] = 1;
            }
            if(dp[i]>maxL)
            {
                maxL = dp[i];
            }
        } 
        return maxL;
    }
};





int main()
{
    vector<int> test = { 1,3,5,4,7 };
    vector<int> test2 = {1,3,5,4,2,3,4,5};
    Solution so;
    cout << "test1 :" << so.findLengthOfLCIS(test) << endl;
    cout << "test2 :" << so.findLengthOfLCIS(test2) << endl;
    return 0 ; 
}

