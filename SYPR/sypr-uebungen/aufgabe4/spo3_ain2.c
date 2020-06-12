//doc

#include "spo3_ain2.h";

bool ist_spo_note(int n)
{
     if (!((n >= 10 && n <= 40 && (n % 10 == 0 || n % 10 == 3 || n % 10 == 7)) || n == 50)) 
        {
            return false;
        }
        return true;
}