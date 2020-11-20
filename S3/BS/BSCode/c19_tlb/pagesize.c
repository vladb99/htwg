#include <unistd.h>
#include <stdio.h>

int main() {
    printf("Before array: Pagesize: %d\n", getpagesize());

    int array[1000];
    for (int i = 0;i < 1000 ; i++) {
        array[i] = 0;
    }

    printf("After array: Pagesize: %d\n", getpagesize());
    return 0;
}