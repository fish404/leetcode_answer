/*
 * @lc app=leetcode id=148 lang=c
 *
 * [148] Sort List
 *
 * https://leetcode.com/problems/sort-list/description/
 *
 * algorithms
 * Medium (34.10%)
 * Total Accepted:    173.1K
 * Total Submissions: 506.2K
 * Testcase Example:  '[4,2,1,3]'
 *
 * Sort a linked list in O(n log n) time using constant space complexity.
 * 
 * Example 1:
 * 
 * 
 * Input: 4->2->1->3
 * Output: 1->2->3->4
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: -1->5->3->4->0
 * Output: -1->0->3->4->5
 * 
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stdio.h>
#include <stdlib.h>

// struct ListNode
// {
//     int val;
//     struct ListNode *next;
// };

struct ListNode *sort_list(struct ListNode *head, int len);

struct ListNode *sortList(struct ListNode *head)
{
    if (!head)
    {
        return head;
    }
    int len = 0;
    struct ListNode *ptr = head;
    while (ptr)
    {
        len++;
        ptr = ptr->next;
    }
    // printf("len is %d\n", len);
    return sort_list(head, len);
}

struct ListNode *merge_two_sorted_list(struct ListNode *plista, struct ListNode *plistb)
{
    if (!plista)
    {
        return plistb;
    }
    if (!plistb)
    {
        return plista;
    }
    
    struct ListNode *pa = plista;
    struct ListNode *pb = plistb;
    struct ListNode *head = NULL;
    if( pa->val <= pb->val )
    {
        head = pa;
        pa = pa->next;
    }
    else
    {
        head = pb;
        pb = pb->next;
    }
    struct ListNode *cur = head;
    while (pa && pb)
    {
        if (pa->val <= pb->val)
        {
            cur->next = pa;
            pa = pa->next;
        }
        else
        {
            cur->next = pb;
            pb = pb->next;
        }
        cur = cur->next;
    }
    if (pa)
    {
        cur->next = pa;
    }
    else
    {
        cur->next = pb;
    }

    return head;
}

void print_all_node_in_list(struct ListNode *head)
{
    struct ListNode * ptr = head;
    while( ptr )
    {
        printf("%d\t", ptr->val);
        ptr = ptr->next;
    }
    printf("\n");
}


struct ListNode *sort_list(struct ListNode *head, int len)
{
    // printf("len is %d\n",len);
    if (!head || len < 1)
    {
        return head;
    }
    // printf("head is %d\n", head->val);
    if (len == 1)
    {
        return head;
    }
    else if (len == 2)
    {
        struct ListNode *pa = head;
        struct ListNode *pb = head->next;
        if (pa && pb)
        {
            if (pa->val > pb->val)
            {
                int tmp = pa->val;
                pa->val = pb->val;
                pb->val = tmp;
            }
        }
        return head;
    }
    else
    {
        int len1 = len / 2 + (len / 2 ) % 2;
        int len2 = len - len1;
        struct ListNode *pa = head;
        struct ListNode *pb = head;
        int i;
        for (i = 0; i < len1 - 1; i++)
        {
            pb = pb->next;
        }
        struct ListNode *tmp = pb;
        pb = tmp->next;
        tmp->next = NULL;
        struct ListNode *pSorteda = sort_list(pa, len1);
        struct ListNode *pSortedb = sort_list(pb, len2);
        return merge_two_sorted_list(pSorteda, pSortedb);
    }
}
