#include <stdio.h>

enum month {jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};
typedef enum month month;

int main(void)
{
    // enum month m = 3; // funktioniert bei C, aber nicht bei C++
    month m = mar;

    //---------------------------------------------- print variable value
    printf("m = %d\n", m);

    //-------------------------------------------- print variable address
    printf("&m = %p\n", (void*) &m);

    //----------------------------------------------- print variable size
    printf("sizeof m = %zu\n", sizeof m);

    return 0;
}
