#ifndef UCI_OUTPUT_H_INCLUDED
#define UCI_OUTPUT_H_INCLUDED

#include "board.h"
#include "poscost.h"
#include "cpputil.h"
#include "moves.h"

void uci_begin_output();
void uci_end_output();

void uci_out(const char*);
void uci_out_fmt(const char*, ...);

void uci_out_info(int depth, POS_COST score, MOVE* pv, int pvsz, int64_t time, int64_t nodes);
void uci_stop(const MOVE& best_move);

#endif // UCI_OUTPUT_H_INCLUDED
