/*
 * =====================================================================================
 *
 *       Filename:  mychiu.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年12月17日 19时51分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Charles Chiu (), charles.r.chiu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "mychiu.h"
#include <time.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>


int ChiuTime::print_time()
{
    _cur_time = clock();
    std::cout << (_cur_time - _pre_time) / static_cast<double>(CLOCKS_PER_SEC) <<std::endl;
    _pre_time = _cur_time;
    return 0;
}



TreeNode* ChiuTool::creat_tree(std::vector<std::string> indata)
{
    std::queue<TreeNode* > tq;
    std::string str = indata[0];
    int number;
    std::stringstream ss;
    ss << str;
    ss >> number;
    TreeNode *root = new TreeNode(number);
    tq.push(root);
    int pos = 1;
    int i = pos;
    TreeNode* tmpPtr = NULL;
    std::cout << indata.size() << std::endl;
    while(i< indata.size())
    {
        std::cout << i << std::endl;
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



