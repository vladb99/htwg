*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $1050
START:
    MOVE    #19,        D0  ;19 weil sub 1 in loop 1
    
LOOP1:
    SUBI    #1,         D0
    CMP.B   #1,         D0
    BEQ     SKIP

    MOVE.B  #$FF,       D1
    MOVE    D0,         D2
    SUBI    #1,         D2
    
    LEA     String,     A0
    LEA     ZIEL,       A1
    
LOOP2:
    ADDI.B  #1,         D1
    CMP     D1,         D2
    BEQ     LOOP1
    
    MOVE.B  (A0)+,      D3
    MOVE.B  (A0),       D4

    CMP     D3,         D4    
    BGE     ELSE
    
    MOVE.B  D4,         (A1)+
    MOVE.B  D3,         (A1)
    
    BRA     LOOP2
    
ELSE
    MOVE.B  D3,         (A1)+
    MOVE.B  D4,         (A1)
   
    BRA     LOOP2
    
SKIP:
    
    
    ORG     $1000
String      DC.B    'Rechnerarchitektur', 0
    ORG     $1020
ZIEL        DC.B    'Rechnerarchitektur', 0
    END    START


*~Font name~Courier New~
*~Font size~12~
*~Tab type~1~
*~Tab size~4~
