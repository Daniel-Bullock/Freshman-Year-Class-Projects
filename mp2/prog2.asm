;
;
;
;
;-----------------------------------------------------------------------------------
;                INTRODUCTION PARAGRAPH - By Daniel Bullock 					   ;
;                                                                          		   ;						
;In this MP we designed our LC-3 program to evaluate postfix expressions after     ;
;	echoing a string of characters the user has inputed from the keyboard		   ;
;	using TRAP vectors. It displays the postfix on the monitor as well as the 	   ;
;	the answer in hex. At the beginning of the program, we receive the user's	   ;
;	input and check if it is an equal sign. If it is then it goes to a subroutine  ;
;	for a final pop out of the stack to get the answer and then goes into the 	   ;
;	hex printing subroutine from last MP. If the equal sign didn't have anything   ;
;	preceding it or the postfix is incorrect, it prints out an error message. The  ;
;	subroutine for an error is called whenever underflow occurs. If it does not    ;
;	detect an equal sign, it goes on to detect if its a number. If it does it	   ;
;	it pushes to the stack. If it's not it goes on to detect if it's a space, then ;
;	a plus sign, then minus, and so on. Once it detects what it is it moves on to  ;
;	actually do the operation with popping and pushing to stack.				   ;
;                                                                                  ;
; 							partners: pdh2,eliseon2                                ;
;-----------------------------------------------------------------------------------
;
;
;
;
.ORIG x3000

;your code goes here

;***********************        Register Table     *****************************

;R0 used for inputs and outputs
;R1 Temp Register
;R2 Temp Register
;R3 Used for sending R0 value that holds the POP to the Printing Hex branch
;   Also used for operators and PUSH and POP subroutines
;R4 Used for doing calculations of operators and PUSH and POP subroutines
;R5 Tests for overflow/underflow as well as holding the final answer
;R6 Used mostly as a temporary register
;R7 Used by subroutines and TRAPs to Return


;*****************        Initializing Registers          **********************

AND R0,R0, #0
AND R1,R1, #0
AND R2,R2, #0
AND R3,R3, #0
AND R4,R4, #0
AND R5,R5, #0
AND R6,R6, #0
AND R7,R7, #0


;***********************           START        ********************************



CalculatorMain                    ; This Function will check whether input was '='
                                  ; If not then it gets sent to get evaluated

GETC                              ; Accepts input from keyboard
OUT                               ; Echo to screen
LD R2, AsciiEQ                    ; Loads R2 with '='
NOT R2, R2
ADD R2, R2, #1                    ; Negates R2
ADD R1, R2, R0                    ; Checks input of R0 with '='

BRz FinalPOP                      ; Branches to function that checks if there is
                                  ; only 1 thing left in the stacks (The Final POP)

JSR EVALUATE                      ; If input not '=' it goes to get evaluated to
                                  ; see what the input was
OUT                               ; Prints out what was in R0 before it was pushed to stack

BR    CalculatorMain              ; Returns to top of Loop



;******************      Evaluation if input was '='    ************************

FinalPOP

  JSR POP
  ADD R3, R0, #0                  ; Moves R0 value that was popped into R3 to print in the PRINT HEX Branches
  ADD R5, R5, #0                  ; Checks for underflow

  BRp ERROR                       ; If R5 = 1, then branch to print error
  JSR POP
  ADD R5, R5, #0

  BRz ERROR                       ; If a second pop works without error (no underflow) then you have invalid expression
  JSR PRINT_HEX                   ; Second pop was invalid, meaning the first pop was the final pop in the stack
                                  ; Jump to print out the value in R3, which was transferred from R0 after the final pop
  HALT                            ; Once printing is done, it returns to this part of the function and halts




;********************      ERROR PRINTING MESSAGE         **********************
ERROR

  LEA R0, Error_Message           ; Loads R0 with "Invalid Expression" error MESSAGE
  PUTS                            ; Prints value in R0 to screen
  HALT                            ; If error was encountered, message was printed to screen and program was ended

Error_Message     .STRINGZ " Invalid Expression"
NewLine     .FILL x000A
AsciiEQ      .FILL x3D


;***   Printing the final popped value of the stack after '=' was pressed    ***

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

;**************         SAVING OLD REGISTER VALUES         *********************

;ST R0, PRINT_SaveR0                   ; Save R0
;ST R1, PRINT_SaveR1                   ; Save R1
;ST R2, PRINT_SaveR2                   ; Save R2
;ST R3, PRINT_SaveR3                   ; Save R3
;ST R4, PRINT_SaveR4                   ; Save R4
;ST R5, PRINT_SaveR5                   ; Save R5
;ST R6, PRINT_SaveR6                   ; Save R6
;ST R7, PRINT_SaveR7                   ; Save R7


;*****************        Initializing Registers          **********************

AND R0,R0, #0          ; Digit
AND R1,R1, #0          ; Digit Counter

AND R2,R2, #0          ; Bit Counter
AND R4,R4, #0          ; Clear Temporary Register R4
AND R5,R5, #0          ; Clear Temporary Register R5
AND R6,R6, #0          ; Clear Temporary Register R6
LD  R5, OChar           ; Load '0' into R5
LD  R6, AChar           ; Load 'A' into R6

DigitLoop

      ADD R4,R1, #-4   ; Check if 4 digits have been printed
      BRzp DONE        ; - if not done yet, branch to done when = 0

FourBitLoop

      ADD R4,R2, #-4   ; Check if 4 bits have been pulled from R3
      BRzp DigitReady  ; BR if 4 bits have been pulled from R3
      ADD R0,R0, R0    ; Shift digit left

          MSBCHECKER
                ADD R4,R3, x0        ; Sets branch up to check MSB for R3
                BRzp MSBP            ; Branches to MSB being positive
                ADD R0,R0, #1        ; Adds 1 to digit

                BR ShiftRThree       ; Branches to shifter for R3

          MSBP
                ADD R0,R0, #0        ; Adds 0 to digit

          ShiftRThree
                ADD R3,R3, R3        ; Shifts R3 left

          ADD R2,R2, #1              ; Increments Bit Counter
          BR FourBitLoop

DigitReady

      ADD R4,R0, #-9                 ; Subtracts 9 from digits
      BRp DigitGreater               ; Branches if digit is larger than 9
      ADD R0,R0, R5                  ; Adds '0' to digit
      BR OutTrap                     ; Branches to OutTrap after adding '0'

  DigitGreater

      ADD R0,R0, R6                  ; Adds 'A' to digit
      ADD R0,R0, #-10                ; Adds -10 to digit

  OutTrap

      TRAP x21                       ; Prints digit in screen
      ADD R1,R1, #1                  ; Increments digit counter
      AND R0,R0, #0                  ; Digit Reset
      AND R2,R2, #0                  ; Bit Counter Reset
      BR     DigitLoop               ; Goes back to top of Digitloop
DONE
      AND R5, R5, #0                 ; Makes sure to put answer in R5 before exiting
      ADD R5, R0, #0

;      LD R0, PRINT_SaveR0            ; Reloads old register values except R5
;      LD R1, PRINT_SaveR1
;      LD R2, PRINT_SaveR2
;      LD R3, PRINT_SaveR3
;      LD R4, PRINT_SaveR4
;      LD R6, PRINT_SaveR6
;      LD R7, PRINT_SaveR7

      HALT                            ; Halts program


;Save Locations

PRINT_SaveR0  .BLKW #1
PRINT_SaveR1  .BLKW #1
PRINT_SaveR2  .BLKW #1
PRINT_SaveR3  .BLKW #1
PRINT_SaveR4  .BLKW #1
PRINT_SaveR6  .BLKW #1
PRINT_SaveR7  .BLKW #1

OChar   .FILL x0030                  ; 0
AChar   .FILL x0041                  ; A


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;







;
EVALUATE

;your code goes here
;*************************     Save Registers     ******************************



ST R0, Ev_SaveR0                   ; Save R0
;ST R1, Ev_SaveR1                   ; Save R1
ST R2, Ev_SaveR2                   ; Save R2
;ST R3, Ev_SaveR3                   ; Save R3
;ST R4, Ev_SaveR4                   ; Save R4
ST R5, Ev_SaveR5                   ; Save R5
;ST R6, Ev_SaveR6                   ; Save R6
;ST R7, Ev_SaveR7                   ; Save R7



;Check if the input is between 0 and 9

;*******************     Checking if input was space        ********************
InputSpace

  LD R1, Ascii_Space                     ; Loads R1 with value of 'Space'
  NOT R1, R1                             ; Inverts R1
  ADD R1, R1, #1                         ; Is now -R1

  ADD R2, R1, R0                         ; Checks if input in R0 is space character
  BRz NEXT_INPUT
;****************       Checking if   0< input <9       ************************

InputNumber

  LD R1, Ascii_Zero                      ; Loads R1 with value of '0'
  NOT R1, R1                             ; Inverts R1
  ADD R1, R1, #1                         ; Is now -R1
  ADD R2, R1, R0                         ; Compares Input with '0'
  BRz InputIsZero
  BRn InputPlus                          ; If input was less than '9' go to check if input was plus '+'

  LD R1, Ascii_Nine                      ; Loads R1 with value of '9'
  NOT R1, R1                             ; Inverts R1
  ADD R1, R1, #1                         ; Is now -R1
  ADD R2, R1, R0                         ; Compares Input with '9'
  BRp InputExp                           ; if input greater than 9 go to check if input was exponent '^'

;If input was a number then it gets converted from ascii to decimal and gets pushed to stack
  LD R2, Ascii_To_Dec_Diff
  NOT R2, R2
  ADD R2, R2, #1
  ADD R0, R0, R2
PushZero
  JSR PUSH
  BR NEXT_INPUT

InputIsZero
	AND R0, R0, #0
BR PushZero
  Ascii_To_Dec_Diff .FILL x0030

;***************          Checking if input was Operator          **************

InputPlus

  LD R1, Ascii_Plus                      ; Loads R1 with value of '+'
  NOT R1, R1                             ; Inverts R1
  ADD R1, R1, #1                         ; Is now -R1
  ADD R2, R1, R0                         ; Compares Input with '+'
  BRnp   InputMinus                      ; Branch to next operator check if comparison does not = 0

  JSR POP
  ADD R3, R0, #0                         ; Stores value which was popped and stored in R0 into R3
  ADD R5, R5, #0                         ; Checks R5 to see if = to 1. This means error occurred (underflow)
  BRp ERROR
  JSR POP
  ADD R4, R0, #0                         ; Stores value which was popped and stored in R0 into R4
  ADD R5, R5, #0                         ; Checks R5 to see if = to 1. This means error occurred (underflow)
  BRp ERROR
  JSR PLUS                               ; Jump to operator +
  JSR PUSH                               ; Push result to stack
  BR NEXT_INPUT                          ; Get next input from keyboard

InputMinus

  LD R1, Ascii_Minus                     ; Loads R1 with value of '-'
  NOT R1, R1                             ; Inverts R1
  ADD R1, R1, #1                         ; Is now -R1
  ADD R2, R1, R0                         ; Compares Input with '-'
  BRnp   InputMult                       ; Branch to next operator check if comparison does not = 0

  JSR POP
  ADD R3, R0, #0                         ; Stores value which was popped and stored in R0 into R3
  ADD R5, R5, #0                         ; Checks R5 to see if = to 1. This means error occurred (underflow)
  BRp ERROR
  JSR POP
  ADD R4, R0, #0                         ; Stores value which was popped and stored in R0 into R4
  ADD R5, R5, #0                         ; Checks R5 to see if = to 1. This means error occurred (underflow)
  BRp ERROR
  JSR MIN                                ; Jump to operator -
  JSR PUSH                               ; Push result to stack
  BR NEXT_INPUT                          ; Get next input from keyboard

InputMult

  LD R1, Ascii_Mult                      ; Loads R1 with value of '*'
  NOT R1, R1                             ; Inverts R1
  ADD R1, R1, #1                         ; Is now -R1
  ADD R2, R1, R0                         ; Compares Input with '*'
  BRnp   InputDiv                        ; Branch to next operator check if comparison does not = 0

  JSR POP
  ADD R3, R0, #0                         ; Stores value which was popped and stored in R0 into R3
  ADD R5, R5, #0                         ; Checks R5 to see if = to 1. This means error occurred (underflow)
  BRp ERROR
  JSR POP
  ADD R4, R0, #0                         ; Stores value which was popped and stored in R0 into R4
  ADD R5, R5, #0                         ; Checks R5 to see if = to 1. This means error occurred (underflow)
  BRp ERROR
  JSR MUL                                ; Jump to operator *
  JSR PUSH                               ; Push result to stack
  BR NEXT_INPUT                          ; Get next input from keyboard

InputDiv

  LD R1, Ascii_Div                       ; Loads R1 with value of '/'
  NOT R1, R1                             ; Inverts R1
  ADD R1, R1, #1                         ; Is now -R1
  ADD R2, R1, R0                         ; Compares Input with '/'
  BRnp   InputExp                        ; Branch to next operator check if comparison does not = 0

  JSR POP
  ADD R3, R0, #0                         ; Stores value which was popped and stored in R0 into R3
  ADD R5, R5, #0                         ; Checks R5 to see if = to 1. This means error occurred (underflow)
  BRp ERROR
  JSR POP
  ADD R4, R0, #0                         ; Stores value which was popped and stored in R0 into R4
  ADD R5, R5, #0                         ; Checks R5 to see if = to 1. This means error occurred (underflow)
  BRp ERROR
  JSR DIV                                ; Jump to operator /
  JSR PUSH                               ; Push result to stack
  BR NEXT_INPUT                          ; Get next input from keyboard

InputExp

  LD R1, Ascii_Exp                       ; Loads R1 with value of '^'
  NOT R1, R1                             ; Inverts R1
  ADD R1, R1, #1                         ; Is now -R1
  ADD R2, R1, R0                         ; Compares Input with '^'
  BRnp   ERROR                           ; Branch to next operator check if comparison does not = 0

  JSR POP
  ADD R3, R0, #0                         ; Stores value which was popped and stored in R0 into R3
  ADD R5, R5, #0                         ; Checks R5 to see if = to 1. This means error occurred (underflow)
  BRp ERROR
  JSR POP
  ADD R4, R0, #0                         ; Stores value which was popped and stored in R0 into R4
  ADD R5, R5, #0                         ; Checks R5 to see if = to 1. This means error occurred (underflow)
  BRp ERROR
  JSR EXP                                ; Jump to operator ^
  JSR PUSH                               ; Push result to stack
  BR NEXT_INPUT                          ; Get next input from keyboard


NEXT_INPUT

  LD R0, Ev_SaveR0                       ; Reload registers
  LD R2, Ev_SaveR2
  LD R5, Ev_SaveR5

  BR CalculatorMain

Ev_SaveR0  .BLKW #1
Ev_SaveR1  .BLKW #1
Ev_SaveR2  .BLKW #1
Ev_SaveR3  .BLKW #1
Ev_SaveR4  .BLKW #1
Ev_SaveR5  .BLKW #1
Ev_SaveR6  .BLKW #1
Ev_SaveR7  .BLKW #1

Ascii_Space       .FILL     x0020
Ascii_Zero        .FILL     x0030
Ascii_Nine        .FILL     x0039
Ascii_Plus        .FILL     x002B
Ascii_Minus       .FILL     x002D
Ascii_Mult        .FILL     x002A
Ascii_Div         .FILL     x002F
Ascii_Exp         .FILL     x005E



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS


;your code goes here
ST R3, Plus_SaveR3                   ; Save R3
ST R4, Plus_SaveR4                   ; Save R4

ADD R0, R4, R3                       ; Add items popped from stack and store in R0

LD R3, Plus_SaveR3                   ; Reload R3
LD R4, Plus_SaveR4                   ; Reload R4

RET

Plus_SaveR3       .BLKW #1
Plus_SaveR4       .BLKW #1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN
;your code goes here

ST R3, Minus_SaveR3                   ; Save R3
ST R4, Minus_SaveR4                   ; Save R4

NOT R3, R3                            ;
ADD R3, R3, #1                        ; -R3

ADD R0, R4, R3                        ; Subtract and store into R0

LD R3, Minus_SaveR3                   ; Reload R3
LD R4, Minus_SaveR4                   ; Reload R4

RET

Minus_SaveR3       .BLKW #1
Minus_SaveR4       .BLKW #1


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL
;your code goes here

ST R3, Mult_SaveR3                   ; Save R3
ST R4, Mult_SaveR4                   ; Save R4
ST R6, Mult_SaveR6
    ADD R6,R3,#0
    ADD R4, R4, #0                      ; Check if Multiplying by zero
BRz MulByZero                            ; This means R4 was zero so branch to MulByZero

MultiplyLoop

    ADD R4, R4, #-1
    BRz  MulComplete
    ADD R3, R6, R3                     ; Add R3 to itself
    BR MultiplyLoop                    ; Go back to top of loop

MulComplete

    ADD R0, R3, #0                       ; Store R3 into R0 and return then push to stack

ZeroComplete
    LD R6, Mult_SaveR6
    LD R3, Mult_SaveR3                   ; Reload R3
    LD R4, Mult_SaveR4                   ; Reload R4

RET



MulByZero

    AND R0, R0, #0                       ; Multiplied by zero at start so set R0 to zero then RET and push to stack

BR ZeroComplete

Mult_SaveR3       .BLKW #1
Mult_SaveR4       .BLKW #1
Mult_SaveR6       .BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV
;your code goes here

ST R3, Div_SaveR3   ; Save R3
ST R4, Div_SaveR4   ; Save R4

AND R0, R0, #0      ; Initialize R0 and R1 to 0
AND R1, R1, #0

; R4 is intial value
; R3 is the divisor. Negate the value in R3
; R1 holds value after subtraction

ADD R3, R3, #0			; If R3 is 0 print error
BRz ERROR

NOT R3, R3
ADD R3, R3, #1      ; -R3

SubtractAgain

ADD R1, R4, R3      ; R4 minus R3

BRn DivComplete

ADD R0, R0, #1      ; Quotient gets incremented
ADD R4, R1, #0      ; R1 value gets put into R4

BRnzp SubtractAgain     ; Jumps back to next iteration

DivComplete

LD R3, Div_SaveR3
LD R4, Div_SaveR4
RET

Div_SaveR3  .BLKW #1    ;
Div_SaveR4  .BLKW #1    ;







;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here

ST R3, Exp_SaveR3  ; Save Registers
ST R4, Exp_SaveR4  ;
ST R6, Exp_SaveR6  ;
ST R7, Exp_SaveR7  ;

; Note* The way that numbers were popped out of the stack means that the value in R4 is raised to the power in R3 (R4^R3)

  AND R6, R6, #0      ; Clear R6
  ADD R6, R6, R3      ; Makes R6 a counter, initialized to exponent value in R3

BRnp GreaterThanZero           ; If R3 is greater than 0 then continue to main loop, otherwise it means that the (R4^0)=1 so set R0 and RET if R3, the exponent value, is 0

    AND R0,R0,#0
    ADD R0,R0,#1

    RET

GreaterThanZero

  ADD R3, R4, #0            ; Also set R3 to R4 because it will go through the multiplication operator and loop through that as many times as the counter (R6) requires

ExponentialLoop

      ADD R6,R6, #-1        ; Decrement Down Counter (R6), which was the value of the exponentials

      BRnz ExpComplete

      JSR MUL            ; Performs multiplications of R4*R3
      ADD R4,R0,#0       ; Store result of MULT into R4

      BRnzp ExponentialLoop        ; Loop back to top until R6 is zero

ExpComplete



LD R3, Exp_SaveR3  ; Reload Registers
LD R4, Exp_SaveR4  ;
LD R6, Exp_SaveR6  ;
LD R7, Exp_SaveR7  ;

Exp_SaveR3 .BLKW #1    ;
Exp_SaveR4 .BLKW #1    ;
Exp_SaveR6 .BLKW #1    ;
Exp_SaveR7 .BLKW #1    ;

  RET

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
