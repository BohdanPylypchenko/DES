#include "byte.h"

#include <malloc.h>

#include <stdio.h>

int main() {
    int a[4] = {1, 2, 3, 4};

    int temp;
    for (int i = 0; i < 2; i++) {
        temp = a[i];
        a[i] = a[3 - i];
        a[3 - i] = temp;
    }

    for (int i = 0; i < 4; i++) {
        printf("%i ", a[i]);
    }
    printf("\n");

    return 0;
}
