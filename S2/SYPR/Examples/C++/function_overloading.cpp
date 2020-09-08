#include <iostream>

int max(int, int);
double max(double, double);
extern "C" int max(int, int, int);
//extern "C" double max(double, double, double); // Namenskonflikt

int main()
{
    std::cout << max(1, 2) << '\n';
    //std::cout << max(1, 2.3) << '\n'; // mehrdeutig
    std::cout << max(static_cast<double>(1), 2.3) << '\n';
    std::cout << max(1, 2, 3) << '\n';
}

int max(int a, int b)
{
    return a > b ? a : b;
}

double max(double a, double b)
{
    return a > b ? a : b;
}

int max(int a, int b, int c)
{
    return max(a, max(b, c));
}