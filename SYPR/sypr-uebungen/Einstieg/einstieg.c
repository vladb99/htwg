/*
 * einstieg.c
 *
 * Das erste C-Programm gibt einen Text aus.
 *
 * Autor: vladb
 * Erstellt am: 23.04.2020
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Anzahl bisher geschriebener C-Programme eingeben: ");
    int anzahl;
    scanf("%d", &anzahl);

    printf("Vorname eingeben: ");
    char *vorname = (char*) malloc(8);
    scanf("%s", vorname);

    printf("%ss %d. C-Programm funktioniert nicht!\n", vorname, anzahl + 1);
    
    free(vorname);
    return 0;
}