#ifndef THREADING_H_INCLUDED
#define THREADING_H_INCLUDED

#include "board.h"
#include "moves.h"
#include "hashtable.h"

void run_analysis(BOARD, MOVE*, int, HASHTABLE&, int64_t);
void stop_analysis();

#endif // THREADING_H_INCLUDED
