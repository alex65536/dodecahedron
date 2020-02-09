#ifndef IT_IS_SEARCH_CPP
    #error It must be included from search.cpp!
#endif // IT_IS_SEARCH_CPP

// C++ has no nested functions :(
// #define will save the world!

#define internal_go(move) \
{ \
    /* Check for validness */ \
    if (!is_opponent_king_attacked(brd)) \
    { \
        have_moves = true; \
        /* Launch search with depth = depth-1 */ \
        POS_COST tmp = -nega_max(depth - 1, max_depth, \
                                brd, new_cost, \
                                new_hsh, htab, \
                                -beta, -alpha, \
                                is_capture, null_move, lazy_eval,  \
                                chains, sizes, \
                                nodes, \
                                timer, analysis_time, \
                                must_stop); \
        /* Update score */ \
        if (tmp > result) \
        {  \
            if (!is_capture) \
            { \
                add_table(depth, move); \
                push_killer(depth, move); \
            } \
            result = tmp; \
            best_move = move; \
            /* Copy chain */ \
            *(chains[depth]) = move; \
            memcpy(chains[depth] + 1, chains[depth-1], sizeof(MOVE) * sizes[depth-1]); \
            sizes[depth] = sizes[depth-1] + 1; \
        } \
        /* Alpha-beta pruning */ \
        alpha = max(alpha, tmp); \
        if (alpha >= beta) { result = alpha; alpha_beta_cut = true; } \
    } \
}

#define searcher(__move) \
{ \
    MOVE move = __move; \
    bool alpha_beta_cut = false; \
    bool is_capture = move_capture(brd, move); \
    make_move_hash(move) \
    internal_go(move); \
    unmake_move_hash(move) \
    if (alpha_beta_cut) { push_to_hash(result); return result; } \
    if (must_exit) return ZERO; \
}
