/*
 * testuhr.cpp
 *
 * Autor: H.Drachenfels
 * Erstellt am: 9.10.2018
 */

#include "testuhr.h"
#include <stdexcept>

testuhr::testuhr()
: stunde(0), minute(0)
{ }

void testuhr::stellen(int s, int m)
{
    if (s < 0 || m < 0)
    {
        throw std::invalid_argument("negative Stunde oder Minute");
    }

    this->stunde = (s + m / 60) % 24;
    this->minute = m % 60;
}

void testuhr::ablesen(int& s, int& m) const
{
    s = this->stunde;
    m = this->minute;
}

