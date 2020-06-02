*-----------------------------------------------------------
* Title      :
* Written by :
* Date       :
* Description:
*-----------------------------------------------------------
    ORG     $2000
START:
    LEA     ANFANG, A1      
    LEA     RESULT, A2
    LEA     ERGEB,  A3      ; Adressen jeweils in den Adressregistern laden
       
    MOVE.W  K1,     D0      
    MOVE.W  K2,     D1      ; K1 und K2 in D0 und D1 laden
    ADD.W   D0,     D1      ; D0 mit D1 addieren und Ergebnis in D1 speichern
    MOVE.W  D1,     (A1)+   ; D1 in die Adresse schieben, auf die A1 zeigt. Danach wird A1 um eine Speicherzelle inkrementiert

    CLR.L   D2              ; Feld für Summe aller Speicherzellen initialisieren
    ADD.W   D1,     D2      ; D1 drauf addieren
    
    MOVE.W  #199,   D3      ; Laufvariable für die Schleife initialisieren
    
LOOP:                       ; for (i = 199; i >= 0; i--)
    ADD.W   #1,     D1      ; D1 um 1 inkrementieren
    ADD.L   D1,     D2      ; D2 mit D1 addieren um die Gesamtsumme aller Speicherzellen zu bilden
    MOVE.W  D1,     (A1)+   ; 
    SUB.W   #1,     D3
    BPL     LOOP

    MOVE.L  D2,     (A2)
    LEA     ANFANG, A1

    MOVE.W  #99,    D3
    CLR.L   D1
    
MOD2:
    CLR.L   D0
    MOVE.W  (A1)+,  D0
    DIVU    #2,     D0      ; D0 durch zwei teilen. Der Quotient wird im Lower-Word und der Rest im Higher-Word gespeichert.
    CLR.W   D0              ; Quotient löschen
    SWAP    D0              ; Higher-Word mit Lower-Word tauschen, also Rest im Lower-Byte schieben
    BNE     SKIP            ; Springe wenn D0 nicht 0 ist
    ADD.W   #1,     D1      ; Inkrementiere D1 um 1
SKIP:
    SUB.W   #1,     D3      ; Subtrahiere 1 vom D3
    BPL     MOD2            ; Springe wenn nicht negativ
    MOVE.W  D1,     (A3)    ; Anzahl der ohne Rest durch 2 teilbaren Zahlen in ERGEB schieben
            
        
ANFANG  EQU     $2500
RESULT  EQU     $2800
ERGEB   EQU     $2810

K1      DC.W    $2000
K2      DC.W    $4000

     END    START        

*~Font name~Courier New~
*~Font size~12~
*~Tab type~1~
*~Tab size~4~
