#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define FIND_VALUE (1297319 - 947848)

int main() {
    uint32_t current_time = time(NULL);
    for (uint32_t seed = current_time; ; seed--) {
         printf("\rSeed: %d", seed);
        srand(seed);
        int rand1 = rand() % 1000000;
        if (rand1 == FIND_VALUE) {
            printf("\nSolved!\n");
            printf("Result: %d\n", seed);
            return;
        }
    }
}
