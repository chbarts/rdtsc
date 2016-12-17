#ifndef RDTSC_H
#define RDTSC_H

#include <stdint.h>

#if defined(__i386__)

static __inline__ uint64_t rdtsc(void)
{
   uint64_t x;
   __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
   return x;
}

#elif defined(__x86_64__)

static __inline__ uint64_t rdtsc(void)
{
   uint32_t hi, lo;
   __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
   return (((uint64_t) hi) << 32) | ((uint64_t) lo);
}

#elif defined(__powerpc__)

static __inline__ uint64_t rdtsc(void)
{
   uint64_t result = 0;
   uint32_t upper, lower, tmp;
   __asm__ volatile(
      "0:\n"
      "\tmftbu %0\n"
      "\tmftb  %1\n"
      "\tmftbu %2\n"
      "\tcmpw  %2,%0\n"
      "\tbne   0b\n"
      : "=r" (upper), "=r" (lower), "=r" (tmp));
   result = upper;
   result <<= 32;
   result |= lower;

   return result;
}

#elif (defined(__ARM_ARCH) && (__ARM_ARCH >= 6))

static __inline__ uint64_t rdtsc(void)
{
   uint64_t result = 0;
   uint32_t pmccntr, pmuseren, pmcntenset;
   asm __volatile__ ("mrc p15, 0, %0, c9, c14, 0" : "=r" (pmuseren));

   if (pmuseren & 1) {
      asm __volatile__ ("mrc p15, 0, %0, c9, c12, 1" : "=r" (pmcntenset));

      if (pmcntenset & 0x80000000ul) {
         asm __volatile__ ("mrc p15, 0, %0, c9, c13, 0" : "=r" (pmccntr));

         result = ((uint64_t) pmccntr) * 64;
      }
   }

   return result;
}

#endif

#endif /* RDTSC_H */
