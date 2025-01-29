#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "board.h"

const size beginner = {9,9, 10};
const size intermediate = {16,16, 40};
const size expert = {30,16, 99};
const size sizes[3] = {beginner, intermediate, expert};

int comp_pos(pos* a, pos* b) {
    if (!(
        a -> x == b -> x
        || a -> y == b -> y
        || a -> is_bomb == b -> is_bomb
        || a -> is_discovered == b -> is_discovered)) {
            //printf("No.\n");
            return 0;
        }
    return 1;
}

void populate_bombs(size board_type, pos** board) {
    srand(time(NULL));
    for (int i = 0; i < board_type.bombs;) {
        pos bomb = {rand() % board_type.x, rand() % board_type.y, 1, 0, 0, 0};

        //printf("%d %d\n", board[bomb.y][bomb.x].x, board[bomb.y][bomb.x].y);
        if (!(comp_pos(&board[bomb.y][bomb.x], &bomb))) {
            continue;
        }
        board[bomb.y][bomb.x] = bomb;
        i += 1;
    }
}

pos** generate_board(size board_type) {
    pos** board = calloc(board_type.y, sizeof(pos));
    if (board == NULL) {
        printf("Failed to allocate memory!");
        exit(-1);
    }

    for (int i = 0; i < board_type.y; i++) {
        pos* cur_row = calloc(board_type.x, sizeof(pos));
        if (cur_row == NULL) {
            printf("Failed to allocate memory!");
            exit(-1);
        }
        board[i] = cur_row;
    }
    
    populate_bombs(board_type, board);

    //printf("Bombs: %d\n", board_type.bombs);
    
    return board;
}

int surround_bombs(pos** board, size* board_size, int x, int y) {
    int count = 0;
    for (int dx = -1; dx < 2; dx++) {
        for (int dy = -1; dy < 2; dy++) {
            if (dx + x < 0 || dy + y < 0 || dx + x >= board_size -> x || dy +  y >= board_size -> y) {
                continue;
            }
            if (board[y + dy][x + dx].is_bomb) {
                count += 1;
            }
        }
    }
    return count;
}

/// mouse_click is 1 for left click and 0 for right click.
/// Returns 1 if a bomb was dug.
int dig(pos** board, size* board_size, int mouse_click, int x, int y) {
    //printf("x: %d, y: %d\n", x, y);
    if (x < 0 || x >= board_size -> x || y < 0 || y >= board_size -> y) {
        return 0;
    }
    if (board[y][x].is_discovered || board[y][x].is_flagged) {
        return 0;
    }

    if (mouse_click) {
        board[y][x].is_discovered = 1;
        if (board[y][x].is_bomb && !board[y][x].is_flagged) {
            board[y][x].is_exploded = 1;
            return 1;
        }
        if (surround_bombs(board, board_size, x, y) == 0) {
            dig(board, board_size, mouse_click, x+1, y);
            dig(board, board_size, mouse_click, x-1, y);
            dig(board, board_size, mouse_click, x, y+1);
            dig(board, board_size, mouse_click, x, y-1);
            dig(board, board_size, mouse_click, x+1, y+1);
            dig(board, board_size, mouse_click, x+1, y-1);
            dig(board, board_size, mouse_click, x-1, y+1);
            dig(board, board_size, mouse_click, x-1, y-1);
        }
    } else {
        if (!board[y][x].is_discovered) {
            board[y][x].is_flagged = board[y][x].is_flagged ^ 1;
        }
    }
    return 0;
}

int check_victory(pos** board, size* board_size) {
    for (int x = 0; x < board_size->x; x++) {
        for (int y = 0; y < board_size->y; y++) {
            if (!board[y][x].is_bomb && !board[y][x].is_discovered) {
                return 0;
            }
        }
    }
    return 1;
}