/*
 * testuhr.h
 *
 * Autor: H.Drachenfels
 * Erstellt am: 18.11.2019
 */

#ifndef TESTUHR_H
#define TESTUHR_H

class testuhr final
{
public:
    testuhr();
    void stellen(int s, int m);
    void ablesen(int& s, int& m) const;
    // entity: kein copy und move
    testuhr(const testuhr&) = delete;
    testuhr& operator=(const testuhr&) = delete;
    testuhr(testuhr&&) = delete;
    testuhr& operator=(testuhr&&) = delete;
private:
    int stunde;
    int minute;
};

#endif

