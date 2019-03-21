/*
 * @lc app=leetcode id=540 lang=c
 *
 * [540] Single Element in a Sorted Array
 *
 * https://leetcode.com/problems/single-element-in-a-sorted-array/description/
 *
 * algorithms
 * Medium (57.18%)
 * Total Accepted:    49.2K
 * Total Submissions: 86.1K
 * Testcase Example:  '[1,1,2]'
 *
 * 
 * Given a sorted array consisting of only integers where every element appears
 * twice except for one element which appears once. Find this single element
 * that appears only once. 
 * 
 * 
 * Example 1:
 * 
 * Input: [1,1,2,3,3,4,4,8,8]
 * Output: 2
 * 
 * 
 * 
 * Example 2:
 * 
 * Input: [3,3,7,7,10,11,11]
 * Output: 10
 * 
 * 
 * 
 * Note:
 * Your solution should run in O(log n) time and O(1) space.
 * 
 * 
 */
int singleNonDuplicate(int *nums, int numsSize)
{

    if (!nums)
    {
        return -1;
    }
    return search_single(nums, numsSize);
}

int search_single(int *parr, int size)
{
    if (!parr || size < 1)
    {
        return -1;
    }
    if (size == 1)
    {
        return parr[0];
    }
    else // 要查找的数组 size 是个奇数
    {
        int median_index = size / 2;
        if (parr[median_index] == parr[median_index - 1])
        {
            if ((size / 2 - 1) % 2 == 1) // 在左半边
            {
                return search_single(parr, size / 2 );
            }
            else // 在右半边
            {
                return search_single(parr + median_index + 1, size/2 );
            }
        }
        else if (parr[median_index] == parr[median_index + 1])
        {
            if ((size / 2 - 1) % 2 == 1) // 在右半边
            {
                return search_single(parr + median_index + 2, size / 2 - 1);
            }
            else // 在左半边
            {
                return search_single(parr, size/2 );
            }          
        }
        else
        {
            return parr[median_index];
        }
    }
}
