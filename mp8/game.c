#include "game.h"
/*                      NetID: Pdh2 djb6    Partners: pdh2, tylerjn2
 *The make_game function takes the inputted columns and rows variables and assigns them to game, as well as
 * sets the initial score to 0. Then it iterates through each cell and sets the value to -1. The next functions
 * remake_game is essentially the same prcoess of initializing the rows and cols of the array, and setting allocate
 * the cells to -1. The get_cell function first checks to see if the inputted cell is in the bounds of the array,
 * and then returns the value being held in that cell. The function move_w starts with initializing its variables.
 * Next, it has two for loops to iterate through all of the cells. Then it sets canmerge to 1, which is used to avoid
 * double merging. It checks then if the cell is empty. Then it iterates through the cells above it, checking if they
 * have the same value as the current cell. If the cell above is empty, the value is moved to the cell above, and deleted
 * from its original cell. If the cell above equals the current, it checks to see if there is another value inebtween the
 * two equal cells. If there isnt, and this cell hasnt already been merged in the same move, the upper cell will double,
 * and the original cell will become -1. The score will increase by the new value. Afterwards, the function returns 0 if
 * no moves were made, and 1 if a move or merge occured. The move_a, move_s, and move_d functions perform similarly,
 * just in their own respective direction. Lastly, the legal_move_check iterates through all the cell checking to see if
 * they are all filled. If one isnt, return 1 since a legal move is possible. If the board is filled, and the sceond set of
 * for loops iterating through all the cells says there are no merges available, return 0 to signify no legal moves are available.
 * We commented out the move_s and move_d functions as we could not get them to work at all to avoid segmentation faults.
*/


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure)
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct

    mygame->rows = rows; //inputted rows assigned to game
    mygame->cols = cols; //inputted columns assigned to game
    mygame->score = 0;  //initialize score to 0
    for(int i = 0; i < rows; i ++){//for loop for rows
      for(int j = 0; j < cols; j++){//for loop for columns
        mygame->cells[i*cols+j] = -1;//initialize board; set all values to -1
      }
    }

    return mygame;//return created game
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any
	memory previously allocated is not lost in this function.
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct

   (*_cur_game_ptr)->rows = new_rows;//changes value of rows in game to new value
   (*_cur_game_ptr)->cols = new_cols;//changes value of cols in game to new value
   (*_cur_game_ptr)->score = 0;//set the score pointer to 0.
   for(int i = 0; i < new_rows; i ++){//iterate through all the rows and columns
     for(int j = 0; j < new_cols; j++){
       (*_cur_game_ptr)->cells[i*new_cols+j] = -1;//set all the cells to -1
     }
   }

	return;
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;


}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{

    //YOUR CODE STARTS HERE

    if(row<0 || row>cur_game->rows || col<0 || col>cur_game->cols){//if the value is out of the bounds of the array
        return NULL;                                               //return NULL
    }

    return &cur_game->cells[row*cur_game->cols+col];        //returns value in cell in this location (2,4,8,16...)


}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/
{
    //YOUR CODE STARTS HERE
     int rows = cur_game->rows;//initialize variable rows to max rows in grid
     int cols = cur_game->cols;// intialize cols to max cols in row
     int moveworks = 0;//this variable will be used as a check to determine if any moves occur
     int canmerge; //initialize canmerge to be used as a checker, so that cells cant double merge in one move
     for(int j = 0; j < cols; j++){//for loop to go through columns

       for(int i = 0; i < rows; i++){//for loop to go through rows
         canmerge = 1;//set canmerge to 1
           if(cur_game->cells[i*cols+j] != -1){//if the cell above the current one is not empty
               for(int availablerow = 1; availablerow <= i; availablerow++){//for loop for each cell above the current
                   int cellabove = *get_cell(cur_game, availablerow-1, j);//save value of cell above current in cellabove
                   int currentcell = *get_cell(cur_game, i, j);//save value of current cell in currentcell
                   if(cellabove == -1){ //check if cell above is empty
                       cur_game->cells[(availablerow-1)*cols+j] = currentcell;//set the value of the empty cell above equal to the current
                       cur_game->cells[i*cols+j] = -1;//set the current cells value to -1
                       moveworks += 1;;//since a move has occurred, increment moveworks
                   }else if(cellabove == currentcell){//check if the cell above equals the current cell
                       for(int a = 1; a<rows-availablerow+1;a++){//initialize a for loop
                               if(cellabove == currentcell){//check if the cell above is the same as the current cell
                                 if(canmerge == 0){//if canmerge variable is set to 0, skip this merge to avoid double merging
                                   break;//break to avoid double merging
                               }
                               int jump = *get_cell(cur_game, availablerow-a+1,j);//set variable jump equal to the cells above the current
                               if(jump != currentcell && jump != -1 ){//if any cell between the one being checked and the current blocks the path for merging
                                 break;//break out of the loop
                               }

                               canmerge = 0;//set canmerge to 0
                               cur_game->cells[(availablerow-a)*cols+j] = 2*currentcell;//set the cell above that is merged to twice the value
                               cur_game->score += 2*currentcell;//increment the score by the new value from the merge
                               cur_game->cells[i*cols+j] = -1;//set the original cell to -1, or not filled
                               moveworks += 1;//increment variable to verify that a move was made
                           }
                       }
                   }
               }
          }
       }
     }

     if(moveworks == 0){//if no moves were made
       return 0;//return 0
     }else{//if a move was made return 1
       return 1;
     }
 };




int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE




//    int rows = cur_game->rows;
  //      int cols = cur_game->cols;
    //    int moveworks = 0;
      //  int canmerge;
        //for(int j = 0; j < cols; j++){
          //for(int i = 0; i < rows; i++){
            //canmerge = 1;
              //if(cur_game->cells[i*cols+j] != -1){
                //  for(int availablerow = 1; availablerow <= i; availablerow++)  {
                  //    int cellabove = *get_cell(cur_game,rows-availablerow+1, j);
                    //  int currentcell = *get_cell(cur_game, i, j);
                      //if(cellabove == -1){
                        //  cur_game->cells[(rows-availablerow+1)*cols+j] = currentcell;
                          //cur_game->cells[i*cols+j] = -1;
                      //    moveworks += 1;
                    //  }else if(cellabove == currentcell){
                      //    for(int a = 1; a<availablerow+1;a++){
                        //          if(cellabove == currentcell){
                          //          if(canmerge == 0){
                            //          break;
                              //    }
                                //  int jump = *get_cell(cur_game, availablerow+a+1,j);
                            //      if(jump != currentcell && jump != -1 ){
                              //      break;
                                //  }
                              //    canmerge = 0;
                              //    cur_game->cells[(availablerow+a)*cols+j] = 2*currentcell;
                                //  cur_game->score += 2*currentcell;
                              //    cur_game->cells[i*cols+j] = -1;
                        //          moveworks += 1;
                        //      }
                        //  }
                    //  }
                //  }
          //   }
        //  }
      //  }

      //  if(moveworks == 0){
        //  return 0;
      //  }else{
        //  return 1;
        //}

    return 1;

};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE

        //this code is the same as the move_w function with some slight differences we noted here

        int rows = cur_game->rows;
        int cols = cur_game->cols;
        int moveworks = 0;
        int canmerge;
        for(int i = 0; i < rows; i++){        //flipped the order of these for loops, the nested one is now columns
          for(int j = 0; j < cols; j++){      // in order to loop to the left
              canmerge = 1;
              if(cur_game->cells[i*cols+j] != -1){
                  for(int availablecol = 1; availablecol <= j; availablecol++)  {     //changed to availble column with the upper bound being the current column index
                      int cellleft = *get_cell(cur_game, i, availablecol-1);      //cell at the current availablecol index -1
                      int currentcell = *get_cell(cur_game, i, j);
                      if(cellleft == -1){
                          cur_game->cells[i*cols+(availablecol-1)] = currentcell;  //row-order major with availablecol - 1 as the changed part
                          cur_game->cells[i*cols+j] = -1;
                          moveworks += 1;
                      }else if(cellleft == currentcell){
                          for(int a = 1; a<cols-availablecol+1;a++){    //same as w but with column
                                  if(cellleft == currentcell){
                                    if(canmerge == 0){
                                      break;
                                  }

                                  canmerge = 0;
                                  cur_game->cells[i*cols+(availablecol-a)] = 2*currentcell; //row-order major variable  part is different
                                  cur_game->score += 2*currentcell;
                                  cur_game->cells[i*cols+j] = -1;
                                  moveworks += 1;
                              }
                          }
                      }
                  }
             }
          }
        }

        if(moveworks == 0){
          return 0;
        }else{
          return 1;
        }



    return 1;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE

        //we attempted and failed


    //int rows = cur_game->rows;
    //int cols = cur_game->cols;
    //int moveworks = 0;
    //int canmerge;
    //for(int i = 0; i < rows; i++){        //flipped the order of these for loops, the nested one is now columns
      //for(int j = 0; j < cols; j++){      // in order to loop to the left
          //canmerge = 1;
          //if(cur_game->cells[i*cols+j] != -1){
              //for(int availablecol = 1; availablecol <= j; availablecol++)  {     //changed to availble column with the upper bound being the current column index
                //  int cellleft = *get_cell(cur_game, i, availablecol+1);      //cell at the current availablecol index -1
                  //int currentcell = *get_cell(cur_game, i, j);
                  //if(cellleft == -1){
                    //  cur_game->cells[i*cols+(availablecol+1)] = currentcell;  //row-order major with availablecol - 1 as the changed part
                      //cur_game->cells[i*cols+j] = -1;
                    //  moveworks += 1;
                //  }else if(cellleft == currentcell){
                  //    for(int a = 1; a<cols-availablecol-1;a++){    //same as w but with column
                    //          if(cellleft == currentcell){
                      //          if(canmerge == 0){
                        //          break;
                          //    }
//
  //                            canmerge = 0;
    //                          cur_game->cells[i*cols+(availablecol+a)] = 2*currentcell; //row-order major variable  part is different
      //                        cur_game->score += 2*currentcell;
        //                      cur_game->cells[i*cols+j] = -1;
          //                    moveworks += 1;
            //              }
              //        }
                //  }
          //    }
      //   }
    //  }
    //}

  //  if(moveworks == 0){
    //  return 0;
  //  }else{
    //  return 1;
  //  }


    return 1;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE


//SEGMENTATION FAULT IF WE DON"T IMPLEMENT get_cell


for(int row=0; row<cur_game->rows;row++){ //loop through each row
  for(int col=0; col<cur_game->cols;col++){//loop through each column
     if(*get_cell(cur_game, row, col) !=-1){//if a cell is found that is empty, return 1
       return 1;
     }
  }
}
for(int row=0; row<cur_game->rows;row++){//loop through all rows
  for(int col=0; col<cur_game->cols;col++){//loop through all columns
     if(*get_cell(cur_game, row, col+1) == *get_cell(cur_game, row, col)){//if cell to the right of original is the same, merge can occur
       return 1;
     }
     if(*get_cell(cur_game, row, col-1) == *get_cell(cur_game, row, col)){//if cell to the left of original is the same, merge can occur
       return 1;
     }
     if(*get_cell(cur_game, row+1, col) == *get_cell(cur_game, row, col)){//if cell below the original is the same, merge can occur
       return 1;
     }
     if(*get_cell(cur_game, row-1, col) == *get_cell(cur_game, row, col)){//if cell above the original is the same, merge can occur
       return 1;
     }
  }
}
return 0;//if board is full, and no merges can occur, return 0

}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{

	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    if (cell_ptr == NULL){
        printf("Bad Cell Pointer.\n");
        exit(0);
    }


	//check for an empty cell
	int emptycheck = 0;
	int i;

	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}

    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game)
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;

	printf("\n\n\nscore:%d\n",cur_game->score);


	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char


    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  ");
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }

	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char

    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;

    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}

		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		}

		remake_game(&cur_game,rows,cols);

		move_success = 1;

    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }




    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game);
		 print_game(cur_game);
    }

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
