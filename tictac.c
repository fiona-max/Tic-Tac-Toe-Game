#include <stdio.h>
#include<stdlib.h>

void display_board(char *square, int n);
int checkwin(char ch, int n, char *square);
void clear_board(char *square, int n);
void play(char *square, int row, int column, int n, char ch);
int validate_move(int row, int column, int n, char *square);
void get_int(int *n);

int main()
{
	// Declaration of the variables 
    int n;
    int game_counter = 0;
    int row, column;
    int number_of_moves = 0;
    printf("Enter board size: ");
    //get the board size
    get_int(&n);
    
    // allocation of memory for the game
	char* square = (char*) malloc(n * n * sizeof(char));
    // clear and display a fresh board
	clear_board(square, n);
	display_board(square, n);	
	// game counter counts the number of cells used after every play    
    for (game_counter = 0; game_counter <= n*n; ++game_counter)
    {
	// asks player X to enter the coordinates of the cell he wants to use    	
    	printf("%s\n", "Player X, your turn");
    	do{
	    	printf("row: ");
	    	get_int(&row);
	    	printf("column: ");
	    	get_int(&column);
	    	if(!validate_move(row, column, n, square)){
	        	printf("%s\n", "Invalid position entered, try again");
		//  validate move enables the user to know if it is possible for player X to use a cell
	        }
	    } while(!validate_move(row, column, n, square));
	    
	    //place the seed 
     	play(square, row, column, n, 'X');
		number_of_moves += 1; 
    	display_board(square, n);
    	
    	// tells user no further action is possible by indicating that the game is a draw
		if(number_of_moves >= n*n)
		{
			printf("Sorry a draw this time!");
			exit(0);
		}
 		// enables  player X to know when he has won   	
    	if(checkwin('X', n, square)) {
    		printf("%s\n", "Player X wins!!!");
    		exit(0);
    	}
		// asks player Y to enter the coordinates of the cell he wants to use 
    	printf("%s\n", "Player Y, your turn");
    	do{
	    	printf("row: ");
	    	get_int(&row);
	    	printf("column: ");
	    	get_int(&column);
			// validate move enables the user to know if it is possible for player Y to use a cell	    	
	    	if(!validate_move(row, column, n, square)){
	        	printf("%s\n", "Invalid position entered, try again");
	        }
	    } while(!validate_move(row, column, n, square));
		
			 
    	play(square, row, column, n, 'Y'); 
    	number_of_moves += 1; 
    	display_board(square, n);
    	
    	// tells user no further action is possible by indicating that the game is a draw
    	if(number_of_moves >= n*n)
		{
			printf("Sorry a draw this time!");
			exit(0);
		}
		// enables  player Y to know when he has won
		if(checkwin('Y', n, square)) {
    		printf("%s\n", "Player Y wins!!!");
    		exit(0);
    	}
    }
	
	scanf("%d", &n);
    return 0;
}
/* the function display  displays a board whose size is determined at runtime
* @param square is the board
* @param n is the size of the board
*/
void display_board(char *square, int n)
{
    int i, j, k;
    for(i = 0; i<n; i++)
    	printf("----");
    printf("\n");
    for(i = 0; i<n; i++)
    {
        for(j = 0; j<n; j++)
        {
           printf("| %c ", *(square + i*n + j));
        }
        printf("|\n");
        for(k = 0; k<n; k++)
    		printf("----");
    	printf("\n");
    }


}

/**
 * checkwin enables us determine when there is a win in the game or indicates when either of the players have won
 * @param ch is the character to be displayed on the board
 * @param n is the size of the board
 * @param square its an n by n board
 */
int checkwin (char ch, int n, char *square)
{
	int i,j;
	int is_true = 1;
	int has_won = 0;
	
	//check win for the diagonal
	for(i=0;i<n;i++)
	{
		if(*(square + i*n + i) == ch){
			has_won+=1;
		} else {
			break;
		}
	}
	
	if(has_won == n)
		return 1;
	
	has_won = 0;
	
	//check win for the other diagonal
	for(i=0; i<n; i++)
	{

		if(*(square + (n-1-i)*n + i) == ch) {
			has_won += 1;
		} else {
			break;
		}
	}
	
	if(has_won >= n)
		return 1;
		
	has_won = 0;
		
	//check win the rows
	for(i=0;i<n;i++)
	{
		
		for (j=0; j<n;j++)
		{
			if(*(square + i*n + j) == *(square + i*n + j+1) && *(square + i*n + j) == ch){
				has_won += 1;
				continue;
			} else {
				if(has_won == (n-1)) 
					return 1;
				has_won = 0;
				break;
			}
		}
	}
	
	if(has_won == (n-1)) 
		return 1;
	
	has_won = 0;
	//check win for the columns
	for(i=0;i<n;i++)
	{		
		for (j=0; j<n;j++)
		{			
			if(*(square + j*n + i) == *(square + (j+1)*n + i) && *(square + j*n + i) == ch){
				has_won += 1;
				continue;
			} else {
				if(has_won == (n-1)) 
					return 1;
				has_won = 0;
				break;
			}
		}
	}
	if(has_won == (n-1)) 
		return 1;
	else 
		return 0;
}
/**
* enables the board to be empty and ready for a play before every game
* @param square is the n by n board
* @param n is the size of the board
*/
void clear_board(char *square, int n) 
{
	int i, j;
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n; ++j)
		{	
			*(square + i*n + j) = ' '; //clear the board
		}
	}
}
/**
* Helps check and determine whether or not a cell is free 
* @param row indicates the width of the board
* @param column indicates the length of the board
*/
int validate_move(int row, int column, int n, char *square) 
{
    if((row >= 0 && row < n) && (column >= 0 && column < n) && (*(square + row*n + column) == ' '))
    	return 1;
    else
    	return 0;
} 
/**
* The function servers as a character controller , insures that only intergers are taken as input for cell coordinates
*@param ch character displayed on the board
*@param n the size of the board
*/
void get_int(int *n)
{
	char ch;
	while((scanf("%d", n))!=1)
	{
		printf("Invalid <try again>: ");
		while((ch=getchar())!='\n')
		{ 
			fflush(stdin);
			fflush(stdout);
		}
	}
}
/**
* The function play ensures that the coordinates entered play the user match with the desired cell
* @param square is the board
* @param row indicates the width of the board
* @param column indicates the length of the board
* @param n the size of the board
* @param ch is the character displayed on the board
*/
void play(char *square, int row, int column, int n, char ch) 
{
	*(square + row * n + column) = ch; //place ch on the board
}


