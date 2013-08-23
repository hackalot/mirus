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
                black         = 0,
                blue          = 1,
                green         = 2,
                cyan          = 3,
                red           = 4,
                magenta       = 5,
                brown         = 6,
                light_grey    = 7,
                dark_grey     = 8,
                light_blue    = 9,
                light_green   = 10,
                light_cyan    = 11,
                light_red     = 12,
                light_magenta = 13,
                light_brown   = 14,
                white         = 15
            };
           
            // place a character at a specified location
            static void putentry(char c, terminal_color color, size_t x, size_t y);

            // place a character
            static void putchar(char c);
            static void putchar(char c, terminal_color color);

            // place a string
            static void writestring(const char* data);
            static void writestring(const char* data, terminal_color color);

            // clear the screen
            static void clear();
            static void clear(terminal_color color);

            static void scroll();
            static void move_cursor();

            // make a color/entry for vga memory
            static terminal_color make_color(vga_color fg, vga_color bg);
            static uint16_t make_vga_entry(char c, terminal_color color);

            static void set_color(terminal_color color);

            static void initilize();
        };
    }
}

#endif
