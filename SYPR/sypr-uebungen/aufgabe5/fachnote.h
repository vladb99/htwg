/*
 * fachnote.h
 *
 * Definiert eine Fachnote mit einem Fachnamen und 
 * einer Variable note vom Typ Benotung
 *
 * Autor: Vlad Bratulescu
 * Erstellt am: 28.06.2020
 */

#ifndef FACHNOTE_H
#define FACHNOTE_H

#include "benotung.h"
#include <string>

class fachnote final
{
public:
    const std::string fach;
    const benotung note;

    fachnote(const std::string&, const benotung&);

    fachnote(const fachnote&) = delete;
    fachnote& operator=(const fachnote&) = delete;
    fachnote(fachnote&&) = default;
    fachnote& operator=(fachnote&&) = default;
};

#endif
