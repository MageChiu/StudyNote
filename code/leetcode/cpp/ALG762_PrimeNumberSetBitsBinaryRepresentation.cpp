/*
 * =====================================================================================
 *
 *       Filename:  ALG762_PrimeNumberSetBitsBinaryRepresentation.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/16/2018 12:31:31 AM
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
    int countPrimeSetBits(int L, int R) {
        int cnt = 0;
        for(int i = L; i<=R; i++)
        {
            if(checkPrime(i)==1)
            {
                cnt++;
            }
        }
        return cnt;
    }
    int checkPrime(int ele){
        int count = 0;
        int n = ele;
        while(n)
        {
            ++count;
            n = (n-1)&n;
        }
        int book[21] = {0,0,1,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0};
        return book[count];
    }
};


int get_prime(int m)
{
    vector<int> record(m*2, 1 );
    record[0] = 0;
    record[1] = 0;
    record[2] = 1;
    for(int i = 2; i<=m; i++)
    {   
        if(record[i]==0)
        {
            continue;
        }
        for(int j = 2*i;j<=m; j +=i)
        {
            record[j] = 0;
        }
    }
    for(int i = 0; i<=m ; i++)
    {
        cout << record[i] <<",";
    }
    return m;
}

int main()
{
    get_prime(20);
}


