/*
 * @lc app=leetcode id=403 lang=c
 *
 * [403] Frog Jump
 *
 * https://leetcode.com/problems/frog-jump/description/
 *
 * algorithms
 * Hard (35.54%)
 * Total Accepted:    47.6K
 * Total Submissions: 133.8K
 * Testcase Example:  '[0,1,3,4,5,7,9,10,12]'
 *
 * A frog is crossing a river. The river is divided into x units and at each
 * unit there may or may not exist a stone. The frog can jump on a stone, but
 * it must not jump into the water.
 * 
 * Given a list of stones' positions (in units) in sorted ascending order,
 * determine if the frog is able to cross the river by landing on the last
 * stone. Initially, the frog is on the first stone and assume the first jump
 * must be 1 unit.
 * 
 * 
 * If the frog's last jump was k units, then its next jump must be either k -
 * 1, k, or k + 1 units. Note that the frog can only jump in the forward
 * direction.
 * 
 * Note:
 * 
 * The number of stones is ≥ 2 and is < 1,100.
 * Each stone's position will be a non-negative integer < 2^31.
 * The first stone's position is always 0.
 * 
 * 
 * 
 * Example 1:
 * 
 * [0,1,3,5,6,8,12,17]
 * 
 * There are a total of 8 stones.
 * The first stone at the 0th unit, second stone at the 1st unit,
 * third stone at the 3rd unit, and so on...
 * The last stone at the 17th unit.
 * 
 * Return true. The frog can jump to the last stone by jumping 
 * 1 unit to the 2nd stone, then 2 units to the 3rd stone, then 
 * 2 units to the 4th stone, then 3 units to the 6th stone, 
 * 4 units to the 7th stone, and 5 units to the 8th stone.
 * 
 * 
 * 
 * Example 2:
 * 
 * [0,1,2,3,4,8,9,11]
 * 
 * Return false. There is no way to jump to the last stone as 
 * the gap between the 5th and 6th stone is too large.
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>

struct last_jump_len_set
{
    int *parray;
    int count;
};

int is_k_in_set(struct last_jump_len_set *pset, int k)
{
    if (!pset)
    {
        return 0;
    }
    int i = 0;
    for (i = 0; i < pset->count; i++)
    {
        if (pset->parray[i] == k)
        {
            return 1;
        }
    }
    return 0;
}

bool canCross(int *stones, int stonesSize)
{

    if (!stones || stonesSize < 1)
    {
        return false;
    }
    struct last_jump_len_set *pall_stone_jump = (struct last_jump_len_set *)calloc(stonesSize, sizeof(struct last_jump_len_set));
    if (!pall_stone_jump)
    {
        return 0;
    }
    int i;
    for (i = 1; i < stonesSize; i++)
    {
        pall_stone_jump[i].parray = (int *)calloc(i, sizeof(int));
        if (!pall_stone_jump[i].parray)
        {
            return 0;
        }
        if (i == 1)
        {
            if (stones[i] != 1)
            {
                continue;
            }
            else
            {
                pall_stone_jump[i].parray[0] = 1;
                pall_stone_jump[i].count = 1;
            }

            continue;
        }
        else
        {
            int j;
            for (j = i - 1; j > 0; j--)
            {
                int dst = stones[i] - stones[j];
                int k;
                for (k = -1; k < 2; k++)
                {
                    if (dst + k > 0)
                    {
                        if (is_k_in_set(&pall_stone_jump[j], dst + k))
                        {
                            pall_stone_jump[i].parray[pall_stone_jump[i].count] = dst;
                            pall_stone_jump[i].count++;
                            break;
                        }
                    }
                }
            }
        }
    }
    int flag = pall_stone_jump[stonesSize - 1].count > 0 ? 1 : 0;
    for (i = 0; i < stonesSize; i++)
    {
        if (pall_stone_jump[i].parray)
        {
            free(pall_stone_jump[i].parray);
        }
    }
    free(pall_stone_jump);
    return flag;
}
