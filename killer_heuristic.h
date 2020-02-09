#ifndef KILLER_HEURISTIC_H_INCLUDED
#define KILLER_HEURISTIC_H_INCLUDED

#include "moves.h"

MOVE first_killer(int);
MOVE second_killer(int);
void push_killer(int, const MOVE&);

#endif // KILLER_HEURISTIC_H_INCLUDED
