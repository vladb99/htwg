/*
 * find.cpp
 *
 * Beispiel-Programm std::find-Funktionstemplate
 *
 * Autor: H.Drachenfels
 * Erstellt am: 11.3.2019
 */

#include <iostream>
#include <algorithm>
#include <array>
//#include <vector>
//#include <list>
 
int main()
{
    int a[] = {3421, 3442, 3635, 3814};
    int *begin = a; // Zeiger auf Elementtyp dienen als Iteratoren
    int *end = a + 4;

    auto i = std::find(begin, end, 3442); // I = int* und T = int
    if (i != end) {
        std::cout << *i << " ist in a enthalten\n";
    }

    std::array<int,4> b = {3421, 3442, 3635, 3814};
    // std::vector<int> b{3421, 3442, 3635, 3814};
    // std::list<int> b{3421, 3442, 3635, 3814};
    //
    auto j = std::find(b.begin(), b.end(), 3442);
    if (j != b.end()) {
        std::cout << *j << " ist in a enthalten\n";
    }
}

