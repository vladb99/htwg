/*
 * arrays.cpp
 *
 * Beispiel-Anwendung von std::array
 *
 * Autor: H.Drachenfels
 * Erstellt am: 4.11.2019
 */

#include <iostream>
#include <array>  // std::array, size, operator[ ], ...

int main()
{
    std::array<int, 4> ia = {3625, 3648, 3853, 4042};
    for (std::size_t i = 0; i < ia.size(); ++i)
    {
        std::cout << ia[i] << '\n';
    }

    std::array<double, 4> da = {3.625, 3.648, 3.853, 4.042};
    for (std::size_t i = 0; i < da.size(); ++i)
    {
        std::cout << da[i] << '\n';
    }
}

