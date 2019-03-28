/*
 * @lc app=leetcode id=639 lang=c
 *
 * [639] Decode Ways II
 *
 * https://leetcode.com/problems/decode-ways-ii/description/
 *
 * algorithms
 * Hard (24.82%)
 * Total Accepted:    20.1K
 * Total Submissions: 81K
 * Testcase Example:  '"*"'
 *
 * 
 * A message containing letters from A-Z is being encoded to numbers using the
 * following mapping way:
 * 
 * 
 * 
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * 
 * 
 * 
 * Beyond that, now the encoded string can also contain the character '*',
 * which can be treated as one of the numbers from 1 to 9.
 * 
 * 
 * 
 * 
 * Given the encoded message containing digits and the character '*', return
 * the total number of ways to decode it.
 * 
 * 
 * 
 * Also, since the answer may be very large, you should return the output mod
 * 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * Input: "*"
 * Output: 9
 * Explanation: The encoded message can be decoded to the string: "A", "B",
 * "C", "D", "E", "F", "G", "H", "I".
 * 
 * 
 * 
 * Example 2:
 * 
 * Input: "1*"
 * Output: 9 + 9 = 18
 * 
 * 
 * 
 * Note:
 * 
 * The length of the input string will fit in range [1, 10^5].
 * The input string will only contain the character '*' and digits '0' - '9'.
 * 
 * 
 */



#define  MOD_CONST  1000000007


// 按照这样的顺序来存储2个字符的解码组合数量
//     0    1   2   3   4   5   6   7   8   9   *
// 0
// 1
// 2
// 3
// 4
// 5
// 6
// 7
// 8
// 9
// *
// 这里记录的是，如果一个原文编码后变成了2个字符的情况，以此2个字符整体作为1个待解码单元，可以得到的解码组合数量。
static char g_two_code[11][11] = 
{
    0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,9,  // 11 到 1*
    1,1,1,1,1,1,1,0,0,0,6,
    0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,
    2,2,2,2,2,2,2,1,1,1,15
};

static char g_one_code[11] = 
{
    0,1,1,1,1,1,1,1,1,1,9
};
#define  MAX_SIZE 100001 
#define  INITIAL_VALUE  -1
static long record[MAX_SIZE];

int  get_one_char_decode_number(char c)  
{
    int index = 0;
    if( c == '*')
    {
        index = 10;
    }
    else
    {
        index = c - '0';
    }
    assert( index <= 10 );
    assert( index >= 0 );
    return g_one_code[index];
}

int  get_tow_char_decode_number(char c1, char c2)  
{
    int index1 = 0;
    int index2 = 0;
    if( c1 == '*')
    {
        index1 = 10;
    }
    else
    {
        index1 = c1 - '0';
    }

    if( c2 == '*')
    {
        index2 = 10;
    }
    else
    {
        index2 = c2 - '0';
    }
    assert( index1 <= 10 );
    assert( index1 >= 0 );
    assert( index2 <= 10 );
    assert( index2 >= 0 );    
    return g_two_code[index1][index2];
}


long get_decode_num( char* s, int index )
{

    if(!s )
    {
        return 0;
    }
    if( strlen(s) < 1)
    {
        return record[index] = 0;
    }
    if( record[index] != INITIAL_VALUE)
    {
        return record[index];
    }
    if( strlen(s) == 1 )
    {
        
        return record[index] = get_one_char_decode_number(*s);
    }
    else if( strlen(s) == 2 )
    {
        return  record[index] = get_tow_char_decode_number(*s, *(s+1)) + get_one_char_decode_number(*s) * get_one_char_decode_number(*(s+1));
    }
    else
    {
        long count =  get_one_char_decode_number(*s) * get_decode_num( s+1 , index + 1) +  get_tow_char_decode_number(*s, *(s+1)) * get_decode_num( s+2, index + 2);
        while( count > MOD_CONST )
        {
            count -= MOD_CONST;
        }
        return  record[index] = count;
    }
}


int numDecodings(char* s) {
    if(!s )
    {
        return 0;
    }
    int i; 
    for( i = 0; i < MAX_SIZE; i++ )
    {
        record[i] = INITIAL_VALUE;
    }
    int count = get_decode_num(s, 0) % MOD_CONST ;
    return count;
}

