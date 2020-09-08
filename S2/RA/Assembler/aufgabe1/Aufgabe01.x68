*-----------------------------------------------------------
* Title      : Aufgabe01
* Written by : Vlad Bratulescu - 299874
* Date       : 02.06.2020
* Description: Erste Aufgabe in REAR Übung
*-----------------------------------------------------------
    ORG     $2000           ; Anfang vom Objektcode
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
    MOVE.W  D1,     (A1)+   ; D1 in die Adresse schieben, auf die A1 zeigt. Danach wird A1 um eine Speicherzelle inkrementiert
    SUB.W   #1,     D3      ; Die Laufvariable um 1 dekrementieren
    BPL     LOOP            ; Wenn der N-Bit nicht gesetzt wurde, springe nach LOOP

    MOVE.L  D2,     (A2)    ; Am Schluss soll die Gesamtsumme aller Speicherzellen an der Adresse RESULT abgelegt werden
    LEA     ANFANG, A1      ; Adresse ANFANG nochmal in A1 laden

    MOVE.W  #99,    D3      ; Laufvariable für die zweite Schleife initialisieren
    CLR.L   D1              ; D1 löschen
    
MOD2:
    CLR.L   D0              ; D0 löschen
    MOVE.W  (A1)+,  D0      ; Den Inhalt von der Adresse auf die A1 zeigt, wird in D0 geladen
    DIVU    #2,     D0      ; D0 durch zwei teilen. Der Quotient wird im Lower-Word und der Rest im Higher-Word gespeichert.
    CLR.W   D0              ; Quotient löschen
    SWAP    D0              ; Higher-Word mit Lower-Word tauschen, also den Rest der Division im Lower-Byte schieben
    BNE     SKIP            ; Springe wenn D0 nicht 0 ist
    ADD.W   #1,     D1      ; Inkrementiere D1 um 1
SKIP:
    SUB.W   #1,     D3      ; Subtrahiere 1 vom D3
    BPL     MOD2            ; Springe wenn nicht negativ
    MOVE.B  D1,     (A3)    ; Anzahl der ohne Rest durch 2 teilbaren Zahlen in ERGEB schieben
            
        
ANFANG  EQU     $2500
RESULT  EQU     $2800
ERGEB   EQU     $2810       ;Symbolische Adressen initialisieren

K1      DC.W    $2000       ; Konstante K1 wird definiert
K2      DC.W    $4000       ; Konstante K2 wird definiert

     END    START        

*~Font name~Courier New~
*~Font size~12~
*~Tab type~1~
*~Tab size~4~
