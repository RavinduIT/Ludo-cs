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
    }

    // Determine and display the winner
    determineWinner(&board);
    
    return 0;
};
