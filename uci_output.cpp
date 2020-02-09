#include "uci_output.h"
#include "cpputil.h"
#include "movestr.h"
#include <mutex>
#include <math.h>

std::mutex output_lock;

void uci_begin_output()
{
    output_lock.lock();
}

void uci_end_output()
{
    out_line("");
    output_lock.unlock();
}

void uci_out(const char* c)
{
    uci_begin_output();
    out_str(c);
    uci_end_output();
}

void uci_out_fmt(const char* c, ...)
{
    uci_begin_output();
    va_list ap;
    va_start(ap, c);
    out_vfmt(c, ap);
    va_end(ap);
    uci_end_output();
}

void uci_out_info(int depth, POS_COST score, MOVE* pv, int pvsz, int64_t time, int64_t nodes)
{
    int nps;
    if (time == 0)
        nps = 0;
    else
        nps = round((1000.0 * nodes) / time);

    uci_begin_output();

    out_str("info depth "); out_int(depth);
    out_str(" nodes "); out_int(nodes);
    out_str(" time "); out_int(time);
    out_str(" nps "); out_int(nps);
    out_str(" score cp "); out_int(score);
    out_str(" pv");
    for (int i = 0; i < pvsz; i++) { out_str(" "); out_move(pv[i]); }

    uci_end_output();
}

void uci_stop(const MOVE& best_move)
{
    uci_begin_output();

    out_str("bestmove "); out_move(best_move);

    uci_end_output();
}
