#include "hashing.h"
#include "cpputil.h"
#include "board.h"

ZOBRIST pieces_hash[COLOR_PIECE_ARRAY_SIZE][BOARD_ARRAY_SIZE];
ZOBRIST castling_hash[COLOR_ARRAY_SIZE][CASTLING_ARRAY_SIZE];
ZOBRIST enpassant_hash[COL_ROW_ARRAY_SIZE];
ZOBRIST color_hash;

bool init_hashes()
{
    randomize64();
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 64; j++)
            pieces_hash[i][j] = random64();
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            castling_hash[i][j] = random64();
    for (int i = 0; i < 8; i++)
        enpassant_hash[i] = random64();
    color_hash = random64();
    return true;
}
bool hashes_inited = init_hashes();

ZOBRIST get_hash(const BOARD& b)
{
    ZOBRIST z = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 7; j++)
            for (int k = 0; k < b.piece_count[i][j]; k++)
                z ^= pieces_hash[make_piece(i, j)][b.pieces[i][j][k]];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (b.castling[i][j])
                z ^= castling_hash[i][j];
    if (b.enpassant_line >= 0)
        z ^= enpassant_hash[b.enpassant_line];
    if (b.move_side == BLACK)
        z ^= color_hash;
    return z;
}

void make_move_recalc_hash(BOARD& b, const MOVE& m, MOVE_PERSISTENCE& p, ZOBRIST& z, int* changes_list, int changes_list_size)
{
    #define cl changes_list
    #define cls changes_list_size
    // Undo old changes
    for (int i = 0; i < cls; i++)
        if (b.board[cl[i]])
            z ^= pieces_hash[b.board[cl[i]]][cl[i]];
    if (b.enpassant_line >= 0)
        z ^= enpassant_hash[b.enpassant_line];
    // Make move
    make_move(b, m, p);
    // Apply new changes
    for (int i = 0; i < cls; i++)
        if (b.board[cl[i]])
            z ^= pieces_hash[b.board[cl[i]]][cl[i]];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (b.castling[i][j] != p.was_castling[i][j])
                z ^= castling_hash[i][j];
    if (b.enpassant_line >= 0)
        z ^= enpassant_hash[b.enpassant_line];
    z ^= color_hash;
    #undef cl
    #undef cls
}
