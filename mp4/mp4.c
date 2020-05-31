#include <stdlib.h>
#include <stdio.h>


int is_prime(int number);
int print_semiprimes(int a, int b);


// Main function to get input and check for validity then call semiprimes function
// Input: none
// Output: none

int main(){
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }
   // call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
   print_semiprimes(a,b);

   printf("\n");    //for aesthetic purposes
   return 0;
}

 // Function to check the number is prime or not.
 // Input    : a number
 // Return   : 0 if the number is not prime, else 1

int is_prime(int number){
  int a;
  if(number<=1) //1,0, and negative numbers are not considered prime
  {
    return 0;
  }
  else if(number==2) // git allows the special case of 2 to be checked
  {
    return 1;
  }
  else{
    for(a=2; a<=number; a++) //enables the number being checked to be divded by every number from 2 to n-1
    {
      if(a==number)      //once a equals the actual number, it is now known to be a prime number
          return 1;
      if(number%a == 0)// if there is no remainder the number is not prime
          return 0;
    }
}
return 0;
}


  // Function to print all semiprimes in [a,b] (including a, b).
  // Input   : a, b (a should be smaller than or equal to b)
  // Return  : 0 if there is no semiprime in [a,b], else 1

int print_semiprimes(int a, int b)
{
  int n,k,c,e,f,m;
  for(n=a;n<=b;n++){        //for loop from a to b
    for(k=2;k<=n-1;k++){    //for loop to check for semiprimes from 2 to n-1
      c = is_prime(k);      //check if k is a prime number
      e = n/k;              //divide current n count by current k count
      m = n%k;               //modulus check for remainder of n/k

      e = is_prime(e);      //check if n/k is a prime number

      if(c==1 && e==1 && m==0){     //if k and n/k are prime numbers and
        printf("%d ",n);            //n/k has no remainder then n is a semiprime
        f = 1+f;                    //so print out the number and add one to
        break;                      //variable for if there are semiprimes "f"
      }
    }
}
  if(f>0)               //if semiprimes, return 1, if not, return 0
    return 1;
  else
    return 0;

}
