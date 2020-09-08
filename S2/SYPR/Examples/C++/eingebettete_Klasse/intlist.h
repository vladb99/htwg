/*
 * intlist.h
 *
 * Beispielprogramm eingebettete Klassen.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 29.1.2020
 */
#ifndef INTLIST_H
#define INTLIST_H

class intlist final
{
    // Entity-Klasse ohne Kopier- und Move-Semantik
    intlist(intlist&) = delete;
    intlist& operator=(intlist&) = delete;
    intlist(intlist&&) = delete;
    intlist& operator=(intlist&&) = delete;

private:
    class element;
    element *head;

public:
    intlist();
    ~intlist();
    intlist& insert(int);

    class iterator final
    {
    private:
        element *current;
        explicit iterator(element*);
    public:
        bool operator!=(const iterator&) const;
        int& operator*() const;
        iterator& operator++();

        friend class intlist;
    };

    iterator begin();
    iterator end();
};

#endif
