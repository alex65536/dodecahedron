#include "killer_heuristic.h"
#include "search.h"

MOVE killer[MAX_DEPTH][2];

bool killer_tab_init()
{
    for (int i = 0; i < MAX_DEPTH; i++)
        for (int j = 0; j < 2; j++)
            killer[i][j] = impossible_move();
    return true;
}
bool killer_tab_inited = killer_tab_init();

MOVE first_killer(int depth)
{
    return killer[depth][0];
}

MOVE second_killer(int depth)
{
    return killer[depth][1];
}

void push_killer(int depth, const MOVE& move)
{
    killer[depth][1] = killer[depth][0];
    killer[depth][0] = move;
}
