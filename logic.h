#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#ifndef LOGIC_H
#define LOGIC_H

#include "types.h"

void intro();


int RollDice();

void PrintPlayer(int player);

void FirstPlayer();
void initializeBoard(Board* board);
int piecesInBase(Board* board, int playerColor);
int validBaseMove();
void movePieceFromBaseToBoard(Board* board, int playerColor);
int movePieceToHome(Board* board, int playerColor, int pieceIndex, int diceRoll);
int allPiecesHome(Board* board);
void triggerMysteryCell(Board* board, int playerColor, int pieceIndex);
int movePieceOnBoard(Board* board, int playerColor, int pieceIndex, int diceRoll);
void playTurn(Board* board);
void determineWinner(Board* board);

#endif
