#include "fachnote.h"

fachnote::fachnote(const std::string &f, const benotung &b)
: fach(f), note(b)
{ 
    if (f.empty())
    {
        throw std::invalid_argument("unzulaessiges Fach");
    }
}