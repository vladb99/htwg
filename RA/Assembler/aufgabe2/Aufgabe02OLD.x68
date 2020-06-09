*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
   ORG     $1050
START:
    LEA     $1000,      A0
    LEA     Zielfeld,   A1
    
    MOVE.B  (A0)+,      D0
    CMP.B   #0,         D0
    BEQ     SKIP    
LOOP:
    CMP.B   #$58,       D0
    BEQ     XYZ
    CMP.B   #$59,       D0
    BEQ     XYZ
    CMP.B   #$5A,       D0
    BEQ     XYZ
    CMP.B   #$78,       D0
    BEQ     XYZ
    CMP.B   #$79,       D0
    BEQ     XYZ
    CMP.B   #$7A,       D0
    BEQ     XYZ
        
NOT_XYZ:
    ADD.B   #3,         D0    BRA     CHECK
XYZ:    
    SUB.B   #23,        D0
CHECK:
      MOVE.B  D0,         (A1)+        
    MOVE.B  (A0)+,      D0
    CMP.B   #0,         D0
    BEQ     SKIP
    BRA     LOOP
SKIP:
    MOVE.B  #0,         (A1)+
    
    ORG     $1000
String      DC.B    'Zykluszeit',       0
    ORG     $1010
Zielfeld    DS.B    11      
  
    END    START

*~Font name~Courier New~
*~Font size~12~
*~Tab type~1~
*~Tab size~4~
