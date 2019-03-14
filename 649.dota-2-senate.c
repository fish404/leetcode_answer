/*
 * @lc app=leetcode id=649 lang=c
 *
 * [649] Dota2 Senate
 *
 * https://leetcode.com/problems/dota2-senate/description/
 *
 * algorithms
 * Medium (37.19%)
 * Total Accepted:    7.8K
 * Total Submissions: 20.9K
 * Testcase Example:  '"RD"'
 *
 * In the world of Dota2, there are two parties: the Radiant and the Dire.
 * 
 * The Dota2 senate consists of senators coming from two parties. Now the
 * senate wants to make a decision about a change in the Dota2 game. The voting
 * for this change is a round-based procedure. In each round, each senator can
 * exercise one of the two rights:
 * 
 * 
 * Ban one senator's right:
 * A senator can make another senator lose all his rights in this and all the
 * following rounds.
 * Announce the victory:
 * If this senator found the senators who still have rights to vote are all
 * from the same party, he can announce the victory and make the decision about
 * the change in the game.
 * 
 * 
 * 
 * 
 * Given a string representing each senator's party belonging. The character
 * 'R' and 'D' represent the Radiant party and the Dire party respectively.
 * Then if there are n senators, the size of the given string will be n.
 * 
 * The round-based procedure starts from the first senator to the last senator
 * in the given order. This procedure will last until the end of voting. All
 * the senators who have lost their rights will be skipped during the
 * procedure.
 * 
 * Suppose every senator is smart enough and will play the best strategy for
 * his own party, you need to predict which party will finally announce the
 * victory and make the change in the Dota2 game. The output should be Radiant
 * or Dire.
 * 
 * Example 1:
 * 
 * 
 * Input: "RD"
 * Output: "Radiant"
 * Explanation: The first senator comes from Radiant and he can just ban the
 * next senator's right in the round 1. 
 * And the second senator can't exercise any rights any more since his right
 * has been banned. 
 * And in the round 2, the first senator can just announce the victory since he
 * is the only guy in the senate who can vote.
 * 
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "RDD"
 * Output: "Dire"
 * Explanation: 
 * The first senator comes from Radiant and he can just ban the next senator's
 * right in the round 1. 
 * And the second senator can't exercise any rights anymore since his right has
 * been banned. 
 * And the third senator comes from Dire and he can ban the first senator's
 * right in the round 1. 
 * And in the round 2, the third senator can just announce the victory since he
 * is the only guy in the senate who can vote.
 * 
 * 
 * 
 * 
 * Note:
 * 
 * 
 * The length of the given string will in the range [1, 10,000].
 * 
 * 
 * 
 * 
 */
#include <stdio.h>
#include <string.h>


#define MAX_LEN 10000

#define PARTY_NAME_R "Radiant"
#define PARTY_NAME_D "Dire"

#define PARTY_ID_R 0
#define PARTY_ID_D 1


#define STATE_ALIVE 1
#define STATE_DEAD 0

struct voter
{
    char party;
    char state;
};

int     party_count[2] = {0 , 0 };
char*   party_name[2] = { PARTY_NAME_R , PARTY_NAME_D};

int is_opposite_all_dead(int party_id )
{
    return  party_count[!party_id] == 0  ? 1 : 0 ;
}

int ban_next_allive_opposite(struct voter* pv, int total, int index )
{
    if(!pv )
    {
        return -1;
    }
    int i;

    // 先检查右边
    for( i = index + 1; i < total ; i++ )
    {
        if( pv[i].state == STATE_ALIVE && pv[i].party != pv[index].party )
        {
            pv[i].state = STATE_DEAD;
            party_count[pv[i].party] --;
            // printf("%d:%d banned\n", i, pv[i].party);
            return 1;
        }
    }

    // 再检查左边
    for( i = 0; i < index ; i++ )
    {
        if( pv[i].state == STATE_ALIVE && pv[i].party != pv[index].party )
        {
            pv[i].state = STATE_DEAD;
            party_count[pv[i].party] --;
            // printf("%d:%d banned\n", i, pv[i].party);
            return 1;
        }
    }    
    return -1;
}

char *predictPartyVictory(char *senate)
{

    if (!senate)
    {
        return NULL;
    }
    int num_total = 0;
    struct voter voters[MAX_LEN];
    int i;
    char *pos = senate;
    for(i = 0; i < 2; i++ )
    {
        party_count[i] = 0;
    }
    i = 0;
    while( pos[i] != 0 )
    {
        voters[i].state = STATE_ALIVE;
        if (pos[i]  == 'D')
        {
            party_count[PARTY_ID_D]++;
            voters[i].party = PARTY_ID_D;
        }
        else
        {
            party_count[PARTY_ID_R]++;
            voters[i].party = PARTY_ID_R;
        }
        i++;
        num_total ++;
    }

    // printf("party d has %d\n", party_count[PARTY_ID_D]);
    // printf("party r has %d\n", party_count[PARTY_ID_R]);
    while (party_count[PARTY_ID_R] > 0 && party_count[PARTY_ID_D] > 0)
    {
        i = 0;
        for (i = 0; i < num_total; i++)
        {
            if (voters[i].state == STATE_ALIVE)
            {
                if (is_opposite_all_dead(voters[i].party)) // 对面阵营是否全部挂了，则宣布己方获胜
                {
                    printf("%s\n", party_name[voters[i].party]);
                    return  party_name[voters[i].party];
                }
                else // 禁止下一个即将表决的对方阵营的人
                {
                    ban_next_allive_opposite(voters, num_total, i);
                }
            }
        }
    }
    if( is_opposite_all_dead(PARTY_ID_R))
    {
        printf("%s\n", party_name[PARTY_ID_R]);
        return party_name[PARTY_ID_R];
    }
    else
    {
        printf("%s\n", party_name[PARTY_ID_D]);
        return party_name[PARTY_ID_D];
    }
    
}


// int main()
// {
//     char s[16]="RDD";
//     printf("%s\n", predictPartyVictory(s));
//     return 0;


// }   
