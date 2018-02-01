/*
 * =====================================================================================
 *
 *       Filename:  ALG747_LargestNumberAtLeastTwiceofOthers.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年01月17日 11时17分20秒
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
    int dominantIndex(vector<int>& nums) {
        int pre_pos = -1;
        int max_pos = -1;
        if(nums.size()<=1)
        {
            return 0;
        }
        if(nums[0]>nums[1])
        {
            pre_pos = 1;
            max_pos = 0;
        }
        else
        {
            pre_pos = 0;
            max_pos = 1;
        }
        for(int i =2;i<nums.size(); i++)
        {
            if(nums[i]>nums[max_pos])
            {
                pre_pos = max_pos;
                max_pos = i;
            }
            else
            {
                if(nums[i]>nums[pre_pos])
                {
                    pre_pos = i;
                }
            }
        }
        if(nums[pre_pos]==0)
        {
            if(nums[max_pos]>0)
            {
                return max_pos;
            }
            else
            {
                return -1;
            }
        }
        else if(nums[max_pos]/nums[pre_pos]>=2)
        {
            return max_pos;
        }
        else
        {
            return -1;
        }
    }
};


int main()
{
    //vector<int> test = {3, 6, 1, 0};
    vector<int> test = {1, 2, 3, 4};
    Solution so;
    cout << so.dominantIndex(test) << endl;
    return 0;
}