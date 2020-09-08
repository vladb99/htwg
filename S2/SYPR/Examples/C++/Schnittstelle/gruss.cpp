/*
 * gruss.cpp
 *
 * Autor: H.Drachenfels
 * Erstellt am: 9.10.2018
 */

#include "gruss.h"

gruss::gruss(uhr *u)
: u(u)
{ }

std::string gruss::gruessen()
{
    int stunde;
    int minute;

    this->u->ablesen(stunde, minute);

    if (6 <= stunde && stunde < 11)
    {
        return "Guten Morgen";
    }

    if (11 <= stunde && stunde < 18)
    {
        return "Guten Tag";
    }

    if (18 <= stunde && stunde <= 23)
    {
        return "Guten Abend";
    }

    throw std::string("Nachtruhe!");
}

