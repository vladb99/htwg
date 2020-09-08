/*
 * gruss.h
 *
 * Autor: H.Drachenfels
 * Erstellt am: 29.1.2020
 */

#ifndef GRUSS_H
#define GRUSS_H

#include "uhr.h"
#include <string>

class gruss
{
private:
    uhr *u;
public:
    // Entity-Klasse ohne Kopier- und Move-Semantik
    gruss(const gruss&) = delete;
    gruss& operator=(const gruss&) = delete;
    // gruss(gruss&&) = delete;
    // gruss& operator=(gruss&&) = delete;

    explicit gruss(uhr *u);
    // ~gruss() = default;
    std::string gruessen();
};

#endif

