#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "board.c"

void print_board(pos** board, size board_type) {
    for (int y = 0; y < board_type.y; y++) {
        for (int x = 0; x < board_type.x; x++) {
            char print = '.';
            if (board[y][x].is_bomb) {
                print = 'X';
            }
            printf("%c", print);
        }
        printf("\n");
    }
}

void choose_board(pos** board, size* size, int* height, int* width) {
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
                int chosen_size = GuiMessageBox((Rectangle){ (*width-720)/2, (*height-90)/2, 720, 90},
                    "Choose size", 
                    "How large do you want your board?", 
                    "Beginner\nIntermediate\nExpert\nCustom (not implemented)");
                if (chosen_size != -1 && chosen_size != 4) {
                    *size = sizes[chosen_size - 1];
                    board = generate_board(*size);
                    EndDrawing();
                    return;
                }
        EndDrawing();
    }
}