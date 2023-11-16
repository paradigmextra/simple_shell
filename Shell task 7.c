#include "main.h"

/**
 * Custom implementation of strlen
 * @input: The string to be calculated
 * Return: The length of the string
 */
size_t gb_strlen(const char *input) {
    size_t len = 0;

    if (!input) {
        return 0;
    }

    while (*input++) {
        len++;
    }

    return len;
}
