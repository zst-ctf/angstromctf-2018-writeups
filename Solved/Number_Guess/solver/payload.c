#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define OFFSET (1521353782 - 1521353773)

int main(int argc, char **argv) {
    uint32_t seed = time(NULL) - OFFSET;
    srand(seed);
    int rand1 = rand() % 1000000;
    int rand2 = rand() % 1000000;
    int sum = rand1 + rand2;
    printf("%%3$d Seed of %d\n", seed);
    printf("%d\n", sum);
    return 0;
}