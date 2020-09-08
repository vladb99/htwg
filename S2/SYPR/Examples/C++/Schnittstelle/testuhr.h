/*
 * testuhr.h
 *
 * Autor: H.Drachenfels
 * Erstellt am: 11.10.2018
 */

#ifndef TESTUHR_H
#define TESTUHR_H

#include "uhr.h"

class testuhr final : public uhr
{
public:
    testuhr();
    void stellen(int s, int m);
    virtual void ablesen(int& s, int& m) const override;
private:
    int stunde;
    int minute;
};

#endif

