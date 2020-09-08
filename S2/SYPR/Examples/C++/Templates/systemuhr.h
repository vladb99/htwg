/*
 * systemuhr.h
 *
 * Autor: H.Drachenfels
 * Erstellt am: 18.11.2019
 */

#ifndef SYSTEMUHR_H
#define SYSTEMUHR_H

class systemuhr final
{
public:
    systemuhr() = default;
    void ablesen(int& s, int& m) const;
    // entity: kein copy und move
    systemuhr(const systemuhr&) = delete;
    systemuhr& operator=(const systemuhr&) = delete;
    systemuhr(systemuhr&&) = delete;
    systemuhr& operator=(systemuhr&&) = delete;
};

#endif

