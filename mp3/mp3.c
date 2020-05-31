/////////////////////////////////////////////////////////////////////////////////
//*                Pascal's Triangle  Program: by djb6                        *//
//*                                                                           *//
//* Pascal’s triangle is an array that consists of binomial coefficients.     *//
//* This program prompts the user for a row from Pascals triangle, and then   *//
//* outputs the coefficients. I used two for loops to make this program work. *//
//* The first one incremented which coefficient was being calculated as well  *//
//* as the upper limit for the pi product. The inner loop served as the pi    *//
//* product facotrial formula, which multiplied a sum by itself to produce    *//
//* the coefficient.                                                          *//
//*                                                                           *//
/////////////////////////////////////////////////////////////////////////////////



#include <stdio.h>
#include <stdlib.h>


int main()
{

  // Write your code here

 int row;                              //* declare row input as interger *//
 unsigned long sum=1;                  //* declare coeffiecients with unsigned long *//
 
 printf("Enter a row index: ");        //* prompt user for row index *//
 scanf("%d",&row);                     //* scan for row index *//

 for (int k=0;k<=row;k++){             //* loop for incrementing through the coeffiecients *//
      
     sum = 1;                          //* reset the coeffiecient *//
     int i = 1;                        //* declare/reset i as integer *//
     float d = 1;                      //declare/reset d for denominator as a float to prevent error *//

     for(i=1,d=1;i<=k;i++,d++){        //* loop for factoring the pi-product formula *//
         sum= (sum*((row+1-i)/d)) ;    //* factoring formula *//
     } 
     printf("%lu ",sum);               //* print a coefficient *//
  }
 printf("\n");                         //* print newline *//

return 0;                              //* null return function *//

}
