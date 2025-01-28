//#include "board.c"
#include "mgui.c"

//#include <raylib.h>
//#define RAYGUI_IMPLEMENTATION
//#include "raygui.h"

int main() {
    int board_choice;
    //printf("%s", "Enter minefield size:\n1: Beginner\n2: Intermediate\n3: Expert\n");
    //scanf("%d", &board_choice);

    /*if (!(board_choice > 0 && board_choice < 4)) {
        printf("%s", "Not a valid board!\n");
        return -1;
    }
    const size board_type = sizes[board_choice-1];
    
    printf("%s%d\n", "Chosen field: ", board_choice);
    
    pos** board = generate_board(board_type);
    //print_board(board, board_type);*/

    int width = 1600;
    int height = 800;
    InitWindow(width, height, "raygui - controls test suite");
    SetTargetFPS(60);

    int prompt_size = 1;
    int is_started = 0;
    pos** board = 0;
    size bsize;

    choose_board(board, &bsize, &height, &width);


    return 0;
}