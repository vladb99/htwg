/*
 * termin.cpp
 *
 * Beispielprogramm intelligente Zeiger.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 11.3.2019
 */
#include "termin.h"

std::unique_ptr<termin> termin::new_instance(const datum& d,
                                             const std::string& s)
{
    return std::unique_ptr<termin>(new termin(d, s));
}

termin::termin(const datum &d, const std::string &s)
: wann(d), was(s)
{ }

void termin::verschieben(const datum &d)
{
    this->wann = d;
}

datum termin::get_datum() const
{
    return this->wann;
}

std::string termin::get_beschreibung() const
{
    return this->was;
}

