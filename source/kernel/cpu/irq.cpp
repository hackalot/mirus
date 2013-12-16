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
// irq.hpp - IRQ implimentation
//

#include <stdafx.hpp>
#include <cpu/idt.hpp>
#include <cpu/regs.hpp>
#include <util/ports.hpp>
#include <cpu/irq.hpp>

using mirus::hardware::io::inb;
using mirus::hardware::io::outb;

namespace mirus
{
    namespace cpu
    {
        static irq_handler_t irq_routines[256] = { NULL };

        //
        // Set up a listener
        //
        void irq::install_handler(int irq, 
            irq_handler_t handler)
        {
            irq_routines[irq] = handler;
        }

        //
        // remove a handler on an irq
        //
        void irq::uninstall_handler(int irq)
        {
            irq_routines[irq] = 0;
        }

        //
        // remap IRQs to avoid conflicts
        //
        void irq::remap()
        {
            outb(0x20, 0x11);
            outb(0xA0, 0x11);
            outb(0x21, 0x20);
            outb(0xA1, 0x28);
            outb(0x21, 0x04);
            outb(0xA1, 0x02);
            outb(0x21, 0x01);
            outb(0xA1, 0x01);
            outb(0x21, 0x0);
            outb(0xA1, 0x0);
        }

        //
        // set IRQ gates
        //
        void irq::gates()
        {
            idt::set_gate(32, (unsigned long)irq0, 0x08, 0x8E);
            idt::set_gate(33, (unsigned long)irq1, 0x08, 0x8E);
            idt::set_gate(34, (unsigned long)irq2, 0x08, 0x8E);
            idt::set_gate(35, (unsigned long)irq3, 0x08, 0x8E);
            idt::set_gate(36, (unsigned long)irq4, 0x08, 0x8E);
            idt::set_gate(37, (unsigned long)irq5, 0x08, 0x8E);
            idt::set_gate(38, (unsigned long)irq6, 0x08, 0x8E);
            idt::set_gate(39, (unsigned long)irq7, 0x08, 0x8E);
            idt::set_gate(40, (unsigned long)irq8, 0x08, 0x8E);
            idt::set_gate(41, (unsigned long)irq9, 0x08, 0x8E);
            idt::set_gate(42, (unsigned long)irq10, 0x08, 0x8E);
            idt::set_gate(43, (unsigned long)irq11, 0x08, 0x8E);
            idt::set_gate(44, (unsigned long)irq12, 0x08, 0x8E);
            idt::set_gate(45, (unsigned long)irq13, 0x08, 0x8E);
            idt::set_gate(46, (unsigned long)irq14, 0x08, 0x8E);
            idt::set_gate(47, (unsigned long)irq15, 0x08, 0x8E);

            idt::set_gate(127, (unsigned long)irq127, 0x08, 0xEE);
        }

        //
        // install the irq handler
        //
        void irq::install()
        {
            irq::remap();
            irq::gates();
        }

        void irq::ack(int irq_no)
        {
            if (irq_no >= 12)
            {
                outb(0xA0, 0x20);
            }

            outb(0x20, 0x20);
        }

        //
        // our irq handler
        //
        extern "C" void irq_handler(struct regs* r)
        {
            void (*handler)(struct regs* r);
            handler = irq_routines[r->int_no - 32];

            if (handler)
                handler(r);
            else
                irq::ack(r->int_no - 32);
        }
    } // !namespace
} // !namespace