*-----------------------------------------------------------
* Title      :  Aufgabe04
* Written by :  Vlad Bratulescu - 299874
* Date       :  02.07.2020
* Description:  Vierte Aufgabe in REAR Übung
*-----------------------------------------------------------
    ORG    $1050                        ; Anfang vom Objektcode  
START:
    LEA     ZIEL,       A2              ; Adresse vom ZIEL in Adressregister laden
    MOVE    #19,        D0              ; Konstante 19 in D0 laden. 19 weil die Dekrementierung der Laufvariable von LOOP1 am Anfang geschieht
                                        ; Implementierung des Bubblesorts Algorithmus
LOOP1:                                  ; for (i = String.length; i > 1; --i)
    LEA     String,     A0              ; Adresse vom String in Adressregister laden       
    SUBI    #1,         D0              ; Laufvariable um 1 dekrementieren
    CMP.B   #1,         D0              ; (i > 1) ?
    BEQ     SKIP                        ; Wenn i gleich 1, springe zu SKIP

    MOVE.B  #$FF,       D1              ; Konstante FF in D1 laden. FF weil die inkrementierung der Laufvariable von LOOP2 am Anfang geschieht
    MOVE    D0,         D2              ; D0 in D2 laden
    SUBI    #1,         D2              ; i - 1
                                        ; LOOP2 schiebt den größten Wert nach hinten
LOOP2:                                  ; for (j = 0; j < i - 1; ++j)
    ADDI.B  #1,         D1              ; Laufvariable um 1 inkrementieren
    CMP     D1,         D2              ; (j < i - 1) ?
    BEQ     LOOP1                       ; wenn j glecih i - 1, spring zu LOOP1
    
    MOVE.B  (A0)+,      D3              ; 1. Buchstabe in D3 laden und den Pointer um ein Byte inkrementieren
    MOVE.B  (A0),       D4              ; 2. Buchstabe in D4 laden

    CMP     D3,         D4              ; Nummerische Codes der Buchstaben vergleichen
    BGE     LOOP2                       ; wenn 2. Buchstabe größer oder gleich ist, dass springe zu LOOP2
                                        ; wenn 1. Buchstabe größer ist, dann tausche die Werte
    MOVE    A0,         A1              ; Adresse von A0 in A1 kopieren
    MOVE.B  D4,         -(A1)           ; Pointer aus A1 zuerst dekrementieren und dann D4 dort laden
    MOVE.B  D3,         (A0)            ; D3 in die Adresse laden auf die A0 zeigt
    
    BRA     LOOP2                       ; Springe zu LOOP2
    
SKIP:                                   ; Sortierte String nach ZIEL kopieren
    MOVE.B  (A0)+,      (A2)+           ; Buchstabe vom A0 in A2 laden und dann beide Pointer inkrementieren
    CMP.B   #0,         (A0)            ; String-Ende erreicht?
    BNE     SKIP                        ; Wenn nein dann springe zurück zu SKIP
    MOVE.B  #0,         (A2)            ; Eine 0 wird am Ende vom ZIEL abgelegt, um das String-Ende zu symbolisieren 
    
    ORG     $1000                       ; Startadresse vom String
String DC.B 'Rechnerarchitektur', 0     ; String wird definiert. 0 steht am Ende des Strings
    ORG     $1020                       ; Startadresse vom Ziel
ZIEL        DS.B    19                  ; Es werden 19 Bytes reserviert. 19 weil String 18 Buchstaben hat und noch 1 Byte für das String-Ende
    END    START



*~Font name~Courier New~
*~Font size~12~
*~Tab type~1~
*~Tab size~4~
