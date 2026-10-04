#include "rsa.h"
#include "rsa_key.h"

/*
 * Простое возведение в степень по модулю.
 *
 * Вычисляет:
 *
 *     base^exponent mod modulus
 *
 * Реализация специально неоптимизированная:
 * умножение выполняется exponent раз.
 */
static uint64_t simple_mod_pow(
    uint64_t base,
    uint64_t exponent,
    uint64_t modulus
)
{
    uint64_t result = 1;

    for (uint64_t i = 0; i < exponent; i++) {
        result = (result * base) % modulus;
    }

    return result;
}

void rsa_encrypt(
    const char *input,
    uint64_t *output,
    size_t length
)
{
    for (size_t i = 0; i < length; i++) {
        uint64_t message = (unsigned char)input[i];

        output[i] = simple_mod_pow(
            message,
            RSA_E,
            RSA_N
        );
    }
}

void rsa_decrypt(
    const uint64_t *input,
    size_t length,
    char *output
)
{
    /*
     * TODO:
     * Дешифрование будет реализовано позже.
     *
     * Для расшифрования будет использоваться:
     *
     *     message = encrypted^RSA_D mod RSA_N
     */

    (void)input;
    (void)length;
    (void)output;
}