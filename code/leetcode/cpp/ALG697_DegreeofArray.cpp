/*
 * =====================================================================================
 *
 *       Filename:  ALG697_DegreeofArray.cpp
 *
 *    Description:  ALG697_DegreeofArray.cpp
 *
 *        Version:  1.0
 *        Created:  2017年12月18日 11时19分40秒
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
#include <map>
#include <set>


using namespace std;

class Solution {
public:
    struct POS
    {
        int start;
        int end;
        int len;
        int cnt;
        POS(int x): start(x), end(x), cnt(1), len(end-start+1) {}
        POS() {}
    };
    int findShortestSubArray(vector<int>& nums) {
        int length = nums.size();
        
        map<int,POS> recode;
        map<int, set<int>> len_re;
        int max_cnt = 0;
        int max_ele = 0;
        for(int i = 0; i < length; ++i)
        {
            int ele = nums[i];
            if(recode.find(ele)==recode.end())
            {
                POS p(i);
                recode.insert(pair<int,POS>(ele,p));
            }
            else
            {
                recode[ele].end = i;
                recode[ele].cnt++;
                recode[ele].len = recode[ele].end - recode[ele].start +1;
            }
            if(recode[ele].cnt > max_cnt)
            {
                max_cnt = recode[ele].cnt;
                max_ele = ele;
            }
            len_re[recode[ele].cnt].insert(ele);
        }
        int ret = length;
        for(set<int>::iterator iter = len_re[max_cnt].begin(); iter != len_re[max_cnt].end(); ++iter)
        {
            int ele = *iter;
            if(ret > recode[ele].len)
            {
                ret = recode[ele].len;
            }
        }
        return ret;
    }
};


int main()
{
    Solution so;
    //vector<int> test_vec = {1, 2, 2, 3, 1};
    vector<int> test_vec = {1,2,2,3,1,4,2};
    cout << so.findShortestSubArray(test_vec) << endl;
    return 0;
}