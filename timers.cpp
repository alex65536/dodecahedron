#include "timers.h"
#include <chrono>

using namespace std::chrono;

typedef system_clock::time_point INTERNAL_TIMER;

TIMER create_timer()
{
    INTERNAL_TIMER *t = new INTERNAL_TIMER;
    *t = system_clock().now();
    return (TIMER)t;
}

int64_t get_timer_time(TIMER timer)
{
    INTERNAL_TIMER *t = (INTERNAL_TIMER*)timer;
    auto d = system_clock().now() - (*t);
    return duration_cast<milliseconds>(d).count();
}

void destroy_timer(TIMER timer)
{
    INTERNAL_TIMER *t = (INTERNAL_TIMER*)timer;
    delete t;
}
