/*
 * ortstermin.h
 *
 * Beispielprogramm Vererbung.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 29.1.2020
 */
#ifndef ORTSTERMIN_H
#define ORTSTERMIN_H

#include "termin.h"
#include <string>

class ortstermin final : public termin
{
private:
    std::string wo;
public:
    ortstermin(const std::string&, const datum&, const std::string&);
    // ~ortstermin() = default;
    // ortstermin(const ortstermin&) = delete;
    // ortstermin& operator=(const ortstermin&) = delete;
    // ortstermin(ortstermin&&) = default;
    // ortstermin& operator=(ortstermin&&) = default;
    std::string get_ort() const;
};

#endif

