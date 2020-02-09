#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

#include "board.h"
#include "moves.h"
#include "hashtable.h"
#include <atomic>

const int MAX_DEPTH = 128;

void launch_analysis(BOARD, MOVE*, int, HASHTABLE&, int64_t, std::atomic_bool*);
bool is_analysing();

#endif // SEARCH_H_INCLUDED
