*-----------------------------------------------------------
* Title      :  Aufgabe02
* Written by :  Vlad Bratulescu - 299874
* Date       :  09.06.2020
* Description:  Verschluesseln eines Zeichenstrings mit Hilfe der "Caesar-Chiffre"
*-----------------------------------------------------------
   ORG     $1050                    ; Anfang vom Objektcode
START:
    LEA     String,     A0          ; Adresse vom String in A0 laden
    LEA     Zielfeld,   A1          ; Adresse vom Zielfeld in A1 laden
       
    MOVE.B  (A0)+,      D0          ; Das erste Zeichen (Byte) vom String in Register D0 laden. Pointer zeigt danach auf den naechsten Buchstaben
    CMP.B   #0,         D0          ; Vergleiche Buchstabe mit '0'. Wenn das erste Zeichen den ASCII-Code '0' hat, heisst es dass der String leer ist
    BEQ     SKIP                    ; Wenn String leer ist, dann springe zu SKIP
                                    ; Wenn nicht leer dann gehe zu LOOP
LOOP:                               ; for (i = 0; i < String.length; i++) in etwa
    CMP.B   #$58,       D0          ; Wenn der Buchstabe X
    BEQ     XYZ
    CMP.B   #$59,       D0          ; oder Y
    BEQ     XYZ
    CMP.B   #$5A,       D0          ; oder Z
    BEQ     XYZ
    CMP.B   #$78,       D0          ; oder x
    BEQ     XYZ
    CMP.B   #$79,       D0          ; oder y
    BEQ     XYZ
    CMP.B   #$7A,       D0          ; oder z ist
    BEQ     XYZ                     ; dann springe zu XYZ
                                    ; Wenn anderer Buchstabe dann gehe zu NOT_XYZ
NOT_XYZ:                            
    ADD.B   #3,         D0          ; ASCII-Code des Zeichens um 3 inkrementieren und im D0 ablegen
    BRA     CHECK                   ; Springe zu CHECK
    
XYZ:                                ; Sonderfall da Sprung vom Ende zum Anfang des Alphabets 
    SUB.B   #23,        D0          ; ASCII-Code des Zeichens um 23 dekrementieren
    
CHECK:                              ; Ueberprueft ob String-Ende erreicht wurde
    MOVE.B  D0,         (A1)+       ; Den geaenderten ASCII-Code im Zielfeld ablegen und dessen Pointer um 1 Byte inkrementieren 
    MOVE.B  (A0)+,      D0          ; Der naechste Buchstabe vom String holen
    CMP.B   #0,         D0          ; Vergleiche den Buchstaben mit '0'
    BEQ     SKIP                    ; Wenn String-Ende erreicht wurde, springe zu SKIP
    BRA     LOOP                    ; Wenn String-Ende nicht erreicht wurde, springe zu LOOP
    
SKIP:
    MOVE.B  #0,         (A1)+       ; Eine '0' wird am Ende des Strings im Zielfeld abgelegt, um das String-Ende zu symbolisieren
    
    ORG     $1000                   ; Startadresse vom String
String      DC.B    'Zykluszeit',0  ; String 'Zykluszeit' definieren. '0' steht am Ende des Strings  
    ORG     $1010                   ; Startadresse vom Zielfeld
Zielfeld    DS.B    11              ; Es werden 11 Bytes reserviert. 11 weil 'Zykluszeit' 10 Buchstaben hat und 1 Byte fuer das String-Ende '0'
                                    ; Darausfolgt, dass das Programm nur fuer ein String mit der Groesse <= 10 richtig funktioniert
    END    START



*~Font name~Courier New~
*~Font size~12~
*~Tab type~1~
*~Tab size~4~
