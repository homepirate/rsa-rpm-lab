#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "rsa.h"

typedef enum {
    MODE_ENCRYPT,
    MODE_DECRYPT
} rsa_mode;

static int parse_mode(
    const char *flag,
    rsa_mode *mode
)
{
    if (strcmp(flag, "-e") == 0) {
        *mode = MODE_ENCRYPT;
        return 0;
    }

    if (strcmp(flag, "-d") == 0) {
        *mode = MODE_DECRYPT;
        return 0;
    }

    return -1;
}

static void print_usage(const char *program)
{
    fprintf(
        stderr,
        "Usage:\n"
        "  %s -e \"text\"\n"
        "  %s -d \"encrypted data\"\n",
        program,
        program
    );
}

int main(int argc, char *argv[])
{
    rsa_mode mode;

    if (argc != 3) {
        print_usage(argv[0]);
        return 1;
    }

    if (parse_mode(argv[1], &mode) != 0) {
        fprintf(
            stderr,
            "Unknown mode: %s\n",
            argv[1]
        );

        print_usage(argv[0]);
        return 1;
    }

    const char *input = argv[2];

    if (strlen(input) == 0) {
        fprintf(stderr, "Input string is empty\n");
        return 1;
    }

    if (mode == MODE_ENCRYPT) {
        size_t length = strlen(input);

        uint64_t *encrypted = malloc(
            length * sizeof(uint64_t)
        );

        if (encrypted == NULL) {
            fprintf(
                stderr,
                "Memory allocation error\n"
            );

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
    }

    if (mode == MODE_DECRYPT) {
        printf("Decryption is not implemented yet\n");
    }

    return 0;
}