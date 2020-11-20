#include <unistd.h>
#include <stdio.h>

int main() {
    printf("Pagesize: %d", getpagesize());

    int array[1000];
    for (int i = 0;i < 1000 ; i++) {
        array[i] = 0;
    }

    printf("Pagesize: %d", getpagesize());
    return 0;
}