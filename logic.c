#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"

void intro(){
	printf("The yellow player has four (04) pieces named Y1, Y2, Y3, and Y4\n");
	printf("The blue player has four (04) pieces named B1, B2, B3, and B4\n");
	printf("The red player has four (04) pieces named R1, R2, R3, and R4\n");
	printf("The green player has four (04) pieces named G1,G2, G3, and G4\n");
}

// rolling dice

int RollDice(){
	
	int diceValue = (rand() % 6)+1 ;
	return diceValue ;
}

//print the colour of player
 
void PrintPlayer(int player) {

    switch(player) {
        case 0:
            printf("Yellow");
            break;
        case 1:
            printf("Blue");
            break;
        case 2:
            printf("Red");
            break;
        case 3:
            printf("Green");
            break;
    }
}

// finding 1st player and order of round

	
void FirstPlayer() {
	int i;
	int value;
	int max = 0;
	int maxplayer;

	for (i = 0; i < 4; i++) {
		PrintPlayer(i);
		value = RollDice();
		printf("Player rolls %d\n", value);
		if (value > max) {
			max = value;
			maxplayer = i;
		}
	}

	printf("Player with highest roll is ");
	PrintPlayer(maxplayer);
	printf(" with a roll of %d\n", max);
	
	int order[4]={maxplayer,(maxplayer+1)%4,(maxplayer+2)%4,(maxplayer+3)%4};	
	printf("The order of ");
	for (i=0; i < 2; i++) {
			PrintPlayer(order[i]);
			printf(",");
			
	}
	PrintPlayer(order[2]);
	printf(" and ");
	PrintPlayer(order[3]);
	printf(" \n");
}
// game begins
void begining(){
	int j;
	for (j=0; j <6 ; j++) {
		printf("Round %d\n", j);
		int i;
		for (i=0; i < 4; i++) {
			PrintPlayer(i);
			
			int value = RollDice();
			printf("Player rolls %d\n", value);
			if (value==6){
			PrintPlayer(i);
			int value1;
			value1=RollDice();
			printf("Player rolls %d\n", value1);
				if (value1==6){
				int value2;
				value2=RollDice();
				PrintPlayer(i);
				printf(" player rolls %d\n", value);
				continue;
				}
				
			}

			else{
				continue;
			}
			
		}	
		printf("\n");
		
	}
}