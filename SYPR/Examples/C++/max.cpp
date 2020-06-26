/*
 * max.cpp
 *
 * Beispiel-Programm std::max-Funktionstemplate
 *
 * Autor: H.Drachenfels
 * Erstellt am: 27.11.2019
 */

#include <iostream>
#include <algorithm>

int main()
{
    // T = int
    std::cout << "std::max(1, 2) = "
              << std::max(1, 2)
              << '\n';

    // T = std::string
    std::cout << "std::max(std::string(\"abc\"), std::string(\"def\")) = "
              << '\"' << std::max(std::string("abc"), std::string("def")) << '\"'
              << '\n';

    // T = const char *
    const char *a = "abc";
    const char *b = "def";
    std::cout << '\"' << a << "\" = " << static_cast<const void*>(a) << '\n';
    std::cout << '\"' << b << "\" = " << static_cast<const void*>(b) << '\n';
    std::cout << "std::max(\"" << a << "\", \"" << b << "\") = "
              << '\"' << std::max(a, b) << '\"'
              << '\n';

    const char def[] = "def";
    const char abc[] = "abc";
    a = abc;
    b = def;
    std::cout << '\"' << a << "\" = " << static_cast<const void*>(a) << '\n';
    std::cout << '\"' << b << "\" = " << static_cast<const void*>(b) << '\n';
    std::cout << "std::max(\"" << a << "\", \"" << b << "\") = "
              << '\"' << std::max(a, b) << '\"'
              << '\n';
}

