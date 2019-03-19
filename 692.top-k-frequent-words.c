/*
 * @lc app=leetcode id=692 lang=c
 *
 * [692] Top K Frequent Words
 *
 * https://leetcode.com/problems/top-k-frequent-words/description/
 *
 * algorithms
 * Medium (44.89%)
 * Total Accepted:    54.2K
 * Total Submissions: 120.5K
 * Testcase Example:  '["i", "love", "leetcode", "i", "love", "coding"]\n2'
 *
 * Given a non-empty list of words, return the k most frequent elements.
 * Your answer should be sorted by frequency from highest to lowest. If two
 * words have the same frequency, then the word with the lower alphabetical
 * order comes first.
 * 
 * Example 1:
 * 
 * Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
 * Output: ["i", "love"]
 * Explanation: "i" and "love" are the two most frequent words.
 * ⁠   Note that "i" comes before "love" due to a lower alphabetical order.
 * 
 * 
 * 
 * Example 2:
 * 
 * Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is",
 * "is"], k = 4
 * Output: ["the", "is", "sunny", "day"]
 * Explanation: "the", "is", "sunny" and "day" are the four most frequent
 * words,
 * ⁠   with the number of occurrence being 4, 3, 2 and 1 respectively.
 * 
 * 
 * 
 * Note:
 * 
 * You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
 * Input words contain only lowercase letters.
 * 
 * 
 * 
 * Follow up:
 * 
 * Try to solve it in O(n log k) time and O(n) extra space.
 * 
 * 
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*********************************************************************************************************/
// 此处是hash的定义，用于单词出现次数统计
#define FACTOR 5
#define BITS_SHIFT_NUM 5
#define MAX_PROCESS_LEN 12 // 字符串中参与计算的字符数，最多从前面开始取这么多个字符

#define min(a, b) ((a) < (b) ? (a) : (b))
// 计算单词的hash值
long get_str_sum(char *str)
{
    long sum = 0;
    if (str)
    {
        int i;
        int limit = min(MAX_PROCESS_LEN, strlen(str));
        for (i = 0; i < limit; i++)
        {
            sum = (sum << BITS_SHIFT_NUM) + (str[i] - 'a');
        }
        // printf("str is %s sum is %ld\n", str, sum);
    }
    return sum;
}

struct node_string
{
    char *pstr;
    int count;
};

struct hash_string;

// typedef int (*hash_string_insert)(struct hash_string *phash, char *str);

int hash_string_insert_str(struct hash_string *phash, char *str);
void hash_string_initial(struct hash_string *phash, int size);
void hash_string_free(struct hash_string *phash);

struct hash_string
{
    struct node_string *parray;
    int capacity;  // 容量
    int total;     // 总插入的元素个数
    int effective; // 实际占据的坑位
};

void hash_string_initial(struct hash_string *phash, int size)
{
    if (!phash || size < 0)
    {
        return;
    }
    phash->capacity = size * FACTOR;
    phash->total = 0;
    phash->effective;
    // phash->insert = hash_string_insert_str;
    phash->parray = (struct node_string *)calloc(FACTOR * size, sizeof(struct node_string));
    if (phash->parray == NULL)
    {
        printf("为parray 分配空间失败\n");
        return;
    }
}

void hash_string_free(struct hash_string *phash)
{
    if (phash)
    {
        if (phash->parray)
        {
            free(phash->parray);
        }
    }
}

int hash_string_insert_str(struct hash_string *phash, char *str)
{
    if (!phash || !str)
    {
        return -1;
    }
    int ret = 1;
    long sum = get_str_sum(str);
    int index = sum % phash->capacity;
    int find_count = 1;
    while (phash->parray[index].pstr != NULL)
    {
        if (strcmp(phash->parray[index].pstr, str) == 0) // 该元素已经存在hash中了
        {
            phash->parray[index].count++;
            phash->total++;
            break;
        }
        else
        {
            find_count++;
            if (find_count >= phash->capacity)
            {
                printf("插入失败\n");
                break;
            }
            index = (index + 1) % phash->capacity;
        }
    }
    if (phash->parray[index].pstr == NULL) // 第一次插入该元素
    {
        phash->parray[index].pstr = strdup(str);
        if (phash->parray[index].pstr)
        {
            phash->parray[index].count = 1;
            phash->total++;
            phash->effective++;
        }
        else
        {
            printf(" 插入元素 %s 失败\n", str);
            ret = -1;
        }
    }
    // printf("插入元素 %s 查找次数 %d\n", str, find_count);
    return ret;
}

//***********************************************************************************************
// 此处是堆的数据结构

enum heap_mode
{
    HEAP_MODE_LITTLE = 0,
    HEAP_MODE_BIG = 1,
};

struct heap_str
{
    struct node_string **parray;
    int num;
    int capacity;
    enum heap_mode mode;
};


int is_less(struct node_string *pa, struct node_string *pb)
{
    if (!pa || !pb)
    {
        return 0;
    }
    if (pa->count < pb->count)
    {
        return 1;
    }
    else if (pa->count == pb->count)
    {
        if (strcmp(pa->pstr, pb->pstr) > 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int is_larger(struct node_string *pa, struct node_string *pb)
{
    if (!pa || !pb)
    {
        return 0;
    }
    if (pa->count > pb->count)
    {
        return 1;
    }
    else if (pa->count == pb->count)
    {
        if (strcmp(pa->pstr, pb->pstr) < 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int get_min_son_index(struct node_string **parray, int index, int limit_index)
{
    if (!parray || index >= limit_index)
    {
        return index;
    }
    int left_index = 2 * index + 1;
    int right_index = 2 * index + 2;
    if (left_index > limit_index) // 没有孩子
    {
        return index;
    }
    if (right_index > limit_index) // 只有左孩子
    {
        return left_index;
    }
    else // 有2个孩子
    {
        return   is_less(parray[left_index], parray[right_index] )  ? left_index :  right_index ;   
    }
}

int get_max_son_index(struct node_string **parray, int index, int limit_index)
{
    if (!parray || index >= limit_index)
    {
        return index;
    }
    int left_index = 2 * index + 1;
    int right_index = 2 * index + 2;
    if (left_index > limit_index) // 没有孩子
    {
        return index;
    }
    if (right_index > limit_index) // 只有左孩子
    {
        return left_index;
    }
    else // 有2个孩子
    {
        if (parray[left_index]->count > parray[right_index]->count)
        {
            return left_index;
        }
        else if (parray[left_index]->count == parray[right_index]->count)
        {
             return   is_larger(parray[left_index], parray[right_index] )  ? left_index :  right_index ; 
        }
        else
        {
            return right_index;
        }
    }
}



void settle_node(struct heap_str *pheap, int index)
{
    if (!pheap)
    {
        return;
    }
    if (pheap->num <= 1)
    {
        return;
    }
    int limit_index = pheap->num - 1;

    int pos = 0;
    int i = index;
    while (i < limit_index)
    {
        if (pheap->mode == HEAP_MODE_BIG)
        {
            pos = get_max_son_index(pheap->parray, i, limit_index);
            if (pos > i && is_larger(pheap->parray[pos], pheap->parray[i]))
            {
                struct node_string *tmp = pheap->parray[i];
                pheap->parray[i] = pheap->parray[pos];
                pheap->parray[pos] = tmp;
                i = pos;
            }
            else
            {
                break;
            }
        }
        else
        {
            pos = get_min_son_index(pheap->parray, i, limit_index);
            if (pos > i && is_less(pheap->parray[pos], pheap->parray[i]))
            {
                struct node_string *tmp = pheap->parray[i];
                pheap->parray[i] = pheap->parray[pos];
                pheap->parray[pos] = tmp;
                i = pos;
            }
            else
            {
                break;
            }
        }
    }
}

// mode表示对的模式， 1 代表大顶堆， 0 代表小顶堆
struct heap_str *build_heap(struct node_string **parray, int num, enum heap_mode mode)
{
    int i;
    int index = 0;
    if (!parray || num < 1)
    {
        return NULL;
    }
    struct heap_str *pret = (struct heap_str *)malloc(sizeof(struct heap_str));
    if (!pret)
    {
        printf("分配堆结构失败\n");
        return NULL;
    }
    pret->parray = (struct node_string **)calloc(num, sizeof(struct node_string *));
    if (!pret->parray)
    {
        printf("分配堆数组失败\n");
        return NULL;
    }
    pret->capacity = num;
    pret->num = num;
    pret->mode = mode;
    for (i = 0; i < num; i++)
    {
        pret->parray[i] = parray[i];
    }
    if (num == 1) // 如果只有1个元素，直接就是堆了
    {
        return pret;
    }
    // 到这里表明 num >= 2
    index = (num - 2) / 2; //开始检查的下标
    while (index >= 0)
    {
        settle_node(pret, index);
        index--;
    }
    return pret;
}

void free_heap(struct heap_str *pheap)
{
    if (pheap)
    {
        free(pheap->parray);
        free(pheap);
    }
}
// 只查看堆顶元素，但是不移出
int peek_top(struct heap_str *pheap, struct node_string **pvalue)
{
    if (!pheap || !pvalue)
    {
        return -1;
    }
    if (pheap->num < 1)
    {
        return -1;
    }
    *pvalue = pheap->parray[0];
    return 1;
}

// 移出堆顶元素
int pop(struct heap_str *pheap, struct node_string **pvalue)
{
    if (!pheap || !pvalue)
    {
        return -1;
    }
    if (pheap->num < 1)
    {
        return -1;
    }
    struct node_string *tmp = pheap->parray[pheap->num - 1];
    *pvalue = pheap->parray[0];
    // printf("pop value %d\n", *pvalue);
    pheap->parray[0] = tmp;
    pheap->num--;
    settle_node(pheap, 0);
    return 1;
}

// 用给定值替换堆顶元素
int replace_top(struct heap_str *pheap, struct node_string *value)
{
    if (!pheap)
    {
        return -1;
    }
    if (pheap->num < 1)
    {
        return -1;
    }
    pheap->parray[0] = value;
    settle_node(pheap, 0);
    return 1;
}

void print_heap_all(struct heap_str *pheap)
{
    if (pheap)
    {
        int i;
        for (i = 0; i < pheap->num; i++)
        {
            printf("%s\t%d\n", pheap->parray[i]->pstr, pheap->parray[i]->count);
        }
        printf("\n");
    }
}

char **topKFrequent(char **words, int wordsSize, int k, int *returnSize)
{
    if (!words || !returnSize)
    {
        return NULL;
    }
    if (wordsSize < 1)
    {
        return NULL;
    }
    struct hash_string hash;
    memset(&hash, 0, sizeof(hash));
    hash_string_initial(&hash, wordsSize);
    int i;
    for (i = 0; i < wordsSize; i++)
    {
        if (words[i])
        {
            // printf("准备插入元素 %s\n", words[i]);
            hash_string_insert_str(&hash, words[i]);
        }
    }

    // printf("capacity is %d total is %d effective is %d\n", hash.capacity, hash.total, hash.effective);

    // 然后再利用堆排序
    struct node_string **pstr_with_count = (struct node_string **)calloc(hash.effective, sizeof(struct node_string *));
    if (!pstr_with_count)
    {
        printf("給计数后的字符串分配数组失败\n");
        return NULL;
    }
    int process_num = 0;
    for (i = 0; i < hash.capacity && process_num < hash.effective; i++)
    {
        if (hash.parray[i].pstr)
        {
            pstr_with_count[process_num] = &hash.parray[i];
            // printf("%s\t%d\n", pstr_with_count[process_num]->pstr, pstr_with_count[process_num]->count);
            process_num++;
        }
    }
    char **ptopk = (char **)malloc( k * sizeof(char *) );
    if (ptopk)
    {
        *returnSize = k;
        struct heap_str *pheap = build_heap(pstr_with_count, k, HEAP_MODE_LITTLE);
        struct node_string *top = NULL;
        if (pheap)
        {
            for (i = k; i < hash.effective; i++)
            {
                if (peek_top(pheap, &top) == 1)
                {
                    if (is_larger(pstr_with_count[i], top))
                    {
                        replace_top(pheap, pstr_with_count[i]);
                    }
                }
            }
        }

        print_heap_all(pheap);

        pheap = build_heap(pheap->parray, k, HEAP_MODE_BIG);

        print_heap_all(pheap);

        for (i = 0; i < k; i++)
        {
            pop(pheap, &top);
            ptopk[i] = (char*) calloc(strlen(top->pstr) + 1, sizeof(char) );
            strcpy(ptopk[i], top->pstr);
            // ptopk[i] = strdup(top->pstr);
            // printf("%s\n", ptopk[i]);
        }


        // 释放内存 
        free_heap(pheap);
        if (pstr_with_count)
        {
            free(pstr_with_count);
        }
        return ptopk;
    }
    
    return ptopk;
}

/* 
 int main()
{
    char *words[8] = {
        "fish",
        "pig",
        "fish",
        "cat",
        "dog",
        "pig",
        "cow",
        "p"};
    int ret_size = 0;
    topKFrequent(words, 8, 2, &ret_size);

    return 0;
} 
*/
