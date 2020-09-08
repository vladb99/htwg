*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG     $1000
    BRA     START
    
ADR1    EQU     $2000
ADR2    EQU     $3000
KONST   DC.W    50
ERG     DS.L    1

START:                  ; first instruction of program
    MOVE.W  #ADR1,  A1
    MOVE.W  #ADR2,  A2
    MOVE.W  (A1),   D1
    ADD.L   (A2),   D1
    ADD.L   KONST,  D1
    MOVE.L  D1,     ERG
   
    SIMHALT

    END     START                  ; last line of source

*~Font name~Courier New~
*~Font size~12~
*~Tab type~1~
*~Tab size~4~
