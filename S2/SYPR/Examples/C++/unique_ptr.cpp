#include <memory>
#include <iostream>

int main()
{
    std::unique_ptr<int> p{new int{1}};
    std::cout << *p << '\n';

    std::unique_ptr<int[]> a{new int[2]};
    a[0] = 10;
    a[1] = 20;

    for (int i = 0; i < 2; ++i) 
    {
        std::cout << a[i] << '\n';
    }
}