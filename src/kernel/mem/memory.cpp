#include <mem/memory.hpp>

unsigned char* mirus::memcpy(unsigned char* dest, const unsigned char* src, int count) {
    const char* sp = (const char *)src;
    char* dp = (char *)dest;

    for(; count != 0; count--)
        *dp++ = *sp++;

    return dest;
}

unsigned short* mirus::memcpy(unsigned short* dest, const unsigned short* src, int count) {
    const short* sp = (const short *)src;
    short* dp = (short *)dest;

    for(; count != 0; count--)
        *dp++ = *sp++;

    return dest;
}

unsigned int* mirus::memcpy(unsigned int* dest, const unsigned int* src, int count) {
    const int* sp = (const int *)src;
    int* dp = (int *)dest;

    for(; count != 0; count--)
        *dp++ = *sp++;

    return dest;
}

unsigned char* mirus::memset(unsigned char* dest, unsigned char val, int count) {
    char* temp = (char *)dest;

    for(; count != 0; count--)
        *temp++ = val;

    return dest;
}

unsigned int* mirus::memset(unsigned int* dest, unsigned int val, int count) {
    int* temp = (int *)dest;

    for(; count != 0; count--)
        *temp++ = val;

    return dest;
}

unsigned short* mirus::memsetw(unsigned short* dest, unsigned short val, int count)
{
    unsigned short* temp = (unsigned short *)dest;

    for( ; count != 0; count--)
        *temp++ = val;

    return dest;
}