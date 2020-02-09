#ifndef POSCOST_CONSTS_H_INCLUDED
#define POSCOST_CONSTS_H_INCLUDED

#include "bitboard.h"

const POS_COST piece_cost[PIECE_ARRAY_SIZE] = {0, 100, 320, 330, 500, 900, 0};

const POS_COST pst[PIECE_ARRAY_SIZE][BOARD_ARRAY_SIZE] =
{
    // none
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    },
    // pawn
    {
        0,  0,  0,   0,   0,  0,  0,  0,
        40, 40, 40,  40,  40, 40, 40, 40,
         8,  8, 12,  24,  24, 12,  8,  8,
         4,  4,  8,  20,  20,  8,  4,  4,
         0,  0,  0,   8,   8,  0,  0,  0,
         4, -4, -8,   0,   0, -8, -4,  4,
         4,  8,  8, -12, -12,  8,  8,  4,
         0,  0,  0,   0,   0,  0,  0,  0
    },
    // knight
    {
        -20, -16, -12, -12, -12, -12, -16, -20,
        -16,  -8,   0,   0,   0,   0,  -8, -16,
        -12,   0,   6,   6,   6,   6,   0, -12,
        -12,   2,   6,   8,   8,   6,   2, -12,
        -12,   0,   6,   8,   8,   6,   0, -12,
        -12,   2,   6,   6,   6,   6,   2, -12,
        -16,  -8,   0,   2,   2,   0,  -8, -16,
        -20, -12, -12, -12, -12, -12, -12, -20,
    },
    // bishop
    {
        -20, -10, -10, -10, -10, -10, -10, -20,
        -10,   0,   0,   0,   0,   0,   0, -10,
        -10,   0,   5,  10,  10,   5,   0, -10,
        -10,   5,   5,  10,  10,   5,   5, -10,
        -10,   5,  10,  10,  10,  10,   5, -10,
        -10,  10,  10,  15,  15,  10,  10, -10,
        -10,  10,   0,   0,   0,   0,  10, -10,
        -20, -10, -10, -10, -10, -10, -10, -20
    },
    // rook
    {
         0,  0,  0,  0,  0,  0,  0,  0,
        15, 25, 25, 25, 25, 25, 25, 15,
        -8,  0,  0,  0,  0,  0,  0, -8,
        -8,  0,  0,  0,  0,  0,  0, -8,
        -8,  0,  0,  0,  0,  0,  0, -8,
        -8,  0,  0,  0,  0,  0,  0, -8,
        -8,  0,  0,  0,  0,  0,  0, -8,
         0,  0,  0, 10, 10,  0,  0,  0
    },
    // queen
    {
        -20, -10, -10, -5, -5, -10, -10, -20,
          3,   5,   5,  5,  5,   5,   5,   3,
        -10,   0,   0,  0,  0,   0,   0, -10,
         -5,   0,   5,  5,  5,   5,   0,  -5,
         -5,   0,   5,  5,  5,   5,   0,  -5,
        -10,   5,   5,  5,  5,   5,   5, -10,
        -10,   0,   5,  0,  0,   5,   0, -10,
        -20, -10, -10, -5, -5, -10, -10, -20
    },
    // king
    {
        -30,  -40,  -40, -50, -50,  -40,  -40, -30,
        -30,  -40,  -40, -50, -50,  -40,  -40, -30,
        -30,  -40,  -40, -50, -50,  -40,  -40, -30,
        -30,  -40,  -40, -50, -50,  -40,  -40, -30,
        -20,  -30,  -30, -40, -40,  -30,  -30, -20,
        -10,  -20,  -20, -20, -20,  -20,  -20, -10,
         10,   10,    0,   0,   0,    0,   10,  10,
         15,   30,   10,   0,   0,   10,   30,  15
    }
};

const int transpos_table[BOARD_ARRAY_SIZE] =
{
    56, 57, 58, 59, 60, 61, 62, 63,
    48, 49, 50, 51, 52, 53, 54, 55,
    40, 41, 42, 43, 44, 45, 46, 47,
    32, 33, 34, 35, 36, 37, 28, 39,
    24, 25, 26, 27, 28, 29, 30, 31,
    16, 17, 18, 19, 20, 21, 22, 23,
     8,  9, 10, 11, 12, 13, 14, 15,
     0,  1,  2,  3,  4,  5,  6,  7
};

const POS_COST pos_cost_multiplier[COLOR_ARRAY_SIZE] = {1, -1};

const POS_COST INFINITY = 1048576;
const POS_COST ZERO = 0;
const POS_COST CHECKMATE = -30000;

#endif // POSCOST_CONSTS_H_INCLUDED