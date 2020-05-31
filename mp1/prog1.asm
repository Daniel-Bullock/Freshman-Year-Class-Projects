;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop

;-----------------------------------------------------------------------------------
;                INTRODUCTION PARAGRAPH - By Daniel Bullock                        ;
;In this lab we designed a part of code to print out the value of occurrences of a ;
;  specific symbol from any string. The count was determined through the COUNTLOOP ;
;  which was stored in addresses x3F00 through x3F1A. In Our part of the code, we  ;
;  first inserted a comparer to determine whether or not to coninue printing a     ;
;  symbol. The range of symbols it printed was from '@' to 'Z'. We accomplished    ;
;  this by comparing it with the '[' symbol, the one right after 'Z', and if the   ;
;  difference between the current symbol being analyzed and the '[' equals 0, the  ;
;  program terminated. After that, the total value of occurences is then pushed    ;
;  through the code we developed in lab which in essence tallys and readys the bits;
;  for being printed as a digit. After the code has run through, it Branches to    ;
;  the end of our code to increment the value of the symbol being analyzed to      ;
;  evalute how many times that new symbol was counted in addition to adding a space;
;  the project then terminated once every character count has been analyzed        ;
;                                                                                  ;
; 							partners: pdh2,eliseon2                                ;
;-----------------------------------------------------------------------------------

PRINT_HIST

	LD R6,CHARSTART	    ;load in R6 with character @
	LD R4,HIST_ADDR     ;Start of count, stores number of @ found first

CHARPRINT
	AND R3,R3,#0		;Clear R3 to use as the register that contains bits to form digit 
	LDR R3,R4,#0		;Load the counted total of the symbol being analyzed
	AND R1,R1,#0		;Clear R1 For comparing use
	LD  R1, NCHAREND	;Load "[", the ascii right after Z 
	ADD R1, R1, R6		;Subtract "[" from the current ascii to see if it will terminate
	BRz DONE			;Program Terminates
	AND R0,R0, #0       ;Clear R0 	
	ADD R0,R6,#0		;Add current character to R0 to print
	OUT					;Print current character
	AND R0, R0, #0      ;Clear R0
	LD R0, SPACE        ;Load in R0 with space charater
	OUT			        ;Print space character
	ADD R6, R6, #1		;Increment character on left of histogram by 1
	
PRINTALL
	;Table of registers used in the Digit printing Portion of the code
	;R0 is the Digit Unit
	;R1 is the Digit Counter
	;R2 is the Bit Counter
	;R3 contains number of occurences of the current symbol being analyzed
	;R5 used to check if Digit is less than or equal to 9 then
	;   manipulates it based on its condition 

	AND R1,R1,#0 		;Initialize Digit Counter
	ADD R1,R1,#5 		;Add the Digit Count Down
	AND R5,R5,#0 		;Initialize Digit Compare unit
	
	
SUBDC	
	ADD R1,R1,#-1		;Decrement Digit Counter By 1

DGTCHK	
	BRz NEWLINEPRINT	;DONE
	AND R5,R5,#0		;0 out Digit Compare Unit
	AND R2,R2,#0 		;Initialize Bit Counter
	ADD R2,R2,#4 		;Set countdown to four
	AND R0,R0,#0 		;Initialize Digit unit
	
RTWO	
	ADD R2,R2,#0 		;R2 Placehold for BR purposes

CHECKB
  	BRz BFALSE   		;Branch if =4 bits from R3
	ADD R0,R0,R0 		;Left Shift Digit
	ADD R3,R3,#0 		;Refernece
	BRn	DTRUE    		;BR if negative
	ADD R0,R0,#0 		;Add 0 to digit
	BR	SHIFTR   		;BR to shift R3 Left
	
DTRUE	
	ADD R0,R0,#1 		;Add 1 to digit

SHIFTR
	ADD R3,R3,R3 		;Shift R3 Left
	ADD R2,R2,#-1		;Decrement Bit Counter
	BR RTWO

BFALSE  
	ADD R5,R5,R0 		;Place value of R0 into R4
	ADD R5,R5,#-9		;Check if < or = to 9
	BRnz NEGZ    		;If negative or zero branch
	AND R5,R5,#0		;0 out R5
	LD R5,AChar			;Load 'A' Character to R5
	ADD R0,R0,R5    	;Add 'A' R0
	ADD R0,R0,#-10		;Subtract 10 from R0
	BR OUTRAP			;BR to output

NEGZ	
	AND R5,R5,#0		;0 out R5
	LD R5,OChar			;Load OChar to R5
	ADD R0,R0,R5		;Add '0' to R0

OUTRAP  
	TRAP x21			;Output to monitor
	BR SUBDC     		;Decrement Digit Counter
						

NEWLINEPRINT
	ADD R4, R4, #1		;Increment address space of counted symbol values		
	LD R0, NEWLINE		;Load x000A into R0 for printing
	TRAP x21			;print newline character
	BR CHARPRINT		;BR back to new character to print

DONE	HALT			; done

; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00 ; histogram starting address
STR_START	.FILL x4000	; string starting address
OChar   	.FILL x0030 ; 0
AChar   	.FILL x0041 ; A
CHARSTART	.FILL x0040	; @ symbol ascii, beginning of ascii to print out to left of histogram
NCHAREND   	.FILL xFFA5 ; [ symbol ascii for end of printing, negated and incremented by 1 easy subjraction
						;  original value in Hex was x005B
NEWLINE		.FILL x000A ; newline character
SPACE		.FILL x0020 ; space character

; for testing, you can use the lines below to include the string in this
; program...
;STR_START	.FILL STRING	; string starting address
;STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."

	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
