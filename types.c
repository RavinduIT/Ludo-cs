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
    int color;  // 0: Red, 1: Green, 2: Yellow, 3: Blue
    int position;  // -1 for base, 0-51 for main board, 52-56 for home path
    int direction;  // 1 for clockwise, -1 for counterclockwise
    int captures;  // Number of opponent pieces captured
    int energized;  // 1 if energized, 0 otherwise
    int energizedRounds;  // Number of rounds remaining for energized effect
    int sick;  // 1 if sick, 0 otherwise
    int sickRounds;  // Number of rounds remaining for sick effect
    int originalDirection;  // To remember original direction when part of a block
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






