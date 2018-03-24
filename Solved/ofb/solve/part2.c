#include <stdio.h>
#include <stdint.h>

#define FIRST_RESULT         (1320590709)
#define SECOND_RESULT        (2225636917)

#define DIFFERENCE (2445943554 - 2225636917) // a-coefficient

// bruteforce coefficient of a
int main() {
    uint64_t val;
    for (uint64_t a = 0; a < (1LL<<32); a++) {
        printf("\r%llu", a);
        val = (FIRST_RESULT + a * DIFFERENCE) & 0xFFFFFFFF;
        if (val == SECOND_RESULT) {
            printf("\n\nSolved\n");
            printf("a = %llu\n\n", a);
        }
    }
    printf("Done");
    return 0;
}
