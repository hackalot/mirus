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

#ifndef _MIRUS_KERNEL_IO_TERM_H_
#define _MIRUS_KERNEL_IO_TERM_H_

#include <stddef.h>     // TODO: do we *really* need these?
#include <stdint.h>
#include <util/string.hpp>
#include <core/ioport.hpp>
#include <mem/memory.hpp>

namespace mirus
{
    namespace io
    {
        typedef uint8_t terminal_color;
        
        class terminal
        {
        public:
            enum class vga_color
            {
                COLOR_BLACK         = 0,
                COLOR_BLUE          = 1,
                COLOR_GREEN         = 2,
                COLOR_CYAN          = 3,
                COLOR_RED           = 4,
                COLOR_MAGENTA       = 5,
                COLOR_BROWN         = 6,
                COLOR_LIGHT_GREY    = 7,
                COLOR_DARK_GREY     = 8,
                COLOR_LIGHT_BLUE    = 9,
                COLOR_LIGHT_GREEN   = 10,
                COLOR_LIGHT_CYAN    = 11,
                COLOR_LIGHT_RED     = 12,
                COLOR_LIGHT_MAGENTA = 13,
                COLOR_LIGHT_BROWN   = 14,
                COLOR_WHITE         = 15
            };
           
            // place a character at a specified location
            void putentry(char c, terminal_color color, size_t x, size_t y);

            // place a character
            void putchar(char c);
            void putchar(c, terminal_color color);

            // place a string
            void writestring(const char* data);
            void writestring(const char* data, terminal_color color);

            // clear the screen
            void clear();
            void clean(terminal_color color);

            void scroll();
            void move_cursor();

            // make a color/entry for vga memory
            static terminal_color make_color(vga_color fg, vga_color bg);
            static uint16_t make_vga_entry(char c, terminal_color color);

            void initilize();
        };
    }
}

#endif
