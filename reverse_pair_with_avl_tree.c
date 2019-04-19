// 平衡树， avl tree，二叉查找树，bst。

/*
* @lc app=leetcode id=493 lang=c
*
* [493] Reverse Pairs
*
* https://leetcode.com/problems/reverse-pairs/description/
*
* algorithms
* Hard (22.72%)
* Total Accepted:    22.4K
* Total Submissions: 98.4K
* Testcase Example:  '[1,3,2,3,1]'
*
* Given an array nums, we call (i, j) an important reverse pair if i < j and
* nums[i] > 2*nums[j].
*
* You need to return the number of important reverse pairs in the given
* array.
*
* Example1:
*
* Input: [1,3,2,3,1]
* Output: 2
*
*
* Example2:
*
* Input: [2,4,3,5,1]
* Output: 3
*
*
* Note:
*
* The length of the given array will not exceed 50,000.
* All the numbers in the input array are in the range of 32-bit integer.
*
*
*/

#include <stdio.h>
#include <stdlib.h>

#define  max(a,b) ( (a) >= (b) ? (a) : (b) )

#define  min(a,b) ( (a) <= (b) ? (a) : (b) )

 
struct node
{
    int value;
    int count;
    char height;
    struct node* left;
    struct node* right;
};




void free_tree(struct node* proot);
struct node* insert(struct node* ptree, long value); // 查找数中 >= value的元素的数量
int search(struct node* ptree, long value);

int reversePairs(int* nums, int numsSize) {
    if (!nums || numsSize < 1)
    {
        return 0;
    }
    struct node* ptree = NULL;
    long count = 0;
    int i;
    int addtion ;
    for (i = 0; i < numsSize; i++)
    {
        addtion = search(ptree, (long)2 * nums[i] + 1);
        count += addtion;
        ptree = insert(ptree, nums[i]);
    }
    free_tree(ptree);
    return count;
}


void print_all(struct node* proot)
{
    if (proot)
    {
        printf("%d\t", proot->value);
        print_all(proot->left);
        print_all(proot->right);
    }
}



void free_tree(struct node* proot)
{
    if (proot)
    {
        free_tree(proot->left);
        free_tree(proot->right);
        free(proot);
    }
}




static int node_height(struct node* p)
{
    if (!p)
    {
        return 0;
    }
    else
    {
        return p->height;
    }
}

// 旋转
// 单旋转 

/*
1、左旋转
        k1
       /
     k2
    /
   k3 

*/

struct node* single_rotate_with_left(struct node* k1)
{
    if( !k1 )
    {
        return NULL;
    }
    struct node* k2 = k1->left;
    k1->left = k2->right;
    k2->right = k1;
    k1->height = max( node_height(k1->left), node_height(k1->right)) + 1;
    k2->height = max(node_height(k2->left), node_height(k2->right)) + 1;
    k2->count += k1->count;
    return k2;
}

/*
2、右旋转
        k1
          \
           k2
            \
             k3
*/

struct node* single_rotate_with_right(struct node* k1)
{
    if( !k1 )
    {
        return NULL;
    }
    struct node* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(node_height(k1->left), node_height(k1->right)) + 1;
    k2->height = max(node_height(k2->left), node_height(k2->right)) + 1;
    k1->count -= k2->count;
    return k2;
}


// 双旋转 

/*
3、双旋转左旋转
        k1
       /
     k2
       \
        k3
*/

struct node* double_rotate_with_left(struct node* k1)
{
    k1->left = single_rotate_with_right(k1->left);
    return single_rotate_with_left(k1);
}

/*
4、双旋转右旋转
        k1
          \
           k2
          / 
        k3
*/

struct node* double_rotate_with_right(struct node* k1)
{
    k1->right = single_rotate_with_left(k1->right);
    return single_rotate_with_right(k1);
}





struct node* insert(struct node* ptree, long value)
{
    if (!ptree)
    {
        struct node* tmp = (struct node*)calloc(1, sizeof(struct node));
        if (!tmp)
        {
            //printf("in fun insert calloc memory failed\n");
            return NULL;
        }
        tmp->value = value;
        tmp->count = 1;
        tmp->height = 1;
        tmp->left = tmp->right = NULL;
        return tmp;
    }
    if (ptree->value == value)
    {
        ptree->count ++;
    }
    else if (ptree->value < value)
    {
        ptree->right = insert(ptree->right, value);
        ptree->count ++;
        if (node_height(ptree->right) - node_height(ptree->left) >= 2)
        {
            if (ptree->right->value < value)
            {
                ptree = single_rotate_with_right(ptree);
            }
            else
            {
                ptree = double_rotate_with_right(ptree);
            }
        }
    }
    else
    {
        ptree->left = insert(ptree->left, value);
        if (node_height(ptree->left) - node_height(ptree->right) >= 2)
        {
            if (ptree->left->value > value)
            {
                ptree = single_rotate_with_left(ptree);
            }
            else
            {
                ptree = double_rotate_with_left(ptree);
            }
        }
    }
    ptree->height = max(node_height(ptree->left), node_height(ptree->right)) + 1;
    return ptree;
}

int search(struct node* ptree, long value)
{
    if (!ptree)
    {
        return 0;
    }
    if (ptree->value == value)
    {
        return ptree->count;
    }
    else if (ptree->value < value)
    {
        return search(ptree->right, value);
    }
    else
    {
        return ptree->count + search(ptree->left, value);
    }
}









