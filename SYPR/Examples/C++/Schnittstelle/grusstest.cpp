#include "gruss.h"
#include "systemuhr.h"
#include "testuhr.h"
#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        systemuhr s;
        gruss g(&s);

        std::cout << g.gruessen() << std::endl;
        // systemuhr ss = s; // kein Copy-Konstruktor

        testuhr t; // Mock-Objekt
        gruss h(&t);

        int stunde, minute;
        while (std::cin >> stunde >> minute)
        {
            t.stellen(stunde, minute);
            std::cout << h.gruessen() << std::endl;
        }

        //testuhr tt;
        // tt = t; // kein operator=
    }
    catch (const std::exception &x)
    {
        std::cerr << x.what() << std::endl;
    }
    catch (std::string &s)
    {
        std::cerr << s << std::endl;
    }
}
