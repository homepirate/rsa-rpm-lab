#ifndef RSA_H
#define RSA_H

#include <stddef.h>
#include <stdint.h>

void rsa_encrypt(
    const char *input,
    uint64_t *output,
    size_t length
);

void rsa_decrypt(
    const uint64_t *input,
    size_t length,
    char *output
);

#endif