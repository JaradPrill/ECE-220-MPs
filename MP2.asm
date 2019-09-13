;jaradjp2 
;bozhaoj2
;rohan
;is this working? yes
.ORIG x3000
    
;your code goes here
    











;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal (use MP1)
PRINT_HEX 

; let R0 be temp storage
; let R1 be char counter
; let R2 be bit counter for hex letter/decimal
; let R3 be hex-value we want to print
; let R4 be storage for printing hex of interest
; let R5 point to hist value we are printing, starting at x3F00
; let R6 be line counter

;"Char" will how many hex values we've printed. ex.) we want to print xECEB and we have printed
; "ECE" then Char will be 3

;"bit counter" is counting how many 1's and 0's we've pushed into R4 from R3

;We will print the @-symbol + R6 and a space anytime we print a line in order to label the HIST data output. 
;We will use R3 to store the 4-char hex number pulled from R5 which points to the HIST data
;Then will push the most-significant bit (MSB) from R3 into R4 4 times until we have the 
;first hex value (composed of 4 bits) in R4.
;Then we subtract #9 from R4 and place the result in temp (R0) to check if it's a letter or decimal.
;If it's a number we add x0030 then print the resulting ASCII character.
;If it's a char we subtract 10 and add x0300
;We do this 4 times for each hex-char before creating a new line and pulling new data into R5
;After printing 27 lines, we are done.

		;int R0, R3, and R6
			AND R0, R0, #0
			AND R3, R3, #0
			AND R6, R6, #0
			LD R5, HIST_ADDR ;load x3F00 into R5

LINE_START	LD R0,at_char	;Use R0 to print char of hist line we are at
			ADD R0, R6, R0	;adjust R0 to which line we are on using R6 pointer
			OUT
			LD R0, space	;print a space
			OUT
			
			LDR R3, R5, #0	;load value at R5 (hist data at line of interest) into R3
			AND R1, R1, #0 	;int char counter
			ADD R1, R1, #4	
char_loop	BRz NEXT_LINE	;if 4 chars printed, then move onto next hist line
			AND R4, R4, #0	;reset R4
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

			ADD R0, R4, #-9 ;check if hex is a decimal or character
			BRp print_char
print_num	LD R0, hex_num	;prints decimal
			ADD R0, R4, R0
			OUT
			BRnzp print_done
print_char	LD R0, hex_char	;prints hex character
			ADD R4, R4, #-10 ;
			ADD R0, R4, R0
			OUT
print_done	ADD R1, R1, #-1	;decriment R1 and loop back
			BRnzp char_loop		

NEXT_LINE	LD R0, Line_break
		OUT
		ADD R5, R5, #1 	;point to next hist data line
		ADD R6, R6, #1	;increment line counter
		LD R0, NUM_BINS	;R0 hold #27
		NOT R0, R0
		ADD R0, R0, #1	;R0 holds #-27
		ADD R0, R6, R0	;compares #27 to R6
		BRz DONE	;if we printed 27 hist line, we are done
		BRnzp LINE_START

space		.FILL x0020
Line_break	.FILL x000A		
at_char		.FILL x0040
hex_num		.FILL x0030
hex_char	.FILL x0041

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 (R3+R4)
;out R0
PLUS

ADD R0, R3, R4    ;holy shit this is a bit too complicated
RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 (R3-R4)
;out R0
MIN

NOT R4, R4
ADD R4, R4, #1
ADD R0, R3, R4
RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 (R3 * R4)
;out R0
;TESTED: works
MUL
            ADD R0, R3, #0    ;in case R4 is 1
MUL_LOOP    ADD R4, R4, #-1    
            BRz MUL_DONE    ;We’ve added R3+R3 #R4 times
ADD R0, R3, R0
BRnzp MUL_LOOP
    
MUL_DONE    RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 (R3/R4)
;out R0
;TESTED: works

DIV
AND R0, R0, #0    ;int R0    
NOT R4, R4
ADD R4, R4, #1    ;negate R4
DIV_LOOP BRn DIV_DONE    ;R4>R3 so remainder which we don’t care about
ADD R0, R0, #1    ;Amount of times R4 fits into R3
ADD R3, R3, #0    
BRz DIV_DONE    ;Check if R4 cleanly divides into R3
BRnzp DIV_LOOP

DIV_DONE    RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 (R3^R4)
;out R0
EXP
    ST R6,EXP_SAVE_R6
    ST R5,EXP_SAVE_R5

    ADD R6,R3,#0    ;load base to R6
    ADD R0,R3,R4    ;R0=R3+R4
    ;BRz INVALID     ;if R0=0, R3=R4=0, operation is invalid
    ADD R4,R4,#0    
    BRp EXP_OUTER_LOOP  ;check if the exponent is 0
    AND R0,R0,#0    ;clear R0
    ADD R0,R0,#1    ;output should be 1 if exp is 0
    LD R6,EXP_SAVE_R6
    RET
EXP_OUTER_LOOP
    ADD R4,R4,#-1   ;use R4 as a counter for the multiplication sequence
    BRz exp_done    
    ADD R0,R6,#0    ;load base to R0 for counter
    ADD R5,R3,#0    ;update the addition number
EXP_INNER_LOOP
    ADD R0,R0,#-1   ;commencing multiplication sequence, decrement counter
    BRz EXP_OUTER_LOOP
    ADD R3,R5,R3    ;update value of R3
    BRnzp EXP_INNER_LOOP
exp_done
    ADD R0,R3,#0    ;load final result to R0
    LD R5,EXP_SAVE_R5
    LD R6,EXP_SAVE_R6
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
    LD R4, STACk_TOP    ;
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
