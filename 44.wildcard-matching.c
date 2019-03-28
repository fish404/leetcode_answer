/*
 * @lc app=leetcode id=44 lang=c
 *
 * [44] Wildcard Matching
 *
 * https://leetcode.com/problems/wildcard-matching/description/
 *
 * algorithms
 * Hard (22.50%)
 * Total Accepted:    166.9K
 * Total Submissions: 741.6K
 * Testcase Example:  '"aa"\n"a"'
 *
 * Given an input string (s) and a pattern (p), implement wildcard pattern
 * matching with support for '?' and '*'.
 * 
 * 
 * '?' Matches any single character.  
 * '*' Matches any sequence of characters (including the empty sequence).
 * 
 * 
 * The matching should cover the entire input string (not partial).
 * 
 * Note:
 * 
 * 
 * s could be empty and contains only lowercase letters a-z.
 * p could be empty and contains only lowercase letters a-z, and characters
 * like ? or *.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input:
 * s = "aa"
 * p = "a"
 * Output: false
 * Explanation: "a" does not match the entire string "aa".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input:
 * s = "aa"
 * p = "*"
 * Output: true
 * Explanation: '*' matches any sequence.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input:
 * s = "cb"
 * p = "?a"
 * Output: false
 * Explanation: '?' matches 'c', but the second letter is 'a', which does not
 * match 'b'.
 * 
 * 
 * Example 4:
 * 
 * 
 * Input:
 * s = "adceb"
 * p = "*a*b"
 * Output: true
 * Explanation: The first '*' matches the empty sequence, while the second '*'
 * matches the substring "dce".
 * 
 * 
 * Example 5:
 * 
 * 
 * Input:
 * s = "acdcb"
 * p = "a*c?b"
 * Output: false
 * 
 * 
 */

#ifndef bool
#define bool char
#endif
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif









int count_wild_char(char *p)
{
    int num = 0;
    while ( *p != 0 )
    {
        if (*p == '*')
        {
            num++;
        }
        p++;
    }
    return num;
}


#define     INITIAL_VALUE   -1 
char** p_g_record = NULL;

bool is_match(char* s, char* p, int index1, int index2)
{
    if(!s || !p )
    {
        return false;
    }
    // printf("s is %s p is %s index1=%d index2=%d [%d][%d]=%d\n", s, p, index1, index2, index1, index2,p_g_record[index1][index2]);
    if( p_g_record[index1][index2] != INITIAL_VALUE )
    {
        return p_g_record[index1][index2];
    }

   if (*s == 0) // 查找串已经到了末尾，模式串如果也到了末尾，或者还有字符但全部都是*，都算匹配成功
    {
        if (strlen(p) == count_wild_char(p))
        {
            return p_g_record[index1][index2] = true;
        }
        else
        {
            return p_g_record[index1][index2] = false;
        }
    }

    if (*p == 0)
    {
        if (strlen(s) == 0)
        {
            return p_g_record[index1][index2] = true;
        }
        else
        {
            return p_g_record[index1][index2] = false;
        }
    }

    // 还没有结束，模式串和串都没有到尾，先判断当前
    if (*p == '*')
    {
        if (strlen(p) == count_wild_char(p))
        {
            return p_g_record[index1][index2] = true;
        }
        else
        {
            int i = 0;
            int len = strlen(s) - ( strlen(p + 1) - count_wild_char(p + 1) );
            for (i = 0; i <= len; i++)
            {
                if (is_match(s + i, p + 1,index1+i, index2+1) == true)
                {
                    return p_g_record[index1][index2] = true;
                }
            }
            return p_g_record[index1][index2] = false;
        }        
    }
    else if (*p == '?')
    {
        return p_g_record[index1][index2] = is_match(s + 1, p + 1,index1+1, index2+1);
    }
    else
    {
        if (*p == *s)
        {
            return p_g_record[index1][index2] = is_match(s + 1, p + 1, index1+1, index2+1);
        }
        else
        {
            return p_g_record[index1][index2] = false;
        }
    }

}



bool isMatch(char *s, char *p)
{
    if (!s || !p)
    {
        return false;
    }
    // printf("s is %s p is %s\n", s, p);
    p_g_record = (char**) malloc((strlen(s) + 1 ) * sizeof(char*) );
    if( !p_g_record )
    {
        return false;
    }

    int i, j;
    for(i = 0; i < strlen(s) + 1; i++)
    {
        p_g_record[i] = (char*)malloc( (strlen(p) + 1)  * sizeof(char));
        if( ! p_g_record[i] )
        {
            return false;
        }
        for(j = 0; j < strlen(p) + 1; j++)
        {
            p_g_record[i][j] = INITIAL_VALUE;
        }
    }
    bool ret = is_match(s, p, 0 ,0);
    for(i = 0; i < strlen(s) + 1; i++)
    {
        free(p_g_record[i]);
    }
    free(p_g_record);
    return ret;
}
