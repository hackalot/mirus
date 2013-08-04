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
