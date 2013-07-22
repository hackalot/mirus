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

#include <mem/memory.hpp>

unsigned char *mirus::memcpy(unsigned char *dest, const unsigned char *src, int count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;

    for (; count != 0; count--)
    { *dp++ = *sp++; }

    return dest;
}

unsigned short *mirus::memcpy(unsigned short *dest, const unsigned short *src, int count)
{
    const short *sp = (const short *)src;
    short *dp = (short *)dest;

    for (; count != 0; count--)
    { *dp++ = *sp++; }

    return dest;
}

unsigned int *mirus::memcpy(unsigned int *dest, const unsigned int *src, int count)
{
    const int *sp = (const int *)src;
    int *dp = (int *)dest;

    for (; count != 0; count--)
    { *dp++ = *sp++; }

    return dest;
}

unsigned char *mirus::memset(unsigned char *dest, unsigned char val, int count)
{
    char *temp = (char *)dest;

    for (; count != 0; count--)
    { *temp++ = val; }

    return dest;
}

unsigned int *mirus::memset(unsigned int *dest, unsigned int val, int count)
{
    int *temp = (int *)dest;

    for (; count != 0; count--)
    { *temp++ = val; }

    return dest;
}

unsigned short *mirus::memsetw(unsigned short *dest, unsigned short val, int count)
{
    unsigned short *temp = (unsigned short *)dest;

    for ( ; count != 0; count--)
    { *temp++ = val; }

    return dest;
}

void memsetb(unsigned int *dest, uint32_t val, int count)
{
    for ( ; count != 0; count--) { *dest++ = val; }
}
