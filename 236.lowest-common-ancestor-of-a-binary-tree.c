/*
 * @lc app=leetcode id=236 lang=c
 *
 * [236] Lowest Common Ancestor of a Binary Tree
 *
 * https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/
 *
 * algorithms
 * Medium (36.01%)
 * Total Accepted:    261.2K
 * Total Submissions: 719.7K
 * Testcase Example:  '[3,5,1,6,2,0,8,null,null,7,4]\n5\n1'
 *
 * Given a binary tree, find the lowest common ancestor (LCA) of two given
 * nodes in the tree.
 * 
 * According to the definition of LCA on Wikipedia: “The lowest common ancestor
 * is defined between two nodes p and q as the lowest node in T that has both p
 * and q as descendants (where we allow a node to be a descendant of itself).”
 * 
 * Given the following binary tree:  root = [3,5,1,6,2,0,8,null,null,7,4]
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
 * Output: 3
 * Explanation: The LCA of nodes 5 and 1 is 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
 * Output: 5
 * Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant
 * of itself according to the LCA definition.
 * 
 * 
 * 
 * 
 * Note:
 * 
 * 
 * All of the nodes' values will be unique.
 * p and q are different and both values will exist in the binary tree.
 * 
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

// struct TreeNode
// {
//     int val;
//     struct TreeNode *left;
//     struct TreeNode *right;
// };

#include <stdio.h>
#include <stdlib.h>

// 链表结构

struct my_node
{
    struct TreeNode node;
    struct TreeNode *ptr;
};

typedef struct my_node StackNode;

struct Stack
{
    StackNode *parr;
    int capacity;
    int size;
};

int stack_insert_tail(struct Stack *pstack, StackNode value);
int stack_peek_tail(struct Stack *pstack, StackNode *pvalue);
int stack_pop_tail(struct Stack *pstack, StackNode *pvalue);
struct Stack *stack_copy(struct Stack *pstack);
struct Stack *stack_new(int size);
void stack_free(struct Stack *pstack);
int stack_empty(struct Stack *pstack);

int stack_empty(struct Stack *pstack)
{
    if (pstack)
    {
        if (pstack->size > 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    return 1;
}
struct Stack *stack_new(int size)
{
    int tmp_size = size;
    if (size <= 0)
    {
        tmp_size = 32;
    }
    struct Stack *pret = (struct Stack *)calloc(1, sizeof(struct Stack));
    if (!pret)
    {
        return NULL;
    }
    pret->parr = (StackNode *)calloc(tmp_size, sizeof(StackNode));
    if (!pret->parr)
    {
        free(pret);
        return NULL;
    }
    pret->capacity = tmp_size;
    pret->size = 0;
    return pret;
}

struct Stack *stack_copy(struct Stack *pstack)
{
    if (!pstack)
    {
        return NULL;
    }
    struct Stack *pret = (struct Stack *)calloc(1, sizeof(struct Stack));
    if (!pret)
    {
        return NULL;
    }
    pret->parr = (StackNode *)calloc(pstack->capacity, sizeof(StackNode));
    if (!pret->parr)
    {
        free(pret);
        return NULL;
    }
    pret->capacity = pstack->capacity;
    pret->size = pstack->size;
    int i;
    for (i = 0; i < pret->size; i++)
    {
        pret->parr[i] = pstack->parr[i];
    }
    return pret;
}

void stack_free(struct Stack *pstack)
{
    if (pstack)
    {
        if (pstack->parr)
        {
            free(pstack->parr);
        }
        free(pstack);
    }
}

int stack_insert_tail(struct Stack *pstack, StackNode value)
{
    if (!pstack)
    {
        return -1;
    }
    if (pstack->size >= pstack->capacity)
    {
        pstack->capacity *= 2;
        pstack->parr = (StackNode *)realloc(pstack->parr, pstack->capacity * sizeof(StackNode));
        if (!pstack->parr)
        {
            return -2;
        }
    }
    // printf("insert[%d]\t", value.val);
    pstack->parr[pstack->size].node.val = value.node.val;
    pstack->parr[pstack->size].node.left = value.node.left;
    pstack->parr[pstack->size].node.right = value.node.right;
    pstack->parr[pstack->size].ptr = value.ptr;
    pstack->size++;
    return 1;
}

int stack_peek_tail(struct Stack *pstack, StackNode *pvalue)
{
    if (!pstack)
    {
        return -1;
    }
    if (pstack->size < 1)
    {
        return -2;
    }
    memcpy(pvalue, &pstack->parr[pstack->size - 1], sizeof(StackNode));
    return 1;
}

int stack_pop_tail(struct Stack *pstack, StackNode *pvalue)
{
    if (!pstack)
    {
        return -1;
    }
    if (pstack->size > 0)
    {
        // printf("pop[%d]\t", pstack->parr[pstack->size - 1].val);
        if (pvalue)
        {
            memcpy(pvalue, &pstack->parr[pstack->size - 1], sizeof(StackNode));
        }
        pstack->size--;
        return 1;
    }
    else
    {
        return -2;
    }
}

struct TreeNode *lowestCommonAncestor(struct TreeNode *root, struct TreeNode *p, struct TreeNode *q)
{

    struct Stack *plst = stack_new(0);
    struct TreeNode *tmp = root;
    struct Stack *ptop = NULL;
    struct Stack *ptoq = NULL;

    // while(0)
    while (tmp)
    {
        StackNode node;
        memset(&node, 0, sizeof(node));
        node.node.val = tmp->val;
        node.node.left = tmp->left;
        node.node.right = tmp->right;
        node.ptr = tmp;
        stack_insert_tail(plst, node);
        if (tmp->val == p->val)
        {
            ptop = stack_copy(plst);
            if (ptop && ptoq)
            {
                break;
            }
        }
        else if (tmp->val == q->val)
        {
            ptoq = stack_copy(plst);
            if (ptop && ptoq)
            {
                break;
            }
        }

        {
            if (tmp->left == NULL && tmp->right == NULL) // 到达叶节点
            {
                stack_pop_tail(plst, NULL); // 从队列尾部去掉该节点，取它的父节点，检查右子树
                tmp = NULL;
            }
            else
            {
                if (tmp->left) // 有左子树
                {
                    tmp = tmp->left;
                }
                else // 没有左子树
                {
                    tmp = tmp->right;
                }
            }

            if (!tmp)
            {
                StackNode tail;
                memset(&tail, 0, sizeof(StackNode));
                while (!stack_empty(plst))
                {
                    if (stack_peek_tail(plst, &tail) == 1)
                    {
                        if (!tail.node.right)
                        {
                            stack_pop_tail(plst, NULL);
                        }
                        else
                        {
                            tmp = tail.node.right;
                            plst->parr[plst->size - 1].node.right = NULL; // 把栈末尾的这个元素右孩子指针设为空
                            break;
                        }
                    }
                }
            }
        }
    }

    int i;
    int val;
    int limit = ptop->size <= ptoq->size ? ptop->size : ptoq->size;
    for (i = 0; i < limit; i++)
    {
        if (ptoq->parr[i].node.val != ptop->parr[i].node.val)
        {
            break;
        }
    }
    struct TreeNode *ret = NULL;
    ret = ptoq->parr[i - 1].ptr;

    stack_free(plst);
    stack_free(ptop);
    stack_free(ptoq);
    return ret;
}
