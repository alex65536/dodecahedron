#include "strutils.h"
#include "cpputil.h"

char* next_str(char* str, char* fragment)
{
    *fragment = 0;
    for (; (*str) <= ' '; str++)
        if (!(*str)) return NULL;
    char* was_str = str;
    while ((*str) > ' ') str++;
    memcpy(fragment, was_str, str - was_str);
    *(fragment + (str - was_str)) = 0;
    return str;
}
