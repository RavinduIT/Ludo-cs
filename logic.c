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

    if (pieceIndex == -1) {
        printf("Error: No pieces in base for player ");
        PrintPlayer(playerColor);
        printf("\n");
        return;
    }

    // Move the piece to the starting position
    board->players[playerColor].pieces[pieceIndex].position = playerColor * 13;

    // Print the move
    printf("[Color ");
    PrintPlayer(playerColor);
    printf("] player moves piece %d to the starting point.\n", pieceIndex + 1);

    // Update and print the new base/board status
    int piecesOnBase = piecesInBase(board, playerColor);
    printf("[Color ");
    PrintPlayer(playerColor);
    printf("] player now has %d/4 pieces on the board and %d/4 pieces on the base.\n", 
           PIECES_PER_PLAYER - piecesOnBase, piecesOnBase);

    // Set the direction if it's not already set
    if (board->players[playerColor].pieces[pieceIndex].direction == 0) {
        board->players[playerColor].pieces[pieceIndex].direction = (rand() % 2 == 0) ? 1 : -1;
        printf("Piece direction set to %s\n", 
               (board->players[playerColor].pieces[pieceIndex].direction == 1) ? "clockwise" : "counter-clockwise");
    }
}
int movePieceOnBoard(Board* board, int playerColor, int pieceIndex, int diceRoll) {
    Piece* piece = &board->players[playerColor].pieces[pieceIndex];
    
    if (piece->position == -1) {
        return 0; // Piece is in base, can't move on board
    }

    int newPosition = (piece->position + diceRoll * piece->direction + BOARD_SIZE) % BOARD_SIZE;

    // Check if the piece can enter home path
    int approachCell = ((playerColor * 13 - 1) + BOARD_SIZE) % BOARD_SIZE;
    if ((piece->direction == 1 && newPosition > approachCell && piece->position <= approachCell) ||
        (piece->direction == -1 && newPosition <= approachCell && piece->position > approachCell)) {
        // Enter home path
        int stepsIntoHomePath = (newPosition - approachCell + BOARD_SIZE) % BOARD_SIZE;
        if (stepsIntoHomePath <= HOME_PATH_SIZE) {
            piece->position = BOARD_SIZE + (playerColor * HOME_PATH_SIZE) + stepsIntoHomePath - 1;
            printf("Piece enters home path at position %d\n", piece->position);
            return 1; // Successful move
        } else {
            printf("Piece cannot enter home path, too many steps\n");
            return 0; // Move not possible
        }
    }

    // Check for captures and update position
    for (int p = 0; p < PLAYER_COUNT; p++) {
        if (p != playerColor) {
            for (int pc = 0; pc < PIECES_PER_PLAYER; pc++) {
                if (board->players[p].pieces[pc].position == newPosition) {
                    board->players[p].pieces[pc].position = -1; // Send back to base
                    piece->captures++;
                    printf("Piece captures a piece from Player ");
                    PrintPlayer(p);
                    printf("!\n");
                }
            }
        }
    }

    piece->position = newPosition;
    printf("Piece moves to position %d\n", newPosition);

    return 1; // Successful move
}


void playTurn(Board* board) {
    int round = 1;
    int gameEnded = 0;
    int maxRounds = 5000; // Set a maximum number of rounds to prevent infinite loops

    while (!gameEnded && round <= maxRounds) {
        printf("\n--- Round %d ---\n", round);
        for (int i = 0; i < 4; i++) {
            int currentPlayer = order[i];
            int continueTurn = 1;
            int consecutiveSixes = 0;
            
            while (continueTurn && consecutiveSixes < 3) {
                int diceRoll = RollDice();
                int moved = 0;

                printf("\nPlayer ");
                PrintPlayer(currentPlayer);
                printf(" rolls %d\n", diceRoll);

                if (diceRoll == 6) {
                    consecutiveSixes++;
                    if (consecutiveSixes == 3) {
                        printf("Three consecutive sixes! Turn ends.\n");
                        break;
                    }
                } else {
                    consecutiveSixes = 0;
                }

                if (diceRoll == 6 && validBaseMove(board, currentPlayer)) {
                    movePieceFromBaseToBoard(board, currentPlayer);
                    moved = 1;
                    printf("Player gets another turn for rolling a 6!\n");
                    continue;
                }

                if (!moved) {
                    for (int j = 0; j < PIECES_PER_PLAYER; j++) {
                        if (movePieceOnBoard(board, currentPlayer, j, diceRoll)) {
                            moved = 1;
                            break;
                        }
                    }
                }

                if (!moved) {
                    printf("No valid moves for Player ");
                    PrintPlayer(currentPlayer);
                    printf(".\n");
                }

                continueTurn = (diceRoll == 6 && moved);

                if (allPiecesHome(board)) {
                    gameEnded = 1;
                    break;
                }
            }

            if (gameEnded) break;
        }
        round++;
    }

    if (round > maxRounds) {
        printf("Game ended due to reaching maximum number of rounds.\n");
    }

    determineWinner(board);
}


void determineWinner(Board* board) {
    int placings[PLAYER_COUNT] = {0};
    int currentPlace = 1;

    while (currentPlace <= PLAYER_COUNT) {
        for (int i = 0; i < PLAYER_COUNT; i++) {
            if (placings[i] == 0) {
                int piecesHome = 0;
                for (int j = 0; j < PIECES_PER_PLAYER; j++) {
                    if (board->players[i].pieces[j].position >= BOARD_SIZE) {
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

int allPiecesHome(Board* board) {
    for (int i = 0; i < PLAYER_COUNT; i++) {
        int piecesHome = 0;
        for (int j = 0; j < PIECES_PER_PLAYER; j++) {
            if (board->players[i].pieces[j].position >= BOARD_SIZE) {
                piecesHome++;
            }
        }
        if (piecesHome == PIECES_PER_PLAYER) {
            return 1;  // All pieces of a player are home
        }
    }
    return 0;  // Not all pieces of any player are home yet
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
                piece->sickRounds = 2;
                printf("Piece is sick for 2 rounds\n");
            }
            break;
        case 1: // Kotuwa (27th cell from Yellow approach)
            piece->position = (0 + 27) % BOARD_SIZE;
            printf("Teleported to Kotuwa\n");
            break;
        case 2: // Pita-Kotuwa (46th cell from Yellow approach)
            piece->position = (0 + 46) % BOARD_SIZE;
            printf("Teleported to Pita-Kotuwa\n");
            break;
        case 3: // Base
            piece->position = -1;
            piece->direction = 0;  // Reset direction
            piece->originalDirection = 0;
            printf("Teleported to Base\n");
            break;
        case 4: // X of the piece color
            piece->position = playerColor * 13;
            // Determine new direction
            piece->direction = (rand() % 2 == 0) ? 1 : -1;
            piece->originalDirection = piece->direction;
            printf("Teleported to starting point X. New direction: %s\n", 
                   piece->direction == 1 ? "Clockwise" : "Counter-clockwise");
            break;
        case 5: // Approach of the piece color
            piece->position = ((playerColor * 13) - 1 + BOARD_SIZE) % BOARD_SIZE;
            printf("Teleported to Approach cell\n");
            break;
    }
}

