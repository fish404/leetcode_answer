/*
 * @lc app=leetcode id=94 lang=c
 *
 * [94] Binary Tree Inorder Traversal
 *
 * https://leetcode.com/problems/binary-tree-inorder-traversal/description/
 *
 * algorithms
 * Medium (55.26%)
 * Total Accepted:    421.9K
 * Total Submissions: 761.4K
 * Testcase Example:  '[1,null,2,3]'
 *
 * Given a binary tree, return the inorder traversal of its nodes' values.
 * 
 * Example:
 * 
 * 
 * Input: [1,null,2,3]
 * ⁠  1
 * ⁠   \
 * ⁠    2
 * ⁠   /
 * ⁠  3
 * 
 * Output: [1,3,2]
 * 
 * Follow up: Recursive solution is trivial, could you do it iteratively?
 * 
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int count_tree_node(struct TreeNode *root)
{
    if (!root)
    {
        return 0;
    }
    return 1 + count_tree_node(root->left) + count_tree_node(root->right);
}

int inorder_trave(struct TreeNode *root, int *parray, int *pindex)
{
    if (!root || !parray || !pindex)
    {
        return -1;
    }
    if (root->left) // 有左孩子
    {
        inorder_trave(root->left, parray, pindex);
    }
    parray[*pindex] = root->val;
    
    // printf("parray[%d]=%d\n", *pindex, parray[*pindex]);
    (*pindex)++;
    
    inorder_trave(root->right, parray, pindex);
    return 1;
}




int *inorderTraversal(struct TreeNode *root, int *returnSize)
{

    int num = count_tree_node(root);
    // printf("num is %d\n", num);
    int *ret = (int *)calloc(num, sizeof(int));
    int index = 0;
    if (ret)
    {
        inorder_trave( root, ret, &index);
        *returnSize = index ;
        // printf("return size is %d\n", *returnSize);
    }
    return ret;
}
