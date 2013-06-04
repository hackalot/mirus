#ifndef _MIRUS_KERNEL_MEMORY_H_
#define _MIRUS_KERNEL_MEMORY_H_

namespace mirus {
    // memcpy
    unsigned char* memcpy(unsigned char* dest, const unsigned char* src, int count);
    unsigned short* memcpy(unsigned short* dest, const unsigned short* src, int count);
    unsigned int* memcpy(unsigned int* dest, const unsigned int* src, int count);

    // memset
    unsigned char* memset(unsigned char* dest, unsigned char val, int count);

    // memsetw
    unsigned short* memsetw(unsigned short* dest, unsigned short val, int count);
}

#endif