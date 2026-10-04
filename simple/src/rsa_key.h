#ifndef RSA_KEY_H
#define RSA_KEY_H

#include <stdint.h>

/*
 * Учебный RSA-ключ.
 *
 * p = 61
 * q = 53
 *
 * n = p * q = 3233
 * phi(n) = (p - 1) * (q - 1) = 3120
 *
 * Public key:
 *     (e, n) = (17, 3233)
 *
 * Private key:
 *     (d, n) = (2753, 3233)
 */

#define RSA_N 3233ULL
#define RSA_E 17ULL
#define RSA_D 2753ULL

#endif