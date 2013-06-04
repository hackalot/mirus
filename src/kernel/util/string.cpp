#include <util/string.hpp>

size_t strlen(const char* str) {
    size_t ret = 0;

    while (str[ret] != 0) {
        ret++;
    }

    return ret;
}

char* iota(int value) {
    char* rc = nullptr;
    char* ptr = nullptr;
    char* low = nullptr;

    rc = ptr;

    // Set '-' for negative decimals.
    if ( value < 0) {
        *ptr++ = '-';
    }

    // Remember where the numbers start.
    low = ptr;

    // The actual conversion.
    do {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % 10];
        value /= 10;
    } while (value);

    // Terminating the string.
    *ptr-- = '\0';

    // Invert the numbers.
    while (low < ptr) {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }

    return rc;
}