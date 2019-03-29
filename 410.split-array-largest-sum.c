/*
 * @lc app=leetcode id=410 lang=c
 *
 * [410] Split Array Largest Sum
 *
 * https://leetcode.com/problems/split-array-largest-sum/description/
 *
 * algorithms
 * Hard (41.92%)
 * Total Accepted:    37.2K
 * Total Submissions: 88.7K
 * Testcase Example:  '[7,2,5,10,8]\n2'
 *
 * Given an array which consists of non-negative integers and an integer m, you
 * can split the array into m non-empty continuous subarrays. Write an
 * algorithm to minimize the largest sum among these m subarrays.
 * 
 * 
 * Note:
 * If n is the length of array, assume the following constraints are
 * satisfied:
 * 
 * 1 ≤ n ≤ 1000
 * 1 ≤ m ≤ min(50, n)
 * 
 * 
 * 
 * Examples: 
 * 
 * Input:
 * nums = [7,2,5,10,8]
 * m = 2
 * 
 * Output:
 * 18
 * 
 * Explanation:
 * There are four ways to split nums into two subarrays.
 * The best way is to split it into [7,2,5] and [10,8],
 * where the largest sum among the two subarrays is only 18.
 * 
 * 
 */

#include <stdlib.h>
#include <stdint.h>

#define max(a,b)  ( (a) > (b) ? (a) : (b) )
#define NOT_SET -1 



int my_split_array(int *nums, int numsSize, int m, long* precord, int row_size, double avg )
{
    if( !nums || !precord )
    {
        return 0;
    }
    int index = ( numsSize - 1) * row_size  + m - 1 ;
    if( precord[index] != NOT_SET )
    {
        return precord[index];
    }

    if( m < 1 )
    {
        return 0;
    }
    else if( m == 1 )
    {
        long sum = 0;
        int i; 
        for( i = 0 ; i < numsSize ; i++ )
        {
            sum += nums[i];
        }
        return precord[ index] =  sum ;
    }
    else
    {
        long min_value = INT64_MAX;
        int j ;
        long sum = 0;
        for( j = numsSize - 1 ; j >= m - 1 ; j-- )
        {
            sum += nums[j];
            long result = my_split_array(nums, j, m -1 , precord, row_size , avg) ;
            long temp = max(sum, result);
            if( temp < min_value )
            {
                min_value = temp;
            }
        }        
        return precord[ index ] =  min_value ;
    }   
}




int splitArray(int *nums, int numsSize, int m)
{

    if( !nums)
    {
        return 0;
    }
    if( numsSize < 1 || m < 1 )
    {
        return 0;
    }
    double ag = 0;
    long sum = 0;
    int i;
    long* precord = (long*)malloc( numsSize * m * sizeof(long) );
    if( precord )
    {
        for( i = 0 ; i < numsSize * m ; i++ )
        {
            precord[i] = NOT_SET;
        }
        return my_split_array(nums, numsSize, m ,precord, m , ag );
    }
    return 0;
}
