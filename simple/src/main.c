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


static int parse_encrypted_data(
    const char *input,
    uint64_t **output,
    size_t *length
)
{
    char *copy = malloc(strlen(input) + 1);

    if (copy == NULL) {
        return -1;
    }

    strcpy(copy, input);

    size_t capacity = 8;
    size_t count = 0;

    uint64_t *numbers = malloc(
        capacity * sizeof(uint64_t)
    );

    if (numbers == NULL) {
        free(copy);
        return -1;
    }

    char *token = strtok(copy, " ");

    while (token != NULL) {

        if (count >= capacity) {
            capacity *= 2;

            uint64_t *tmp = realloc(
                numbers,
                capacity * sizeof(uint64_t)
            );

            if (tmp == NULL) {
                free(numbers);
                free(copy);
                return -1;
            }

            numbers = tmp;
        }

        char *end = NULL;

        uint64_t value = strtoull(
            token,
            &end,
            10
        );

        if (*token == '\0' || *end != '\0') {
            free(numbers);
            free(copy);
            return -1;
        }

        numbers[count] = value;
        count++;

        token = strtok(NULL, " ");
    }

    free(copy);

    if (count == 0) {
        free(numbers);
        return -1;
    }

    *output = numbers;
    *length = count;

    return 0;
}


static void encrypt_text(const char *input)
{
    size_t length = strlen(input);

    uint64_t *encrypted = malloc(
        length * sizeof(uint64_t)
    );

    if (encrypted == NULL) {
        fprintf(
            stderr,
            "Memory allocation error\n"
        );

        return;
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


static void decrypt_text(const char *input)
{
    uint64_t *encrypted = NULL;
    size_t length = 0;

    if (parse_encrypted_data(
            input,
            &encrypted,
            &length
        ) != 0) {

        fprintf(
            stderr,
            "Invalid encrypted data\n"
        );

        return;
    }

    char *decrypted = malloc(length + 1);

    if (decrypted == NULL) {
        fprintf(
            stderr,
            "Memory allocation error\n"
        );

        free(encrypted);
        return;
    }

    rsa_decrypt(
        encrypted,
        length,
        decrypted
    );

    decrypted[length] = '\0';

    printf(
        "Decrypted: %s\n",
        decrypted
    );

    free(encrypted);
    free(decrypted);
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
        fprintf(
            stderr,
            "Input string is empty\n"
        );

        return 1;
    }

    if (mode == MODE_ENCRYPT) {
        encrypt_text(input);
    }

    if (mode == MODE_DECRYPT) {
        decrypt_text(input);
    }

    return 0;
}