/*
 * @lc app=leetcode id=56 lang=c
 *
 * [56] Merge Intervals
 *
 * https://leetcode.com/problems/merge-intervals/description/
 *
 * algorithms
 * Medium (34.94%)
 * Total Accepted:    315.9K
 * Total Submissions: 901.8K
 * Testcase Example:  '[[1,3],[2,6],[8,10],[15,18]]'
 *
 * Given a collection of intervals, merge all overlapping intervals.
 * 
 * Example 1:
 * 
 * 
 * Input: [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 * Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into
 * [1,6].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: [[1,4],[4,5]]
 * Output: [[1,5]]
 * Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 * 
 */
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *pa, const void *pb);

void print_all(struct Interval *intervals, int size)
{
    if( !intervals )
    {
        return ;
    }
    int i ;
    for( i = 0; i < size; i++ )
    {
        printf("[%d,%d]\t", intervals[i].start, intervals[i].end);
    }
    printf("\n");
}

struct Interval *merge(struct Interval *intervals, int intervalsSize, int *returnSize)
{

    if (!intervals || intervalsSize < 1)
    {
        return intervals;
    }
    if (!returnSize)
    {
        return NULL;
    }

    qsort(intervals, intervalsSize, sizeof(struct Interval), cmp);

    // print_all(intervals, intervalsSize);

    struct Interval *ret = (struct Interval *)calloc(intervalsSize, sizeof(struct Interval));
    if (ret)
    {
        int i;
        int index = 0;
        ret[0] = intervals[0];
        for (i = 1; i < intervalsSize; i++)
        {
            if (ret[index].end >= intervals[i].start)
            {
                if( ret[index].end < intervals[i].end )
                {
                    ret[index].end = intervals[i].end;
                }               
            }
            else
            {
                index++;
                ret[index].start = intervals[i].start;
                ret[index].end = intervals[i].end;
            }
        }
        *returnSize = index + 1;
    }
    return ret;
}

int cmp(const void *pa, const void *pb)
{
    if (!pa || !pb)
    {
        return 0;
    }
    struct Interval *pleft = (struct Interval *)pa;
    struct Interval *pright = (struct Interval *)pb;

    if (pleft->start < pright->start)
    {
        return -1;
    }
    else if (pleft->start == pright->start)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
