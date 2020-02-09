#define internal_go(move) \
{ \
    if (is_capture && !is_opponent_king_attacked(brd)) \
    { \
        /* Recursive call */ \
        POS_COST tmp = -static_analysis(brd, new_cost, \
                                        -beta, -alpha, \
                                        nodes); \
        /* Alpha-beta pruning */ \
        if (tmp > result) result = tmp; \
        if (tmp > alpha) alpha = tmp; \
        if (alpha >= beta) { result = alpha; analysis_quit = true; } \
    } \
}

#define searcher(__move) \
{ \
    MOVE move = __move; \
    bool analysis_quit = false; \
    bool is_capture = move_capture(brd, move); \
    if (is_capture) \
    { \
        make_move_no_hash(move); \
        internal_go(move); \
        unmake_move_no_hash(move); \
        if (analysis_quit) return result; \
    } \
}
