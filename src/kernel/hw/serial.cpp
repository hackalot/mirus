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

#include <hw/serial.hpp>

void mirus::serial_install()
{
    mirus::outb(PORT + 1, 0x00);    // Disable all interrupts
    mirus::outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    mirus::outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    mirus::outb(PORT + 1, 0x00);    //                  (hi byte)
    mirus::outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    mirus::outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    mirus::outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

int mirus::serial_received()
{
    return mirus::inb(PORT + 5) & 1;
}

char mirus::read_serial()
{
    while (serial_received() == 0);
    return mirus::inb(PORT);
}

int mirus::is_transmit_empty()
{
    return mirus::inb(PORT + 5) & 0x20;
}

void mirus::write_serial(char a)
{
    while (is_transmit_empty() == 0);
    mirus::outb(PORT, a);
}
