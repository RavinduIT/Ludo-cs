#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"

int main() {
    srand(time(NULL));  // Initialize random seed
    
    Board board;
    initializeBoard(&board);
    
    intro();  // Display game introduction
    FirstPlayer();  // Determine the first player and playing order

    // Call the main game function
    while (!allPiecesHome(&board)) {
        game(&board);
        
        // Check if the game is over after each turn
        if (allPiecesHome(&board)) {
            printf("\n--- Game Over ---\n");
            determineWinner(&board);
            break; 
        }
    }
    
    printf("\nThank you for playing Ludo!\n");
    
    return 0;
}