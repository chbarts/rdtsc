#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rdtsc.h"

typedef unsigned long long int ull;

int main(int argc, char *argv[])
{
    uint64_t beg, end, r = 0;
    int i;

    beg = rdtsc();
    for (i = 1; i < argc; i++)
        r += strtoll(argv[i], NULL, 0);
    end = rdtsc();

    printf("beg = %llu end = %llu diff = %llu tot = %llu\n", (ull) beg,
           (ull) end, (ull) (end - beg), (ull) r);

    return 0;
}
