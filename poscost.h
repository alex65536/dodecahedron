#ifndef POSCOST_H_INCLUDED
#define POSCOST_H_INCLUDED

#include "board.h"

typedef int POS_COST;

// Dynamic position calc
POS_COST dynamic_calc_init(const BOARD&);
void dynamic_calc_before_move(const BOARD&, POS_COST&, int*, int);
void dynamic_calc_after_move(const BOARD&, POS_COST&, int*, int);

#include "poscost_consts.h"

// Function that return the position score :)
POS_COST get_position_cost(const BOARD&, POS_COST);

#endif // POSCOST_H_INCLUDED
