#include "hashtable.h"
#include <stdlib.h>

void hashtable_create(HASHTABLE& h)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        h.sizes[i] = 0;
        h.alloc_cnt[i] = HASHTABLE_INC;
        h.table[i] = (ZOBRIST*)malloc(h.alloc_cnt[i] * sizeof(ZOBRIST));
    }
}

void hashtable_push(HASHTABLE& h, ZOBRIST z)
{
    int hsh = z & (HASHTABLE_SIZE - 1);
    if (h.sizes[hsh] == h.alloc_cnt[hsh])
    {
        h.alloc_cnt[hsh] += HASHTABLE_INC;
        h.table[hsh] = (ZOBRIST*)realloc(h.table[hsh], h.alloc_cnt[hsh] * sizeof(ZOBRIST));
    }
    h.table[hsh][h.sizes[hsh]++] = z;
}

void hashtable_pop(HASHTABLE& h, ZOBRIST z)
{
    int hsh = z & (HASHTABLE_SIZE - 1);
    int pos = -1;
    for (int i = 0; i < h.sizes[hsh]; i++)
        if (h.table[hsh][i] == z)
        {
            pos = i;
            break;
        }
    if (pos < 0)
    {
        fatal_error("Don\'t try to remove a hashtable entry that doesn\'t exist!!!");
        return;
    }
    h.sizes[hsh]--;
    h.table[hsh][pos] = h.table[hsh][h.sizes[hsh]];
}

void hashtable_clear(HASHTABLE& h)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
        h.sizes[i] = 0;
}

int hashtable_count(const HASHTABLE& h, ZOBRIST z)
{
    int hsh = z & (HASHTABLE_SIZE - 1);
    int cnt = 0;
    for (int i = 0; i < h.sizes[hsh]; i++)
        if (h.table[hsh][i] == z) cnt++;
    return cnt;
}

void hashtable_destroy(HASHTABLE& h)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
        free(h.table[i]);
}
