/*
 * uhr.h
 *
 * Autor: H.Drachenfels
 * Erstellt am: 29.1.2020
 */

#ifndef UHR_H
#define UHR_H

class uhr // interface
{
public:
    virtual ~uhr() = default;
    virtual void ablesen(int& s, int& m) const = 0;
    /*
     * Interfaces sind nur fuer Entities gedacht.
     * Bei Entities kein copy, nur move.
     */
    uhr(const uhr&) = delete;
    uhr& operator=(const uhr&) = delete;
    uhr(uhr&&) = default;
    uhr& operator=(uhr&&) = default;
protected:
    uhr() = default;
};

#endif

