/*
 * benotung.h
 *
 * Definiert eine Benotung mit einer int note
 *
 * Autor: Vlad Bratulescu
 * Erstellt am: 28.06.2020
 */

#ifndef BENOTUNG_H
#define BENOTUNG_H

class benotung final
{
private:
    int note;

public:
    static const benotung beste;
    static const benotung schlechteste;

    benotung() = default;
    explicit benotung(int n);

    int int_value() const;
    bool ist_bestanden() const;

    friend bool operator==(const benotung&, const benotung&);
};

#endif
