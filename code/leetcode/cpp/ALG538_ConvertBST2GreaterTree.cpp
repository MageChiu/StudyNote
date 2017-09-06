/*
 * =====================================================================================
 *
 *       Filename:  ALG538_ConvertBST2GreaterTree.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年09月07日 01时13分02秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Charles Chiu (), charles.r.chiu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include <iostream>
#include <string>
#include <sstream>

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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void printTreeNode(TreeNode *root)
{
    if (root == NULL) return;
    cout << root->val << " ";
    printTreeNode(root->left);
    printTreeNode(root->right);
    return;
}

class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        convertBST2(root,0);
        return root;
    }
    int convertBST2(TreeNode* root,int num) {
        if(root == NULL) return num;
        int rsum = convertBST2(root->right,num);
        root->val += rsum;
        
        int lsum = convertBST2(root->left, root->val);
        
        return lsum;
    }
};



void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

TreeNode* stringToTreeNode(string input) {
    input = input.substr(1, input.length() - 2);
    if (!input.size()) {
        return nullptr;
    }

    string item;
    stringstream ss;
    ss.str(input);

    getline(ss, item, ',');
    TreeNode* root = new TreeNode(stoi(item));
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);

    while (true) {
        TreeNode* node = nodeQueue.front();
        nodeQueue.pop();

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int leftNumber = stoi(item);
            node->left = new TreeNode(leftNumber);
            nodeQueue.push(node->left);
        }

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int rightNumber = stoi(item);
            node->right = new TreeNode(rightNumber);
            nodeQueue.push(node->right);
        }
    }
    return root;
}

string treeNodeToString(TreeNode* root) {
    string output = "";
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (node == nullptr) {
          output += "null, ";
          continue;
        }

        output += to_string(node->val) + ", ";
        q.push(node->left);
        q.push(node->right);
    }
    return "[" + output.substr(0, output.length() - 2) + "]";
}

// int main() {
//     string line;
//     while (getline(cin, line)) {
//         TreeNode* root = stringToTreeNode(line);
        
//         TreeNode* ret = Solution().convertBST(root);

//         string out = treeNodeToString(ret);
//         cout << out << endl;
//     }
//     return 0;
// }
int main()
{
    TreeNode *root= new TreeNode(5);
    root->left = new TreeNode(2);
    root->right = new TreeNode(13);

    Solution so;
    root = so.convertBST(root);

    printTreeNode(root);
    cout << endl;


}