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
// serial.cpp - Serial port implimentation
//

#include <hardware/serial.hpp>
#include <util/ports.hpp>

using mirus::hardware::io::outb;
using mirus::hardware::io::inb;

namespace mirus
{
    namespace hardware
    {
        void serial::install()
        {
            outb(COM1 + 1, 0x00);    // Disable all interrupts
            outb(COM1 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
            outb(COM1 + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
            outb(COM1 + 1, 0x00);    //                  (hi byte)
            outb(COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
            outb(COM1 + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
            outb(COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set
        }

        char serial::read()
        {
            while (serial::serial_received() == 0);
            return inb(COM1);
        }

        int serial::serial_received()
        {
            return inb(COM1 + 5) & 1;
        }

        int serial::is_transmit_empty()
        {
            return inb(COM1 + 5) & 0x20;
        }

        void serial::write(char a)
        {
            while (serial::is_transmit_empty() == 0);
            outb(COM1, a);
        }
    } // !namespace
} // !namespace