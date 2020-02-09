#ifndef IT_IS_SEARCH_CPP
    #error It must be included from search.cpp!
#endif // IT_IS_SEARCH_CPP

POS_COST static_analysis
    (BOARD& brd, POS_COST dyn_cost,
     POS_COST alpha, POS_COST beta,
     int64_t& nodes)
{
    nodes++;
    // Try to update with current position cost
    POS_COST result = get_position_cost(brd, dyn_cost);
    if (result > alpha) alpha = result;
    if (alpha >= beta) return alpha;
    // Iterate through the moves
    #include "static_analysis_searcher.h"
    MOVE lst[300];
    int cnt = gen_moves(brd, lst);
    // MVV/LVA (LVA is built in move generator, sort for MVV ...)
    #define gen_for(PIECE) \
        for (int i = 0; i < cnt; i++) \
            if (get_kind(brd.board[lst[i].dst]) == PIECE || \
                (PIECE == PAWN && lst[i].flags == FLAG_ENPASSANT)) \
                searcher(lst[i]);
    gen_for(QUEEN)
    gen_for(ROOK)
    gen_for(BISHOP)
    gen_for(KNIGHT)
    gen_for(PAWN)
    #undef gen_for
    // That's all!
    return result;
    #undef internal_go
    #undef searcher
}
