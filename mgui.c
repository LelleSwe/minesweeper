#include <raylib.h>
#include <stdio.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "board.h"

void print_board(pos** board, size* board_type) {
    for (int y = 0; y < (board_type->y); y++) {
        for (int x = 0; x < (board_type->x); x++) {
            char print = '.';
            if (board[y][x].is_bomb) {
                print = 'X';
            }
            printf("%c", print);
        }
        printf("\n");
    }
}

void choose_board(pos*** board, size* size, int* height, int* width) {
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
                int chosen_size = GuiMessageBox((Rectangle){ (*width-720)/2, (*height-90)/2, 720, 90},
                    "Choose size", 
                    "How large do you want your board?", 
                    "Beginner\nIntermediate\nExpert\nCustom (not implemented)");
                if (chosen_size != -1 && chosen_size != 4) {
                    *size = sizes[chosen_size - 1];
                    *board = generate_board(*size);
                    EndDrawing();
                    return;
                }
        EndDrawing();
    }
}

/// Get's a 16x16 sprite from the `tiles`.
/// Intended is the 8x2 sprite sheet for tiles,
/// 0 - Undug tile
/// 1 - Empty tile
/// 2 - Flagged tile
/// 3 - ? tile
/// 4 - Dug ? tile
/// 5 - Bomb
/// 6 - Detonated bomb
/// 7 - Fake bomb
/// 8 -> 15 - Numbers 1 to 8
Texture2D splice_tile(Texture2D* tiles, int index) {
    Image img = LoadImageFromTexture(*tiles);
    ImageCrop(
        &img, 
        (Rectangle){
            (float)((index*16)%128), 
            (float)(((index/8)*16)%32), 
            16., 
            16.
            }
    );
    Texture2D tex = LoadTextureFromImage(img);
    UnloadImage(img);
    return tex;
}

Texture2D* draw_board(pos** board, size* board_type, float top_left_x, float top_left_y, float size_mul, Texture2D* tiles) {
    Texture2D* ret_ptr = malloc(sizeof(Texture2D) * board_type->x * board_type->y);
    for (int y = 0; y < (board_type->y); y++) {
        for (int x = 0; x < (board_type->x); x++) {           
            Texture2D texture;// = {0, 0, 0, 0, 0};
            //UnloadTexture(texture);
            if (board[y][x].is_discovered) {
                if (!board[y][x].is_bomb) {
                    int bomb_count = surround_bombs(board, board_type, x, y);
                    if (bomb_count != 0) {
                        texture = splice_tile(tiles, 7 + bomb_count);
                    } else {
                        texture = splice_tile(tiles, 1);
                    }
                } else {
                    texture = splice_tile(tiles, 5);
                }
            } else {
                if (!board[y][x].is_flagged) {
                    texture = splice_tile(tiles, 0);    
                } else {
                    texture = splice_tile(tiles, 2);
                }
            }
            DrawTextureEx(
                texture, 
                (Vector2){top_left_x + x*16*size_mul, top_left_y + y*16*size_mul}, 
                0., 
                size_mul, 
                WHITE
            );
            ret_ptr[x + board_type->x * y] = texture;
        }
    }
    return ret_ptr;
}

