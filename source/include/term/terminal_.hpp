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

#ifndef _MIRUS_KERNEL_IO_TERM_H_
#define _MIRUS_KERNEL_IO_TERM_H_

#include <system.hpp>

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
            static void putentry(char c, terminal_color color, size_t x, size_t y);

            // place a character
            static void putchar(char c);
            static void putchar(c, terminal_color color);

            // place a string
            static void writestring(const char* data);
            static void writestring(const char* data, terminal_color color);

            // clear the screen
            static void clear();
            static void clean(terminal_color color);

            static void scroll();
            static void move_cursor();

            // make a color/entry for vga memory
            static terminal_color make_color(vga_color fg, vga_color bg);
            static uint16_t make_vga_entry(char c, terminal_color color);

            static void initilize();
        };
    }
}

#endif
