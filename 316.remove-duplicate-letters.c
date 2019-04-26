/*
* @lc app=leetcode id=316 lang=c
*
* [316] Remove Duplicate Letters
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_min(char *s, char* pused,  int start, int end)
{
    if (!s || !pused ||  start > end)
    {
        return -1;
    }
    int i ;
    int index = start;
    int min = s[start];
    for (i = start + 1; i <= end; i++)
    {
        if ( s[i] < min && pused[ s[i] - 'a'] == 0 )
        {
            min = s[i];
            index = i;
        }
    }
    return index;
}


int  get_next_must(char* s , char* pused, int* last_index, int start , int end )
{
    if (!s || !last_index)
    {
        return -1;
    }
    int i;
    int ret = end;
    for (i = start; i <= end; i++ )
    {
        int tmp = last_index[s[i] - 'a'] ;
        if( pused[ s[i] - 'a' ] == 0 && tmp != -1  && tmp < ret )
        {
            ret = tmp;
        }
    }
    return ret;
}

#define  handle(x)   do{ pstr[index] = (x);  index++;  has_used[ (x) - 'a'] = 1; } while(0)


char *removeDuplicateLetters(char *s)
{

    if (!s)
    {
        return NULL;
    }
    int len = strlen(s);
    int count[26] = { 0 };
    char has_used[26] = { 0 };
    int last[26] ;
    int i;
    for (i = 0; i < 26; i++)
    {
        count[i] = 0;
        has_used[i] = 0;
        last[i] = -1;
    }

    char *p = s;
    while ( *p )
    {
        count[(*p - 'a')]++;
        p++;
    }

    for (i = len - 1; i >= 0; i--)
    {
        if (last[s[i] - 'a'] == -1)
        {
            last[s[i] - 'a'] = i;
        }
    }
    int num = 0;
    for (i = 0; i < 26; i++)
    {
        if (count[i] > 0)
        {
            num++;
        }
    }
    char *pstr = (char *)calloc(num + 1, sizeof(char));
    if (!pstr)
    {
        printf("calloc memory for pstr failed\n");
        return NULL;
    }
    int index = 0;
    for (i = 0; i < len; i++)
    {
        if (has_used[s[i] - 'a'] > 0 ) // 这个字母已经用了，跳过
        {
            continue;
        }
        else if ( i == last[s[i] - 'a']) // 该字母最后一次出现
        {
            handle(s[i]);
            continue;
        }
        else
        {
            int last_index = last[s[i] - 'a'];
            int must_index = get_next_must(s, has_used, last, i, last_index);
            int min_index = find_min(s, has_used, i, must_index); // 给定范围内，最小的字母的下标           
            handle( s[min_index] );
            i = min_index;
        }
    }
    return pstr;
}
