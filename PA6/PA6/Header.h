#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define ROWS 10
#define COLS 10
#define NO_OF_SHIPS 5
#define CARRIER  'C'
#define BATTLESHIP 'B'
#define SUBMARINE 'S'
#define CRUISER 'R'
#define DESTROYER 'D'
#define WATER '-'

#define HIT 'H'
#define MISS 'M'
#define NEITHER '~'

// STRUCT DEFINITIONS

typedef enum direction
{
	HORI, VERT
}Direction;

typedef enum filled
{
	TRUE, FALSE
}Filled;

typedef struct cell
{
	char hit;
	Filled ContainShip;
	char symbol;
}Cell;

typedef struct stat
{
	int Totalhits;
	int Totalshots;
	int Totalmisses;
	double hm_ratio;
	Filled win;
}Stats;


// FUNCTION PROTOTYPES

void welcome_screen(void);
void display_board(char board[][10], int no_rows, int no_columns);
int yes_no(void);
int who_starts_first(void);

void initialize_playerboards(Cell p1_board[][COLS], Cell p2_board[][COLS]);
int rng(int size); // random number generator for deciding who goes first and CPU battleship attacks

void place_ships(Cell board[][COLS], int row, int cols, int size, char ship_symbol, Direction dir);
void ship_placements(Cell p1_board[][COLS], Cell p2_board[][COLS]);
Direction get_coordinates(Cell board[][COLS], int* row, int* cols, int size_of_ship);
int is_positionValid(Cell board[][COLS], Direction dir, int row, int cols, int size, int silent); // int silent is used, set to '0' to not print invalid statement when function is called for randomly_placeships

void manually_placeships(Cell board[][COLS]);
void randomly_placeships(Cell board[][COLS]);

void you_n_cpu_battlesheet(Cell p1_board[][COLS], Cell p2_board[][COLS]);

void shot_validation(Cell board[][COLS], int* row, int* cols); // Check if the shot co-ordinate is in bound of the board, and if cell would shot before
char shots_fired(Cell battle_board[][COLS], int row, int cols); // Should tell the player if function is a hit or miss.
void rshot_validation(Cell board[][COLS], int* row, int* cols); // Similar to line 67 but this function is used for player 2.

int start_battle(Cell p1_board[][COLS], Cell p2_board[][COLS]); // When we start taking Health points (17 HP because 17 total ship units) into consideration w/ implemention of who_starts_first() function





#endif
