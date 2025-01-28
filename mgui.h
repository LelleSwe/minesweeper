#include "board.h"
#include "raygui.h"
#include <raylib.h>
Texture2D* draw_board(pos** board, size* board_type, float top_left_x, float top_left_y, float size_mul, Texture2D* tiles);
void choose_board(pos*** board, size* size, int* height, int* width);
void print_board(pos** board, size* board_type);
Texture2D splice_tile(Texture2D* tiles, int index);