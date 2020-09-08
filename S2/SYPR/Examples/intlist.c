#include  <stdio.h>

struct int_list
{
    struct int_list *next; // Verkettung
    int n;
}; 

int main(void)
{
    struct int_list last = {NULL, 10};
    struct int_list first = {&last, 20};

    for (struct int_list *p = &first; p != NULL; p = p->next)
    {
        printf("%d\n", p->n);
    }

    return 0;
}
