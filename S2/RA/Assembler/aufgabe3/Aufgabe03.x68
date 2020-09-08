*-----------------------------------------------------------
* Title      :  Aufgabe03
* Written by :  Vlad Bratulescu - 299874
* Date       :  23.06.2020
* Description:  Dritte Aufgabe in REAR Übung
*-----------------------------------------------------------
    ORG    $1050                        ; Anfang vom Objektcode
START:                  
    LEA     String1,    A0              
    LEA     String2,    A1
    LEA     String3,    A2
    LEA     summe,      A3              ; Adressen jeweils in den Adressregistern laden
    
    CLR     D2                          ; Register D2 initialisieren
    BRA     CHECK                       ; Springe nach CHECK
    
LOOP:                                   ; for (i = 0; i < String1.length; i++) in etwa
    CMP.B   D0,         D1              ; Buchstabe aus D0 wird mit dem aus D1 vergliechen
    BLT     D1_LESS                     ; Wenn D1 kleiner ist, dann springe nach D1_LESS
    
D1_GREATER_EQUAL:
    MOVE.B  D0,         (A2)+           ; Buchstabe aus D0 in String3 ablegen und dessen Pointer um 1 Byte inkrementieren
    ADD     D0,         D2              ; der kleinere Buchstaben zu Gesamtsumme D2 addieren
    BRA     CHECK                       ; Springe nach CHECK

D1_LESS:
    MOVE.B  D1,         (A2)+           ; Buchstabe aus D1 in String3 ablegen und dessen Pointer um 1 Byte inkrementieren
    ADD     D1,         D2              ; der kleinere Buchstaben zu Gesamtsumme D2 addieren 

CHECK:                                  ; Prüft ob String-Ende erreicht wurde
    MOVE.B  (A0)+,      D0              ; Buchstabe vom String1 holen und Pointer inkrementieren
    MOVE.B  (A1)+,      D1              ; Buchstabe vom String2 holen und Pointer inkrementieren

    CMP.B   #0,         D0              ; Hier werden die Buchstaben mit 0 vergliechen,
    BEQ     SKIP                        ; um zu schauen ob String-Ende erreicht wurde. Wenn ja, dann springe nach SKIP
    CMP.B   #0,         D1              ; sonst mach weiter mit der Schleife
    BEQ     SKIP                        ; Da das Programm annimmt, dass beide Strings gleich lang sind,
    BRA     LOOP                        ; würde nur einen Check auf String-Ende reichen.
                                        ; Hier werden aber beide Buchstaben geprüft, wenn Buchstabe aus D0 nicht 0 ist
SKIP:
    MOVE.B  #0,         (A2)+           ; Eine 0 wird am Ende vom String3 abgelegt, um das String-Ende zu symbolisieren
    MOVE    D2,         (A3)+           ; Die Gesamtsumme der kleineren Buchstaben in die Adresse ablegen, auf die A3 zeigt
    
    ORG     $1000                       ; Startadresse vom String1 
String1     DC.B    'Studierender', 0   ; String 'Studierender' definieren. 0 steht am Ende des Strings
    ORG     $1010                       ; Startadresse vom String2
String2     DC.B    'Informatiker', 0   ; String 'Informatiker' definieren. 0 steht am Ende des Strings
    ORG     $1020                       ; Startadresse vom String3
String3     DS.B    13                  ; Es werden 13 Bytes reserviert. 13 weil String1 und String2 jeweils 12 Buchstaben haben und 1 Byte für das String-Ende '0'
summe       EQU     $1030               ; Symbolische Adresse mit $1030 initialisieren

    END    START       




*~Font name~Courier New~
*~Font size~12~
*~Tab type~1~
*~Tab size~4~
