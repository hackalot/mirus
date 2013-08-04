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

// terminal sizes
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 24;

// term info
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

uint8_t mirus::make_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

uint16_t mirus::make_vgaentry(char c, uint8_t color)
{
    uint16_t c16 = c;
    uint16_t color16 = color;

    return c16 | color16 << 8;
}

void mirus::terminal_initialize()
{
    using namespace mirus;

    terminal_row = 0;
    terminal_column = 0;
    terminal_color = make_color(COLOR_WHITE, COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;

    for ( size_t y = 0; y < VGA_HEIGHT; y++ )
    {
        for ( size_t x = 0; x < VGA_WIDTH; x++ )
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = make_vgaentry(' ', terminal_color);
        }
    }
}

// set color
void mirus::terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

// put an entry at location
void mirus::terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    using namespace mirus;

    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = make_vgaentry(c, color);
}

// put a char at a location
void mirus::terminal_putchar(char c)
{
    using namespace mirus;

    if (c == '\r')
    {
        terminal_row++;
        terminal_column = 0;
    }
    else if (c == '\b')
    {
        terminal_column--;
        terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
    }
    else
    {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

        if ( ++terminal_column == VGA_WIDTH )
        {
            terminal_column = 0;
            terminal_row++;

            // if (++terminal_row == 25)
            // {
            //     terminal_scroll();
            // }

        }
    }

    // TODO: bug here
    // if (++terminal_row == VGA_HEIGHT) {
    //     terminal_scroll();
    // }

    terminal_move_cursor();
}

void mirus::terminal_putchar(char c, uint8_t color)
{
    uint8_t oldcolor = terminal_color;
    terminal_setcolor(color);
    mirus::terminal_putchar(c);
    terminal_setcolor(oldcolor);
}

// write a string
void mirus::terminal_writestring(const char* data)
{
    using namespace mirus;

    size_t datalen = strlen(data);

    for (size_t i = 0; i < datalen; i++)
    {
        if (data[i] == '\r')
        {
            terminal_row++;
            terminal_column = 0;
        }
        else if (data[i] == '\b')
        {
            terminal_column--;
            terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
        }
        else
        {
            terminal_putchar(data[i]);
        }
    }
}

void mirus::terminal_writestring(const char* data, uint8_t color)
{
    using namespace mirus;

    size_t datalen = strlen(data);
    for (size_t i = 0; i < datalen; i++)
    {
        if (data[i] == '\r')
        {
            terminal_row++;
            terminal_column = 0;
        }
        else if (data[i] == '\b')
        {
            terminal_column--;
            terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
        }
        else
        {
            terminal_putchar(data[i], color);
        }
    }
}

void mirus::terminal_clear()
{
    using namespace mirus;

    for (int i = 0; i < 80 * 25; i++)
    {
        terminal_buffer[i] = 0;
    }

    // Move the hardware cursor back to the start.
    terminal_row = 0;
    terminal_column = 0;

    terminal_move_cursor();
}

void mirus::terminal_clear(uint8_t color)
{
    using namespace mirus;

    for (int i = 0; i < 80 * 25; i++)
    {
        terminal_putchar(' ', color);
    }

    // Move the hardware cursor back to the start.
    terminal_row = 0;
    terminal_column = 0;

    terminal_move_cursor();
}

// TODO: does not scroll correctly
void mirus::terminal_scroll()
{
    using namespace mirus;

    uint8_t blank = make_color(COLOR_BLACK, COLOR_BLACK);
    unsigned temp;
    unsigned short* vidmem = nullptr;

    vidmem = (unsigned short*)0xB8000;

    temp = terminal_column - 25 + 1;

    mirus::memcpy(vidmem, vidmem + temp * 80, (25 - temp) * 80 * 2);
    mirus::memsetw(vidmem + (25 - temp) * 80, blank, 80);

    terminal_column = 25 - 1;
}

void mirus::terminal_move_cursor()
{
    using namespace mirus;

    unsigned temp;

    /* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    temp = terminal_row * 80 + terminal_column;

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
    mirus::outb(0x3D4, 14);
    mirus::outb(0x3D5, temp >> 8);
    mirus::outb(0x3D4, 15);
    mirus::outb(0x3D5, temp);
}
