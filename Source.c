#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include "othello.h"


int main() {
	char square[8][8];
	int player_input, player = 1, black = 2, white = 2, flag = 1;
	int change_player_count = 0;

	for (int i = 0; i < 8; i++) {	//assigning the square array with primitive values
		for (int j = 0; j < 8; j++) {
			square[i][j] = '.';
		}
	}
	square[3][3] = square[4][4] = 'b';
	square[3][4] = square[4][3] = 'w';

	while (flag) {
		board(square, &black, &white);
		if (can_player_play(square, player)) {		//shows if this player can make a move this turn or not
			change_player_count = 0;
			if (player == 1)
				printf("\nBlack turn, Please Enter a number between 11 to 88 : ");
			else
				printf("\nWhite turn, Please Enter a number between 11 to 88 : ");
			//The square availability for black or white hasnt checked yet
			if (scanf("%d", &player_input)) {	//if the player entered a character shows an error
				if (player_input >= 11 && player_input <= 88) {	//if the player entered a invalid number shows an error
					int i = player_input / 10 - 1;
					int j = player_input % 10 - 1;
					if (square[i][j] == '.') {
						if (player == 1) {
							square[i][j] = 'b';
							if (update_map(square, i, j, player, 1) != 1) {		//if the square the player is choosed was unplayable, shows an error
								square[i][j] = '.';
								printf("\nNot a valid square to choose (not playable), please try again\n\n");
								continue;
							}

						}
						else {
							square[i][j] = 'w';
							if (update_map(square, i, j, player, 1) != 1) {
								square[i][j] = '.';
								printf("\nNot a valid square to choose (not playable), please try again\n\n");
								continue;
							}
						}
					}
					else {
						printf("\nThis square is taken, please choose a valid square\n\n");
						continue;
					}
				}
				else {
					printf("\nThere is no square with such row and colomn, please try again\n\n");
					continue;
				}
			}
			else {
				printf("\nNot a number, please try again");
				scanf("%c", &player_input);
				continue;
			}
			change_player(&player);

		}
		else {
			printf("\n\nThis player can't make a move this turn , turn is passed to the other!\n");
			change_player(&player);
			change_player_count++;
			if (change_player_count == 2) {
				printf("\n\nThere is no valid move for both players , Game Over!, Here is the result\n");
				flag = winning(black, white);
			}
		}
	}	//end of the while
	printf("\n\nGood bye!");
	_getch();
}
