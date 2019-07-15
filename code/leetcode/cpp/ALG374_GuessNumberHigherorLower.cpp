/*
 * @Author: zhaopeng 
 * @Date: 2019-07-16 00:37:04 
 * @Last Modified by: zhaopeng
 * @Last Modified time: 2019-07-16 00:49:07
 */


// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int start = 1;
        int end = n;
        int mid;
        while (start <= end) {
            mid = start + (end - start) / 2;
            int ret = guess(mid);
            if (-1 == ret) {
                start = mid + 1;
            } else if (1 == ret) {
                end = mid - 1;
            } else {
                return mid;
            }
            
            
        }
        return -1;    
    }
};