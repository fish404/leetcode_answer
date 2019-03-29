/*
 * @lc app=leetcode id=32 lang=c
 *
 * [32] Longest Valid Parentheses
 *
 * https://leetcode.com/problems/longest-valid-parentheses/description/
 *
 * algorithms
 * Hard (25.10%)
 * Total Accepted:    178.7K
 * Total Submissions: 712K
 * Testcase Example:  '"(()"'
 *
 * Given a string containing just the characters '(' and ')', find the length
 * of the longest valid (well-formed) parentheses substring.
 * 
 * Example 1:
 * 
 * 
 * Input: "(()"
 * Output: 2
 * Explanation: The longest valid parentheses substring is "()"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: ")()())"
 * Output: 4
 * Explanation: The longest valid parentheses substring is "()()"
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_STACK_SIZE 64

typedef int element_type;

#define LEFT -2
#define RIGHT -1

struct stack
{
    element_type *parray;
    int capacity;
    int count;
};

int init(struct stack *pstack)
{
    if (!pstack)
    {
        return -1;
    }
    pstack->capacity = DEFAULT_STACK_SIZE;
    pstack->count = 0;
    pstack->parray = (element_type *)calloc(pstack->capacity, sizeof(element_type));
    if (!pstack->parray)
    {
        return -2;
    }
    return 1;
}

int push(struct stack *pstack, element_type value)
{
    if (!pstack)
    {
        return -1;
    }
    if (pstack->count >= pstack->capacity)
    {
        pstack->capacity *= 2;
        pstack->parray = (element_type *)realloc(pstack->parray, pstack->capacity * sizeof(element_type));
        if (!pstack->parray)
        {
            return -2;
        }
    }
    pstack->parray[pstack->count++] = value;
    return 1;
}

// 取出栈顶的元素
int pop(struct stack *pstack, element_type *pvalue)
{
    if (!pstack)
    {
        return -1;
    }
    if (pstack->count > 0)
    {
        if (pvalue)
        {
            *pvalue = pstack->parray[--pstack->count];
        }
        else
        {
            pstack->count--;
        }
        

        return 1;
    }
    return 0;
}

// 只查看栈顶元素，不取出
int peek(struct stack *pstack, element_type *pvalue)
{
    if (!pstack || !pvalue)
    {
        return -1;
    }
    if (pstack->count > 0)
    {
        *pvalue = pstack->parray[pstack->count - 1];
        return 1;
    }
    return 0;
}

int get_max(struct stack *pstack, element_type *pvalue)
{
    if (!pstack || !pvalue)
    {
        return -1;
    }
    int i;
    element_type tmp = 0;
    for (i = 0; i < pstack->count; i++)
    {
        // printf("%d\t", pstack->parray[i]);
        if (pstack->parray[i] > tmp)
        {
            tmp = pstack->parray[i];
        }
    }
    *pvalue = tmp;
    return tmp > 0 ? 1 : 0;
}

void merge_top_numbers(struct stack *pstack)
{
    if (!pstack)
    {
        return;
    }
    int ret = 0;
    int num1 = 0;
    int num2 = 0;
    while (pstack->count >= 2)
    {
        if (pstack->parray[pstack->count -1] > 0 && pstack->parray[pstack->count - 2 ] > 0 )
        {
            pop(pstack, &num1);
            pop(pstack, &num2);
            push(pstack, num1 + num2);
        }
        else
        {
            break;
        }
    }
}

int longestValidParentheses(char *s)
{
    if (!s)
    {
        return 0;
    }
    struct stack st;
    init(&st);
    int size = strlen(s);
    int i;
    int ret = 0;
    element_type tmp = 0;
    char *ptr = s;
    for (i = 0; i < size; i++)
    {
        if (ptr[i] == '(') // 左括号
        {
            push(&st, LEFT);
        }
        else // 右括号
        {
            if (peek(&st, &tmp) == 1)
            {
                if (tmp == LEFT)
                {
                    pop(&st, NULL);
                    push(&st, 2);
                    merge_top_numbers(&st);
                    continue;
                }
                else if (tmp > 0)
                {
                    element_type priev_count = 0;
                    pop(&st, &priev_count);
                    if ((peek(&st, &tmp) == 1) && (tmp == LEFT))
                    {
                        pop(&st, NULL);
                        priev_count += 2;
                        push(&st, priev_count);
                        merge_top_numbers(&st);
                        continue;
                    }
                    push(&st, priev_count);
                    push(&st, RIGHT);
                }
                else
                {
                    push(&st, RIGHT);
                }
            }
            else
            {
                push(&st, RIGHT);
            }
        }
    }
    if (get_max(&st, &tmp) == 1)
    {
        return tmp;
    }
    return 0;
}
