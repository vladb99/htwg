/*
 * istream.cpp
 *
 * Verwendung von istream-Funktionen.
 * 
 * Autor: H.Drachenfels
 * Erstellt am: 11.3.2019
 */

#include <iostream>

int main()
{
    int n;
    std::cin.setf(std::ios_base::hex, std::ios_base::basefield);
    std::cin >> n;  // liest hexadezimale Zahl
    std::cout << n << std::endl;  // gibt n dezimal aus

    // das gleiche mit Manipulatoren:
    std::cin >> std::hex >> n;  // liest hexadezimale Zahl
    std::cout << n << std::endl;  // gibt n dezimal aus
}

