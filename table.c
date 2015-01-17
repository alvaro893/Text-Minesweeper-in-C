#include "table.h"


int initialize_table(){
	int i,j,r,c,value, rows[8], columns[8];
	table.nMines = 10;
	srand (time(NULL));						// random seed

	// set all cells to 0
	for(i = 0; i < 10; i++)				
		for(j = 0; j < 10; j++)
			table.array[i][j] = 0;

	for(i = 0; i < table.nMines; i++){
		/* initialize random seed: */

		r = rand() % 10;					// it generates a integer in the range 0 to 9
		c = rand() % 10;
		
		// put mines
		if(table.array[r][c] != 99){
			table.array[r][c] = 99;

			// Get position of adjacent cells of current cell
			rows[0] = r - 1;	columns[0] = c + 1;
			rows[1] = r;		columns[1] = c + 1;
			rows[2] = r + 1;	columns[2] = c + 1;
			rows[3] = r - 1;	columns[3] = c;
			rows[4] = r + 1;	columns[4] = c;
			rows[5] = r - 1;	columns[5] = c - 1;
			rows[6] = r;		columns[6] = c - 1;
			rows[7] = r + 1;	columns[7] = c - 1;

			for(j = 0; j < 8; j++){
				value = table.array[rows[j]][columns[j]];
				if( (rows[j] >= 0 && rows[j] < MAX) && (columns[j] >= 0 && columns[j] < MAX) ){		// to prevent negative index and out of bounds
						if(value != 99)																// to prevent remove mines
							table.array[rows[j]][columns[j]] += 1;									// sums 1 to each adjacent cell
				}
			}
			
		}else{								// to make sure that there are the properly number of mines in table
			i--;
			continue;
		}
	}



}

void print_table(){
	int i, j, value;

	for(i = 0; i < MAX; i++){
		printf("|%d", i+1);
	}
	printf("|\n");

	for(i = 0; i < MAX; i++){
		for(j = 0; j < MAX; j++){
			
			value = table.array[i][j];

			if(value >= 0 && value <= 8 || value == 0 || value == 99)
				printf("|X");
			else if(value >= 10 && value <= 18)
				printf("|%d", value - 10);
			else if(value >= 20 && value <= 28 || value == 100)
				printf("|F");
			else
				printf("ERROR"); // test purposes
			
		}
		printf("| %d\n", i+1);
	}
}

int read_cell(int *row, int *col){
	
	printf("write the row and column with a space:");
	scanf("%d %d", col, row);
	(*row)--;	// subtract 1 because actually array need a number between 0-9 not 1-10
	(*col)--;	// ...
	return table.array[*row][*col];
}

int put_flag(){
	int row, col, value;

	value = read_cell(&row, &col);		// read

	if (value == 99){					// mine case
		table.array[row][col] += 1;
		table.nMines -= 1;				// mine found
		return 1;
	}else if(value >= 0 && value <= 8){	// number of mines case (the next cell is a mine)
		table.array[row][col] += 20;
		return 1;
	}else if(value >= 20 && value <= 28){
		remove_flag(row, col, value);
	}else
		return 0;						// error
}

// NOTE: this function is actually inside put_flag()
int remove_flag(int row, int col ,int value){
	if (value == 100){						// mine case
		table.array[row][col] -= 1;
		table.nMines += 1;					// mine missed
		return 1;
	}else if(value >= 20 || value <= 28){	// number of mines case (the next cell is a mine)
		table.array[row][col] -= 20;
		return 1;
	}else
		return 0;							// error
}

/* this is the most important function, it checks if there are a mine (uncover it),
sums 20 if there are a number, if the cell is blank then uncover_blank_cell() function is called */
int look_cell(){
	int row, col, value;

	value = read_cell(&row, &col);		// this implements the previous variables
	
	if(value == 0)						// blank case
		uncover_blank_cell(row, col);	
	else if(value == 99)				// mine case
		game_over();
	else if(value > 0 && value <= 8)	// number case (the next cell is a mine)
		table.array[row][col] += 10;
	else
		return 0;						// error
}

/*This is a recursive function which uncovers blank cells while they are adjacent*/
int uncover_blank_cell(int row, int col){
	int value, rows[8], columns[8], i;

	if(table.array[row][col] != 0)
		return 0; // error

	table.array[row][col] += 10; // uncover current cell
	
	// Get position of adjacent cells of current cell
	rows[0] = row - 1;	columns[0] = col + 1;
	rows[1] = row;		columns[1] = col + 1;
	rows[2] = row + 1;	columns[2] = col + 1;
	rows[3] = row - 1;	columns[3] = col;
	rows[4] = row + 1;	columns[4] = col;
	rows[5] = row - 1;	columns[5] = col - 1;
	rows[6] = row;		columns[6] = col - 1;
	rows[7] = row + 1;	columns[7] = col - 1;

	for(i = 0; i < 8; i++){
		value = table.array[rows[i]][columns[i]];

		if( (rows[i] >= 0 && rows[i] < MAX) && (columns[i] >= 0 && columns[i] < MAX) ){		// to prevent negative index and out of bounds
			if(value > 0 && value <= 8)
				table.array[rows[i]][columns[i]] += 10;										// it is a cell with 1-8 number so we need to uncover
			else if(value == 0)
				uncover_blank_cell(rows[i], columns[i]);
		}
		
	}

	return 1; // success!
}

void game_over(){
	printf("GAME OVER\n");

	if(table.nMines == 0){
		system("cls");
		print_table();
		printf("you won!!!!\n");

	}else
		printf("BOOM! you LOOSE!");

	printf("\n push any key to continue...\n");
	
	fflush(stdin);
	getchar();

	exit(0);
}
