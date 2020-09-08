/*
 * ortstermin.cpp
 *
 * Beispielprogramm Vererbung.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 10.3.2019
 */
#include "ortstermin.h"

ortstermin::ortstermin(const std::string &t, const datum &d, const std::string &s)
: termin(d, s), wo(t)
{ }

std::string ortstermin::get_ort() const
{
    return this->wo;
}

