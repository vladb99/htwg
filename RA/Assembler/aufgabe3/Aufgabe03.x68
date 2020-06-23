*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $1050
START:                  
    LEA     String1,    A0
    LEA     String2,    A1
    LEA     String3,    A2
    LEA     summe,      A3
    
    CLR     D2
    BRA     CHECK
    
LOOP:
    CMP.B   D0,         D1
    BLT     D1_LESS
    
D1_GREATER_EQUAL:
    MOVE.B  D0,         (A2)+
    ADD     D0,         D2
    BRA     CHECK

D1_LESS:
    MOVE.B  D1,         (A2)+
    ADD     D1,         D2

CHECK:
    MOVE.B  (A0)+,      D0
    MOVE.B  (A1)+,      D1

    CMP.B   #0,         D0
    BEQ     SKIP
    CMP.B   #0,         D1
    BEQ     SKIP
    BRA     LOOP

SKIP:
    MOVE.B  #0,         (A2)+
    MOVE    D2,         (A3)+
    
    ORG     $1000 
String1     DC.B    'Studierender', 0
    ORG     $1010
String2     DC.B    'Informatiker', 0
    ORG     $1020
String3     DS.B    13
summe       EQU     $1030

    END    START       


*~Font name~Courier New~
*~Font size~12~
*~Tab type~1~
*~Tab size~4~
