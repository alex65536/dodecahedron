#include "threading.h"
#include "search.h"
#include "uci_output.h"
#include <thread>

bool must_stop;
std::thread cur_thread;

void run_analysis(BOARD brd, MOVE* moves, int move_cnt, HASHTABLE& hsh, int64_t analysis_time)
{
    if (is_analysing())
    {
        uci_out("Analysis is already running!");
        return;
    }
    must_stop = false;
    cur_thread = std::thread(launch_analysis, brd, moves, move_cnt, std::ref(hsh), analysis_time, &must_stop);
    cur_thread.detach();
}

void stop_analysis()
{
    if (!is_analysing()) return;
    must_stop = true;
    while (is_analysing());
}
