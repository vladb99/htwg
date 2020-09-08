/*
 * shared_ptr_test.cpp
 *
 * Autor: H.Drachenfels
 * Erstellt am: 10.12.2019
 */
#include <iostream> // std::cout
#include <utility>  // std::move
#include "htwg_shared_ptr.h"

int main()
{
    htwg::shared_ptr<int> p{new int{123}}; // use_count = 1
    std::cout << "*p = *"
              << p.get() << '(' << p.use_count() << ") = " << *p << '\n';

    auto q = p; // Copy-Konstruktor: ++use_count
    if (q == p)
    {
        std::cout << "*p = *q = *"
                  << q.get() << '(' << q.use_count() << ") = " << *q << '\n';

        htwg::shared_ptr<int> r;
        if (r != q)
        {
            r = q; // Copy-Zusweisung: ++use_count
            std::cout << "*p = *q = *r = *"
                      << r.get() << '(' << r.use_count() << ") = " << *r
                      << '\n';
        }
    } // Destruktor r: --use_count

    q = q; // Copy-Selbstzuweisung
    std::cout << "*p = *q = *"
              << q.get() << '(' << q.use_count() << ") = " << *q << '\n';

    auto r = std::move(q); // Move-Zuweisung
    if (!q)
    {
        std::cout << "q = " << q.get() << '\n';
    }

    if (r)
    {
        std::cout << "*p = *r = *"
                  << r.get() << '(' << r.use_count() << ") = " << *r << '\n';
    }
}
// Destruktor r: --use_count, Destruktor q, Destruktor p: --use_count -> delete

