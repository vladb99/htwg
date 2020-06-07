#include "datum.h"
#include <utility>

int main()
{
    std::cout << "Welches Datum ist heute [jjjj-mm-tt]? ";

    datum d;
    std::cin >> d;
    if (!std::cin)
    {
        std::cerr << "Eingabefehler!\n";
        return 1;
    }

    datum heute = datum::heute();
    if (d == heute) 
    {
        std::cout << "Richtig, " << d << " ist das heutige Datum!\n";
    }
    else
    {
        std::cout << "Falsch, "
                  << heute << " ist das heutige Datum, nicht " << d << "!\n";
    }   
}