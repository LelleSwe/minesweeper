//#include "board.c"
#include "mgui.h"
#include "raylib.h"
#include "board.h"

//#include <raylib.h>
//#define RAYGUI_IMPLEMENTATION
//#include "raygui.h"

int main() {
    int board_choice;

    int screen_width = 1600;
    int screen_height = 800;
    InitWindow(screen_width, screen_height, "Lelles minesweeper magi :D");
    SetTargetFPS(24);
    SetTraceLogLevel(LOG_ERROR); 

    int prompt_size = 1;
    int is_started = 0;
    float size_mul = 2.2;
    int game_over = 0;
    int victory = 0;
    pos** board = 0;
    size bsize;
    Vector2 base_pos = {10., 50.};
    
    Texture2D tiles_raw = LoadTexture("sprites/tiles.png");
    Texture2D numbers = LoadTexture("sprites/numbers.png");
    Texture2D faces = LoadTexture("sprites/faces.png");
    Texture2D* tiles = get_tile_splices(&tiles_raw);

    choose_board(&board, &bsize, &screen_height, &screen_width);
    //print_board(board, &bsize);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Lelle gjorde en minesweeper klon", 10, 10, 25, BLACK);

        if (!game_over) {
            Vector2 mouse_pos = GetMousePosition();
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                game_over = dig(board, &bsize,  1, (int) (mouse_pos.x - base_pos.x) / 16./size_mul, (int) (mouse_pos.y - base_pos.y) / 16./size_mul);
            }   
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                game_over = dig(board, &bsize, 0, (int) (mouse_pos.x - base_pos.x) / 16./size_mul, (int) (mouse_pos.y - base_pos.y) / 16./size_mul);
            }
            victory = check_victory(board, &bsize);
            if (victory) {
                game_over = 1;
            }
        }
        draw_board(board, &bsize, base_pos.x, base_pos.y, size_mul, tiles, game_over);
        
        EndDrawing();
        /*for (int i = 0; i < bsize.x * bsize.y; i++) {
            UnloadTexture(clear[i]);
        }*/
    }

    return 0;
}