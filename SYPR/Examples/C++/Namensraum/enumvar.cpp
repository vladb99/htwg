//
// enumvar.cpp
//
// Beispiel-Programm enum-Variable
//
// Autor: H.Drachenfels
// Erstellt am: 19.12.2006
//

#include "month.h" // htwg::Month, htwg::oct, ...
using namespace htwg;

#include <iostream> // std::cout, std::oct, ...
using namespace std;

int main ()
{
  Month aMonth = htwg::oct; // Month eindeutig htwg::Month, oct mehrdeutig

  //---------------------------------------------------- print variable value
  cout << "aMonth = " << aMonth << '\n'; // cout eindeutig std::cout

  //-------------------------------------------------- print variable address
  cout << "&aMonth = " << &aMonth << '\n';

  //----------------------------------------------------- print variable size
  cout << "sizeof aMonth = " << sizeof aMonth << '\n';
}

