/*
 * fachnote.cpp
 *
 * Implementiert die Fachnote
 *
 * Autor: Vlad Bratulescu
 * Erstellt am: 28.06.2020
 */

#include "fachnote.h"
#include <stdexcept>

fachnote::fachnote(const std::string &f, const benotung &b)
: fach(f), note(b)
{ 
    if (f.empty())
    {
        throw std::invalid_argument("unzulaessiges Fach");
    }
}