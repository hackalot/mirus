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

        static void print_center(const char* msg)
        {
            int a = strlen(msg);
            int location = 80 / 2 - (a / 2);
            screen::terminal::set_col(location);
            screen::terminal::write(msg);
        }

        // TODO: this is a mess....
        void panic(cpu::regs* r)
        {
            if (r->int_no < 32)
            {
                // Do kernel panic here
                screen::terminal::clear();

                screen::terminal::set_color((unsigned char)screen::vga_color::red,
                    (unsigned char)screen::vga_color::white);
                screen::terminal::set_row(5);

                print_center(" Mirus ");

                screen::terminal::set_color((unsigned char)screen::vga_color::red,
                    (unsigned char)screen::vga_color::black);

                screen::terminal::write('\n\n');
                print_center("System Panic!\n");

                print_center(exception_messages[r->int_no]);
                print_center(" Exception\n\n");
                print_center("System Halted");

                while (true);
            }
        }
    } // !namespace
} // !namespace