#include "sudoku.h"



/*      MP 7: Sudoku Solver by djb6, partners: pdh2 and chall28
 *  For this mp we created a program that could solve a soduku from 2D array.
 * We used three functions to check the array for all the variations a value
 * could exist in it. To check in the row we iterated through the row and checked
 * each value with the value and retured 1 if it was there. To check in the column
 * we iterated through the column and checked each value with the value and retured
 * 1 if it was there. To check in the 3x3 grid, we made a variable for the start of
 * the 3x3 grid by subtracting the modulus of the row and column from itself and
 * iterated though past that. We implemented a function that check for the validity
 * of a value which basically checked that the value wasn't already in the array
 * position and none of the value checkers were true. We then made the solve_sudoku
 * function which uses backtracking to solve the sudoku. It starts by checking if
 * all the cells are assigned by numbers, and if not finds an empty index. We then
 * check with every possible value in there, 1-9, with the validity checker function
 * It would then calls itself to check if all cells are assigned. If not it assigns
 * the index with 0 to go back through. Return 0 is placed at the end to initiate
 * backtracking.
*/







//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO

  for(int y = 0; y < 9; y++){       //iterate through the row
    if(sudoku[i][y] == val){        //if at that row index the value is there return 1
      return 1;
    }
  }
  return 0;           //else return 0

  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j < 9);

  // BEG TODO

  for(int x = 0; x < 9; x++){         //iterate though column
    if(sudoku[x][j] == val){        //if at that column index the value is there return 1
      return 1;
    }
  }
  return 0;             //else return 0

  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO

  int xstart = i-(i%3);                 //these logic statements set the column and row starts
  int ystart = j-(j%3);                //the modulus of the row/column is subtactd from itself to get the start of the 3x3 zone

  for (int x = 0; x < 3; x++){                  //these iterate though the row and column
        for (int y = 0; y < 3; y++){
            if (sudoku[x+xstart][y+ystart] == val){         //checks for the value of the start plus current iteration of the row and column
                return 1;                                   //if there, return 1, else 0
            }
        }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO

  if(is_val_in_col(val,j,sudoku) == 1|| is_val_in_row(val,i,sudoku) == 1 || (is_val_in_3x3_zone(val,i,j,sudoku) == 1 && sudoku[i][j] != val)){
    return 0;                           //this checks fo if the value is in the row, column, 3x3 zone, and itself; if it is the value is invalid
  }else{return 1;}                      //return 1 if the value being checked is valid

  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.

  int i, j, unfilled = 0;
  for(i = 0; i < 9;i++){          //iterate though the columns and rows
    for(j = 0; j < 9;j++){
      if(sudoku[i][j] == 0){        //check if there's anything in the cell
          unfilled = 1;
          break;      //break out if it's unfilled
      }
    }
    if (unfilled == 1){
        break;      //break out if it's unfilled
    }
  }


    if(sudoku[i][j] != 0){    //if the out cell is not unfilled, all of them are filled
        return true;               //return 1 as all are filled
    }

  for(int num = 1; num <= 9; num++) {             //iterate through all 9 possible values
    if (is_val_valid(num, i, j, sudoku) == 1) {   //check validity of value
      sudoku[i][j] = num;           //if it's valid set the index to it
      if (solve_sudoku(sudoku)) {   //backtrack through to see if it filled up right
        return true;                     //it's all filled in so end it
      }
      //sudoku[i][j] <- non-filled (0)
      sudoku[i][j] = 0;             //set it back to 0 to go back through loop
    }
  }

  return false;                   //initiate backtracking

  // END TODO.


}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
