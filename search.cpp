#include "search.h"
#include "uci_output.h"
#include "poscost.h"
#include "hashing.h"
#include "movegen.h"
#include "cpputil.h"
#include "timers.h"
#include "hashtable.h"
#include "search_hash.h"
#include "killer_heuristic.h"

// We are in search.cpp
#define IT_IS_SEARCH_CPP

#include "history_heuristic.h"

const int CHAIN_SIZE = 256;

typedef MOVE* MOVE_CHAIN;
typedef MOVE_CHAIN* MOVE_CHAINS;
typedef int* CHAIN_SIZES;

#define must_exit (*must_stop || get_timer_time(timer) > analysis_time)
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

bool analysing = false;

bool is_analysing()
{
    return analysing;
}

inline MOVE_CHAINS alloc_chains()
{
    MOVE_CHAINS ch = new MOVE_CHAIN[CHAIN_SIZE];
    for (int i = 0; i < CHAIN_SIZE; i++)
        ch[i] = new MOVE[CHAIN_SIZE];
    return ch;
}

inline void unalloc_chains(MOVE_CHAINS ch)
{
    for (int i = 0; i < CHAIN_SIZE; i++)
        delete[] ch[i];
    delete[] ch;
}

#include "move_stuff.h"
#include "static_analysis.h"
#include "nega_max.h"

void launch_analysis(BOARD b, MOVE* m, int move_cnt, HASHTABLE& htab, int64_t analysis_time, bool* must_stop)
{
    analysing = true;
    clear_table();
    hashtable_clear(htab);
    MOVE best_move; best_move.dst = best_move.src = best_move.promote = 0;
    TIMER timer = create_timer();
    MOVE_CHAINS ch = alloc_chains();
    int sz[CHAIN_SIZE];
    // Make first moves and calc some variables.
    MOVE_PERSISTENCE p;
    hashtable_push(htab, get_hash(b));
    for (int i = 0; i < move_cnt; i++)
    {
        make_move(b, m[i], p);
        hashtable_push(htab, get_hash(b));
    }
    POS_COST dyn_cost = dynamic_calc_init(b);
    // Iterative deepening algorithm
    bool always_false = false; // for must_stop in depth = 1
    int64_t nodes = 0;
    for (int i = 1; i <= MAX_DEPTH; i++)
    {
        POS_COST tmp = nega_max(i, i,
                                b, dyn_cost,
                                get_hash(b), htab,
                                -INFINITY, +INFINITY,
                                false, false, false,
                                ch, sz,
                                nodes,
                                timer, analysis_time,
                                (i == 1) ? &always_false : must_stop);
        if (must_exit) break;
        best_move = ch[i][0];
        uci_out_info(i, tmp, ch[i], sz[i], get_timer_time(timer), nodes);
    }
    // Output the result
    uci_stop(best_move);
    // Free memory
    destroy_timer(timer);
    unalloc_chains(ch);
    analysing = false;
}
