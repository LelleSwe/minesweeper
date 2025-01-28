
//#pragma once

#ifndef BOARD_POS_GUARD
#define BOARD_POS_GUARD

typedef struct {
    int x;
    int y;
    int is_bomb;
    int is_discovered;
    int is_flagged;
} pos;

#endif
#ifndef BOARD_SIZE_GUARD
#define BOARD_SIZE_GUARD

typedef struct {
    int x;
    int y;
    int bombs;
} size;

#endif

#ifndef BOARD_SIZES_GUARD
#define BOARD_SIZES_GUARD
extern const size beginner;
extern const size intermediate;
extern const size expert;
extern const size sizes[3];

#endif

pos** generate_board(size board_type);
int surround_bombs(pos** board, size* board_size, int x, int y);
int dig(pos** board, size* board_size, int mouse_click, int x, int y);