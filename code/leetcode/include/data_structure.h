/*
 * =====================================================================================
 *
 *       Filename:  data_structure.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年07月23日 21时29分54秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Charles Chiu (), charles.r.chiu@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __DATA_STRUCTURE_H__

#define __DATA_STRUCTURE_H__



#ifndef __TREE_NODE__
#define __TREE_NODE__

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x)
    {
        val = x;
        left=NULL;
        right = NULL;
    }
};



#endif







#endif 
