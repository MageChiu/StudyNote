/*
 * =====================================================================================
 *
 *       Filename:  ALG673_NumberOfLongestIncreasingSubsequence.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年09月11日 23时13分52秒
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
    int findNumberOfLIS(vector<int>& nums) {
        int cnt = 0;
        int maxL = 0;
        int maxCnt = 0;
        int nL = nums.size();
        vector<int> dp;
        if(nL == 0) return 0;
        dp.resize(nL+1,0);
        dp[0]=1;
        for(int i = 1; i < nL; ++i)
        {
            int j = i -1;
            dp[i] = 1;
            cnt = 1;
            while(j>=0)
            {
                if(nums[i]>nums[j]  )
                {
                    if(dp[i] < dp[j] +1)
                    {
                        dp[i]=dp[j]+1;
                        cnt = 1;
                    }
                    else if(dp[i] == dp[j]+1)
                    {
                        cnt++;
                    }
                }
                
                j--;
            }
            if(dp[i]>maxL)
            {
                maxCnt = cnt;
                maxL = dp[i];
            }
        }
        cnt = 0;
        for(int i = 0 ; i< dp.size(); i++)
        {
            if(dp[i] == maxL)
            {
                cnt++;
            }
        }
        if(cnt > maxCnt)
            maxCnt = cnt;
        // for(int i =0;i<nums.size(); ++i)
        // {
        //     cout <<nums[i] <<  "===>" << dp[i] << endl;
        // }
        return maxCnt;
    }
};


int main()
{
    Solution so;
    vector<int> test={1,3,5,4,7};
    vector<int> test2={1,2,2,2,2,2};
    cout << so.findNumberOfLIS(test) << endl;
    cout << so.findNumberOfLIS(test2) << endl;
    return 0;
}
