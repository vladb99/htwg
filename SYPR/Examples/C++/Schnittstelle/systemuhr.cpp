/*
 * systemuhr.cpp
 *
 * Autor: H.Drachenfels
 * Erstellt am: 9.10.2018
 */

#include "systemuhr.h"
#include <ctime>

void systemuhr::ablesen(int& s, int& m) const
{
    std::time_t t = std::time(0);
    std::tm *lt = std::localtime(&t);
    s = lt->tm_hour;
    m = lt->tm_min;
}

