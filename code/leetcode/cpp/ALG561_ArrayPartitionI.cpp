/*
 * =====================================================================================
 *
 *       Filename:  ALG561_ArrayPartitionI.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年09月03日 00时27分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Charles Chiu (), charles.r.chiu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


/**********************
 *
 * Input: [1,4,3,2]
 *
 * Output: 4
 * Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).
 *
 * *******************/

#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int ret = 0;
        for(int i = 0 ; i<nums.size(); i+=2)
        {
            ret += nums[i];
        }
        return ret;
    }
};
