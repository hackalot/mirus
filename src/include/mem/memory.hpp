// Copyright (c) 2013 Joshua Beitler, Mirus contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef _MIRUS_KERNEL_MEMORY_H_
#define _MIRUS_KERNEL_MEMORY_H_

#include <stddef.h>
#include <stdint.h>

namespace mirus {
    // memcpy
    unsigned char* memcpy(unsigned char* dest, const unsigned char* src, int count);
    unsigned short* memcpy(unsigned short* dest, const unsigned short* src, int count);
    unsigned int* memcpy(unsigned int* dest, const unsigned int* src, int count);

    // memset
    unsigned char* memset(unsigned char* dest, unsigned char val, int count);
    unsigned int* memset(unsigned int* dest, unsigned int val, int count);
    void memseti(uint8_t *dest, uint8_t val, uint32_t len);
    void memsetb(unsigned int* dest, uint8_t val, int count);

    // memsetw
    unsigned short* memsetw(unsigned short* dest, unsigned short val, int count);
}

#endif