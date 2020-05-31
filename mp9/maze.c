/*                  MP 9: Maze Solver - by djb6 - parterns: pdh2, tylerjn2
 *    For this mp we had to implement several functions to solve a maze via a DFS recursive algorithm.
 * We had two functions for allocating and freeing memory for the maze, createMaze and destroyMaze. For
 * createMaze we opened a file and got the size of of the maze form the txt file and set all of the points
 * in the array to the characters in the memory. For destroyMaze we first freed the maze array and then the
 * whole maze.We then solved the maze with a depth first search algorith in solveMazeDFS. This function
 * changes the contents of the 2D array (cells) by indicating which cells are along the solution path and
 * which cells were visited during the search. If the maze is unsolvable this function return 0
 * otherwise it should return 1.
 *
 *
 */





#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{


    FILE * fmaze;
    fmaze = fopen (fileName,"r");         //read the file


    maze_t * maze = malloc(sizeof(maze_t));     //allocate memory for maze_t maze
    if(maze == NULL){         //if it doesn't succeed  at reading, then print out malloc error
      printf("malloc error");
    }


    int wmaze;
    int hmaze;
    fscanf(fmaze,"%d %d\n", &wmaze,&hmaze);       //read the width and height from the txt file
    maze->height = hmaze;                 //declare pointers at height and width to the contents of the file
    maze->width = wmaze;


    maze->cells = malloc(sizeof(maze->height) * sizeof(char*));       //allocate memory of the cells for height and it's character
    int z;
    for(z = 0; z<maze->height;z++){                                      //loop to allocate memory for all rows of the maze
     maze->cells[z] = malloc(sizeof(maze->width) * sizeof(char));
    }
    int rows = (maze->height);            //row and column declared to the pointers set to each of those
    int cols = (maze->width);
    char mazechar[rows][cols];            //character array for the maze
    int i,j;
    for(i=0;i<(maze->height);i++){
      for(j=0;j<=(maze->width);j++){
        fscanf(fmaze, "%c", &mazechar[i][j]);//scans characters line by line for every i and j
        if(mazechar[i][j] == 'S'){    //find start of maze
          maze->startRow = i;
          maze->startColumn = j;
          maze->cells[i][j] = 'S';        //assign start of maze
        }
        else if(mazechar[i][j] == '%'){    //find walls
          maze->cells[i][j] = '%';          //assign walls
        }
        else if(mazechar[i][j] == 'E'){    //find end of maze
          maze->endRow = i;
          maze->endColumn = j;
          maze->cells[i][j] = 'E';        //assign end
        }
        else if(mazechar[i][j] == ' '){     //find available path points in maze
            maze->cells[i][j] = ' ';   // seg fault here in test 2 --------------------------------------
        }
        
      }
    }
    fclose (fmaze);           //close the file
    return maze;          //return the maze pointer
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
//int col = maze->width;
//  int row = maze->height;
 //int i, j;
//   for(i=0; i<col; i++){
//  for(j=0; j<row; j++){
//   free(maze->cells[j][i]);
//   }
//   }        //free the array before the entire thing      MUST CLEAR EACH CELL INDIVIDUALLY
//  free(maze->cells);
int z;
for(z = 0; z<maze->height;z++){
  free(maze->cells[z]);
}
  free(maze);             //then free the whole thing
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int row = maze->height;
      int col = maze->width;
      int i, j;
      for(i=0; i<col; i++){
        for(j=0; j<=row; j++){
          char out = maze->cells[i][j]; //i or j first?
          printf("%s",&out);
        }
        printf("\n");
      }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeDFS(maze_t * maze, int col, int row)
  {
    if(col > maze->width || col < 0|| row > maze->height || row < 0){ // 1
    return 0;
  }
    if(maze->cells[row][col]!=' '){
      return 0;
  }

    if(maze->cells[row][col]=='E'){ //3
          maze->cells[row][col]='*';
          return 1;
  }
        maze->cells[row][col]='*'; //4
        if(solveMazeDFS(maze, col, row+1) == 1){ //5
          return 1;
        }

        if(solveMazeDFS(maze, col+1, row) == 1){//6
          return 1;
        }

        if(solveMazeDFS(maze, col, row-1) == 1){//7
          return 1;
        }

        if(solveMazeDFS(maze, col-1, row) == 1){//8
          return 1;
        }
            maze->cells[col][row]='~';//9
            return 0;//10 || maze->cells[row][col+1]=='E' || maze->cells[row][col+1]=='E' || maze->cells[row-1][col]=='E' || maze->cells[row][col-1]=='E' || maze->cells[row-1][col]=='E' || maze->cells[row][col-1]=='E'
        //if one of the four directions is empty, move pointer to that cell and call recursive part,
        //continue until it gets to point that contains no empty cells. Return false and backtrack replacing cells with tildes.
        //entire time it moves should be placing asterisks, unless backtracking. it will continue backtracking until it gets to
        // the cell where it branched and finds the other empty path. Continue searching until it finds the E.Return 1 afterwards.
    return 0;
}
