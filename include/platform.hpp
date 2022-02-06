#ifndef MARTIN_PLATFORM
#define MARTIN_PLATFORM

#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__)
#define bits_64
#else
#define bits_32
#endif

#endif