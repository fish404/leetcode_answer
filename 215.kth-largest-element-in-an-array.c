/*
 * @lc app=leetcode id=215 lang=c
 *
 * [215] Kth Largest Element in an Array
 *
 * https://leetcode.com/problems/kth-largest-element-in-an-array/description/
 *
 * algorithms
 * Medium (46.12%)
 * Total Accepted:    331.4K
 * Total Submissions: 717.1K
 * Testcase Example:  '[3,2,1,5,6,4]\n2'
 *
 * Find the kth largest element in an unsorted array. Note that it is the kth
 * largest element in the sorted order, not the kth distinct element.
 * 
 * Example 1:
 * 
 * 
 * Input: [3,2,1,5,6,4] and k = 2
 * Output: 5
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: [3,2,3,1,2,4,5,5,6] and k = 4
 * Output: 4
 * 
 * Note: 
 * You may assume k is always valid, 1 ≤ k ≤ array's length.
 * 
 */


// heap 
#include <stdio.h>
#include <stdlib.h>


 


struct heap_int 
{
    int* parray;
    int  num;
    int  capacity;
};

int get_min_son_index(int* parray, int index, int limit_index)
{
    if( !parray || index >=limit_index )
    {
        return index;
    }    
    int left_index = 2 * index + 1;
    int right_index = 2 * index + 2;
    if( left_index > limit_index ) // 没有孩子
    {
        return index;
    }
    if( right_index > limit_index ) // 只有左孩子
    {
        return left_index;
    }
    else                            // 有2个孩子
    {
        return  parray[left_index] < parray[right_index] ? left_index : right_index;
    }
}


void settle_node(struct heap_int* pheap, int index )
{    
    if( !pheap )
    {
        return ;
    }
    if(pheap->num <= 1)
    {
        return ;
    }
    int limit_index = pheap->num - 1;

    int min_index = 0;
    int i = index;
    while( i < limit_index )
    {
        min_index = get_min_son_index( pheap->parray, i, limit_index);
        if( min_index > i    &&  pheap->parray[min_index] < pheap->parray[i] ) 
        {
            int tmp = pheap->parray[i];
            pheap->parray[i] = pheap->parray[min_index];
            pheap->parray[min_index] = tmp;
            i = min_index ;
        }
        else
        {
            break;
        }        
    }
}


struct heap_int* build_heap(int* parray, int num)
{
    int i;
    int index = 0;
    if( !parray || num < 1 )
    {
        return NULL;
    }
    struct heap_int* pret = (struct heap_int* )malloc( sizeof( struct heap_int) );
    if( !pret )
    {
        printf("分配堆结构失败\n");
        return NULL;
    }
    pret->parray = (int* )calloc( num, sizeof(int));
    if( !pret->parray )
    {
        printf("分配堆数组失败\n");
        return NULL;
    }
    pret->capacity = num;
    pret->num = num;
    for( i = 0; i < num ; i++ )
    {
        pret->parray[i] = parray[i];
    }
    if( num == 1 ) // 如果只有1个元素，直接就是堆了
    {
        return pret;
    }
    // 到这里表明 num >= 2 
    index = (num - 2) / 2; //开始检查的下标
    while( index >= 0 )
    {
        settle_node(pret, index);
        index --;
    }
    return pret;
}

void free_heap(struct heap_int* pheap)
{
    if( pheap)
    {
        free(pheap->parray);
        free(pheap);
    }
}
// 只查看堆顶元素，但是不移出
int peek_top(struct heap_int* pheap, int* pvalue)
{
    if(!pheap || !pvalue )
    {
        return -1;
    }
    if( pheap->num < 1 )
    {
        return -1;
    }
    *pvalue = pheap->parray[0];
    return 1;
}

// 移出堆顶元素 
int pop(struct heap_int* pheap, int* pvalue)
{
    if( !pheap || !pvalue )
    {
        return -1;
    }
    if( pheap->num < 1)
    {
        return -1;
    }
    int tmp = pheap->parray[ pheap->num - 1];
    *pvalue = pheap->parray[0];
    // printf("pop value %d\n", *pvalue);
    pheap->parray[0] = tmp;
    pheap->num -- ;
    settle_node(pheap, 0);
    return 1;
}

// 插入元素 
int insert(struct heap_int* pheap, int value)
{
    if( !pheap )
    {
        return -1;
    }
    if( pheap->num >=  pheap->capacity)
    {
        return -1;
    }
    pheap->num ++ ;
    pheap->parray[ pheap->num - 1] = value;
    settle_node(pheap, (pheap->num - 2) / 2 );
    return 1;
}

// 用给定值替换堆顶元素 
int replace_top(struct heap_int* pheap, int value)
{
    if( !pheap )
    {
        return -1;
    }
    if( pheap->num < 1)
    {
        return -1;
    }
    pheap->parray[0] = value;
    settle_node(pheap, 0);
    return 1;
}

void print_heap_all(struct heap_int* pheap)
{
    if( pheap)
    {
        int i;
        for( i = 0; i < pheap->num ; i++ )
        {
            printf("%d\t", pheap->parray[i]);
        }
        printf("\n");
    }
}




int findKthLargest(int* nums, int numsSize, int k) {

    if( !nums || numsSize < 1)
    {
        return -1;
    }
    struct heap_int* pheap = build_heap(nums, k);
    int i = k;
    int top_element = 0;
    // print_heap_all(pheap);
    for(i = k; i < numsSize; i++ )
    {
        if( peek_top(pheap, &top_element) == 1 && nums[i] > top_element)
        {
            replace_top(pheap, nums[i]);
            // print_heap_all(pheap);
        }
    }
    top_element = 0;
    peek_top(pheap, &top_element);
    // printf("%d\n",top_element);
    free_heap(pheap);
    return top_element;
}

// int main()
// {

//     int data[10] = {1};
//     int ret = findKthLargest(data, 1, 1);
//     printf("%d\n", ret);


// }

