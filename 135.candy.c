#include <stdio.h>
#include <stdlib.h>
#include "fun_math.h"




int my_square(int a);

int my_square(int a)
{
    return a * a;
}

int my_abs(int a)
{
    return  a >= 0 ? a : -a;
}

/*
* @lc app=leetcode id=135 lang=c
*
* [135] Candy
*
* https://leetcode.com/problems/candy/description/
*
* algorithms
* Hard (27.93%)
* Total Accepted:    98.9K
* Total Submissions: 353.9K
* Testcase Example:  '[1,0,2]'
*
* There are N children standing in a line. Each child is assigned a rating
* value.
*
* You are giving candies to these children subjected to the following
* requirements:
*
*
* Each child must have at least one candy.
* Children with a higher rating get more candies than their neighbors.
*
*
* What is the minimum candies you must give?
*
* Example 1:
*
*
* Input: [1,0,2]
* Output: 5
* Explanation: You can allocate to the first, second and third child with 2,
* 1, 2 candies respectively.
*
*
* Example 2:
*
*
* Input: [1,2,2]
* Output: 4
* Explanation: You can allocate to the first, second and third child with 1,
* 2, 1 candies respectively.
* ⁠            The third child gets 1 candy because it satisfies the above two
* conditions.
*
*
*/


int get_max_incr(int* parr, int num, int index)
{
    if (!parr || num < 1)
    {
        return 0;
    }
    if (index < 0 || index > num - 1)
    {
        return 0;
    }
    int left = 0;
    int right = 0;
    int i = index;
    while ( i > 0)
    {
        if (parr[i] > parr[i - 1])
        {
            left++;
            i--;
        }
        else
        {
            break;
        }
    }
    i = index;
    while (i < num - 1)
    {
        if (parr[i] > parr[i + 1])
        {
            right++;
            i++;
        }
        else
        {
            break;
        }
    }
    return left > right ? left : right;
    
}



#if 0

int candy(int* ratings, int ratingsSize) {

    if (!ratings)
    {
        return 0;
    }
    int* pcount = (int*)calloc(ratingsSize, sizeof(int));
    if (!pcount)
    {
        printf("calloc memory for pcount failed\n");
        return 0;
    }
    int i;
    for (i = 0; i < ratingsSize; i++)
    {
        pcount[i] = 1;
    }

    
    while (1)
    {
        int flag = 0;
        for (i = 0; i < ratingsSize; i++)
        {
            if (i - 1 >= 0)
            {
                if (ratings[i] > ratings[i - 1] && pcount[i] <= pcount[i - 1])
                {
                    flag++;
                    pcount[i] += (pcount[i - 1] - pcount[i] + 1);
                }
            }
            if (i + 1 < ratingsSize)
            {
                if (ratings[i] > ratings[i + 1] && pcount[i] <= pcount[i + 1])
                {
                    flag++;
                    pcount[i] += (pcount[i + 1] - pcount[i] + 1);
                }
            }
        }
        if (flag == 0)
        {
            break;
        }
       
    }

    int sum = 0;
    for (i = 0; i < ratingsSize; i++)
    {
        //printf("pcount[%d]=%d\t", i, pcount[i]);
        sum += pcount[i];
    }
    //printf("\n");
    //printf("");
    free(pcount);
    return sum;
}

#else


int candy(int* ratings, int ratingsSize) {

    if (!ratings)
    {
        return 0;
    }
    int* pcount = (int*)calloc(ratingsSize, sizeof(int));
    if (!pcount)
    {
        printf("calloc memory for pcount failed\n");
        return 0;
    }
    int i;
    for (i = 0; i < ratingsSize; i++)
    {
        pcount[i] = 1;
    }


    //while (1)
    {
        int flag = 0;
        for (i = 0; i < ratingsSize; i++)
        {
            int incr = get_max_incr(ratings, ratingsSize, i);
            pcount[i] += incr;

            //if (i - 1 >= 0)
            //{
            //    if (ratings[i] > ratings[i - 1] && pcount[i] <= pcount[i - 1])
            //    {
            //        flag++;
            //        pcount[i] += (pcount[i - 1] - pcount[i] + 1);
            //    }
            //}
            //if (i + 1 < ratingsSize)
            //{
            //    if (ratings[i] > ratings[i + 1] && pcount[i] <= pcount[i + 1])
            //    {
            //        flag++;
            //        pcount[i] += (pcount[i + 1] - pcount[i] + 1);
            //    }
            //}
        }
        //if (flag == 0)
        //{
        //    break;
        //}

    }

    int sum = 0;
    for (i = 0; i < ratingsSize; i++)
    {
        //printf("pcount[%d]=%d\t", i, pcount[i]);
        sum += pcount[i];
    }
    //printf("\n");
    //printf("");
    free(pcount);
    return sum;
}











#endif 