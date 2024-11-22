#ifndef PRIME_H
#define PRIME_H

#include <stddef.h>

typedef enum { IS_PRIME, NOT_PRIME, UNKNOWN } PrimeType;

PrimeType is_prime(const size_t x);
size_t next_prime(size_t x);

#endif // !PRIME_H
