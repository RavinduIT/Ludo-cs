#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 52
#define HOME_PATH_SIZE 5
#define PIECES_PER_PLAYER 4
#define PLAYER_COUNT 4

typedef enum {
    YELLOW = 0,
    BLUE,
    RED,
    GREEN
} PlayerColor;

typedef enum {
    NORMAL = 0,
    ENERGIZED,
    SICK
} SpecialEffect;

typedef struct {
    PlayerColor color;
    int position;  // -1 for base, 0-51 for main board, 52-56 for home path
    int direction;  // 1 for clockwise, -1 for counterclockwise
    int captures;
    SpecialEffect special_effect;
} Piece;

typedef struct {
    Piece pieces[PIECES_PER_PLAYER];
    PlayerColor color;
} Player;

typedef struct {
    int main_path[BOARD_SIZE];
    int home_paths[PLAYER_COUNT][HOME_PATH_SIZE];
    int mystery_cell_position;
    Player players[PLAYER_COUNT];
} Board;

// Function declarations
void initializeBoard(Board* board);
void intro();
int rollDice();
void printPlayer(PlayerColor color);
void determineFirstPlayer(int order[]);
void movePieceFromBaseToBoard(Board* board, PlayerColor color, int pieceIndex);
int movePiece(Board* board, PlayerColor color, int pieceIndex, int steps);
void playerTurn(Board* board, PlayerColor color);
void playGame(Board* board);
void triggerMysteryCell(Board* board, PlayerColor color, int pieceIndex);

int main() {
    srand(time(NULL));
    Board board;
    initializeBoard(&board);
    intro();
    playGame(&board);
    return 0;
}

void initializeBoard(Board* board) {
    for (int i = 0; i < PLAYER_COUNT; i++) {
        board->players[i].color = i;
        for (int j = 0; j < PIECES_PER_PLAYER; j++) {
            board->players[i].pieces[j].color = i;
            board->players[i].pieces[j].position = -1;
            board->players[i].pieces[j].direction = (i % 2 == 0) ? 1 : -1;
            board->players[i].pieces[j].captures = 0;
            board->players[i].pieces[j].special_effect = NORMAL;
        }
    }
    board->mystery_cell_position = rand() % BOARD_SIZE;
}

void intro() {
    printf("Welcome to LUDO-CS!\n");
    printf("Yellow pieces: Y1, Y2, Y3, Y4\n");
    printf("Blue pieces: B1, B2, B3, B4\n");
    printf("Red pieces: R1, R2, R3, R4\n");
    printf("Green pieces: G1, G2, G3, G4\n");
}

int rollDice() {
    return (rand() % 6) + 1;
}

void printPlayer(PlayerColor color) {
    switch(color) {
        case YELLOW: printf("Yellow"); break;
        case BLUE: printf("Blue"); break;
        case RED: printf("Red"); break;
        case GREEN: printf("Green"); break;
    }
}

void determineFirstPlayer(int order[]) {
    int maxRoll = 0;
    int maxPlayer = 0;
    for (int i = 0; i < PLAYER_COUNT; i++) {
        int roll = rollDice();
        printf("Player ");
        printPlayer(i);
        printf(" rolls %d\n", roll);
        if (roll > maxRoll) {
            maxRoll = roll;
            maxPlayer = i;
        }
    }
    printf("Player ");
    printPlayer(maxPlayer);
    printf(" starts first with a roll of %d\n", maxRoll);
    
    for (int i = 0; i < PLAYER_COUNT; i++) {
        order[i] = (maxPlayer + i) % PLAYER_COUNT;
    }
}

void movePieceFromBaseToBoard(Board* board, PlayerColor color, int pieceIndex) {
    board->players[color].pieces[pieceIndex].position = color * 13;
    printf("Player ");
    printPlayer(color);
    printf(" moves piece %d to the starting point.\n", pieceIndex + 1);
}

int movePiece(Board* board, PlayerColor color, int pieceIndex, int steps) {
    Piece* piece = &board->players[color].pieces[pieceIndex];
    
    if (piece->position == -1 && steps == 6) {
        movePieceFromBaseToBoard(board, color, pieceIndex);
        return 1;
    }
    
    if (piece->position >= 0) {
        int newPosition = (piece->position + steps * piece->direction + BOARD_SIZE) % BOARD_SIZE;
        
        // Check for blockades
        for (int i = piece->position + piece->direction; i != newPosition; i = (i + piece->direction + BOARD_SIZE) % BOARD_SIZE) {
            int count = 0;
            for (int p = 0; p < PLAYER_COUNT; p++) {
                for (int pc = 0; pc < PIECES_PER_PLAYER; pc++) {
                    if (board->players[p].pieces[pc].position == i) {
                        count++;
                        if (count == 2) return 0; // Blockade found
                    }
                }
            }
        }
        
        // Move the piece
        piece->position = newPosition;
        
        // Check for capture
        for (int p = 0; p < PLAYER_COUNT; p++) {
            if (p != color) {
                for (int pc = 0; pc < PIECES_PER_PLAYER; pc++) {
                    if (board->players[p].pieces[pc].position == piece->position) {
                        board->players[p].pieces[pc].position = -1;
                        piece->captures++;
                        printf("Player ");
                        printPlayer(color);
                        printf(" captures a piece from Player ");
                        printPlayer(p);
                        printf("!\n");
                        return 2; // Capture occurred
                    }
                }
            }
        }
        
        // Check for mystery cell
        if (piece->position == board->mystery_cell_position) {
            triggerMysteryCell(board, color, pieceIndex);
        }
        
        return 1; // Move successful
    }
    
    return 0; // Move not possible
}

void playerTurn(Board* board, PlayerColor color) {
    int diceRoll;
    do {
        printf("Player ");
        printPlayer(color);
        printf("'s turn.\n");
        diceRoll = rollDice();
        printf("Rolled a %d\n", diceRoll);
        
        int moved = 0;
        for (int i = 0; i < PIECES_PER_PLAYER; i++) {
            if (movePiece(board, color, i, diceRoll)) {
                moved = 1;
                break;
            }
        }
        
        if (!moved) {
            printf("No move possible.\n");
        }
    } while (diceRoll == 6);
}

void playGame(Board* board) {
    int order[PLAYER_COUNT];
    determineFirstPlayer(order);
    
    while (1) {
        for (int i = 0; i < PLAYER_COUNT; i++) {
            playerTurn(board, order[i]);
            
            // Check for win condition
            int piecesHome = 0;
            for (int j = 0; j < PIECES_PER_PLAYER; j++) {
                if (board->players[order[i]].pieces[j].position >= BOARD_SIZE) {
                    piecesHome++;
                }
            }
            if (piecesHome == PIECES_PER_PLAYER) {
                printf("Player ");
                printPlayer(order[i]);
                printf(" wins!\n");
                return;
            }
        }
    }
}

void triggerMysteryCell(Board* board, PlayerColor color, int pieceIndex) {
    Piece* piece = &board->players[color].pieces[pieceIndex];
    int effect = rand() % 3;
    switch (effect) {
        case 0:
            piece->special_effect = ENERGIZED;
            printf("Piece gets energized!\n");
            break;
        case 1:
            piece->special_effect = SICK;
            printf("Piece gets sick!\n");
            break;
        case 2:
            piece->direction *= -1;
            printf("Piece changes direction!\n");
            break;
    }
}