#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 0
#define BOARD_SIZE 52
#define HOME_PATH_SIZE 5
#define PLAYER_COUNT 4
#define PIECES_PER_PLAYER 4

// Structure for a game piece
typedef struct {
    int color;  
    int position; 
    int direction; 
    int captures; 
    int energized;  
    int energizedRounds; 
    int sick;  
    int sickRounds; 
    int originalDirection; 
} Piece;

// Structure for a player
typedef struct {
    Piece pieces[PIECES_PER_PLAYER];
    int color;
} Player;

// The game board
typedef struct {
    int main_path[BOARD_SIZE];
    int home_paths[4][HOME_PATH_SIZE];
    int mystery_cell_position;
    Player players[4];
} Board;






