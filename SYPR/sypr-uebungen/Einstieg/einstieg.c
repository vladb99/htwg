/*
 * einstieg.c
 *
 * Das erste C-Programm gibt einen Text aus.
 *
 * Autor: ...
 * Erstellt am: ...
 */

#include <stdio.h>

int main(void)
{
    printf("Anzahl bisher geschriebener C-Programme eingeben: ");
    int anzahl;
    scanf("%d", &anzahl);

    printf("Vorname eingeben: ");
    char vorname[8];
    scanf("%s", vorname);

    printf("%ss %d. C-Programm funktioniert!\n", vorname, anzahl + 1);
    
    return 0;
}