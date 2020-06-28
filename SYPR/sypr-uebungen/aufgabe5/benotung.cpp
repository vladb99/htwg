#include "benotung.h"
#include <stdexcept>
#include <string>

const benotung benotung::beste = benotung(10);
const benotung benotung::schlechteste = benotung(50);

benotung::benotung(int n)
: note(n)
{
    std::string msg = std::string("unzulaessige Note ") + std::to_string(n);
    if (!((n >= 10 && n <= 40 && (n % 10 == 0 || n % 10 == 3 || n % 10 == 7)) || n == 50))
    {
        throw std::invalid_argument(msg);
    }
}

int benotung::int_value() const
{
    return this->note;
}

bool benotung::ist_bestanden() const
{
    return this->note <= 40;
}

bool operator==(const benotung& lhs, const benotung& rhs)
{
    return &lhs == &rhs || lhs.note == rhs.note;
}
