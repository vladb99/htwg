/*
 * systemuhr.h
 *
 * Autor: H.Drachenfels
 * Erstellt am: 11.10.2018
 */

#ifndef SYSTEMUHR_H
#define SYSTEMUHR_H

#include "uhr.h"

class systemuhr final : public uhr
{
public:
    virtual void ablesen(int& s, int& m) const override;
};

#endif

