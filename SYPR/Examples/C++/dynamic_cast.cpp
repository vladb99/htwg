/*
 * dynamic_cast.cpp
 *
 * Zeigt die Benutzung von dynamic_cast<>.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 10.3.2019
 */
#include <iostream>

class A
{
public:
    virtual ~A() { }
};

class B
{
public:
    virtual ~B() { }
};

class C : public A, public B { };

int main()
{
    // Upcast von Unterklasse C nach Oberklasse A:
    A *a = new C();

    // Crosscast von Oberklasse A nach Oberklasse B:
    B *b = dynamic_cast<B*>(a);
    if (!b)
    {
        std::cerr << "a ist kein B\n";
    }

    // Downcast von Oberklasse B nach Unterklasse C:
    C *c = dynamic_cast<C*>(b);
    if (!c)
    {
        std::cerr << "b ist kein C\n";
    }
}

