#include "uci_input.h"
#include "cpputil.h"
#include "strutils.h"
#include "movegen.h"
#include "movestr.h"
#include "about.h"
#include "uci_output.h"
#include "threading.h"
#include "timers.h"
#include "search_hash.h"
#include <stdlib.h>

const int MAX_STR_LEN = 65536;
const int MAX_MOVES = 2048;

char buf[MAX_STR_LEN];
char cmd[MAX_STR_LEN];
HASHTABLE htab;

bool must_quit;

MOVE moves[MAX_MOVES];
int move_cnt = 0;
BOARD brd = start_position();
BOARD new_brd = start_position();

void put_position(char* str)
{
    // Parsing position
    str = next_str(str, cmd);
    if (!str)
    {
        brd = new_brd = start_position();
        move_cnt = 0;
        return;
    }
    if (strcmp(cmd, "fen") == 0)
    {
        // Parse fen
        char* cur_cmd = cmd;
        while (str)
        {
            str = next_str(str, cur_cmd);
            if (strcmp(cur_cmd, "moves") == 0) break;

            while (*cur_cmd) cur_cmd++;
            *(cur_cmd++) = ' ';
        }
        *(cur_cmd++) = 0;
        // Applying position
        if (!load_from_fen(brd, cmd))
        {
            uci_out("FEN error !!!");
            brd = start_position();
        }
    }
    else
    {
        brd = start_position();
        // skip before "moves"
        while (str)
        {
            str = next_str(str, cmd);
            if (strcmp(cmd, "moves") == 0) break;
        }
    }
    // Parsing & adding moves
    new_brd = brd;
    MOVE lst[512];
    MOVE_PERSISTENCE p;
    move_cnt = 0;
    if (!str) return;
    str = next_str(str, cmd);
    while (str)
    {
        gen_moves(new_brd, lst);
        MOVE* m = parse_move(lst, cmd);
        if (!m)
        {
            uci_out("Illegal move !!!");
            break;
        }
        moves[move_cnt++] = *m;
        make_move(new_brd, *m, p);
        str = next_str(str, cmd);
    }
}

void uci_process_command(char* str)
{
    str = next_str(str, cmd);
    if (!str) return;
    // Now, parse commands
    if (strcmp(cmd, "uci") == 0)
    {
        show_uci_about();
        uci_out("uciok");
        return;
    }
    if (strcmp(cmd, "isready") == 0)
    {
        uci_out("readyok");
        return;
    }
    if (strcmp(cmd, "quit") == 0)
    {
        must_quit = true;
        return;
    }
    if (strcmp(cmd, "position") == 0)
    {
        put_position(str);
        return;
    }
    if (strcmp(cmd, "go") == 0)
    {
        // TODO : Improve time scheme.
        int64_t time = INFINITE_TIME;
        while (str)
        {
            str = next_str(str, cmd);
            if (new_brd.move_side == WHITE &&
                str &&
                strcmp(cmd, "winc") == 0)
            {
                str = next_str(str, cmd);
                time = atoll(cmd);
            }
            if (new_brd.move_side == BLACK &&
                str &&
                strcmp(cmd, "binc") == 0)
            {
                str = next_str(str, cmd);
                time = atoll(cmd);
            }
        }
        time -= 15;
        if (time <= 15) time = 15;

        run_analysis(brd, moves, move_cnt, htab, time);
        return;
    }
    if (strcmp(cmd, "stop") == 0)
    {
        stop_analysis();
        return;
    }
}

void run_uci_loop()
{
    alloc_hash(BASE_HASH_SIZE);
    hashtable_create(htab);
    must_quit = false;
    while (!must_quit)
    {
        in_line(buf, MAX_STR_LEN);
        uci_process_command(buf);
    }
    hashtable_destroy(htab);
    free_hash();
}
