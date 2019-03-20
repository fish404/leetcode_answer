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

// 实现一个简单的栈
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode node_t;
typedef struct
{
    node_t *parray;
    int capacity;
    int count;
} stack_t;

stack_t *stack_init(int size)
{
    if (size < 1)
    {
        return NULL;
    }
    stack_t *pstack = (stack_t *)calloc(1, sizeof(stack_t));
    if (pstack)
    {
        pstack->parray = (node_t *)calloc(size, sizeof(node_t));
        if (pstack->parray)
        {
            pstack->capacity = size;
        }
    }
    return pstack;
}

int stack_push(stack_t *pstack, node_t node)
{
    if (!pstack)
    {
        return -1;
    }
    if (pstack->count > pstack->capacity)
    {
        return -1;
    }
    // printf("插入元素%d\n", node.val);
    pstack->count++;
    pstack->parray[pstack->count - 1] = node;

    return 1;
}

node_t stack_pop(stack_t *pstack)
{
    node_t ret;
    memset(&ret, 0, sizeof(node_t));
    if (!pstack || pstack->count < 1)
    {
        return ret;
    }
    ret = pstack->parray[pstack->count - 1];
    pstack->count--;
    return ret;
}

int stack_is_empty(stack_t *pstack)
{
    if (pstack)
    {
        return (pstack->count == 0) ? 1 : 0;
    }
    return 1;
}

int count_tree_node(struct TreeNode *root)
{
    if (!root)
    {
        return 0;
    }
    return 1 + count_tree_node(root->left) + count_tree_node(root->right);
}

// 递归实现
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
    // 递归实现
    /*     
    if (ret)
    {
        inorder_trave(root, ret, &index);
        *returnSize = index;
    } */

    // 非递归实现
    stack_t *pstack = stack_init(num);
    if (pstack)
    {
        struct TreeNode *ptr = root;
        struct TreeNode one;
        while (ptr || !stack_is_empty(pstack))
        {
            if (ptr)
            {
                if (ptr->left)
                {
                    stack_push(pstack, *ptr);
                    ptr = ptr->left;
                }
                else
                {
                    ret[index] = ptr->val;
                    index++;
                    ptr = ptr->right;
                }
            }
            else
            {
                if (!stack_is_empty(pstack))
                {
                    one = stack_pop(pstack);
                    ret[index] = one.val;
                    index++;
                    if (one.right)
                    {
                        ptr = one.right;
                    }
                    // printf("从栈里面弹出元素%d\n", one.val);
                }
            }
        }
    }
    *returnSize = index;
    return ret;
}
