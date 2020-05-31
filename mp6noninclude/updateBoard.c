/*                                           MP6: Game of Life by djb6, parters: pdh2 and chall28
 *  Our program runs the updating sequence of a game of life simulation using 3 functions to operate on the board
 *  array which contains the cells. The first one counts the number of "live" neighborsof the
 * 8 cells which surround a cell. It takes into account the cells on the edges and corners as well as not
 * counting itself with if statments. We used two for loops to increment through the rows and columns around
 * the cell. We check if the array has a '1' inside of it using array indexing and if it does we
 * increment a living cells variable. Our next function, updateBoard updates the board to the next index of the simulation.
 * It calls our countLiveNeighbor function and checks for all of the cases which change the game. If the cell has 3 neighbors
 * the cell either stays alive or comes alive. If it was alive and has 2 neighbors it stays alive. Otherwise, the cell dies or stays
 * dead. After each of those cases it updates the board array.Our final function, aliveStable, has a copy of the updateBoard function
 * in it which puts the new values of the board into a temporary board. We then subtract all of the values of the tempboard
 * from the real board and if any part of it changes(i.e. the difference doesn't equal 0) it increments a variable d. If d = 0 at
 * the end of it all, we return 1, otherwise, it will return 0.
*/







/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
int cells=0,j,i;      //intialize alive neighbor cell count and current row(j) and current column(i)
for(j = row-1; j < row+2; j++){            //loop from 1 left of cell to 1 right of cell
  for(i = col-1; i < col+2; i++){         //loop from 1 below cell to 1 above cell
    if(j == row && i == col){             //checks for if it's itself, if so continue back
      continue;}
    if(j>=0 && j<boardRowSize && i<=boardColSize && i>=0)    //checks that cell it's checking is within the bounds of the boardd
     if(board[(boardColSize*j+i)]){
          cells++;       //increment living cells variable
        }
      }
}
return cells;
}
/*
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
int status, col, row;
for(row = 0; row < boardRowSize+1; row++){            //row incrementer
  for(col = 0; col < boardColSize+1; col++){        //column  incrementer
    status = countLiveNeighbor(board,boardRowSize,boardColSize,row,col);    //calls countLiveNeighbor and stores in variable
      if(status == 3){                  //if 3 neighbors, always alive
        board[boardColSize*row+col] = 1;
      }
      if(status ==2 && board[boardColSize*row+col]==1){     //if cell is alive with 2 neighbors, keep it alive
        board[boardColSize*row+col] = 1;
      }
      else{                   //any other cases it dies/stays dead
        board[boardColSize*row+col]=0;
      }
    }
      }
return;
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize){
int status, col, row, d=0;
int tempBoard[boardRowSize*boardColSize];
   for(row = 0; row < boardRowSize+1; row++){
   	for(col = 0; col < boardColSize+1; col++){			// cycles through entire board
   		status = countLiveNeighbor(board, boardRowSize, boardColSize, row, col);				// calls countLiveNeighbor function
   		if(board[row*boardColSize + col] == 1){			// if cell is currently ALIVE
   			if(status == 2 || status == 3){				// if number of live surrounding cells = 2 or 3
   				tempBoard[row*boardColSize + col] = 1;
   			}
   			else{
   				tempBoard[row*boardColSize + col] = 0;	// store 1 if cell should remain alive, 0 if should die
   			}
   		}
   		else{							// else if cell in question is currently DEAD
   			if(status == 3){				// if number of live surrounding cells 3
   				tempBoard[row*boardColSize + col] = 1;	// store 1 if cell will be born again
   		}
   	}
  }
   }
   for(col = 0; col < boardColSize; col++){
   	for(row = 0; row < boardRowSize; row++){			// cycles through entire board again
   	if(board[row*boardColSize + col] - tempBoard[row*boardColSize + col] != 0){
 			d = d + 1;
 		}	// updates board with values configured previously in tempboard
   	}
   }
 	if(d == 0){      //if no changes are made, return 1, otherwise it was changed, return 0
 		return 1;
 	}
 return 0;
 }
