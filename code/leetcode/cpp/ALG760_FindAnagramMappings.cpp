/*
 * =====================================================================================
 *
 *       Filename:  ALG760_FindAnagramMappings.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年01月16日 20时27分22秒
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


using namespace std;

class Solution {
public:
    vector<int> anagramMappings(vector<int>& A, vector<int>& B) {
        map<int,vector<int>> book;
        for(int i = 0; i < B.size() ; ++i)
        {
            book[B[i]].push_back(i);
        }
        vector<int> ret;
        ret.reserve(A.size() +1);
        for(int i = 0; i< A.size(); ++i)
        {
            ret.push_back(book[A[i]].back());
            book[A[i]].pop_back();
        }
        return ret;
    }
};



int main()
{
    vector<int> A = {12, 28, 46, 32, 50};
    vector<int> B = {50, 12, 32, 46, 28};
    Solution so;
    vector<int> res =  so.anagramMappings(A, B);
    for ( int i = 0 ; i < res.size() ; ++i )
    {
        cout << res[i] << ", " ;
    }
    cout << endl;
    return 0;
}
