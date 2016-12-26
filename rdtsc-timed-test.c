#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rdtsc.h"

typedef unsigned long long int ull;

int main(int argc, char *argv[])
{
    long double avg = 0;
    uint64_t num, beg, end, tot = 0, r = 0, b, e, j;
    int i;

    if (1 == argc) {
        puts("usage: rdtsc-timed-test trials [nums...]");
        puts("repeat the process of summing [nums...] trials times");
        return 0;
    }

    num = strtoll(argv[1], NULL, 0);

    beg = rdtsc();
    for (j = 0; j < num; j++) {
        b = rdtsc();
        for (i = 2; i < argc; i++)
            r += strtoll(argv[i], NULL, 0);
        e = rdtsc();
        tot += (e - b);
    }

    end = rdtsc();

    if (num > 0)
        avg = ((long double) tot) / ((long double) num);

    printf
        ("beg = %llu end = %llu diff = %llu tot = %llu avg = %.*Lg sum = %llu\n",
         (ull) beg, (ull) end, (ull) (end - beg), (ull) tot, LDBL_DIG, avg,
         (ull) r);

    return 0;
}
