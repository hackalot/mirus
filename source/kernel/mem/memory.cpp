// Copyright 2013 Mirus Project

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
