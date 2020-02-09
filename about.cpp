#define NO_USE_EXTERN
    #include "about.h"
#undef NO_USE_EXTERN

#include "cpputil.h"
#include "uci_output.h"

#ifdef __WIN32
    #include "logo_dos.h"
#else
    #include "logo_utf8.h"
#endif // __WIN32

bool init()
{
    hello_message();
    return true;
}
bool inited = init();

void hello_message()
{
    uci_begin_output();
        out_line(logo);
        out_line_fmt("%s version %s", app_name, app_version);
        out_line("This program is a UCI chess engine.");
        out_str("Type \"uci\" to start communicating with it.");
    uci_end_output();
}

void show_uci_about()
{
    uci_out_fmt("id name %s %s", app_name, app_version);
    uci_out_fmt("id author %s", app_author);
}
