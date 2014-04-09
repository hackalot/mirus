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
// isr.cpp - isr implimentation
//

#include <lib/stdio.h>
#include <kernel/idt.h>
#include <kernel/isr.h>
#include <kernel/regs.h>
#include <kernel/memory.h>

namespace mirus
{
    extern "C"
    {
        void isr0();
        void isr1();
        void isr2();
        void isr3();
        void isr4();
        void isr5();
        void isr6();
        void isr7();
        void isr8();
        void isr9();
        void isr10();
        void isr11();
        void isr12();
        void isr13();
        void isr14();
        void isr15();
        void isr16();
        void isr17();
        void isr18();
        void isr19();
        void isr20();
        void isr21();
        void isr22();
        void isr23();
        void isr24();
        void isr25();
        void isr26();
        void isr27();
        void isr28();
        void isr29();
        void isr30();
        void isr31();

        void isr127();
    }

    irq_handler_t isr_routines[256] = { NULL };

    void isr::install_handler(size_t isr, irq_handler_t handler)
    {
        isr_routines[isr] = handler;
    }

    void isr::uninstall_handler(size_t isr)
    {
        isr_routines[isr] = 0;
    }

    void isr::init()
    {
        memset_v(isr_routines, 0x00, sizeof(isr_routines));

        idt::set_gate(0, (unsigned long)isr0, 0x08, 0xEE);
        idt::set_gate(1, (unsigned long)isr1, 0x08, 0x8E);
        idt::set_gate(2, (unsigned long)isr2, 0x08, 0x8E);
        idt::set_gate(3, (unsigned long)isr3, 0x08, 0x8E);
        idt::set_gate(4, (unsigned long)isr4, 0x08, 0x8E);
        idt::set_gate(5, (unsigned long)isr5, 0x08, 0x8E);
        idt::set_gate(6, (unsigned long)isr6, 0x08, 0x8E);
        idt::set_gate(7, (unsigned long)isr7, 0x08, 0x8E);

        idt::set_gate(8, (unsigned long)isr8, 0x08, 0x8E);
        idt::set_gate(9, (unsigned long)isr9, 0x08, 0x8E);
        idt::set_gate(10, (unsigned long)isr10, 0x08, 0x8E);
        idt::set_gate(11, (unsigned long)isr11, 0x08, 0x8E);
        idt::set_gate(12, (unsigned long)isr12, 0x08, 0x8E);
        idt::set_gate(13, (unsigned long)isr13, 0x08, 0x8E);
        idt::set_gate(14, (unsigned long)isr14, 0x08, 0x8E);
        idt::set_gate(15, (unsigned long)isr15, 0x08, 0x8E);

        idt::set_gate(16, (unsigned long)isr16, 0x08, 0x8E);
        idt::set_gate(17, (unsigned long)isr17, 0x08, 0x8E);
        idt::set_gate(18, (unsigned long)isr18, 0x08, 0x8E);
        idt::set_gate(19, (unsigned long)isr19, 0x08, 0x8E);
        idt::set_gate(20, (unsigned long)isr20, 0x08, 0x8E);
        idt::set_gate(21, (unsigned long)isr21, 0x08, 0x8E);
        idt::set_gate(22, (unsigned long)isr22, 0x08, 0x8E);
        idt::set_gate(23, (unsigned long)isr23, 0x08, 0x8E);

        idt::set_gate(24, (unsigned long)isr24, 0x08, 0x8E);
        idt::set_gate(25, (unsigned long)isr25, 0x08, 0x8E);
        idt::set_gate(26, (unsigned long)isr26, 0x08, 0x8E);
        idt::set_gate(27, (unsigned long)isr27, 0x08, 0x8E);
        idt::set_gate(28, (unsigned long)isr28, 0x08, 0x8E);
        idt::set_gate(29, (unsigned long)isr29, 0x08, 0x8E);
        idt::set_gate(30, (unsigned long)isr30, 0x08, 0x8E);
        idt::set_gate(31, (unsigned long)isr31, 0x08, 0x8E);
    }

    extern "C" void fault_handler(regs* r)
    {
        kprintf("crap\n");
    }
} // !namespace