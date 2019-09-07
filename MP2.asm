;
;
;
.ORIG x3000
    
;your code goes here
    











;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal (use MP1)
PRINT_HEX

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
    ADD R0,R3,R4    ;R0=R3+R4
    BRz INVALID    ;if R0=0, R3=R4=0, operation is invalid
    ADD R4,R4,#0    
    BRp EXP_NOT0    ;check if the exponent is 0
    AND R3,R3,#0    ;clear R3
    ADD R3,R3,#1    ;output should be 1 if exp is 0
    BRnzp exp_done
EXP_NOT0
    ADD R4,R4,#-1
    ADD R0,R3,#0    ;load base to R0 for counter
    ADD R3,R3,R3    ;commencing multiplication sequence
    ADD R3,R3,#-1
    
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
