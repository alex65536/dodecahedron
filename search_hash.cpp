#define SHASH_NO_USE_EXTERN
    #include "search_hash.h"
#undef SHASH_NO_USE_EXTERN

#include <string.h>
#include <stdlib.h>

int hash_pow = 0;
int hash_cnt = 1;

SEARCH_HASH_ENTRY* extract_hash(ZOBRIST z)
{
    SEARCH_HASH_ENTRY *p_el = table + (z & (hash_cnt-1));
    return (p_el->brd == z) ? p_el : NULL;
}

void add_hash(ZOBRIST z, MOVE m, POS_COST p, ANALYSIS_MODE am, int d)
{
    SEARCH_HASH_ENTRY *p_el = table + (z & (hash_cnt-1));
    p_el->brd = z;
    p_el->move = m;
    p_el->cost = p;
    p_el->mode = am;
    p_el->depth = d;
}

inline bool recalc_cnt(int sz)
{
    int was_pow = hash_pow;
    sz = (1048576LL * sz) / sizeof(SEARCH_HASH_ENTRY);
    hash_pow = 0;
    while ((1 << hash_pow) <= sz) hash_pow++;
    hash_pow--;
    hash_cnt = 1 << hash_pow;
    return was_pow != hash_pow;
}

void alloc_hash(int sz)
{
    recalc_cnt(sz);
    table = (SEARCH_HASH_ENTRY*)malloc(hash_cnt * sizeof(SEARCH_HASH_ENTRY));
    memset(table, 0, hash_cnt * sizeof(SEARCH_HASH_ENTRY));
}

void realloc_hash(int sz)
{
    int was_hash_pow = hash_pow,
        was_hash_cnt = hash_cnt;
    if (!recalc_cnt(sz)) return;

    SEARCH_HASH_ENTRY* new_table = (SEARCH_HASH_ENTRY*)realloc(table, hash_cnt * sizeof(SEARCH_HASH_ENTRY));
    if (!new_table)
    {
        // error: cannot allocate such hash
        hash_pow = was_hash_pow;
        hash_cnt = was_hash_cnt;
    }
    else
    {
        table = new_table;
        memset(table, 0, hash_cnt * sizeof(SEARCH_HASH_ENTRY));
    }
}

void clear_hash()
{
    memset(table, 0, hash_cnt * sizeof(SEARCH_HASH_ENTRY));
}

void free_hash()
{
    free(table);
}

int hash_size()
{
    return hash_cnt;
}
