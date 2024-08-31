#ifndef TYPES_H
#define TYPES_H

#define RED 0
#define BOARD_SIZE 52
#define HOME_PATH_SIZE 5
#define PIECES_PER_PLAYER 4

typedef struct {
    int color;
    int position;
    int direction;
    int captures;
    int special_effect;
} Piece;

typedef struct {
    Piece pieces[PIECES_PER_PLAYER];
    int color;
} Player;

typedef struct {
    int main_path[BOARD_SIZE];
    int home_paths[4][HOME_PATH_SIZE];
    int mystery_cell_position;
    Player players[4];
} Board;

extern int b;
extern int order[];

#endif // TYPES_H