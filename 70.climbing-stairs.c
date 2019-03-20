/*
 * @lc app=leetcode id=70 lang=c
 *
 * [70] Climbing Stairs
 *
 * https://leetcode.com/problems/climbing-stairs/description/
 *
 * algorithms
 * Easy (43.58%)
 * Total Accepted:    367.7K
 * Total Submissions: 842.6K
 * Testcase Example:  '2'
 *
 * You are climbing a stair case. It takes n steps to reach to the top.
 * 
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can
 * you climb to the top?
 * 
 * Note: Given n will be a positive integer.
 * 
 * Example 1:
 * 
 * 
 * Input: 2
 * Output: 2
 * Explanation: There are two ways to climb to the top.
 * 1. 1 step + 1 step
 * 2. 2 steps
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: 3
 * Output: 3
 * Explanation: There are three ways to climb to the top.
 * 1. 1 step + 1 step + 1 step
 * 2. 1 step + 2 steps
 * 3. 2 steps + 1 step
 * 
 * 
 */


int climbStairs(int n) {
    

    if( n == 1 )
    {
        return n;
    }
    else if ( n == 2)
    {
        return 2;
    }
    else
    {
        int f_n_1 = 1;
        int f_n_2 = 2;   
        int i;
        int ret = 0;
        for( i = 3; i <= n; i++ )
        {
            ret = f_n_1 + f_n_2;
            f_n_1 = f_n_2;
            f_n_2 = ret;
        }
        return ret;
    }
}

