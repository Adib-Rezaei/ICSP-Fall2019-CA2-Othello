#pragma once

void board(char square[][8], int *black, int *white);
void change_player(int *player);
void valuable_assignment(int *x, int *y, int first_x, int first_y, int *i, int *j);
int update_map(char square[][8], int i, int j, int player, int check);
int can_player_play(char square[][8], int player);
int winning(int black, int white);


void board(char square[][8], int *black, int *white) {	//draws the board of the game
	*black = *white = 0;
	for (int i = 0; i<8; i++)
		for (int j = 0; j < 8; j++) {
			if (square[i][j] == 'b')
				*black = *black + 1;
			else if (square[i][j] == 'w')
				*white = *white + 1;
		}
	printf("\n    1  2  3  4  5  6  7  8 [black =%d, white = %d]\n", *black, *white);
	for (int i = 0; i < 8; i++) {
		printf("%d0  ", i + 1);
		for (int j = 0; j < 8; j++) {
			printf("%c  ", square[i][j]);
		}
		printf("\n");
	}
}

void change_player(int *player) {	//changes the turn
	if (*player == 1)
		*player = 2;
	else
		*player = 1;
}

int can_player_play(char square[][8], int player) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (square[i][j] == '.') {
				if (update_map(square, i, j, player, 0)) {
					return 1;
				}
				else
					continue;
			}
		}
	}
	return 0;
}

void valuable_assignment(int *x, int *y, int first_x, int first_y, int *i, int *j) { //resets the values by pointer
	*x = first_x;
	*y = first_y;
	*i = first_x;
	*j = first_y;
}

int update_map(char square[][8], int i, int j, int player, int check) {   //updates the map
	int x, y, first_x = i, first_y = j;
	int availability = 0;
	valuable_assignment(&x, &y, first_x, first_y, &i, &j); //resets the values

	for (y += 1; y < 8; y++) {	//updates the right side of the row
		if (square[x][y] == '.')	//if the loop reached the dot break 
			break;
		if (player == 1) {	//if player =1 then assign squares with 'b'
			if (square[x][y] == 'b') {
				if (y != j + 1)		//checks the availability of the square to be assigned , 
					availability = 1;		//if 0 at the end of the loop it means that player entered an invalid square
				if (check)
					for (j; j <= y; j++) {	//fill with character 'b'
						square[i][j] = 'b';
					}
				break;
			}
		}
		else	//player 2 (white)
			if (square[x][y] == 'w') {
				if (y != j + 1)
					availability = 1;
				if (check)
					for (j; j <= y; j++) {
						square[i][j] = 'w';
					}
				break;
			}
	}
	valuable_assignment(&x, &y, first_x, first_y, &i, &j);
	for (y -= 1; y > 0; y--) {	//updates the left side of the row
		if (square[x][y] == '.')
			break;
		if (player == 1) {
			if (square[x][y] == 'b') {
				if (y != j - 1)
					availability = 1;
				if (check)
					for (j; j >= y; j--) {
						square[i][j] = 'b';
					}
				break;
			}
		}
		else
			if (square[x][y] == 'w') {
				if (y != j - 1)
					availability = 1;
				if (check)
					for (j; j >= y; j--) {
						square[i][j] = 'w';
					}
				break;
			}
	}
	valuable_assignment(&x, &y, first_x, first_y, &i, &j);
	for (x += 1; x < 8; x++) {	//updates the down side of the coloumn
		if (square[x][y] == '.')
			break;
		if (player == 1) {
			if (square[x][y] == 'b') {
				if (x != i + 1)
					availability = 1;
				if (check)
					for (i; i <= x; i++) {
						square[i][j] = 'b';
					}
				break;
			}
		}
		else
			if (square[x][y] == 'w') {
				if (x != i + 1)
					availability = 1;
				if (check)
					for (i; i <= x; i++) {
						square[i][j] = 'w';
					}
				break;
			}
	}
	valuable_assignment(&x, &y, first_x, first_y, &i, &j);
	for (x -= 1; x > 0; x--) {	//updates the up side of the coloumn
		if (square[x][y] == '.')
			break;
		if (player == 1) {
			if (square[x][y] == 'b') {
				if (x != i - 1)
					availability = 1;
				if (check)
					for (i; i >= x; i--) {
						square[i][j] = 'b';
					}
				break;
			}
		}
		else
			if (square[x][y] == 'w') {
				if (x != i - 1)
					availability = 1;
				if (check)
					for (i; i >= x; i--) {
						square[i][j] = 'w';
					}
				break;
			}
	}
	valuable_assignment(&x, &y, first_x, first_y, &i, &j);

	//diagnol moving
	while (x < 8 && y < 8) {	//go to +1 right and -1 down
		x += 1;
		y += 1;
		if (square[x][y] == '.')
			break;
		if (player == 1) {
			if (square[x][y] == 'b') {
				if (x != i + 1)
					availability = 1;
				if (check)
					while (i <= x) {
						square[i][j] = 'b';
						i += 1;
						j += 1;
					}
				break;
			}
		}
		else
			if (square[x][y] == 'w') {
				if (x != i + 1)
					availability = 1;
				if (check)
					while (i <= x) {
						square[i][j] = 'w';
						i += 1;
						j += 1;
					}
				break;
			}
	}
	valuable_assignment(&x, &y, first_x, first_y, &i, &j);

	while (x > 0 && y > 0) {	//go to -1 left and +1 up
		x -= 1;
		y -= 1;
		if (square[x][y] == '.')
			break;
		if (player == 1) {
			if (square[x][y] == 'b') {
				if (x != i - 1)
					availability = 1;
				if (check)
					while (i >= x) {
						square[i][j] = 'b';
						i -= 1;
						j -= 1;
					}
				break;
			}
		}
		else
			if (square[x][y] == 'w') {
				if (x != i - 1)
					availability = 1;
				if (check)
					while (i >= x) {
						square[i][j] = 'w';
						i -= 1;
						j -= 1;
					}
				break;
			}
	}
	valuable_assignment(&x, &y, first_x, first_y, &i, &j);

	while (x < 8 && y > 0) {	//go to -1 left -1 down
		x += 1;
		y -= 1;
		if (square[x][y] == '.')
			break;
		if (player == 1) {
			if (square[x][y] == 'b') {
				if (x != i + 1)
					availability = 1;
				if (check)
					while (i <= x) {
						square[i][j] = 'b';
						i += 1;
						j -= 1;
					}
				break;
			}
		}
		else
			if (square[x][y] == 'w') {
				if (x != i + 1)
					availability = 1;
				if (check)
					while (i <= x) {
						square[i][j] = 'w';
						i += 1;
						j -= 1;
					}
				break;
			}
	}
	valuable_assignment(&x, &y, first_x, first_y, &i, &j);

	while (x > 0 && y < 8) {	// go to +1 right +1 up
		x -= 1;
		y += 1;
		if (square[x][y] == '.')
			break;
		if (player == 1) {
			if (square[x][y] == 'b') {
				if (x != i - 1)
					availability = 1;
				if (check)
					while (i >= x) {
						square[i][j] = 'b';
						i -= 1;
						j += 1;
					}
				break;
			}
		}
		else
			if (square[x][y] == 'w') {
				if (x != i - 1)
					availability = 1;
				if (check)
					while (i >= x) {
						square[i][j] = 'w';
						i -= 1;
						j += 1;
					}
				break;
			}
	}
	return availability;
}

int winning(int black, int white) {		//shows who won the game
	if (black > white) {
		printf("\nBlack wins!\nBlack = %d\nWhite = %d", black, white);
		return 0;
	}
	else if (white > black) {
		printf("\nWhite wins!\nBlack = %d\nWhite = %d", black, white);
		return 0;
	}
	else {
		printf("\nDraw!\nBlack = %d\nWhite = %d", black, white);
		return 0;
	}
}