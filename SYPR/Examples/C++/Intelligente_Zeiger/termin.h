/*
 * termin.h
 *
 * Beispielprogramm intelligente Zeiger.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 11.3.2019
 */
#ifndef TERMIN_H
#define TERMIN_H

#include "datum.h"
#include <string>
#include <memory>

class termin final
{
private:
    datum wann;
    std::string was;
    termin(const datum&, const std::string&);

public:
    static std::unique_ptr<termin> new_instance(const datum&,
                                                const std::string&);
    // ~termin();

    termin(const termin&) = delete;
    termin(termin&&) = delete;
    termin& operator=(const termin&) = delete;
    termin& operator=(termin&&) = delete;

    void verschieben(const datum&);
    datum get_datum() const;
    std::string get_beschreibung() const;
};

#endif

