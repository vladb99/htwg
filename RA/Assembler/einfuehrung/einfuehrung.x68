*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG    $1000
START:                  ; first instruction of program

* Put program code here
    MOVE.W  number, D0
    MOVE.B  $1234,  D1
    ADD.W   D0,     D1

   SIMHALT             ; halt simulator

* Put variables and constants here
number DC.W 42
string DC.W 'Rechnerarchitektur', 0

    END    START        ; last line of source

*~Font name~Courier New~
*~Font size~12~
*~Tab type~1~
*~Tab size~4~
