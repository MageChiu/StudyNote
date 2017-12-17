/*
 * =====================================================================================
 *
 *       Filename:  ALG543_DiameterofBinaryTree.cpp
 *
 *    Description:  ALG543_DiameterofBinaryTree.cpp
 *
 *        Version:  1.0
 *        Created:  2017年12月17日 17时03分02秒
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
    int diameterOfBinaryTree(TreeNode* root) {
        if(NULL == root)
        {
            return 0;
        }
        int deepth = 0;
        return _diameterOfBinaryTree(root, deepth);
    }
    int _diameterOfBinaryTree(TreeNode* root, int &deepth)
    {
        if(NULL == root)
        {
            return 0;
        }
        int deep_l = 0;
        int dia_l = _diameterOfBinaryTree(root->left, deep_l);
        int deep_r = 0;
        int dia_r = _diameterOfBinaryTree(root->right, deep_r);
        deepth =  (deep_r > deep_l ? deep_r:deep_l) +1;
        return max(max(dia_l, dia_r), deep_l + deep_r);
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
