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
// panic.cpp - The cooler cousin of the BSOD
//

#include <stdafx.hpp>
#include <core/panic.hpp>
#include <util/string.hpp>

namespace mirus
{
    namespace core
    {
        //
        // exception_messages - all intel messages possible
        //
        const char* exception_messages[] =
        { 
            "Division By Zero",
            "Debug",
            "Non Maskable Interrupt",
            "Breakpoint",
            "Into Detected Overflow",
            "Out of Bounds",
            "Invalid Opcode",
            "No Coprocessor",

            "Double Fault",
            "Coprocessor Segment Overrun",
            "Bad TSS",
            "Segment Not Present",
            "Stack Fault",
            "General Protection Fault",
            "Page Fault",
            "Unknown Interrupt",

            "Coprocessor Fault",
            "Alignment Check",
            "Machine Check",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",

            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved"
        };

        //
        // panic_at_the_disco - Kill the kernel and light everything on fire
        //                      TODO: this is a mess...
        //
        void panic(cpu::regs* r)
        {
            if (r->int_no < 32)
            {
                // Do kernel panic here
                screen::terminal::clear();

                screen::terminal::set_color((unsigned char)screen::vga_color::red,
                    (unsigned char)screen::vga_color::white);

                int a = strlen(" Mirus ");
                int location = 80 / 2 - (a / 2);

                screen::terminal::set_col(location);
                screen::terminal::set_row(5);

                screen::terminal::writeln(" Mirus ");

                screen::terminal::set_color((unsigned char)screen::vga_color::red,
                    (unsigned char)screen::vga_color::black);

                screen::terminal::write('\n');

                a = strlen(exception_messages[r->int_no]);
                int b = strlen(" Exception.");
                a += b;
                location = 80 / 2 - (a / 2);
                screen::terminal::set_col(location);

                screen::terminal::write(exception_messages[r->int_no]);
                screen::terminal::write(" Exception\n");
                a = strlen("The system has been halted.");
                location = 80 / 2 - (a / 2);
                screen::terminal::set_col(location);
                screen::terminal::write("The system has been halted.");

                while (true);
            }
        }
    } // !namespace
} // !namespace