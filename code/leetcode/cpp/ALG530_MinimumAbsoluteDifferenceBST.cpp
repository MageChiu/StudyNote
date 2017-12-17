/*
 * =====================================================================================
 *
 *       Filename:  ALG530_MinimumAbsoluteDifferenceBST.cpp
 *
 *    Description:  ALG530_MinimumAbsoluteDifferenceBST.cpp
 *
 *        Version:  1.0
 *        Created:  2017年12月17日 20时23分45秒
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
#include <string>
#include <queue>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string.h>



using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/**
 *         1
 *        / \
 *       2   3
 *      / \     
 *     4   5 
 **/ 
class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        if(root == NULL)
        {
            return 0;
        }
    }
    int _getMinimumDifference(TreeNode* root, int& type, int& val)
    {
        if(root == NULL)
        {
            type = -1;
            return 0;
        }
        int l_max, r_min, l_val, r_val;
        int lt = 1;
        int rt = 2;
        l_val = _getMinimumDifference(root->left, lt, l_max);
        r_val = _getMinimumDifference(root->right, rt, r_min);
        
    }
};

TreeNode *creat_tree(vector<string> indata)
{
    queue<TreeNode* > tq;
    string str = indata[0];
    int number;
    std::stringstream ss;
    ss << str;
    ss >> number;
    TreeNode *root = new TreeNode(number);
    tq.push(root);
    int pos = 1;
    int i = pos;
    TreeNode* tmpPtr = NULL;
    cout << indata.size() << endl;
    while(i< indata.size())
    {
        cout << i << endl;
        tmpPtr = tq.front();
        tq.pop();
        if(tmpPtr == NULL)
        {
            continue;
        }
        if(strcmp(indata[i].c_str(), "null")==0)
        {
            tmpPtr->left = NULL;
        }
        else
        {
            ss << indata[i];
            ss >> number;
            tmpPtr->left = new TreeNode(number);  
        }
        tq.push(tmpPtr->left); 
        i++;
        if (i == indata.size())
        {
            break;
        }
        if(strcmp(indata[i].c_str(), "null")==0)
        {
            tmpPtr->right = NULL;
        }
        else
        {
            ss << indata[i];
            ss >> number;
            tmpPtr->right = new TreeNode(number);  
        }
        tq.push(tmpPtr->right); 
        i++;
        
    }
    return root;
}

int main()
{
    TreeNode* test_root = new TreeNode(1);
    test_root->left = new TreeNode(2);
    test_root->left->left = new TreeNode(4);
    test_root->left->right = new TreeNode(5);
    test_root->right = new TreeNode(3);
    vector<string> test_str = { "4","-7","-3","null","null","-9","-3","9","-7","-4","null","6","null","-6","-6","null","null","0","6","5","null","9","null","null","-1","-4","null","null","null","-2" };
    test_root  = creat_tree(test_str);
    Solution so;
    cout << so.diameterOfBinaryTree(test_root) << endl;
    return 0;
}


