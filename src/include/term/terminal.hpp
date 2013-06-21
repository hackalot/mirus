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

#ifndef _MIRUS_KERNEL_TERMINAL_H_
#define _MIRUS_KERNEL_TERMINAL_H_

#include <stddef.h>
#include <stdint.h>
#include <util/string.hpp>
#include <core/ioport.hpp>
#include <mem/memory.hpp>

// Hardware text mode color constants.
enum vga_color
{
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
};

namespace mirus
{
    // create a color
    uint8_t make_color(enum vga_color fg, enum vga_color bg);

    // create a VGA entry
    uint16_t make_vgaentry(char c, uint8_t color);

    // init the terminal
    void terminal_initialize();

    // set color
    void terminal_setcolor(uint8_t color);

    // put an entry at location
    void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);

    // put a char at a location
    void terminal_putchar(char c);
    void terminal_putchar(char c, uint8_t color);

    // write a string
    void terminal_writestring(const char *data);
    void terminal_writestring(const char *data, uint8_t color);

    // clear function
    void terminal_clear();
    void terminal_clear(uint8_t color);

    // our test void
    void test();

    // scroll it
    void terminal_scroll();

    // move cursor
    void terminal_move_cursor();
}

#endif
