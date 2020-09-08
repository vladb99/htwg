/*
 * vectorvar.cpp
 *
 * Beispiel-Programm std::vector-Variable
 *
 * Autor: H.Drachenfels
 * Erstellt am: 2.8.2019
 */

#include <iostream>
#include <vector> // alternativ: #include <array>

int main()
{
    std::vector<int> v(4); // alternativ: std::array<int,4> v;
    v.at(0) = 3421;
    v.at(1) = 3442;
    v.at(2) = 3635;
    v.at(3) = 3814;
  
    // print vector values
    for (unsigned i = 0; i < v.size(); ++i)
    {
        std::cout << i << ": " << v[i] << '\n'; // v.operator[](i)
    }

    // print vector size
    std::cout << "sizeof v = " << sizeof v << '\n';
    std::cout << "v.size() = " << v.size() << '\n';
}

