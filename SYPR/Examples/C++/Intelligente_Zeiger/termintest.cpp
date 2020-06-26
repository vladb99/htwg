/*
 * termintest.cpp
 *
 * Beispielprogramm Klasse.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 2.8.2019
 */
#include "termin.h"
#include <list>
#include <iostream>

int main()
{
    std::list<std::shared_ptr<termin>> pruefer_kalender;
    std::list<std::shared_ptr<termin>> kandidaten_kalender;
    std::shared_ptr<termin> pruefung
        = termin::new_instance(datum::heute(), "Pruefung Systemprogrammierung");

    pruefer_kalender.push_back(pruefung);    // Referenzzaehler = 2
    kandidaten_kalender.push_back(pruefung); // Referenzzaehler = 3
    pruefung->verschieben({1, 4, 2040});     // Aufruf operator->()

    for (auto t : pruefer_kalender)
    {
        std::cout << "Pruefer: "
                  << t->get_datum()
                  << ", "
                  << t->get_beschreibung()
                  << std::endl;
    }

    for (auto t : kandidaten_kalender)
    {
        std::cout << "Kandidat: "
                  << t->get_datum()
                  << ", "
                  << t->get_beschreibung()
                  << std::endl;
    }
} // Destruktoren dekrementieren Referenzzaehler von pruefung

