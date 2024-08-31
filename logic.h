#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#ifndef LOGIC_H
#define LOGIC_H

void intro();

int RollDice();

void PrintPlayer(int player);

void FirstPlayer();

void begining();

void MovePieceFromBaseToBoard(int player, int piece);

extern int VALUE;

void movePiece(Board* board, int playerIndex, int pieceIndex, int steps);

void move();

void playGame(Board* board);

void playerTurn(Board* board, int playerIndex);
void initializeBoard(Board* board);

#endif 

