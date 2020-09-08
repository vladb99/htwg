/*
 * termin.h
 *
 * Beispielprogramm Vererbung.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 29.1.2020
 */
#ifndef TERMIN_H
#define TERMIN_H

#include "datum.h"
#include <string>

class termin // Oberklasse: ohne final
{
private:
    datum wann;
    std::string was;
public:
    termin(const datum&, const std::string&);
    virtual ~termin() = default; // Oberklasse: dynamische Bindung

    // Entity-Klasse: keine Objektkopien, nur move
    termin(const termin&) = delete;
    termin& operator=(const termin&) = delete;
    termin(termin&&) = default;
    termin& operator=(termin&&) = default;

    void verschieben(const datum&);
    datum get_datum() const;
    std::string get_beschreibung() const;
};

#endif

