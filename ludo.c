#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include "types.h"


int main() {
    srand(time(0));  // Initialize random seed
    
    intro();  // Display game introduction
      // Determine the first player and playing order
    
    Board board;
    initializeBoard(&board);  // Initialize the game board
    
    int allPiecesHome = 0;
    while (1) {
       
        
            int roundNumber = 1;
            int allPiecesHome = 0;
            while (1) {
                
            printf("\n--- Round %d ---\n", roundNumber);

              FirstPlayer();
                
                for (int i = 0; i < 4; i++) {
                playerTurn(&board, order[i]);
                
                // Check if all pieces are in home straight
                allPiecesHome = 1;
                for (int j = 0; j < 4; j++) {
                    for (int k = 0; k < PIECES_PER_PLAYER; k++) {
                        if (board.players[j].pieces[k].position < BOARD_SIZE) {
                            allPiecesHome = 0;
                            break;
                        }
                    }
                    if (!allPiecesHome) break;
                }
                
                if (allPiecesHome) {
                    printf("All players have moved their pieces to home straight. Game over!\n");
                    break;
                }
                
                // Existing win condition check
                int piecesHome = 0;
                for (int j = 0; j < PIECES_PER_PLAYER; j++) {
                    if (board.players[order[i]].pieces[j].position >= BOARD_SIZE) {
                        piecesHome++;
                    }
                }
                if (piecesHome == PIECES_PER_PLAYER) {
                    printf("Player ");
                    PrintPlayer(order[i]);
                    printf(" wins!\n");
                    return 0;
            }
        }
        
        if (allPiecesHome) break;
            }
        
        roundNumber++;
    }
    
}
        
    

