/*
 * listvar.cpp
 *
 * Beispielprogramm eingebettete Klassen.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 14.3.2019
 */
#include "intlist.h"
#include <iostream>

int main()
{
    //----------------------------------------------------------- Liste anlegen
    intlist list;
    list.insert(3814).insert(3635).insert(3442).insert(3421);

    //---------------------------------------------------------- Liste ausgeben
    for (int n : list)
    {
        std::cout << n << std::endl;
    }

    for (auto i = list.begin(); i != list.end(); ++i)
    {
        std::cout << *i << std::endl; // i.operator*()
    }
}
