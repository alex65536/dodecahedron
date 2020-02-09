#ifndef IT_IS_SEARCH_CPP
    #error It must be included from search.cpp!
#endif // IT_IS_SEARCH_CPP

POS_COST nega_max
    (int depth, int max_depth,
     BOARD& brd, POS_COST dyn_cost,
     ZOBRIST hsh, HASHTABLE& htab,
     POS_COST alpha, POS_COST beta,
     bool was_capture, bool null_move, bool lazy_eval,
     MOVE_CHAINS chains, CHAIN_SIZES sizes,
     int64_t& nodes,
     TIMER timer, int64_t analysis_time,
     bool* must_stop)
{
    // Some init stuff ...
    POS_COST was_alpha = alpha, was_beta = beta;
    POS_COST result = -INFINITY;
    bool have_moves = false;
    MOVE lst[300];
    int cnt = 0;
    MOVE best_move = impossible_move();
    MOVE hash_move = impossible_move();
    bool can_gen_moves = true;
    sizes[depth] = 0;
    nodes++;
    // Pre-exit (if out of depth or draw)
    if (hashtable_count(htab, hsh) >= 3) return ZERO;
    if (depth <= 0) return static_analysis(brd, dyn_cost, alpha, beta, nodes);
    // Extract data from hash
    SEARCH_HASH_ENTRY* hel = extract_hash(hsh);
    int h_depth = hel ? hel->depth : -1;
    #define push_to_hash(score) \
        if (!null_move && depth >= h_depth && !must_exit) \
        { \
            POS_COST s = score; \
            ANALYSIS_MODE am = MODE_NORMAL; \
            if (score <= was_alpha) { s = was_alpha; am = MODE_UPPERBOUND; } \
            if (score >= was_beta)  { s = was_beta;  am = MODE_LOWERBOUND; } \
            add_hash(hsh, best_move, s, am, depth); \
        }
    // Internal iterative deepening
    const POS_COST iterative_deepening_margin = 0;
    if (!lazy_eval &&
        !was_capture &&
        !is_check(brd) &&
        get_position_cost(brd, dyn_cost) + iterative_deepening_margin <= alpha)
    {
        nega_max(depth-2, max_depth,
                 brd, dyn_cost,
                 hsh, htab,
                 alpha, beta,
                 was_capture, null_move, true,
                 chains, sizes,
                 nodes,
                 timer, analysis_time, must_stop);
    }
    // Cut using hash value
    if (hel)
    {
        if (hel->depth >= depth)
        {
            if (hel->mode == MODE_LOWERBOUND) alpha = max(alpha, hel->cost);
            if (hel->mode == MODE_UPPERBOUND) beta  = min(beta , hel->cost);
            if (alpha >= beta) return alpha;

            if (hel->mode == MODE_NORMAL)
            {
                cnt = 1;
                lst[0] = hel->move;
                can_gen_moves = false;
            }
        }
        hash_move = hel->move;
    }
    // Futility pruning & razoring
    const POS_COST futility_margin = 50;
    const POS_COST razoring_margin = 900;
    if (!null_move && // not null move
        !lazy_eval && // not shortened evaluation
        depth != max_depth && // we are not in root
        !was_capture && // not capture
        !is_check(brd) // not check
       )
    {
        if (depth <= 2)
        {
            // Futility pruning
            POS_COST beta_and_margin = beta + futility_margin;
            if (get_position_cost(brd, dyn_cost) >= beta_and_margin)
                return beta;
        }
        if (depth <= 4)
        {
            // Razoring
            POS_COST beta_and_margin = beta + razoring_margin;
            POS_COST value = static_analysis(brd, dyn_cost, beta_and_margin-1, beta_and_margin, nodes);
            if (value >= beta_and_margin) return beta;
        }
    }
    // TODO: Implement null move heuristic properly and make it work!
    // Iterate through the moves
    #include "nega_max_searcher.h"
    {
        if (can_gen_moves) cnt = gen_moves(brd, lst);
        MOVE killer1 = first_killer(depth),
             killer2 = second_killer(depth);
        // First, move from the hash
        if (hash_move.flags != FLAG_END_OF_LIST) searcher(hash_move);
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
        // Then, killers ...
        for (int i = 0; i < cnt; i++)
            if (moves_equal(killer1, lst[i]) ||
                moves_equal(killer2, lst[i]))
                searcher(lst[i]);
        // Then, the rest of the moves by history heuristic
        {
            int64_t hval[300] = {};
            int ttable[300];
            int ttable_cnt = 0;
            // Prepare to sort ...
            for (int i = 0; i < cnt; i++)
                if (!move_capture(brd, lst[i]) &&
                    !moves_equal(hash_move, lst[i]) &&
                    !moves_equal(killer1,   lst[i]) &&
                    !moves_equal(killer2,   lst[i]))
                {
                    hval[i] = extract_table(lst[i]);
                    ttable[ttable_cnt++] = i;
                }
            // Sort!
            for (int i = 0; i < ttable_cnt; i++)
            {
                // Search for maximum
                int k = i;
                for (int j = k+1; j < ttable_cnt; j++)
                    if (hval[ttable[j]] > hval[ttable[k]]) k = j;
                // Swap
                int tmp = ttable[k];
                ttable[k] = ttable[i];
                ttable[i] = tmp;
                // Make move
                searcher(lst[ttable[i]]);
            }
        }
    }
    // Check for checkmate/stalemate
    if (!have_moves)
    {
        result = (is_check(brd)) ? (CHECKMATE - depth) : ZERO;
        sizes[depth] = 0;
        return result;
    }
    // Now, exit!
    push_to_hash(result);
    return result;
    // That's all :)
    #undef push_to_hash
    #undef exit_proc
    #undef internal_go
    #undef searcher
}
