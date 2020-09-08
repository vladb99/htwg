#include  <stdio.h>

enum int_or_string {type_int, type_string};

struct struct_with_union
{
    enum int_or_string u_type;

    union
    {
        int i;
        char *s;
    };
};

int main(void)
{
    struct struct_with_union x;

    //-------------------------------------------- print variable value
    x.u_type = type_int;
    x.i = 1;
    printf("%d: %d\n", x.u_type, x.i);

    x.u_type = type_string;
    x.s = "Hallo";
    printf("%d: %s\n", x.u_type, x.s);

    //------------------------------------------ print variable address
    printf("&x = %p\n", (void*) &x);
    printf("&x.u_type = %p\n", (void*) &x.u_type);
    printf("&x.i = %p\n", (void*) &x.i);
    printf("&x.s = %p\n", (void*) &x.s);

    //--------------------------------------------- print variable size
    printf("sizeof d = %zu\n", sizeof x);

    return 0;
}
