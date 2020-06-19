/*
 * stringvar.cpp
 *
 * Beispiel-Anwendung von std::string-Funktionen
 * (vergleiche stringvar.c aus Teil 2)
 *
 * Autor: H.Drachenfels
 * Erstellt am: 22.11.2017
 */

#include <iostream>
#include <string>

int main()
{
    std::string a = "halli"; // a("halli")
    std::string s = "hallo"; // s("hallo")
    std::string t; // leerer String

    //----------------------------- compare, copy and concatenate strings
    if (a < s) // operator<(a, s)
    {
        t = a + s; // t.operator=(operator+(a, s))
    }

    //------------------------------------- print string values and sizes
    std::cout << "a = " << a << '\n';
    // operator<<(operator<<(operator<<(std::cout, "a = "), a), '\n')
    std::cout << "s = " << s << '\n';
    std::cout << "t = " << t << '\n';

    std::cout << "sizeof a = " << sizeof a << '\n';
    std::cout << "sizeof s = " << sizeof s << '\n';
    std::cout << "sizeof t = " << sizeof t << '\n';

    std::cout << "a.length() = " << a.length() << '\n';
    std::cout << "s.length() = " << s.length() << '\n';
    std::cout << "t.length() = " << t.length() << '\n';
}

