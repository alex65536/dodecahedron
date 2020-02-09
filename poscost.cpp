#include "poscost.h"
#include "poscost_consts.h"

inline void internal_dynamic_recalc(const BOARD& b, POS_COST& p, int* cl, int cls, int mul)
{
    for (int i = 0; i < cls; i++)
    {
        if (!b.board[cl[i]]) continue;
        int c = get_color(b.board[cl[i]]),
            k = get_kind(b.board[cl[i]]);
        if (c == WHITE)
            p += mul * (piece_cost[k] + pst[k][cl[i]]);
        else
            p -= mul * (piece_cost[k] + pst[k][transpos_table[cl[i]]]);
    }
}

void dynamic_calc_before_move(const BOARD& b, POS_COST& p, int* cl, int cls)
{
    internal_dynamic_recalc(b, p, cl, cls, -1);
}

void dynamic_calc_after_move(const BOARD& b, POS_COST& p, int* cl, int cls)
{
    internal_dynamic_recalc(b, p, cl, cls, 1);
}

POS_COST dynamic_calc_init(const BOARD& b)
{
    POS_COST p = 0;
    for (int i = 0; i < 7; i++)
    {
        // White
        p += piece_cost[i] * b.piece_count[WHITE][i];
        for (int j = 0; j < b.piece_count[WHITE][i]; j++)
            p += pst[i][b.pieces[WHITE][i][j]];
        // Black
        p -= piece_cost[i] * b.piece_count[BLACK][i];
        for (int j = 0; j < b.piece_count[BLACK][i]; j++)
            p -= pst[i][transpos_table[b.pieces[BLACK][i][j]]];
    }
    return p;
}

POS_COST get_position_cost(const BOARD& b, POS_COST p)
{
    return p * pos_cost_multiplier[b.move_side];
}

