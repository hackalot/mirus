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
// printf.cpp - printf and formatting
//

#include <stdafx.hpp>
#include <util/printf.hpp>
#include <hardware/serial.hpp>

namespace mirus
{
    //
    // Print a decimal number
    //
    void print_dec(unsigned int value, 
        unsigned int width, 
        char* buf, 
        int* ptr) 
    {
        unsigned int n_width = 1;
        unsigned int i = 9;
        
        while (value > i && i < UINT32_MAX)
        {
            n_width += 1;
            i *= 10;
            i += 9;
        }

        int printed = 0;
        
        while (n_width + printed < width) 
        {
            buf[*ptr] = '0';
            *ptr += 1;
            printed += 1;
        }

        i = n_width;
        
        while (i > 0)
        {
            unsigned int n = value / 10;
            int r = value % 10;
            buf[*ptr + i - 1] = r + '0';
            i--;
            value = n;
        }

        *ptr += n_width;
    }

    //
    // Print a hexadecimal number
    //
    void print_hex(unsigned int value, 
        unsigned int width, 
        char* buf, 
        int* ptr) 
    {
        int i = width;

        if (i == 0) 
            i = 8;

        unsigned int n_width = 1;
        unsigned int j = 0x0F;
        
        while (value > j && j < UINT32_MAX) 
        {
            n_width += 1;
            j *= 0x10;
            j += 0x0F;
        }

        while (i > (int)n_width) 
        {
            buf[*ptr] = '0';
            *ptr += 1;
            i--;
        }

        i = (int)n_width;
        
        while (i-- > 0) 
        {
            buf[*ptr] = "0123456789abcdef"[(value>>(i*4))&0xF];
            *ptr += + 1;
        }
    }

    //
    // Format a string for printing
    //
    size_t vasprintf(char* buf, 
        const char* fmt, 
        va_list args) 
    {
        char *s;
        int ptr = 0;
        int len = strlen(fmt);
            
        for (int i = 0; i < len && fmt[i]; ++i) 
        {
            if (fmt[i] != '%') 
            {
                buf[ptr++] = fmt[i];
                continue;
            }

            ++i;
            unsigned int arg_width = 0;
                
            while (fmt[i] >= '0' && fmt[i] <= '9') 
            {
                arg_width *= 10;
                arg_width += fmt[i] - '0';
                ++i;
            }

            switch (fmt[i]) 
            {
                // string
                case 's':
                    s = (char *)va_arg(args, char *);
                    while (*s)
                        buf[ptr++] = *s++;
                    break;

                // char
                case 'c':
                    buf[ptr++] = (char)va_arg(args, int);
                    break;

                // hex
                case 'x':
                    print_hex((unsigned long)va_arg(args, unsigned long), 
                        arg_width, 
                        buf, 
                        &ptr);
                    break;

                // decimal
                case 'd':
                    print_dec((unsigned long)va_arg(args, unsigned long), 
                        arg_width, 
                        buf, 
                        &ptr);
                    break;

                // escape
                case '%':
                    buf[ptr++] = '%';
                    break;

                default:
                    buf[ptr++] = fmt[i];
                    break;
            }
        }
            /* Ensure the buffer ends in a null */
        buf[ptr] = '\0';
        return ptr;
    }

    //
    // Print a string
    //
    int kprintf(const char* fmt,
        ...) 
    {
        char buf[1024] = { -1 };
        va_list args;

        va_start(args, fmt);
        int out = vasprintf(buf, fmt, args);
        va_end(args);

        // Print
        if (buf[strlen(buf) - 1] == '\n') 
        {
            // buf[strlen(buf) - 1] = '\0';
            screen::terminal::write(buf);
            // char buf2[1024];
            // screen::terminal::write(buf2);
        } 
        else 
        {
            screen::terminal::write(buf);
        }   
        return out;
    }
} // !namespace