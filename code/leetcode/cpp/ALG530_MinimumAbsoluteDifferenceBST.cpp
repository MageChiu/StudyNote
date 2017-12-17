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
#define DEBUG_INT(val)  \
do{ \
    printf("[%s][%s][%d][%s][%d]\n",__FILE__, __FUNCTION__, __LINE__, #val, val);   \
}while(0)

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
        int min_val, max_val, ret;
        ret =  _getMinimumDifference(root,min_val, max_val);
        return ret;
    }
    int _getMinimumDifference(TreeNode* root, int& min_val, int& max_val)
    {
        if(root == NULL)
        {
            return -1;
        }
        int l_min, l_max, r_min, r_max, l_val = -1, r_val = -1;
        int ret = -1;
        if(NULL != root->left)
        {
            l_val = _getMinimumDifference(root->left, l_min, l_max);  
            ret = root->val - l_max;
            if(l_val != -1)
            {
                ret = min(l_val, ret);
            }
            min_val = l_min;      
        }
        else
        {
            min_val = root->val;
        }
        if(NULL != root->right)
        {
            r_val = _getMinimumDifference(root->right, r_min, r_max);
            if(ret != -1)
            {
                ret = min(ret, r_min - root->val);
            }
            else
            {
                ret = r_min - root->val;
            }
            if(r_val != -1)
            {
                ret = min(ret , r_val);            
            }
            max_val = r_max;
        }
        else
        {
            max_val = root->val;
        } 
        return ret;  
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
int print_tree(TreeNode* root)
{
    if(root == NULL)
    {
        return -1;
    }
    print_tree(root->left);
    cout << root->val << endl;
    print_tree(root->right);
    return 0;
}
int main()
{
    TreeNode* test_root = NULL;
    test_root = new TreeNode(1);
    test_root->right = new TreeNode(3);
    test_root->right->left = new TreeNode(2);
    // test_root->left = new TreeNode(2);
    // test_root->left->left = new TreeNode(4);
    // test_root->left->right = new TreeNode(5);
    

    //vector<string> test_str = { "4","-7","-3","null","null","-9","-3","9","-7","-4","null","6","null","-6","-6","null","null","0","6","5","null","9","null","null","-1","-4","null","null","null","-2" };
    vector<string> test_str = {"1","null","3","2"};
    //test_root  = creat_tree(test_str);
    print_tree(test_root);
    Solution so;
    cout << so.getMinimumDifference(test_root) << endl;
    return 0;
}


