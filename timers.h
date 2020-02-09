#ifndef TIMERS_H_INCLUDED
#define TIMERS_H_INCLUDED

#include "cpputil.h"

typedef void* TIMER;

const int64_t INFINITE_TIME = 9223372036854775807;

TIMER create_timer();
int64_t get_timer_time(TIMER); // From creation moment
void destroy_timer(TIMER);

#endif // TIMERS_H_INCLUDED
