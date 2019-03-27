/*
 * @lc app=leetcode id=139 lang=c
 *
 * [139] Word Break
 *
 * https://leetcode.com/problems/word-break/description/
 *
 * algorithms
 * Medium (34.47%)
 * Total Accepted:    313.2K
 * Total Submissions: 904K
 * Testcase Example:  '"leetcode"\n["leet","code"]'
 *
 * Given a non-empty string s and a dictionary wordDict containing a list of
 * non-empty words, determine if s can be segmented into a space-separated
 * sequence of one or more dictionary words.
 * 
 * Note:
 * 
 * 
 * The same word in the dictionary may be reused multiple times in the
 * segmentation.
 * You may assume the dictionary does not contain duplicate words.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "leetcode", wordDict = ["leet", "code"]
 * Output: true
 * Explanation: Return true because "leetcode" can be segmented as "leet
 * code".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "applepenapple", wordDict = ["apple", "pen"]
 * Output: true
 * Explanation: Return true because "applepenapple" can be segmented as "apple
 * pen apple".
 * Note that you are allowed to reuse a dictionary word.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
 * Output: false
 * 
 * 
 */

#include <string.h>
#include <stdio.h>

bool word_break_dp(char *s, char **wordDict, int wordDictSize, int index, char *p);


bool wordBreak(char *s, char **wordDict, int wordDictSize)
{

    if (!s || !wordDict)
    {
        return false;
    }
    if (wordDictSize < 1)
    {
        return false;
    }
    int size = strlen(s);
    char *pRecord ;
    pRecord = (char *)malloc(size * sizeof(char));
    int i;
    if ( !pRecord )
    {
        printf("malloc failed for pRecord\n");
        return 0;
    }
    for( i = 0; i < size ; i++ )
    {
        pRecord[i] = -1;
    }
    int ret = word_break_dp(s, wordDict, wordDictSize, 0, pRecord);
    free(pRecord );  
    return ret;

}

bool word_break_dp(char *s, char **wordDict, int wordDictSize, int index, char *p)
{
    if (!s || !wordDict || !p)
    {
        return false;
    } 
    if( p[index] > -1 )
    {
        return p[index];
    }
    int i = 0;
    for (i = 0; i < wordDictSize; i++)
    {
        if (strncmp(s, wordDict[i], strlen(wordDict[i])) == 0)
        {
            if (*(s + strlen(wordDict[i])) == 0)
            {
                p[index] = 1;
                return true;
            }
            else
            {
                if ( word_break_dp(s + strlen(wordDict[i]), wordDict, wordDictSize, index + strlen(wordDict[i]), p ) == true ) 
                {
                    p[index ] = 1;
                    return true;
                }
            }
        }
    }
    p[index] = 0;
    return false;
}
