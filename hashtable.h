#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include "hashing.h"

const int HASHTABLE_POW = 16;
const int HASHTABLE_SIZE = 1 << HASHTABLE_POW;
const int HASHTABLE_INC = 16;

struct HASHTABLE
{
    ZOBRIST* table[HASHTABLE_SIZE];
    int sizes[HASHTABLE_SIZE];
    int alloc_cnt[HASHTABLE_SIZE];
};

void hashtable_create(HASHTABLE&);
void hashtable_push(HASHTABLE&, ZOBRIST);
void hashtable_pop(HASHTABLE&, ZOBRIST);
void hashtable_clear(HASHTABLE&);
int hashtable_count(const HASHTABLE&, ZOBRIST);
void hashtable_destroy(HASHTABLE&);

#endif // HASHTABLE_H_INCLUDED
