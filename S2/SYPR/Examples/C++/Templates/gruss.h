/*
 * gruss.h
 *
 * Autor: H.Drachenfels
 * Erstellt am: 18.11.2019
 */

#ifndef GRUSS_H
#define GRUSS_H

#include <string>

template<typename T>
class gruss final
{
public:
    gruss() = default;
    T uhrzeit;
    std::string gruessen();
    // entity: kein copy und move
    gruss(const gruss&) = delete;
    gruss& operator=(const gruss&) = delete;
    gruss(gruss&&) = delete;
    gruss& operator=(gruss&&) = delete;
};

template<typename T>
std::string gruss<T>::gruessen()
{
    int stunde;
    int minute;

    this->uhrzeit.ablesen(stunde, minute);

    if (6 <= stunde && stunde < 11)
    {
        return "Guten Morgen";
    }

    if (11 <= stunde && stunde < 18)
    {
        return "Guten Tag";
    }

    if (18 <= stunde && stunde <= 23)
    {
        return "Guten Abend";
    }

    throw std::string("Nachtruhe!");
}

#endif

