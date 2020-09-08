/*
 * intlist.cpp
 *
 * Beispielprogramm eingebettete Klassen.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 14.3.2019
 */
#include "intlist.h"

//----------------------------------------------------- Klasse intlist::element
class intlist::element final
{
    element *next;
    int n;

    element(element *e, int m)
    : next(e), n(m)
    { }

    friend class intlist;
    friend class intlist::iterator;
};

//----------------------------------------- Member-Funktionen intlist::iterator
intlist::iterator::iterator(element *e)
: current(e)
{ }

bool intlist::iterator::operator!=(const iterator& i) const
{
    return this->current != i.current;
}

int& intlist::iterator::operator*() const
{
    return this->current->n;
}

intlist::iterator& intlist::iterator::operator++()
{
    this->current = this->current->next;
    return *this;
}

//--------------------------------------------------- Member-Funktionen intlist
intlist::intlist()
: head(nullptr)
{ }

intlist::~intlist()
{
    element *e = this->head;
    while (e != nullptr)
    {
        element *x = e;
        e = e->next;
        delete x;
    }
}

intlist& intlist::insert(int n)
{
    this->head = new element(this->head, n);
    return *this;
}

intlist::iterator intlist::begin()
{
    return intlist::iterator(this->head);
}

intlist::iterator intlist::end()
{
    return intlist::iterator(nullptr);
}
