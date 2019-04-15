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

struct node
{
    long value;
    int count;
    struct node* left;
    struct node* right;
};

void free_tree(struct node* proot );
struct node* insert(struct node* ptree, long value );
int search(struct node* ptree, long value);

int reversePairs(int* nums, int numsSize) {
    if( !nums || numsSize < 1)
    {
        return 0;
    }
    struct node* ptree = NULL;
    int count = 0;
    int i;
    for(i = 0 ; i < numsSize; i++ )
    {
        int addtion = search(ptree, (long)2 * nums[i] + 1);
        // printf("nums[%d]=%d\tadd=%d\t",i,nums[i], addtion);
        count += addtion;
        // printf("count=%d\t",count);
        ptree = insert(ptree,  nums[i]);
        // print_all(ptree);
        // printf("\n");

    }
    free_tree(ptree);
    return count;
}


void print_all( struct node* proot)
{
    if( proot )
    {
        printf("%d:%d\t",proot->value, proot->count);
        print_all(proot->left);
        print_all(proot->right);
    }
}



void free_tree(struct node* proot )
{
    if( proot )
    {
        free_tree(proot->left);
        free_tree(proot->right);
        free(proot);
    }
}

struct node* insert(struct node* ptree, long value )
{
    if( !ptree )
    {
        struct node* tmp = (struct node*)calloc(1, sizeof(struct node));
        if(!tmp )
        {
            printf("in fun insert calloc memory failed\n");
            return NULL;
        }
        tmp->value = value;
        tmp->count = 1;
        tmp->left = tmp->right = NULL;
        return tmp;
    }
    if( ptree->value == value )
    {
        ptree->count ++;
    }
    else if ( ptree->value < value )
    {
        ptree->count++;
        ptree->right = insert(ptree->right, value);
    }
    else
    {
        
        ptree->left = insert(ptree->left, value);
    }
    return ptree;
}

int search(struct node* ptree, long value)
{
    if(!ptree )
    {
        return 0;
    }
    if( ptree->value == value )
    {
        return ptree->count;
    }
    else if ( ptree->value < value)
    {
        return search( ptree->right, value);
    }
    else
    {
        return ptree->count + search(ptree->left, value);
    }
}









