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
// screen.cpp - VGA text mode
//

#include <screen/screen.hpp>
#include <util/asm.hpp>
#include <util/ports.hpp>

using mirus::hw::io::inb;
using mirus::hw::io::outb;

namespace mirus
{
    namespace screen
    {
        void screen::install()
        {
            screen::video_memory = (signed int*)0xB8000;
            screen::rows = 25;
            screen::cols = 80;
            screen::x_pos = 0;
            screen::y_pos = 0;
            screen::term_color = vga_color::white;

            screen::clear();
        }

        void screen::set_color(vga_color color)
        {

        }

        signed int screen::make_entry(vga_color color,
            char c)
        {
            signed int c16 = c;
            signed int color16 = (signed int)color;

            return c16 | color16 << 8;
        }

        void screen::put_entry(char c,
            vga_color color,
            unsigned int x,
            unsigned int y)
        {
            const unsigned int index = y * cols + x;
            video_memory[index] = make_entry(vga_color::white, 
                c);
        }

        void screen::move_cursor()
        {
            unsigned temp;

            // Index = [(y * width) + x]
            temp = screen::y_pos * screen::cols
                + screen::x_pos;

            outb(0x3D4, 14);
            outb(0x3D5, temp >> 8);
            outb(0x3D4, 15);
            outb(0x3D5, temp);
        }

        void screen::clear()
        {
            for (int i = 0; i < 80 * 25; i++)
            {
                screen::video_memory[i] = 0;
            }

            // Move the hardware cursor back to the start.
            screen::x_pos = 0;
            screen::y_pos = 0;

            screen::move_cursor();
        }
    } // !namespace
} // !namespace