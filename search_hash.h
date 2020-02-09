#ifndef SEARCH_HASH_H_INCLUDED
#define SEARCH_HASH_H_INCLUDED

#include "board.h"
#include "moves.h"
#include "hashing.h"

#define MODE_LOWERBOUND -1
#define MODE_NORMAL 0
#define MODE_UPPERBOUND 1

#include "poscost.h"
#include "moves.h"
#include "hashing.h"

typedef int ANALYSIS_MODE;

struct SEARCH_HASH_ENTRY
{
    ZOBRIST brd;
    MOVE move;
    POS_COST cost;
    ANALYSIS_MODE mode;
    int depth;
};

const int BASE_HASH_SIZE = 256;

#ifdef SHASH_NO_USE_EXTERN
    #define extern
#endif

extern SEARCH_HASH_ENTRY *table;

#ifdef SHASH_NO_USE_EXTERN
    #undef extern
#endif

SEARCH_HASH_ENTRY* extract_hash(ZOBRIST);
void add_hash(ZOBRIST, MOVE, POS_COST, ANALYSIS_MODE, int);
void alloc_hash(int);
void realloc_hash(int);
void clear_hash();
void free_hash();
int hash_size();

#endif // SEARCH_HASH_H_INCLUDED
