#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "rsa.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(
            stderr,
            "Usage: %s \"text\"\n",
            argv[0]
        );

        return 1;
    }

    const char *input = argv[1];
    size_t length = strlen(input);

    if (length == 0) {
        fprintf(stderr, "Input string is empty\n");
        return 1;
    }

    uint64_t *encrypted = malloc(
        length * sizeof(uint64_t)
    );

    if (encrypted == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    rsa_encrypt(
        input,
        encrypted,
        length
    );

    printf("Encrypted: ");

    for (size_t i = 0; i < length; i++) {
        printf(
            "%" PRIu64,
            encrypted[i]
        );

        if (i + 1 < length) {
            printf(" ");
        }
    }

    printf("\n");

    free(encrypted);

    return 0;
}