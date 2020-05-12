#include <stdio.h>

int main(void)
{
    int a[] = {3421, 3442, 3635, 3814};
    const int n = (int)(sizeof a / sizeof(int));

    printf("a = %p\n", (void*)a);
    for (int i = 0; i < n; ++i) {
        printf("%d: %p %d\n", i, (void*) &a[i], a[i]);
    }

    printf("sizeof a = %zu\n", sizeof a);
    return 0;
}