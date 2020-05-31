/*                       Codebreaker: by djb6, partner: pdh2
*   With this program we set out to take an integer input from a user for a random seed,
* then prompt the user to guess a 4 integer solution. The user has 12 attempts to guess
* the exact order and comination of these numbers. In our first function we check if the user has entered a seed
* correctly by checking if they entered just one integer. If they did, we use that with the randomizer
* in C programming to generate 4 random integers from that dataset in the function start game into four pointers
* and then copy those pointers into four static solution variables. We then start the game with the make guess
* function and have the user input a guess. We check to see if that guess is between 1 and 8 and they entered 4
* integers.If all is well, we go into the logic to check for matches to the solution and misplaced matches.
* We implmeneted that using a lot of if statements checking each variable for equivalence. The number of
* matches and misplaced matches is displayed on the screen and if they are not correct yet, it loops back to
* another guess. If they are correct it tels how many guesses it took, then finishes.
*/






/*
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read.
//    We declare
//    int seed;
//    char post[2];utpu
//    The sscanf statement below reads the integer into seed.
//    sscanf (seed_str, "%d%1s", &seed, post)hout warnings in the future.
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully.
//    Check that the return value is 1 to ensure the user enters only an integer.
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary.
//    You may need to change the return statement below
    int seed;
    char post[2];
    int a = sscanf(seed_str, "%d%1s", &seed,post);       //declare an integer a as sscanf for the seed string
    if(a==1){                                            //if sscanf detects only one integer, set the seed as the randomimzer and return
      srand(seed);
      return 1;
    }else {                                              //if there's more than one integer or characters, print out that it's an invalid seed and loop back to try again
      printf("set_seed: invalid seed\n");
      return 0;
    }

    return 0;      //return 0 just in case of error


}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here
    * one = (rand() % 8)+1;     //declare pointers as random numbers with a maximum of 7 inclusive and add 1 to it
    * two = (rand() % 8)+1;
    * three = (rand() % 8)+1;
    * four = (rand() % 8)+1;
    guess_number = 1;           //set the guess number as the first attempt
    solution1 = * one;          //store the 4 solutions to the game
    solution2 = * two;
    solution3 = * three;
    solution4 = * four;

}

/*utpu
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str.
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, thechmod +x gold-version
chmod +x mp5_functionality guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
    int w,x,y,z;
    char post[2];

    int b = sscanf(guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);     //declare integer b as the sscanf for the 4 values the user inputs

    if(b==4){    //continue if there are 4 integers detected in b
        if(w>=1 && w<=8 && x>=1 && x<=8 && y>=1 && y<=8 && z>=1 && z<=8){       //if all inputs are between 1 and 8, continue
            int pair1=0, pair2=0, pair3=0, pair4=0, mispair1=0, mispair2=0, mispair3=0, mispair4=0, perfect=0, misplaced=0;     // declare/reset variables for keeping track
                                                                                                                                //of perfect matches (pair(n)) and misplaced mathes(mispair(n))
            if(solution1 == w){                  //next 4 if statements check for perfect matches in all of the inputs
              pair1 = 1;
            }
            if(solution2 == x){
              pair2 = 1;
            }
            if(solution3 == y){
              pair3 = 1;
            }
            if(solution4 == z){
              pair4 = 1;
            }

            perfect = pair1 + pair2 + pair3 + pair4;        //sum of perfect matches detected to be printed

            if (pair1 ==1 && pair2==1 && pair3==1 && pair4 ==1){      //if the user guesses the exact anser(all 4 perfect pairs), continue
              printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced);
              printf("You guessed correctly in %d guesses.\n", guess_number);
              return(0);                //exit program after guess is made correctly
            }

            if(solution1 == x && pair2 != 1){                           //if the solution in the first position is equal to second position guess and the second position isn't a perect match, set misplaced
              mispair2 = 1;                                            //match in second position to 1
            }else if(solution1 == y && pair3 != 1){                     //if solution in first position is equal to third position guess and the third position isn't a perfect match, set misplaced match in
              mispair3 = 1;                                            //third position to 1
            }else if(solution1 == z && pair4 != 1){                     //if the solution in the first position is equal to fourth position guess and the fouth position isn't a perfect match, set misplaced
              mispair4 = 1;}                                            //match in fourth position to 1

            if(solution2 == w && pair1 != 1){                          //if the solution in the second position is equal to first position guess and the first position isn't a perect match, set misplaced
              mispair1 = 1;                                             //match in  first position to 1
            }else if(solution2 == y && mispair3!=1 && pair3!= 1){       //if the solution in the second position is equal to third position guess and the third misplaced match isn't made yet and the third position isn't a perect match, set misplaced
              mispair3 = 1;                                             //match in third position to 1
            }else if(solution2 == z && mispair4 !=1 && pair4 != 1){    //if the solution in the second position is equal to fourth position guess and the fourth misplaced match isn't made yet and the fourth position isn't a perect match, set misplaced
              mispair4 = 1;}                                            //match in the fourth position to 1utpu

            if(solution3 == w && mispair1 != 1 && pair1 != 1){         //if the solution in the third position is equal to first position guess and the first misplaced match isn't made yet and the first position isn't a perect match, set misplaced
              mispair1 = 1;                                             //match in first position to 1
            }else if(solution3 == x && mispair2 != 1 && pair2 != 1){     //if the solution in the third position is equal to second position guess and the second misplaced match isn't made yet and the second position isn't a perect match, set misplaced
              mispair2 = 1;                                            //match in second position to 1
            }else if(solution3 == z && mispair4 !=1 && pair4 != 1){     //if the solution in the third position is equal to fourth position guess and the fourth misplaced match isn't made yet and the fourth position isn't a perect match, set misplaced
              mispair4 = 1;}                                            //match in fourth position to 1

            if(solution4 == w && mispair1 != 1 && pair1 != 1){           //if the solution in the fourth position is equal to first position guess and the first misplaced match isn't made yet and the first position isn't a perect match, set misplaced
              mispair1 = 1;                                              //match in first position to 1
            }else if(solution4 == x && mispair2 != 1 && pair2 != 1){     //if the solution in the fourth position is equal to second position guess and the second misplaced match isn't made yet and the second position isn't a perect match, set misplaced
              mispair2 = 1;                                              //match in second position to 1
            }else if(solution4 == y && mispair3 !=1 && pair3 != 1){      //if the solution in the fourth position is equal to third position guess and the third misplaced match isn't made yet and the third position isn't a perect match, set misplaced
              mispair3 = 1;                                              //match in third position to 1
            }



        misplaced = mispair1 + mispair2 + mispair3 + mispair4;         //sum of misplaced matches detected to be printed

        printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced);    //print out number of perfect and misplaced matches

        guess_number = 1+guess_number;            //increment guess number

        return 1;                    //return



        }else{
          printf("make_guess: invalid guess\n");            //if guess is not between 1 and 8 print out that it's an invalid guess and return 0
          return 0;
        }
    }else{                                            //if four integers are not detected. printout that it's an invalid guess and return 0
        printf("make_guess: invalid guess\n");
        return 0;
    }
}
