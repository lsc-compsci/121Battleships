/*
* Programmer: Sher Chhi LY
* Class: CptS 121
* TA: Jacob Lin
* Description: PA 6 - Battleships
*/

#include "Header.h"

int main(void)
{
	int winner = 0;
	Cell player1_board[ROWS][COLS];
	Cell player2_board[ROWS][COLS];

	welcome_screen();
	srand((int unsigned)time(NULL));

	printf("\n Are you ready?\n Press any key to start game\n");
	system("pause > nul");
	system("cls");

	initialize_playerboards(player1_board, player2_board);
	ship_placements(player1_board, player2_board);
	winner = start_battle(player1_board, player2_board);

	if (winner == 1)
	{
		printf(" PLAYER ONE WINS!\n");
		system("pause");
		system("exit");
	}
	if (winner == 2)
	{
		printf(" PLAYER TWO WIN!\n");
		system("pause");
		system("exit");
	}
	return 0;
}