#include <iostream>

int main()
{
    std::cout << "Dezimalzahl eingeben: ";
    int zahl;
    std::cin >> zahl;
    std::cout << "Hexadezimalzahl: " << std::hex << zahl << std::endl;
}