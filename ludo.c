#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include "types.h"

int main() {
    srand(time(NULL));  // Initialize random seed
    
    Board board;
    initializeBoard(&board);
    
    intro();  // Display game introduction
    FirstPlayer();  // Determine the first player and playing order

    printf("Starting game loop\n");
    playTurn(&board);
    printf("Game loop ended\n");

    determineWinner(&board);
    
    return 0;
}
