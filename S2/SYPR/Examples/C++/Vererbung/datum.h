/*
 * datum.h
 *
 * Beispielprogramm Klasse.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 29.1.2020
 */
#ifndef DATUM_H
#define DATUM_H

#include <iostream>

class datum final
{
private:
    int tag;
    int monat;
    int jahr;

public:
    static datum heute();

    datum() = default;
    datum(int t, int m, int j);
    // datum(const datum&) = default;
    // datum(datum&&) = default;
    // ~datum() = default;

    // datum& operator=(const datum&) = default;
    // datum& operator=(datum&&) = default;

    friend bool operator==(const datum&, const datum&);
    friend std::ostream& operator<<(std::ostream&, const datum&);
};

std::istream& operator>>(std::istream&, datum&);

#endif

