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

#include <term/terminal.hpp>

namespace mirus
{
    namespace io
    {
        // terminal sizes
        const size_t VGA_WIDTH = 80;
        const size_t VGA_HEIGHT = 24;

        // term info
        size_t terminal_row;
        size_t terminal_column;
        uint8_t _terminal_color;
        uint16_t* terminal_buffer;

        void terminal::putentry(char c, terminal_color color, size_t x, size_t y)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = terminal::make_vga_entry(c, color);
        }

        void terminal::putchar(char c)
        {
            if (c == '\r')
            {
                terminal_row++;
                _terminal_color = 0;
            }
            else if (c == '\b')
            {
                _terminal_color--;
                terminal::putentry(' ', _terminal_color, terminal_column, terminal_row);
            }
            else
            {
                terminal::putentry(c, _terminal_color, terminal_column, terminal_row);
            }

            terminal::move_cursor();
        }

        void terminal::putchar(char c, terminal_color color)
        {
            terminal_color oldcolor = _terminal_color;

            terminal::set_color(color);
            terminal::putchar(c);
            terminal::set_color(oldcolor);
        }

        void terminal::write_string(const char* data)
        {
            size_t datalen = strlen(data);

            for (size_t i = 0; i < datalen; i++)
            {
                // TODO: do we really need this?
                // if (data[i] == '\r')
                // {
                //     terminal_row++;
                //     terminal_column = 0;
                // }
                // else if (data[i] == '\b')
                // {
                //     terminal_column--;
                //     terminal::putentry(' ', _terminal_color, terminal_column, terminal_row);
                // }
                // else
                // {
                //     terminal::putchar(data[i]);
                // }
                terminal::putchar(data[i]);
            }
        }

        void terminal::write_string(const char* data, terminal_color color)
        {
            terminal_color prev_color = _terminal_color;
            terminal::set_color(color);

            terminal::write_string(data);

            terminal::set_color(prev_color);
        }

        void terminal::clear()
        {
            for (int i = 0; i < 80 * 25; i++)
            {
                terminal_buffer[i] = 0;
            }

            // Move the hardware cursor back to the start.
            terminal_row = 0;
            terminal_column = 0;

            terminal::move_cursor();
        }

        void terminal::clear(terminal_color color)
        {
             for (int i = 0; i < 80 * 25; i++)
            {
                terminal::putchar(' ', color);
            }

            // Move the hardware cursor back to the start.
            terminal_row = 0;
            terminal_column = 0;

            terminal::move_cursor();
        }

        void terminal::scroll()
        {

        }

        void terminal::move_cursor()
        {
            unsigned temp;

            // Index = [(y * width) + x]
            temp = terminal_row * 80 + terminal_column;

            mirus::outb(0x3D4, 14);
            mirus::outb(0x3D5, temp >> 8);
            mirus::outb(0x3D4, 15);
            mirus::outb(0x3D5, temp);
        }

        terminal_color terminal::make_color(vga_color fg, vga_color bg)
        {
            return (int)fg | (int)bg << 4;
        }

        uint16_t terminal::make_vga_entry(char c, terminal_color color)
        {
            uint16_t c16 = c;
            uint16_t color16 = color;

            return c16 | color16 << 8;
        }

        void terminal::set_color(terminal_color color)
        {
            _terminal_color = color;
        }

        void terminal::initilize()
        {
            terminal_row = 0;
            terminal_column = 0;
            _terminal_color = terminal::make_color(vga_color::white, vga_color::black);
            terminal_buffer = (uint16_t*)0xb8000;

            terminal::clear();
        }
    }
}
