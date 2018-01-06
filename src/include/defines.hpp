#ifndef DEFINES_H
#define DEFINES_H

//for some reason g++ does not let me use #elifdef
#if defined(__linux__) || defined(__gnu_linux__)
    #include <gmpxx.h>
    using ulong_t = unsigned long;
    using long_t = long;
#elif defined(_WIN32) || defined(_WIN64)
    #include "mpirxx.h"
    //for some reason windows 64bit long is only 32bits long
    using ulong_t = unsigned long long;
    using long_t = long long;
#else
#error No Big Numbers Lib Defined for your platform
#endif

// #undef BigInt_t
// #define BigInt_t mpz_class
using BigInt_t = mpz_class;

// #undef BigFloat_t
// #define BigFloat_t mpf_class
using BigFloat_t = mpf_class;

// #undef Exponent_t
// #define Exponent_t mp_exp_t
using Exponent_t = mp_exp_t;

// #define SERVER_DEBUGS

#endif // DEFINES_H
