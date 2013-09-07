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

//
// string.cpp - string utils
//

#include <stdafx.hpp>
#include <util/string.hpp>

namespace mirus
{
    size_t strlen(const char *str)
    {
        size_t ret = 0;

        while (str[ret] != 0)
            ret++;

        return ret;
    }

    char *iota(int value)
    {
        char *rc = 0;
        char *ptr = 0;
        char *low = 0;

        rc = ptr;

        // Set '-' for negative decimals.
        if (value < 0)
            *ptr++ = '-';

        // Remember where the numbers start.
        low = ptr;

        // The actual conversion.
        do
        {
            // Modulo is negative for negative value. This trick makes abs() unnecessary.
            *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % 10];
            value /= 10;
        }
        while (value);

        // Terminating the string.
        *ptr-- = '\0';

        // Invert the numbers.
        while (low < ptr)
        {
            char tmp = *low;
            *low++ = *ptr;
            *ptr-- = tmp;
        }

        return rc;
    }

    char *strpad(char *data, int padlen)
    {
        unsigned long long int datalen = strlen(data);
        int subtotal = padlen - datalen;
        char *ret = data;

        for (int i = 0; i < subtotal; i++)
            ret += ' ';

        return ret;
    }

    char* strcat(char *dest, const char *src)
    {
        char *rdest = dest;

        while (*dest)
            dest++;

        while ((*dest++ = *src++));
    
        return rdest;
    }
} // !namespace