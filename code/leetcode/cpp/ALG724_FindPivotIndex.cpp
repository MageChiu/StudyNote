/*
 * =====================================================================================
 *
 *       Filename:  ALG724_FindPivotIndex.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年11月20日 16时55分11秒
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
    int pivotIndex(vector<int>& nums) {
        int sum = 0;
        if(nums.empty())
        {
            return -1;
        }
        if(nums.size()==1)
        {
            return 0;
        }
        int cnt = nums.size();
        for(int i = 0; i< nums.size(); ++i)
        {
            sum += nums[i];
        }
        int loc = 0;
        int lsum = 0 - nums[loc];
        int rsum = sum ;
        while(loc < cnt)
        {
            //lsum += nums[loc];
            lsum = sum - rsum;
            rsum -= nums[loc];

            if(lsum == rsum)
            {
                return loc;
            }
            loc ++ ;
        }
        return -1; 
    }
};


int main()
{
    vector<int> test = {1, 7, 3, 6, 5, 6};
    Solution so;
    cout << so.pivotIndex(test) << endl;
    return 0;
}



