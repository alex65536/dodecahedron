#ifndef IT_IS_SEARCH_CPP
    #error It must be included from search.cpp!
#endif // IT_IS_SEARCH_CPP

int64_t history_table[BOARD_ARRAY_SIZE][BOARD_ARRAY_SIZE];

inline void clear_table()
{
    for (int i = 0; i < BOARD_ARRAY_SIZE; i++)
        for (int j = 0; j < BOARD_ARRAY_SIZE; j++)
            history_table[i][j] = 0;
}

inline void add_table(int depth, const MOVE& m)
{
    history_table[m.dst][m.src] += depth * depth;
}

inline int64_t extract_table(const MOVE& m)
{
    return history_table[m.dst][m.src];
}
