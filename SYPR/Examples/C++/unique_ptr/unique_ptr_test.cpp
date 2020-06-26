#include <iostream>
#include <utility>
#include "htwg_unique_ptr.h"

int main()
{
    htwg::unique_ptr<int> p{new int{123}};
    std::cout << "*p = *" << p.get() << " = " << *p << '\n';

    //auto q = p; // copy unsupported
    auto q = std::move(p);
    std::cout << "*q = *" << q.get() << " = " << *q << '\n';

    htwg::unique_ptr<int> r;
    if (r != q)
    {
        //r = q; // copy unsupported
        r = std::move(q);
        std::cout << "*r = *" << r.get() << " = " << *r << '\n';
    }

    r = std::move(r);

    if (!p)
    {
        std::cout << "p = " << p.get() << '\n';
    }

    if (q == p)
    {
        std::cout << "q = " << q.get() << '\n';
    }

    if (r)
    {
        std::cout << "*r = *" << r.get() << " = " << *r << '\n';
    }
}