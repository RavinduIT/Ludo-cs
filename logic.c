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
            board->players[i].pieces[j].direction = (i % 2 == 0) ? 1 : -1;
            board->players[i].pieces[j].captures = 0;
            board->players[i].pieces[j].special_effect = 0;  // Normal
        }
    }
}

void MovePieceFromBaseToBoard(int player, int piece) {
	printf("Color ");
	PrintPlayer(player);
	printf(" player moves piece ");
	PrintPlayer(player);
	printf("%d to the starting point.\n", piece + 1);
}

void move() {
	int i;
	printf("\nStarting the game:\n");
	for (i = 0; i < 4; i++) {
		int currentPlayer = order[i];
		printf("Color ");
		PrintPlayer(currentPlayer);
		printf(" player's turn:\n");
		value = RollDice();
		printf("Rolled a %d\n", value);
		if (value == 6) {
			MovePieceFromBaseToBoard(currentPlayer, 0);
		} else {
			printf("Cannot move any piece. Turn passes.\n");
		}
	}
}
 

// Function to move a piece
void movePiece(Board* board, int playerIndex, int pieceIndex, int steps) {
    Player* player = &board->players[playerIndex];
    Piece* piece = &player->pieces[pieceIndex];

    // If piece is in base and dice roll is 6, move to starting point
    if (piece->position == -1 && steps == 6) {
        piece->position = playerIndex * 13; // Starting point for each player
        printf("Player %d moves piece %d from base to starting point\n", playerIndex, pieceIndex);
        return;
    }

    // If piece is already on board, move it
    if (piece->position >= 0) {
        int newPosition = (piece->position + steps * piece->direction) % BOARD_SIZE;
        
        // Check if piece is entering home straight
        if (newPosition / 13 == playerIndex && piece->position / 13 != playerIndex) {
            if (piece->captures > 0) {
                printf("Player %d's piece %d enters home straight\n", playerIndex, pieceIndex);
                piece->position = BOARD_SIZE + (newPosition % 13);
            } else {
                printf("Player %d's piece %d cannot enter home straight without captures\n", playerIndex, pieceIndex);
                return;
            }
        } else {
            piece->position = newPosition;
        }

        printf("Player %d moves piece %d to position %d\n", playerIndex, pieceIndex, piece->position);

        // Check for capture
        for (int i = 0; i < 4; i++) {
            if (i != playerIndex) {
                for (int j = 0; j < PIECES_PER_PLAYER; j++) {
                    if (board->players[i].pieces[j].position == piece->position) {
                        board->players[i].pieces[j].position = -1; // Send back to base
                        piece->captures++;
                        printf("Player %d's piece %d captures Player %d's piece %d\n", playerIndex, pieceIndex, i, j);
                        return; // Bonus turn for capture
                    }
                }
            }
        }
    }
}

// Function to handle a player's turn
void playerTurn(Board* board, int playerIndex) {
    Player* player = &board->players[playerIndex];
    int diceRoll = RollDice();
    printf("Player %d rolls a %d\n", playerIndex, diceRoll);

    // Check if any move is possible
    int canMove = 0;
    for (int i = 0; i < PIECES_PER_PLAYER; i++) {
        if (player->pieces[i].position == -1 && diceRoll == 6) {
            canMove = 1;
            break;
        }
        if (player->pieces[i].position >= 0) {
            canMove = 1;
            break;
        }
    }

    if (!canMove) {
        printf("Player %d cannot move any piece\n", playerIndex);
        return;
    }

    // For simplicity, we'll move the first available piece
    for (int i = 0; i < PIECES_PER_PLAYER; i++) {
        if (player->pieces[i].position == -1 && diceRoll == 6) {
            movePiece(board, playerIndex, i, diceRoll);
            return;
        }
        if (player->pieces[i].position >= 0) {
            movePiece(board, playerIndex, i, diceRoll);
            return;
        }
    }
}

