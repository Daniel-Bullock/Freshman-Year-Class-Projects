
/*
            Username: djb6   ;  Partners: pdh2, tylerjn2
For this code we started off by writing the load tuples function. In this function we take the input_file
,read the file, allocate the memory within it, store the dimensions of the matrix from the file.
 we also find the parameters to call the function set tuples. The next function, gv_tuples returns the variable values
based on whether the counter is null or not, and if the row and coloumn match. Since we are dealing with linked lists
and not arrays, we increment the pointer.For the funciton set tuples set the elements at the row and coloumn to the value
this checks first to see if the pointer is valid (not NULL) and then set a pointer bewteen to redefine the tuple.
for tuple nodes ahead, we look ahead by advancing the pointer to look ahead at the next


given the layout of our code we actually have no use for the function delete node. The function save tuples goes
and writes it back to the file of which we first drew from. This is then closed at the end of the iterations until
NULL has been reached within the linked list. Add Tuples and Multipy Tuples do the relatively same basic thing structurally.
Add tuples takes the data from the different mats and then adds it together into a matc. again since we are not utilzing
matrices this was done through pointer itterations because of the linked list. similarly, the multiply function takes the
elements within each of the linked lists and multiply them and stores it back through the use of pointer logic.
finally our last line of logic was the destory tuples funciton which goes and breaks up the memory locations in the dynmaic
memory.
*/



#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

sp_tuples * load_tuples(char* input_file)
{

      FILE * file;
       file = fopen (input_file,"r");         //read the file
       sp_tuples * mat_t = malloc(sizeof(sp_tuples));
       //sp_tuples_node  * temporary = malloc(sizeof(sp_tuples_node));
       fscanf(file,"%d %d\n", &(mat_t->m),&(mat_t->n));          //scan for dimensions of the matrix
       //temporary = mat_t->tuples_head;
       int row, col;
       double value;
       while(fscanf(file,"%d %d %lf\n",&(row),&(col),&(value))!=EOF){

             set_tuples(mat_t,row,col,value);        //call set typles to add to linked list

       }
       fclose(file);       //close file
       return mat_t;        //return pointer to matrix

}



double gv_tuples(sp_tuples * mat_t,int row,int col)
{
  double value; //initialize int to store value at row col
  sp_tuples_node *temporary = mat_t->tuples_head; //initialize counter

  while((temporary != NULL)){ //if the counter is null, stop the iteration
      if(temporary->row == row && temporary->col == col){ //if the row and column match
        value = temporary->value;//assign the value to the varibale
      }
      temporary = temporary->next;//increment the pointer
  }

  return value;//return the variable value

}

void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{

    if(value == 0){ //if the value being inserter is not zero, increment nonzero count
          return;
    }
    sp_tuples_node * current = mat_t->tuples_head; //initialize pointer

    if(current == NULL){ //if the pointer gets to NULL, means node location does not exist
          sp_tuples_node *temporary = malloc(sizeof(sp_tuples_node));
          temporary->row = row; // set row, col and value values for new node
          temporary->col = col;
          temporary->value = value;
          mat_t->nz += 1;
          temporary->next = NULL;     //set new node's next value to be NULL
          mat_t->tuples_head = temporary;   //set the head of mat_t to be temporary
          return;
    }

    sp_tuples_node * ahead = mat_t->tuples_head;//create a second pointer one step ahead of first
    ahead=ahead->next;
    while(current!=NULL){ //iterate through tuples
          if(ahead!=NULL){
                if(ahead->row > row || (ahead->col > col && ahead->row == row)){ //once ahead pointer finds values greater thna input row and col
                  sp_tuples_node *temporary = malloc(sizeof(sp_tuples_node));
                  temporary->row = row; // insert a node between the two pointers,
                  temporary->col = col;
                  temporary->value = value;
                  current->next=temporary;//set fist pointer's next to point to new node
                  temporary->next=ahead;//set new node's next to point to second pointer
                  mat_t->nz += 1;//increase nonzero count
                  return;
                }
                ahead = ahead->next; //increment the pointers
          }

          if(current->row == row && current->col == col){ //if the row and column match
                current->value = value; //if value is not 0, and you are not replazing a 0, just assign value
                return; //return
          }

          if(current->next==NULL){
                sp_tuples_node *temporary = malloc(sizeof(sp_tuples_node));
                temporary->row = row; //set row, col, next, and value values for node temporary
                temporary->col = col;
                temporary->value = value;
                temporary->next=NULL;
                current->next=temporary;//set first pointers next pointer to be new node
                mat_t->nz+=1;
                return;
          }
          current = current->next;
    }
    return;
}


void save_tuples(char * file_name, sp_tuples * mat_t)
{

  FILE *file;
  file = fopen(file_name, "w");   //open file for writing

  sp_tuples_node * temp = mat_t->tuples_head;   //set temporary pointer to mat_t head

  fprintf(file,"%d %d\n",mat_t->m,mat_t->n);    //establish the rows and columns from mat_t to the file
  while(temp != NULL){      //if the has cells with values, establish the row, col, and value to the file
      fprintf(file,"%d %d %lf\n",temp->row,temp->col,temp->value);
      temp = temp->next;
  }
  fclose(file);     //close the file and return
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

      matA = malloc(sizeof(sp_tuples));
      matA = malloc(sizeof(sp_tuples));
      sp_tuples * matC = malloc(sizeof(sp_tuples));   //allocate memory for matrices C
      matC->nz= 0;      //assign nz, m, and n values to matC
      matC->m = matA->m;
      matC->n = matA->n;
      sp_tuples_node * currentC = malloc(sizeof(sp_tuples_node));   //allocate memory for nodes in C
      currentC = matC->tuples_head; //initialize pointer

      sp_tuples_node * currentA = malloc(sizeof(sp_tuples_node));   //allocate memory for nodes in A
      currentA = matA->tuples_head; //initialize pointer

      sp_tuples_node * currentB= malloc(sizeof(sp_tuples_node));      //allocate memory for nodes in B
      currentB = matB->tuples_head; //initialize pointer


      if(matA->m != matB->m || matA->n != matB->n ){   //if the rows and cols dont match, return null
        return NULL;
      }


      while(currentA!=NULL){    //while node for matrices A points to null
          if(currentA->row == currentC->row && currentA->col == currentC->col){   //if col and row of A and C matches. add A and C
                currentC->value = currentC->value + currentA->value;
          }

          currentA = currentA->next;    //set Matrices A and C to next point to next cell
          currentC = currentC->next;
      }
      while(currentB!=NULL){
          if(currentB->row == currentC->row && currentB->col == currentC->col){ //if col and row of B and C match, add values of Matrices B and C
                currentC->value = currentC->value + currentB->value;
          }

          currentA = currentB->next;  //increment nodes of matrices B and C
          currentC = currentC->next;
      }


    	return matC;     //return sum matC
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){


          sp_tuples * matC = malloc(sizeof(sp_tuples));   //initialize matC pointer
          matC->nz= 0;
          matC->m = matA->m;
          matC->n = matB->n;
          sp_tuples_node * currentC = malloc(sizeof(sp_tuples_node));  //allocate memory for node pointers of A,B,C
          currentC = matC->tuples_head; //initialize pointer

          sp_tuples_node * currentA = malloc(sizeof(sp_tuples_node));
          currentA = matA->tuples_head; //initialize pointer

          sp_tuples_node * currentB= malloc(sizeof(sp_tuples_node));
          currentB = matB->tuples_head; //initialize pointer

          while(currentA!=NULL){    //while pointer of nodes for Matrices A points to NULL
                int jA = currentA->col;   //integer jA holds current column value of node for A
                while(currentB!=NULL){   //while node pointer for matrices B does not point to null
                    if(currentB->row == jA){  //if jA equals the row value of node pointer in matrices B
                          if(currentC!=NULL){
                                currentC->value = currentC->value + (currentA->value*currentB->value);
                          }  //value of cell in matrices C = value of C, plus A and B multiplied
                          currentB = currentB->next;
                          currentC = currentC->next;
                    }else{
                      break; //break of out of iteration if B's row doesn't equal column of A
                    }
                }
                currentA = currentA->next;    //set node pointer of A to the next value
          }

          return matC;;//return matices C
}



void destroy_tuples(sp_tuples * mat_t){
    sp_tuples_node * temporary = mat_t->tuples_head;    //initialize pinter temporary


    while (temporary != NULL){    //while loop to iterate through all
      temporary = mat_t->tuples_head; //assigned pointer to tuples_head
      mat_t->tuples_head = temporary->next;//set tuples_head to next element
      free(temporary);  //free memory for temporary
    }
    free(mat_t); //free mat_t
    return;
}
