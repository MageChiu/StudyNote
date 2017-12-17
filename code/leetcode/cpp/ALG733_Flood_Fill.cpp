/*
 * =====================================================================================
 *
 *       Filename:  ALG733_Flood_Fill.cpp
 *
 *    Description:  ALG733_Flood_Fill.cpp
 *
 *        Version:  1.0
 *        Created:  2017年12月15日 14时59分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Charles Chiu (), charles.r.chiu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include <vector>
#include <iostream>


using namespace std;

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int r = image.size();
        int c = image[0].size();
        int oldColor = 0;
        if(r<= sr || c <= sc || sr <0 || sc < 0)
        {
            return image;
        }
        oldColor = image[sr][sc];
        if (oldColor == newColor)
        {
            return image;
        }
        floodFillFunc(image, sr, sc, newColor, r, c, oldColor);
        return image;
    }
    int floodFillFunc(vector<vector<int>>& image, int sr, int sc, int newColor, int r, int c, int oldColor)
    {
        if(r<= sr || c <= sc || sr <0 || sc < 0)
        {
            return -1;
        }
        static int d[4][2] = {
            {-1, 0},
            {1 , 0},
            {0 , -1},
            {0 , 1}
        };
        if(image[sr][sc] == oldColor)
        {
            image[sr][sc] = newColor;
            for(int i = 0; i< 4; i++)
            {
                floodFillFunc(image, sr+d[i][0], sc + d[i][1], newColor, r, c, oldColor);
            }
        }
        return 0;
    }
};

int main()
{
    // vector<vector<int>> image = {
    //     {1,1,1},
    //     {1,1,0},
    //     {1,0,1}
    // };
    vector<vector<int>> image = {
        {0,0,0},
        {0,1,1}
    };
    Solution so;
    int sr = 1, sc = 1, newColor = 1;
    vector<vector<int>> reimage = so.floodFill(image, sr,  sc, newColor);
    cout << "ok" << endl;
    for ( auto v : reimage)
    {
        for (auto s : v)
        {
            cout << s << ' ';
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}

