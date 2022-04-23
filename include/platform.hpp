#ifndef MARTIN_PLATFORM
#define MARTIN_PLATFORM

#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__)
#define bits_64
#else
#define bits_32
#endif

#if defined(__i386__) || defined(_X86_) || defined(__x86_64__) || defined(_M_AMD64)
#define cpu_x86
#endif

#if defined(_WIN32) || defined(WIN32)
#define windows
#else
#define unix
#endif

#endif