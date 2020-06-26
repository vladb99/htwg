/*
 * datum.h
 *
 * Beispielprogramm Klasse.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 2.8.2019
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
    // datum(const datum&);
    // datum(datum&&);
    // ~datum();

    // datum& operator=(const datum&);
    // datum& operator=(datum&&);

    friend bool operator==(const datum&, const datum&);
    friend std::ostream& operator<<(std::ostream&, const datum&);
};

std::istream& operator>>(std::istream&, datum&);

#endif

