// Programming course project
// Developed by Alvaro Bolaños Rodriguez

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// OS: use "_WIN32" for windows and "linux" for linux-like OS
#ifdef _WIN32
#include <conio.h>
#endif

// table size by default (10 x 10 cells)
#define MAX 10

// Values of a cell (two digits)
//		   ___ it says the number of near mines 0-8
//		  |
//		X Y    
//		|_____ it says state (0 covered, 1 uncovered , 2 with flag)
//
// 0 performs a blank cell
// 1-8 a number of mines around and un checked cells
// 10-18 are checked (uncovered) cells (+10)
// 20-28 with flag (+20)
// 99 is a mine
// 100 is a mine with flag (+1)

/** this array performs the table */
struct Ttable{
	unsigned char array[MAX][MAX];		// unsigned char let us to use 1 byte integer type in order to not waste memory
	int nMines;							// when a flag are put in a mine cell nMines decreases, when nMines goes to zero you win the game 
} table;

/** It puts mines randomly on the table and calc the "approximation numbers" */
int initialize_table();

/** Prints the table */
void print_table();

/** ask a row and column by keyboard and returns the value of cell */
int read_cell(int *row, int *col);

/**  If the cell value is a mine, sums 1. if it is a value between 1-8 sums 20 */
int put_flag();

int remove_flag(int row, int col ,int value);

/** this is the most important function, it checks if there are a mine (uncover it),
sums 20 if there are a number, if the cell is blank then uncover_blank_cell() function is called */
int look_cell();

/**This is a recursive function which uncovers blank cells while they are adjacent*/
int uncover_blank_cell(int row, int col);

/** game over, program ends and show it */
void game_over();
