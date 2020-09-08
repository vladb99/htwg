/*
 * einstieg-mit-fehlerbehandlung.cpp
 *
 * Das erste C++-Programm gibt einen Text aus.
 * 
 * Autor(en): H.Drachenfels
 * Erstellt am: 7.6.2018
 */

#include <iostream>
#include <string>

int main()
{
    std::cout << "Anzahl bisher geschriebener C++-Programme eingeben: ";
    int anzahl;
    if (!(std::cin >> anzahl))
    {
        std::cerr << "*** Eingabefehler: ganze Zahl erwartet\n";
        return 1;
    }

    std::cout << "Vorname eingeben: ";
    std::string vorname;
    if (!(std::cin >> vorname))
    {
        std::cerr << "*** Eingabefehler: Zeichenkette erwartet\n";
        return 1;
    }

    std::cout << vorname
              << "s "
              << anzahl + 1
              << ". C++-Programm funktioniert!\n";

    // return 0; wird automatisch ergaenzt
}

