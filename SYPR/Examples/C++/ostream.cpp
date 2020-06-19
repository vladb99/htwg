/*
 * ostream.cpp
 *
 * Verwendung von ostream-Funktionen.
 * 
 * Autor: H.Drachenfels
 * Erstellt am: 11.3.2019
 */

#include <iostream>
#include <iomanip>  // setprecision, setw, setfill

int main()
{
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    std::cout.precision(1);
    std::cout << 1.26 << std::endl; // gibt 1.3 aus

    std::cout.width(4);
    std::cout.fill('0');
    std::cout << 1 << std::endl; // gibt 0001 aus

    // das gleiche mit Manipulatoren:
    std::cout << std::fixed << std::setprecision(1) << 1.26 << std::endl;
    std::cout << std::setw(4) << std::setfill('0') << 1 << std::endl;
}

