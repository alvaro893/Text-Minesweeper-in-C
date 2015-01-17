#include "table.h"

/* This is a extra function in order to count passed time */
void count_time(time_t *fin, time_t init){
	time(fin);
	printf("%d seconds\n", (int) difftime(*fin, init));
}

void print_tablex(){ // only for testing!!
	int i, j, value;

	for(i = 0; i < MAX; i++){
		printf("|%d", i+1);
	}
	printf("|\n");

	for(i = 0; i < MAX; i++){
		for(j = 0; j < MAX; j++){
			value = table.array[i][j];
			if(value == 99)
				printf("|m");
			else
				printf("|%d",value);
			
		}
		printf("| %d\n", i+1);
	}
}

int main(void){

	time_t init, fin;						// we need start time and end time
	char ch;

	time(&init);							// set current time in seconds
	initialize_table();
	
	while(table.nMines != 0){				// when nMines becomes 0 you will win the game
	
		system("cls");
		print_table();
		count_time(&fin, init);				// every time which count_time is called passed time is updated
		printf("cell values: 'X' unknown, '0' no mines close, '1-8' number of near mines, 'F' flag in cell\n");
		printf("push t (see Time), f (put/remove Flag in cell), c (Check cell), n (New game), e (Exit game): ");

		ch = getche(); putchar('\n');

		switch (ch){
		case 't':							// just update the time in the next loop
			break;
		case 'f':							// Flag
			put_flag();
			break;
		case 'c':							// check cell
			look_cell();
			break;
		case 'n':							// new game
			count_time(&fin, init);
			initialize_table();
			time(&init);
			break;
		case 'e':							// exit
			game_over();
			count_time(&fin, init);
			
		default:							// whatever other key is the same that 't' option
			break;
		}
	}
	game_over();							// on this point means that all mines were found
	count_time(&fin, init);
	

	return 0;
}