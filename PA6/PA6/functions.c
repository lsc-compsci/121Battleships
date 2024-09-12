#include "Header.h"

void welcome_screen(void)
{
	printf("   --- Welcome to Battleships ---\n\n");
	printf(" 1.This is a two-player game.\n 2.The objective is to sink all of your opponent's navy (ships).\n 3.The first to sink the other's fleet wins.\n");
	printf(" 4.The game will be played on a 10x10 board.\n 5.You and your opponent will have to pick the co-ordinates of where to place your ships without letting the other know.\n 6.Afterwards you each will alternate picking which 'cell' on the board to attack/to sink.\n");
	printf(" 7.Carrier(C) - 5 cells, Battleship(B) - 4 cells, Cruiser(R) - 3 cells, Submarine(S) - 3 cells, Destroyer(D) - 2 cells.\n");
	printf(" Lastly, you are Player 1, and the CPU is Player 2.\n\n");
	printf("   ----- Goodluck! -----\n");
}


void display_board(Cell board[][COLS], int no_rows, int no_columns)
{

	int row_i = 0, col_j = 0;
	printf("%5d%2d%2d%2d%2d%2d%2d%2d%2d%2d\n", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
	for (; row_i < no_rows; ++row_i)
	{
		printf("%3d", row_i);
		for (col_j = 0; col_j < no_columns; ++col_j)
		{
			printf("%2c", board[row_i][col_j].symbol);
		}

		putchar('\n');
	}
}

int yes_no(void)
{
	char y_n = '\0';
	int value = -1;

	do
	{
		printf("(Y/N)\n");
		scanf("%c", &y_n);
	} while (!(y_n == 'Y' || y_n == 'y' || y_n == 'N' || y_n == 'n'));
	if (y_n == 'Y' || y_n == 'y')
	{
		return 1;
	}
	if (y_n == 'N' || y_n == 'n')
	{
		return 0;
	}
}

int select_who_starts_first(void)
{
	int r_value = 0;

	r_value = rand() % 2;
	if (r_value == 1)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

void initialize_playerboards(Cell p1_board[][COLS], Cell p2_board[][COLS])
{
	int row_i = 0, col_j = 0;

	for (; row_i < ROWS; ++row_i)
	{
		for (col_j = 0; col_j < COLS; ++col_j)
		{
			p1_board[row_i][col_j].symbol = WATER;
			p1_board[row_i][col_j].ContainShip = FALSE;
			p1_board[row_i][col_j].hit = NEITHER;
		}
	}

	for (row_i = 0; row_i < ROWS; ++row_i)
	{
		for (col_j = 0; col_j < COLS; ++col_j)
		{
			p2_board[row_i][col_j].symbol = WATER;
			p2_board[row_i][col_j].ContainShip = FALSE;
			p2_board[row_i][col_j].hit = NEITHER;
		}
	}
}

int rng(int size)
{
	return rand() % size + 1;
}

void place_ships(Cell board[][COLS], int row, int cols, int size, char ship_symbol, Direction dir)
{
	int count = 0;
	if (dir == HORI)
	{
		for (count = 0; count < size; ++count)
		{
			board[row][cols + count].symbol = ship_symbol;
			board[row][cols + count].ContainShip = TRUE;
		}
	}
	if (dir == VERT)
	{
		for (count = 0; count < size; ++count)
		{
			board[row + count][cols].symbol = ship_symbol;
			board[row + count][cols].ContainShip = TRUE;
		}
	}
}

void ship_placements(Cell p1_board[][COLS], Cell p2_board[][COLS])
{
	int y_nvalue = -1;
	printf(" Would you like to place your ships manually?\n");
	y_nvalue = yes_no();

	if (y_nvalue)
	{
		manually_placeships(p1_board);
		system("cls");
		printf("  Your Finalized Navy: \n");
		display_board(p1_board, ROWS, COLS);
		system("pause");
	}
	else
	{
		randomly_placeships(p1_board);
		system("cls");
		printf("Your Randomized Navy has been Finalized: \n");
		display_board(p1_board, ROWS, COLS);
		system("pause");
	}
	randomly_placeships(p2_board);
	system("cls");
	printf("  CPU's Navy has been generated and finalized... \n");
	system("pause");
}

Direction get_coordinates(Cell board[][COLS], int* row, int* cols, int size_of_ship)
{
	int x = 0, y = 0, valid = 1;
	char hor_vert = '\0'; // declaration to the user whether they want to place it horizontally or vertically
	Direction direction;
	do
	{
		do
		{
			printf("Enter a starting point on the board (x, y):\n");
			scanf("%d %d", &x, &y);
		} while (!((x >= 0 && x < 10) && (y >= 0 && y < 10)));
		*row = x;
		*cols = y;

		//PROMPTS THE USER FOR A VALID DIRECTION
		do
		{
			printf("Enter the direction in which you want to place your ship. H for horizontal, V for vertical.\n");
			scanf(" %c", &hor_vert);
		} while (!(hor_vert == 'H' || hor_vert == 'V'));
		if (hor_vert == 'H')
		{
			direction = HORI;
		}
		if (hor_vert == 'V')
		{
			direction = VERT;
		}
		//VALIDATES IF THE SHIP FITS PROPERLY IN THE BOARD CELLS
		valid = is_positionValid(board, direction, x, y, size_of_ship, 0);

	} while (!valid);
	return direction;
}

int is_positionValid(Cell board[][COLS], Direction dir, int row, int cols, int size, int silent)
{
	int valid = 1, count = 0;
	if (dir == HORI)
	{
		for (count = 0; count < size; ++count)
		{
			if (board[row][cols + count].ContainShip == TRUE || cols + count > 9)
			{
				valid = 0;
			}
		}
	}
	if (dir == VERT)
	{
		for (count = 0; count < size; ++count)
		{
			if (board[row + count][cols].ContainShip == TRUE || row + count > 9)
			{
				valid = 0;
			}
		}
	}
	if (valid == 0 && silent == 0)
	{
		printf(" Invalid Ship Placement. There's an error with your position on the board!\n");
		system("pause");
	}
	return valid;
}


void manually_placeships(Cell board[][COLS])
{
	int row = 0, cols = 0;
	Direction dir;
	system("cls");
	printf("Select a co-ordinate for your carrier (5 units).\n");
	display_board(board, ROWS, COLS);
	dir = get_coordinates(board, &row, &cols, 5);
	place_ships(board, row, cols, 5, CARRIER, dir);

	system("cls");
	printf("Select a co-ordinate for your battleship (4 units).\n");
	display_board(board, ROWS, COLS);
	dir = get_coordinates(board, &row, &cols, 4);
	place_ships(board, row, cols, 4, BATTLESHIP, dir);

	system("cls");
	printf("Select a co-ordinate for your cruiser (3 units).\n");
	display_board(board, ROWS, COLS);
	dir = get_coordinates(board, &row, &cols, 3);
	place_ships(board, row, cols, 3, CRUISER, dir);

	system("cls");
	printf("Select a co-ordinate for your submarine (3 units).\n");
	display_board(board, ROWS, COLS);
	dir = get_coordinates(board, &row, &cols, 3);
	place_ships(board, row, cols, 3, SUBMARINE, dir);

	system("cls");
	printf("Select a co-ordinate for your destroyer (2 units).\n");
	display_board(board, ROWS, COLS);
	dir = get_coordinates(board, &row, &cols, 2);
	place_ships(board, row, cols, 2, DESTROYER, dir);
}

void randomly_placeships(Cell board[][COLS])
{
	int row = 0, cols = 0, r_dir = 0, valid = 1;
	Direction direction;
	// CARRIER RANDO PLACEMENT
	do
	{
		r_dir = rng(2);
		if (r_dir == 1)
		{
			direction = HORI;
		}
		if (r_dir == 2)
		{
			direction = VERT;
		}
		row = (rng(10) - 1); // that way we can get a random number starting from '0'
		cols = (rng(10) - 1);
		valid = is_positionValid(board, direction, row, cols, 5, 1);
	} while (!valid);
	place_ships(board, row, cols, 5, CARRIER, direction);

	// BATTLESHIP RANDO PLACEMENT
	do
	{
		r_dir = rng(2);
		if (r_dir == 1)
		{
			direction = HORI;
		}
		if (r_dir == 2)
		{
			direction = VERT;
		}
		row = (rng(10) - 1); // that way we can get a random number starting from '0'
		cols = (rng(10) - 1);
		valid = is_positionValid(board, direction, row, cols, 4, 1);
	} while (!valid);
	place_ships(board, row, cols, 4, BATTLESHIP, direction);

	// CRUISER RANDO PLACEMENT
	do
	{
		r_dir = rng(2);
		if (r_dir == 1)
		{
			direction = HORI;
		}
		if (r_dir == 2)
		{
			direction = VERT;
		}
		row = (rng(10) - 1); // that way we can get a random number starting from '0'
		cols = (rng(10) - 1);
		valid = is_positionValid(board, direction, row, cols, 3, 1);
	} while (!valid);
	place_ships(board, row, cols, 3, CRUISER, direction);

	// SUBMARINE RANDO PLACEMENT 
	do
	{
		r_dir = rng(2);
		if (r_dir == 1)
		{
			direction = HORI;
		}
		if (r_dir == 2)
		{
			direction = VERT;
		}
		row = (rng(10) - 1); // that way we can get a random number starting from '0'
		cols = (rng(10) - 1);
		valid = is_positionValid(board, direction, row, cols, 3, 1);
	} while (!valid);
	place_ships(board, row, cols, 3, SUBMARINE, direction);

	// DESTROYER RANDO PLACEMENT
	do
	{
		r_dir = rng(2);
		if (r_dir == 1)
		{
			direction = HORI;
		}
		if (r_dir == 2)
		{
			direction = VERT;
		}
		row = (rng(10) - 1); // that way we can get a random number starting from '0'
		cols = (rng(10) - 1);
		valid = is_positionValid(board, direction, row, cols, 2, 1);
	} while (!valid);
	place_ships(board, row, cols, 2, DESTROYER, direction);
}

void you_n_cpu_battlesheet(Cell p1_board[][COLS], Cell p2_board[][COLS])
{
	printf("\n     - Your Board -\n");
	display_board(p1_board, ROWS, COLS);

	int row_i = 0, col_j = 0;
	printf("\n  -Info on Enemy's Board-\n");
	printf("%5d%2d%2d%2d%2d%2d%2d%2d%2d%2d\n", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
	for (; row_i < ROWS; ++row_i)
	{
		printf("%3d", row_i);
		for (col_j = 0; col_j < COLS; ++col_j)
		{
			printf("%2c", p2_board[row_i][col_j].hit);
		}
		putchar('\n');
	}
	}

	void shot_validation(Cell board[][COLS], int* row, int* cols)
	{
		int valid = 1, x = 0, y = 0;
		do
		{
			valid = 1;
			do
			{
				printf("Enter a co-ordinate (x, y) to fire at:\n");
				scanf("%d %d", &x, &y);
			} while (!((x >= 0 && x < 10) && (y >= 0 && y < 10)));
			if (board[x][y].hit != NEITHER)
			{
				valid = 0;
				printf(" Invalid input, Position has already been shot at before. Pick a different co-ordinate.\n");
			}
		} while (!valid);
		*row = x;
		*cols = y;
	}

	char shots_fired(Cell battle_board[][COLS], int row, int cols)
	{
		char value = '\0';

		if (battle_board[row][cols].ContainShip == TRUE)
		{
			value = battle_board[row][cols].symbol;
			battle_board[row][cols].hit = HIT;
			battle_board[row][cols].symbol = HIT;
		}
		if (battle_board[row][cols].ContainShip == FALSE)
		{
			value = battle_board[row][cols].symbol;
			battle_board[row][cols].hit = MISS;
			battle_board[row][cols].symbol = MISS;
		}
		return value;
	}

void rshot_validation(Cell board[][COLS], int* row, int* cols)
{
	int valid = 1, x = 0, y = 0;
	do
	{
		valid = 1;
		x = (rng(10) - 1);
		y = (rng(10) - 1);
		if (board[x][y].hit != NEITHER)
		{
			valid = 0;
		}
	} while (!valid);
	*row = x;
	*cols = y;
}

int start_battle(Cell p1_board[][COLS], Cell p2_board[][COLS])
{
	FILE* outfile = fopen("battleship.log", "w"); // opens file in function and writes to it in the .txt file 
	char result = '\0';
	int deter_win = -1, p_turn = 0, x = 0, y = 0,
		carrier1 = 5, carrier2 = 5, bship1 = 4, bship2 = 4, cruiser1 = 3, cruiser2 = 3, sub1 = 3, sub2 = 3, dest1 = 2, dest2 = 2,
		p1_HP = carrier1 + bship1 + cruiser1 + sub1 + dest1, 
		p2_HP = carrier2 + bship2 + cruiser2 + sub2 + dest2,
		p1_shots = 0, p2_shots = 0,
		p1_hits = 0, p2_hits = 0;

	Stats player1 = { 0, 0, 0, 0, FALSE },
		  player2 = { 0, 0, 0, 0, FALSE };

	p_turn = select_who_starts_first(2);

	while (p1_HP > 0 && p2_HP > 0)
	{
		switch (p_turn)
		{
		case 1: system("cls");
			printf("  Player 1's Turn\n");
			fprintf(outfile, "Player 1's Turn\n");
			you_n_cpu_battlesheet(p1_board, p2_board);
			shot_validation(p2_board, &x, &y);
			result = shots_fired(p2_board, x, y);
			printf(" You shot at (%d, %d)\n", x, y);
			fprintf(outfile, "Player 1 shot at (%d, %d)\n", x, y);
			system("pause");

			switch (result) //replaces output_current_move() and check_if_sunk_ship()
			{
			case CARRIER: carrier2 -= 1; printf(" HIT!\n"); fprintf(outfile, "Player One shot down a Carrier unit.\n"); 
				if (carrier2 == 0)
				{
					fprintf(outfile, "Player One has sunk the Enemy's Carrier.\n");
				}
				system("pause"); ++player1.Totalhits; 
				break;
			case BATTLESHIP: bship2 -= 1; printf(" HIT!\n"); fprintf(outfile, "Player One shot down a Battleship unit.\n");
				if (bship2 == 0)
				{
					fprintf(outfile, "Player One has sunk the Enemy's Battleship.\n");
				}
				system("pause"); ++player1.Totalhits;
				break;
			case CRUISER: cruiser2 -= 1; printf(" HIT!\n"); fprintf(outfile, "Player One shot down a Cruiser unit.\n");
				if (cruiser2 == 0)
				{
					fprintf(outfile, "Player One has sunk the Enemy's Cruiser.\n");
				}
				system("pause"); ++player1.Totalhits;
				break;
			case SUBMARINE: sub2 -= 1; printf(" HIT!\n");  fprintf(outfile, "Player One shot down a Submarine unit.\n");
				if (sub2 == 0)
				{
					fprintf(outfile, "Player One has sunk the Enemy's Submarine.\n");
				}
				system("pause"); ++player1.Totalhits;
				break;
			case DESTROYER: dest2 -= 1; printf(" HIT!\n"); fprintf(outfile, "Player One shot down a Destroyer unit.\n");
				if (dest2 == 0)
				{
					fprintf(outfile, "Player One has sunk the Enemy's Destroyer.\n");
				}
				system("pause"); ++player1.Totalhits;
				break;
			case WATER: printf(" MISS!\n");  fprintf(outfile, "Player One Missed.\n"); system("pause"); ++player1.Totalmisses;
				break;
			}
			++player1.Totalshots;
			p1_HP = carrier1 + bship1 + cruiser1 + sub1 + dest1;
			p_turn = 2;
			break;

		case 2: system("cls");
			printf("  Player 2's Turn\n");
			fprintf(outfile, "Player 2's Turn\n");
			rshot_validation(p1_board, &x, &y);
			result = shots_fired(p1_board, x, y);
			printf(" Player 2 shot at (%d, %d)\n", x, y);
			fprintf(outfile, "CPU shot at (%d, %d)", x, y);
			system("pause");

			switch (result)
			{
			case CARRIER: carrier1 -= 1; printf(" HIT!\n");  fprintf(outfile, "CPU shot down a Carrier unit.\n"); 
				if (carrier1 == 0)
				{
					fprintf(outfile, "CPU has sunk Player One's Carrier.\n");
				}
				system("pause"); ++player2.Totalhits;
				break;
			case BATTLESHIP: bship1 -= 1; printf(" HIT!\n"); fprintf(outfile, "CPU shot down a Battleship unit.\n");
				if (bship1 == 0)
				{
					fprintf(outfile, "CPU has sunk Player One's Battleship.\n");
				}
				system("pause"); ++player2.Totalhits;
				break;
			case CRUISER: cruiser1 -= 1; printf(" HIT!\n"); fprintf(outfile, "CPU shot down a Cruiser unit.\n");
				if (cruiser1 == 0)
				{
					fprintf(outfile, "CPU has sunk Player One's Cruiser.\n");
				}
				system("pause"); ++player2.Totalhits;
				break;
			case SUBMARINE: sub1 -= 1; printf(" HIT!\n");  fprintf(outfile, "CPU shot down a Submarine unit.\n");
				if (sub1 == 0)
				{
					fprintf(outfile, "CPU has sunk Player One's Submarine");
				}
				system("pause"); ++player2.Totalhits;
				break;
			case DESTROYER: dest1 -= 1; printf(" HIT!\n"); fprintf(outfile, "CPU shot down a Destroyer unit.\n"); 
				if (dest1 == 0)
				{
					fprintf(outfile, "CPU has sunk Player One's Destroyer.\n");
				}system("pause"); ++player2.Totalhits;
				break;
			case WATER: printf(" MISS!\n"); fprintf(outfile, "CPU Missed.\n"); system("pause"); ++player2.Totalmisses;
				break;
			}
			++player2.Totalshots;
			p2_HP = carrier2 + bship2 + cruiser2 + sub2 + dest2;
			p_turn = 1;
			break;
		}
	}

	if (p1_HP == 0)
	{
		player2.win = TRUE;
		deter_win = 2;
		fprintf(outfile, "\nPLAYER TWO WINS!\n");
	}
	if (p2_HP == 0)
	{
		player1.win = TRUE;
		deter_win = 1;
		fprintf(outfile, "\nPLAYER ONE WINS!\n");
	}


	// WRITING STATS TO THE OUTFILE

	player1.hm_ratio = (((double)player1.Totalhits / player1.Totalshots) * 100); // Calculates the Hit_Miss ratio
	player2.hm_ratio = (((double)player2.Totalhits / player2.Totalshots) * 100);
	fprintf(outfile, "\nGAME END REPORT\n");
	fprintf(outfile, "Player One's Stats:\n Total Shots: %d  Total Hits: %d  Total Misses: %d Hit/Miss Ratio: %.2lf%\n", player1.Totalshots, player1.Totalhits, player1.Totalmisses, player1.hm_ratio);
	fprintf(outfile, "Player Two's Stats:\n Total Shots: %d  Total Hits: %d  Total Misses: %d Hit/Miss Ratio: %.2lf%\n", player2.Totalshots, player2.Totalhits, player2.Totalmisses, player2.hm_ratio);
	fclose(outfile);

	return deter_win;
}