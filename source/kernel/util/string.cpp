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

    void itoa (char *buf, int base, int d)
     {
       char *p = buf;
       char *p1, *p2;
       unsigned long ud = d;
       int divisor = 10;
     
       /* If %d is specified and D is minus, put `-' in the head. */
       if (base == 'd' && d < 0)
         {
           *p++ = '-';
           buf++;
           ud = -d;
         }
       else if (base == 'x')
         divisor = 16;
     
       /* Divide UD by DIVISOR until UD == 0. */
       do
         {
           int remainder = ud % divisor;
     
           *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
         }
       while (ud /= divisor);
     
       /* Terminate BUF. */
       *p = 0;
     
       /* Reverse BUF. */
       p1 = buf;
       p2 = p - 1;
       while (p1 < p2)
         {
           char tmp = *p1;
           *p1 = *p2;
           *p2 = tmp;
           p1++;
           p2--;
         }
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