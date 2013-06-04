#include <term/terminal.hpp>

uint8_t make_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color) {
    uint16_t c16 = c;
    uint16_t color16 = color;

    return c16 | color16 << 8;
}

void terminal_initialize() {
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
void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

// put an entry at location
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = make_vgaentry(c, color);
}

// put a char at a location
void terminal_putchar(char c) {
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

    // TODO: bug here
    // if (++terminal_row == VGA_HEIGHT) {
    //     terminal_scroll();
    // }

    terminal_move_cursor();
}

// write a string
void terminal_writestring(const char* data) {
    size_t datalen = strlen(data);
    for (size_t i = 0; i < datalen; i++) {
        if (data[i] == '\n') {
            // LF.  We don't like it, but we support it.
            // set rows++, cols to 0.
            ++terminal_row;
            terminal_column = 0;
        } else if (data[i] == '\r') {
            // CR is default...
            ++terminal_row;
            terminal_column = 0;
        } else {
            terminal_putchar(data[i]);
        }
    }
}

void terminal_clear() {
    int spaces = VGA_WIDTH * VGA_HEIGHT;

    for (int i = 0; i < spaces; i++) {
        terminal_putchar(' ');
    }

    terminal_row = 0;
    terminal_column = 0;
}

// TODO: does not scroll correctly
void terminal_scroll() {
    uint8_t blank = make_color(COLOR_BLACK, COLOR_BLACK);
    unsigned temp;
    unsigned short* vidmem = nullptr;

    vidmem = (unsigned short*)0xB8000;

    temp = terminal_column - 25 + 1;

    mirus::memcpy(vidmem, vidmem + temp * 80, (25 - temp) * 80 * 2);
    mirus::memsetw(vidmem + (25 - temp) * 80, blank, 80);

    terminal_column = 25 - 1;
}

void terminal_move_cursor() {
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