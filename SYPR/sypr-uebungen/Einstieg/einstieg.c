/*
 * einstieg.c
 *
 * Das erste C-Programm gibt einen Text aus.
 *
 * Autor: vladb
 * Erstellt am: 23.04.2020
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

    printf("%sss %d. C-Programm funktioniert nicht!\n", vorname, anzahl + 1);
    
    return 0;
}