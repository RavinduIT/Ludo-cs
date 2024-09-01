#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include "types.h"


int maxplayer;
int order[4] = {0};
int value;

void intro(){
	printf("The yellow player has four (04) pieces named Y1, Y2, Y3, and Y4\n");
	printf("The blue player has four (04) pieces named B1, B2, B3, and B4\n");
	printf("The red player has four (04) pieces named R1, R2, R3, and R4\n");
	printf("The green player has four (04) pieces named G1,G2, G3, and G4\n");
}

int RollDice(){
	return (rand() % 6) + 1;
}

void PrintPlayer(int player) {
	switch(player) {
		case 0: printf("Yellow"); 
		break;
		case 1: printf("Blue"); 
		break;
		case 2: printf("Red");
		 break;
		case 3: printf("Green");
		 break;
	}
}

void FirstPlayer() {
	int i;
	int max = 0;
	for (i = 0; i < 4; i++) {
		PrintPlayer(i);
		value = RollDice();
		printf(" Player rolls %d\n", value);
		if (value > max) {
			max = value;
			maxplayer = i;
		}
	}

	printf("Player with highest roll is ");
	PrintPlayer(maxplayer);
	printf(" with a roll of %d\n", max);
	
	for (i = 0; i < 4; i++) {
		order[i] = (maxplayer + i) % 4;
	}
	
	printf("The order of ");
	for (i = 0; i < 2; i++) {
		PrintPlayer(order[i]);
		printf(", ");
	}
	PrintPlayer(order[2]);
	printf(" and ");
	PrintPlayer(order[3]);
	printf("\n");
}

void initializeBoard(Board* board) {
    // Initialize main path
    for (int i = 0; i < BOARD_SIZE; i++) {
        board->main_path[i] = 0;
    }

    // Initialize home paths
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < HOME_PATH_SIZE; j++) {
            board->home_paths[i][j] = 0;
        }
    }

    // Set mystery cell position
    board->mystery_cell_position = rand() % BOARD_SIZE;

    // Initialize players and their pieces
    for (int i = 0; i < 4; i++) {
        board->players[i].color = i;
        for (int j = 0; j < PIECES_PER_PLAYER; j++) {
            board->players[i].pieces[j].color = i;
            board->players[i].pieces[j].position = -1;  // Start in base
            board->players[i].pieces[j].direction = (rand() % 2 == 0) ? 1 : -1;
            board->players[i].pieces[j].captures = 0;
            board->players[i].pieces[j].energized = 0;
            board->players[i].pieces[j].energizedRounds = 0;
            board->players[i].pieces[j].sick = 0;
            board->players[i].pieces[j].sickRounds = 0;
            board->players[i].pieces[j].originalDirection = board->players[i].pieces[j].direction;
        }
    }
}
int piecesInBase(Board* board, int playerColor) {
    int count = 0;
    for (int i = 0; i < PIECES_PER_PLAYER; i++) {
        // Check if the piece is in the base (position -1)
        if (board->players[playerColor].pieces[i].position == -1) {
            count++;
        }
    }
    return count;
}

int validBaseMove(Board* board, int playerColor) { 
    if (piecesInBase(board, playerColor) != 0) {
        return 1; // at least one piece in base
    }
    return 0;
}


// Function to move a piece from base to home
void movePieceFromBaseToBoard(Board* board, int playerColor) {
    int pieceIndex = -1;
    
    // Find the first piece in base
    for (int i = 0; i < PIECES_PER_PLAYER; i++) {
        if (board->players[playerColor].pieces[i].position == -1) {
            pieceIndex = i;
            break;
        }
    }
    // Move the piece to the starting position
    board->players[playerColor].pieces[pieceIndex].position = playerColor * 13;

    // Coin toss to determine direction
    int coinToss = rand() % 2;
    int direction = (coinToss == 0) ? 1 : -1;
    board->players[playerColor].pieces[pieceIndex].direction = direction;
    board->players[playerColor].pieces[pieceIndex].originalDirection = direction;

    // Print the move and direction
    printf("[Color ");
    PrintPlayer(playerColor);
    printf("] player moves piece %d to the starting point (position %d).\n", 
           pieceIndex + 1, board->players[playerColor].pieces[pieceIndex].position);
    printf("Coin toss result: Moving %s\n", (direction == 1) ? "clockwise" : "counter-clockwise");

    // Update and print the new base/board status
    int piecesOnBase = piecesInBase(board, playerColor);
    printf("[Color ");
    PrintPlayer(playerColor);
    printf("] player now has %d/4 pieces on the board and %d/4 pieces on the base.\n", 
           PIECES_PER_PLAYER - piecesInBase, piecesInBase);
}

int generateRandomEmptyCell(Board* board) {
    int emptyCells[BOARD_SIZE];
    int emptyCount = 0;

    // Find all empty cells
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board->main_path[i] == 0) {
            emptyCells[emptyCount++] = i;
        }
    }

    // If there are empty cells, choose one randomly
    if (emptyCount > 0) {
        return emptyCells[rand() % emptyCount];
    }

    // If no empty cells, return -1 or handle this case as needed
    return -1;
}
void updateMysteryCell(Board* board, int currentRound) {
    if (currentRound == 2) {
        // Spawn mystery cell for the first time after two rounds
        board->mystery_cell_position = generateRandomEmptyCell(board);
        board->mystery_cell_rounds = 4;
    } else if (board->mystery_cell_rounds > 0) {
        board->mystery_cell_rounds--;
    } else {
        // Respawn mystery cell at a new location
        int newPosition;
        do {
            newPosition = generateRandomEmptyCell(board);
        } while (newPosition == board->mystery_cell_position);
        
        board->mystery_cell_position = newPosition;
        board->mystery_cell_rounds = 4;
    }
}
void triggerMysteryCell(Board* board, int playerColor, int pieceIndex) {
    printf("Mystery cell triggered for Player ");
    PrintPlayer(playerColor);
    printf(", Piece %d!\n", pieceIndex + 1);

    // Randomly select one of the six teleport options
    int teleportOption = rand() % 6;
    Piece* piece = &board->players[playerColor].pieces[pieceIndex];

    switch (teleportOption) {
        case 0: // Bhawana (9th cell from Yellow approach)
            piece->position = (0 + 9) % BOARD_SIZE;
            printf("Teleported to Bhawana\n");
            // Implement Bhawana effect (Rule CS-12)
            if (rand() % 2 == 0) {
                piece->energized = 1;
                piece->energizedRounds = 4;
                printf("Piece is energized for 4 rounds\n");
            } else {
                piece->sick = 1;
                piece->sickRounds = 4;
                printf("Piece is sick for 4 rounds\n");
            }
            break;
        case 1: // Kotuwa (27th cell from Yellow approach)
            piece->position = (0 + 27) % BOARD_SIZE;
            printf("Teleported to Kotuwa\n");
            break;
        case 2: // Pita-Kotuwa (46th cell from Yellow approach)
            piece->position = (0 + 46) % BOARD_SIZE;
            printf("Teleported to Pita-Kotuwa\n");
            if (piece->direction == 1) {
                piece->direction = -1;
                printf("Direction changed to counter-clockwise\n");
            } else {
                piece->position = (0 + 27) % BOARD_SIZE;
                printf("Teleported to Kotuwa\n");
            }
            break;
        case 3: // Base
            piece->position = -1;
            printf("Teleported to Base\n");
            break;
        case 4: // X of the piece color
            piece->position = playerColor * 13;
            printf("Teleported to starting point X\n");
            break;
        case 5: // Approach of the piece color
            piece->position = ((playerColor * 13) - 1 + BOARD_SIZE) % BOARD_SIZE;
            printf("Teleported to Approach cell\n");
            break;
    }
}

int movePieceOnBoard(Board* board, int playerColor, int pieceIndex, int diceRoll) {
    Piece* piece = &board->players[playerColor].pieces[pieceIndex];
    int startingPoint = (playerColor * 13 + 2) % BOARD_SIZE;
    int approachCell = (playerColor * 13 - 1 + BOARD_SIZE) % BOARD_SIZE;

    // Calculate new position
    int newPosition;
    if (piece->position < BOARD_SIZE) {
        newPosition = (piece->position + diceRoll * piece->direction + BOARD_SIZE) % BOARD_SIZE;
    } else {
        newPosition = piece->position + diceRoll;
    }

    // Check if the piece has completed a full round (for counterclockwise movement)
    if (piece->direction == -1 && 
        ((piece->position < startingPoint && newPosition >= startingPoint) || 
         (piece->position > newPosition && newPosition >= startingPoint))) {
        piece->captures++;  // Increment captures as a way to track rounds
    }

    // Check if the piece can enter home path
    if (piece->position < BOARD_SIZE && piece->captures > 0) {
        if ((piece->direction == 1 && newPosition > approachCell && piece->position <= approachCell) ||
            (piece->direction == -1 && piece->captures >= 2 && 
             newPosition <= approachCell && piece->position > approachCell)) {
            
            int stepsIntoHomePath;
            if (piece->direction == 1) {
                stepsIntoHomePath = (newPosition - approachCell + BOARD_SIZE) % BOARD_SIZE;
            } else {
                stepsIntoHomePath = (newPosition - approachCell + BOARD_SIZE) % BOARD_SIZE - 4;
            }
            
            if (stepsIntoHomePath > 0 && stepsIntoHomePath <= HOME_PATH_SIZE) {
                piece->position = BOARD_SIZE + (playerColor * HOME_PATH_SIZE) + stepsIntoHomePath - 1;
                printf("Piece enters home path at position %d\n", stepsIntoHomePath);
                return 1;  // Successful move into home path
            }
        }
    }

    // Move on the main board
    if (piece->position < BOARD_SIZE) {
        piece->position = newPosition;
        printf("Piece moves to position %d on the main board\n", newPosition);
        return 1;  // Successful move on main board
    } else if (newPosition < BOARD_SIZE + (playerColor * HOME_PATH_SIZE) + HOME_PATH_SIZE) {
        piece->position = newPosition;
        printf("Piece moves to position %d in home path\n", newPosition - BOARD_SIZE - (playerColor * HOME_PATH_SIZE));
        return 1;  // Successful move in home path
    }

    printf("Invalid move\n");
    return 0;  // Move not possible
}
void determineWinner(Board* board) {
    int placings[PLAYER_COUNT] = {0};
    int currentPlace = 1;

    while (currentPlace <= PLAYER_COUNT) {
        for (int i = 0; i < PLAYER_COUNT; i++) {
            if (placings[i] == 0) {
                int piecesHome = 0;
                for (int j = 0; j < PIECES_PER_PLAYER; j++) {
                    if (board->players[i].pieces[j].position >= BOARD_SIZE + (i * HOME_PATH_SIZE) + HOME_PATH_SIZE - 1) {
                        piecesHome++;
                    }
                }
                if (piecesHome == PIECES_PER_PLAYER) {
                    placings[i] = currentPlace;
                    printf("Player ");
                    PrintPlayer(i);
                    printf(" finished in ");
                    switch (currentPlace) {
                        case 1: printf("1st"); break;
                        case 2: printf("2nd"); break;
                        case 3: printf("3rd"); break;
                        case 4: printf("4th"); break;
                    }
                    printf(" place!\n");
                    currentPlace++;
                }
            }
        }
    }
}
void game(Board* board) {
    int round = 1;
    while (1) {
        printf("\n--- Round %d ---\n", round);
        updateMysteryCell(board, round);

        for (int i = 0; i < 4; i++) {
            int currentPlayer = order[i];
            int rollCount = 0;
            int continueTurn = 1;

            while (continueTurn && rollCount < 3) {
                rollCount++;
                int diceValue = RollDice();
                PrintPlayer(currentPlayer);
                printf(" player rolls a %d (Roll %d/3)\n", diceValue, rollCount);

                int moved = 0;

                if (diceValue == 6 && validBaseMove(board, currentPlayer)) {
                    movePieceFromBaseToBoard(board, currentPlayer);
                    moved = 1;
                    if (rollCount < 3) {
                        printf("Player gets another roll for rolling a 6!\n");
                        continue;
                    }
                }

                if (!moved) {
                    for (int j = 0; j < PIECES_PER_PLAYER; j++) {
                        int moveResult = movePieceToHome(board, currentPlayer, j, diceValue);
                        if (moveResult == 1) {
                            moved = 1;
                            continueTurn = 0;
                            break;
                        } else if (moveResult == 2) {
                            moved = 1;
                            if (rollCount < 3) {
                                printf("Player gets another roll for capturing!\n");
                                break;
                            }
                        }
                    }
                }

                if (!moved) {
                    printf("No valid moves for Player ");
                    PrintPlayer(currentPlayer);
                    printf(".\n");
                    continueTurn = 0;
                }

                if (allPiecesHome(board)) {
                    determineWinner(board);
                    return;
                }

                if (rollCount == 3) {
                    continueTurn = 0;
                }
            }
        }
        round++;
    }
}



















