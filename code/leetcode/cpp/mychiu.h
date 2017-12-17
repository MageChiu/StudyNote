/*
 * =====================================================================================
 *
 *       Filename:  mychiu.h
 *
 *    Description:  my public head
 *
 *        Version:  1.0
 *        Created:  2017年12月17日 19时49分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Charles Chiu (), charles.r.chiu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef __MY_CHIU_H__
#define __MY_CHIU_H__

#include <time.h>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class ChiuTime
{
public:
    int print_time();
    int startTimer();
    int endTimer();
private:
    clock_t _pre_time;
    clock_t _cur_time;
};

class ChiuTool
{
public:
    TreeNode *creat_tree(std::vector<std::string> indata);
private:
    long version;
};



#endif /* __MY_CHIU_H__ */

