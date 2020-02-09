#ifndef HASHING_H_INCLUDED
#define HASHING_H_INCLUDED

#include "board.h"
#include "moves.h"
#include "cpputil.h"

typedef int64_t ZOBRIST;

ZOBRIST get_hash(const BOARD&);
void make_move_recalc_hash(BOARD&, const MOVE&, MOVE_PERSISTENCE&, ZOBRIST&, int*, int);

#endif // HASHING_H_INCLUDED
