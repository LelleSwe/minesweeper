#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int x;
    int y;
    int is_bomb;
    int is_discovered;
} pos;

typedef struct {
    int x;
    int y;
    int bombs;
} size;

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
        pos bomb = {rand() % board_type.x, rand() % board_type.y, 1, 0};

        //printf("%d %d\n", board[bomb.y][bomb.x].x, board[bomb.y][bomb.x].y);
        if (!(comp_pos(&board[bomb.y][bomb.x], &bomb))) {
            continue;
        }
        board[bomb.y][bomb.x] = bomb;
        i += 1;
    }
}

pos** generate_board(size board_type) {
    pos** board = malloc(sizeof(pos) * board_type.y);
    if (board == NULL) {
        printf("Failed to allocate memory!");
        exit(-1);
    }

    for (int i = 0; i < board_type.y; i++) {
        pos* cur_row = malloc(sizeof(pos) * board_type.x);
        if (cur_row == NULL) {
            printf("Failed to allocate memory!");
            exit(-1);
        }
        board[i] = cur_row;
    }
    
    populate_bombs(board_type, board);

    printf("Bombs: %d\n", board_type.bombs);
    
    return board;
}