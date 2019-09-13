; Program Description
; This program processes keypress inputs, adding them to the stack if they are numbers or performing 
; operations on them if they are +, -, *, /, or ^. We check for stack underflow after popping twice before each operation 
; to ensure that we are operating on the digit inputs. If an operator is seen, then the program calls the corresponding 
; subroutine to perform the operation of the numbers in the stack. Then we push the result into the stack. This is repeated until
; the user inputs "=" where we then check if there's only one value in the stack and print that value along with
; storing the final result into R5. If anytime during the program the user inputs a character that isn't a digit
; or operator then we print "INVALID EXPRESSION" and halt the program. This is also done if underflow occurs.

;partners: jaradjp2, bozhaoj2, kamatar2

;is this working? YES FINALLY
.ORIG x3000
    
;your code goes here
NEXT_CHAR	
	GETC
	JSR EVALUATE
	BRnzp NEXT_CHAR  

INVALID_EXP                 ;subroutine for invalid inputs
	LEA R0, INVALID_STRING	
	PUTS					;prints string
	HALT
INVALID_STRING .STRINGZ " INVALID EXPRESSION"



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal (use MP1)
PRINT_HEX 
; let R0 be temp storage
; let R1 be char counter
; let R2 be bit counter for hex group
; let R3 be hex we want to print
; let R4 be storage for printing hex of interest
			AND R0, R0, #0
			AND R3, R3, #0
            AND R5, R5, #0
			JSR POP
            ADD R3, R0, #0
            ADD R5, R3, #0  ;put R3 into R5
			AND R1, R1, #0 	;Char counter
			ADD R1, R1, #4	

char_loop	BRz done		;if 4 chars printed, then finish
			AND R4, R4, #0
			AND R2, R2, #0
			ADD R2, R2, #4	;int bit counter
hex_loop	
			ADD R4, R4, R4 	;Left shift R4	
			ADD R3, R3, #0 	;update nzp with R3
			BRzp shift_r3	;if most sig bit of R3 is 0, don't add 1 to R4
			ADD R4, R4, #1 
shift_r3	ADD R3, R3, R3 	;Left shift R3
			ADD R2, R2, #-1
			BRp hex_loop

			ADD R0, R4, #-10 ;check if hex is a decimal or character
			BRp print_char
print_num	LD R0, hex_num	;prints decimal
			ADD R0, R4, R0
			OUT
			BRnzp print_done
print_char	LD R0, hex_char	;prints hex character
			ADD R4, R4, #-10
			ADD R0, R4, R0
			OUT
print_done	ADD R1, R1, #-1	;decriment R1 and loop back
			BRnzp char_loop		
hex_num		.FILL x0030
hex_char	.FILL x0041
done        HALT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R5 - current numerical output
EVALUATE
	ST R0,SAVE_R0
	ST R7,SAVE_R7
	OUT					;echo to screen

;Check if character is =
	LD R6, EQUALS_CHAR	;Loads EQUALS to temp register
	NOT R6,R6	
	ADD R6,R6,#1		;Negates EQUALS
	ADD R6,R0,R6		;Checks if input is '=' by performing R0-'='
	BRnp SPACE_CHECK	;Branch to check space if the input != '='
EQUALS_CHAR .FILL x003D

;input is '=', Check if stack only has one value
	LD R6,STACK_TOP		;Loads STACK_TOP to R6
	ADD R6,R6,#1		;Adds one to Stack top
	LD R5,STACK_START	;Load STACK_START to R5
	NOT R5,R5
	ADD R5,R5,#1		;negate R5 (storing STACK_START)
	ADD R6,R6,R5		;perform (STACK_TOP+1)-STACK_START
	BRz PRINT_HEX		;if there is only one value in stack branch to Print hex
    JSR INVALID_EXP		;stack has more than one value, invalid



;Check if char is space
SPACE_CHECK
	LD R6, SPACE_CHAR	;Load SPACE to temp register 
	NOT R6,R6	
	ADD R6,R6,#1		;Negates SPACE
	ADD R6,R0,R6		;Checks if input is space char
    BRnp DIGITS
    LD R7, SAVE_R7      ;Succeded check so we return without pushing/popping
	RET
SPACE_CHAR .FILL x0020

;Check if is digit
DIGITS
	LD R4,NINE_CHAR	;
	LD R3,ZERO_CHAR	;
	NOT R4,R4
	ADD R4,R4,#1	;negates NINE_CHAR
	NOT R3,R3
	ADD R3,R3,#1	;negates ZERO_CHAR
	ADD R4,R4,R0
	BRp OPERATORS	;check if input is between '0' and '9'
	ADD R3,R3,R0
	BRn OPERATORS	;if input is not a digit then it must be something else

	LD R3, ZERO_CHAR;turns R0 into its decimal value
	NOT R3, R3
	ADD R3, R3, #1
	ADD R0, R0, R3

	JSR PUSH        ;Input was a number so we push then return for a new GETC
    LD R7, SAVE_R7
	RET
NINE_CHAR .FILL x0039
ZERO_CHAR .FILL	x0030

;checking operator
OPERATORS
;Pops two numbers to be operated on
;Prints invalid expression if underflow
	JSR POP
	ADD R5,R5,#0
	BRp INVALID_EXP
	ADD R4,R0,#0
	JSR POP
	ADD R5,R5,#0
	BRp INVALID_EXP
	ADD R3,R0,#0
	LD R0, SAVE_R0  ;restore original GETC char into R0

	LD R6,PLUS_CHAR	;Checks plus operator
	NOT R6,R6
	ADD R6,R6,#1
    ADD R6,R0,R6
	BRnp NEG_OPERATOR   ;check if R0 is the MINUS symbol next
	JSR PLUS
	JSR PUSH
	LD R7,SAVE_R7
	RET
PLUS_CHAR .FILL x002B

NEG_OPERATOR
	LD R6,MINUS_CHAR
	NOT R6,R6
	ADD R6,R6,#1
    ADD R6, R0, R6
	BRnp DIV_OPERATOR   ;check if R0 is the DIVITION symbol next
	JSR MIN
    JSR PUSH
	LD R7,SAVE_R7
	RET
MINUS_CHAR .FILL x002D
	
DIV_OPERATOR
	LD R6,DIV_CHAR	
	NOT R6,R6
	ADD R6,R6,#1
    ADD R6, R0, R6
	BRnp MUL_OPERATOR   ;check if R0 is the MULTIPLICATION symbol next
	JSR DIV
    JSR PUSH
	LD R7,SAVE_R7
	RET
DIV_CHAR .FILL x002F

MUL_OPERATOR
	LD R6,MUL_CHAR	
	NOT R6,R6
	ADD R6,R6,#1
    ADD R6, R0, R6
	BRnp EXP_OPERATOR   ;check if R0 is the EXPONENTIAL symbol next
	JSR MUL
    JSR PUSH
	LD R7,SAVE_R7
	RET
MUL_CHAR .FILL x002A

EXP_OPERATOR
	LD R6,EXP_CHAR	
	NOT R6,R6
	ADD R6,R6,#1
    ADD R6, R0, R6
	BRnp INVALID_EXP    ;R0 was not a =, digit, +, -, /, *, or ^ so it must be an invalid input
	JSR EXP
    JSR PUSH
	LD R7,SAVE_R7
	RET
EXP_CHAR .FILL x005E
SAVE_R7 .BLKW #1
SAVE_R0 .BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 (R3+R4)
;out R0
PLUS

ADD R0, R3, R4    ;By focusing all our big brains, we formulated this advanced function in a mere 10 hours
RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 (R3-R4)
;out R0
MIN

NOT R4, R4
ADD R4, R4, #1
ADD R0, R3, R4  ;invert R4 then add to R3 and store in R0
RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 (R3 * R4)
;out R0
;TESTED: works
MUL
            ADD R0, R3, #0    ;in case R4 is 1, R0 is just R3
MUL_LOOP    ADD R4, R4, #-1    
            BRz MUL_DONE    ;We’ve added R3+R3 #R4 times
ADD R0, R3, R0
BRnzp MUL_LOOP
    
MUL_DONE 
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 (R3/R4)
;out R0
;TESTED: works

DIV
AND R0, R0, #0    ;int R0    
NOT R4, R4
ADD R4, R4, #1    ;negate R4
DIV_LOOP 
ADD R3, R4, R3
BRn DIV_DONE    ;R4>R3 so remainder which we don’t care about
ADD R0, R0, #1    ;Amount of times R4 fits into R3
ADD R3, R3, #0    
BRz DIV_DONE    ;Check if R4 cleanly divides into R3
BRnzp DIV_LOOP

DIV_DONE   
 RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 (R3^R4)
;out R0
EXP
    ST R6,EXP_SAVE_R6	;save regs
    ST R5,EXP_SAVE_R5

    ADD R6,R3,#0    ;load base to R6
    ADD R0,R3,R4    ;R0=R3+R4
    ;BRz UNDEFINED     ;if R0=0, R3=R4=0, operation 0^0 is undefined
    ADD R4,R4,#0    
    BRp EXP_OUTER_LOOP  ;check if the exponent is 0
    AND R0,R0,#0		;clear R0
    ADD R0,R0,#1		;output should be 1 if exp is 0
    LD R6,EXP_SAVE_R6
    RET
EXP_OUTER_LOOP
    ADD R4,R4,#-1		;use R4 as a counter for the multiplication sequence
    BRz exp_done    
    ADD R0,R6,#0		;load base to R0 for counter
    ADD R5,R3,#0		;update the addition number
EXP_INNER_LOOP
    ADD R0,R0,#-1		;commencing multiplication sequence, decrement counter
    BRz EXP_OUTER_LOOP
    ADD R3,R5,R3		;update value of R3
    BRnzp EXP_INNER_LOOP
exp_done
    ADD R0,R3,#0		;load final result to R0
    LD R5,EXP_SAVE_R5
    LD R6,EXP_SAVE_R6	;restore reg
    RET
EXP_SAVE_R5 .BLKW #1
EXP_SAVE_R6 .BLKW #1    
    
;your code goes here
    
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH    
    ST R3, PUSH_SaveR3    ;save R3
    ST R4, PUSH_SaveR4    ;save R4
    AND R5, R5, #0        ;
    LD R3, STACK_END    ;
    LD R4, STACK_TOP    ;
    ADD R3, R3, #-1        ;
    NOT R3, R3        ;
    ADD R3, R3, #1        ;
    ADD R3, R3, R4        ;
    BRz OVERFLOW        ;stack is full
    STR R0, R4, #0        ;no overflow, store value in the stack
    ADD R4, R4, #-1        ;move top of the stack
    ST R4, STACK_TOP    ;store top of stack pointer
    BRnzp DONE_PUSH        ;
OVERFLOW
    ADD R5, R5, #1        ;R5=1 -> fail, invalid expression
DONE_PUSH
    LD R3, PUSH_SaveR3    ;
    LD R4, PUSH_SaveR4    ;
    RET


PUSH_SaveR3    .BLKW #1    ;
PUSH_SaveR4    .BLKW #1    ;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP    
    ST R3, POP_SaveR3    ;save R3
    ST R4, POP_SaveR4    ;save R3
    AND R5, R5, #0        ;clear R5
    LD R3, STACK_START    ;
    LD R4, STACK_TOP    ;
    NOT R3, R3        ;
    ADD R3, R3, #1        ;
    ADD R3, R3, R4        ;
    BRz UNDERFLOW        ;
    ADD R4, R4, #1        ;
    LDR R0, R4, #0        ;
    ST R4, STACK_TOP    ;
    BRnzp DONE_POP        ;
UNDERFLOW
    ADD R5, R5, #1        ;R5=1 -> fail, invalid expression
DONE_POP
    LD R3, POP_SaveR3    ;
    LD R4, POP_SaveR4    ;
    RET


POP_SaveR3    .BLKW #1    ;
POP_SaveR4    .BLKW #1    ;
STACK_END    .FILL x3FF0    ;
STACK_START    .FILL x4000    ;
STACK_TOP    .FILL x4000    ;


.END  