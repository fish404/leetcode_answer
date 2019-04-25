/*
 * @lc app=leetcode id=164 lang=c
 *
 * [164] Maximum Gap
 */
#include <stdio.h>

// 基数排序

int radix_sort(int *pdata, int size)
{
    if (!pdata || size < 1)
    {
        return -1;
    }
    int i;
    int *tmp = calloc(size, sizeof(int));
    int count[10];
    int pos[10];
    if (!tmp)
    {
        printf("calloc memory failed\n");
        return -1;
    }

    // 根据最大元素，取得需要循环的最大轮次，最多32次
    int max = pdata[0];
    int loop_limit = 0;
    for (i = 1; i < size; i++)
    {
        if (pdata[i] > max)
        {
            max = pdata[i];
        }
    }
    while (max)
    {
        loop_limit++;
        max /= 10;
    }
    // printf("loop_limit is %d\n",loop_limit );
    int loop = 0;
    int base = 1;
    for (loop = 0; loop < loop_limit; loop++)
    {
        // 记录下每个桶有多少个元素，然后算出对应筒的元素在数组中的起始位置
        for (i = 0; i < 10; i++)
        {
            count[i] = 0;
            pos[i] = 0;
        }
        int index = 0;
        for (i = 0; i < size; i++)
        {
            index = ( pdata[i] / base ) % 10;
            count[ index ]++;
        }
        pos[0] = 0;
        for( i = 1; i < 10; i++ )
        {
            pos[i] = pos[ i-1] + count[ i - 1 ];
            // printf("pos[%d]=%d\tcount[%d]=%d\n",i, pos[i], i-1 , count[i-1]);
        }

        // 从末尾开始，依次将元素存到临时数组中
        for( i = size - 1 ; i >= 0; i-- )
        {
            index = ( pdata[i] / base ) % 10;
            tmp[ pos[index] + count[index] - 1] = pdata[i];
            count[ index] --;
        }
        base *= 10;

        // 将数据拷贝回原数组
        for( i = 0 ; i < size ; i++ )
        {
            pdata[i] = tmp[i];
        }

    }
    free(tmp);
    return 1;
}

int maximumGap(int *nums, int numsSize)
{
    if( !nums || numsSize <= 1 )
    {
        return 0;
    }
    radix_sort(nums, numsSize);
    int i; 
    int gap = 0;
    for( i = 1 ; i < numsSize ; i++ )
    {
        if( nums[i] - nums[i-1] > gap )
        {
            gap = nums[ i] - nums[i-1];
        }
    }
    return gap;

}
