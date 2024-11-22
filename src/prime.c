#include "prime.h"
#include <math.h>

PrimeType is_prime(const size_t x) {
  if (x < 2) {
    return UNKNOWN;
  }

  if (x == 2 || x == 3) {
    return IS_PRIME;
  }

  if (x % 2 == 0) {
    return NOT_PRIME;
  }

  for (int i = 3; i <= floor(sqrt(x)); i += 2) {
    if (x % i == 0) {
      return NOT_PRIME;
    }
  }

  return IS_PRIME;
}

size_t next_prime(size_t x) {
  while (is_prime(x) != IS_PRIME) {
    x++;
  }

  return x;
}
