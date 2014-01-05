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

#include <cpu/isr.hpp>
#include <cpu/regs.hpp>
#include <system/core/panic.hpp>

namespace mirus
{
    namespace cpu
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

        void isr::install()
        {
            memset_v(isr_routines, 0x00, sizeof(isr_routines));

            idt::set_gate(0, (unsigned)isr0, 0x08, 0xEE);
            idt::set_gate(1, (unsigned)isr1, 0x08, 0x8E);
            idt::set_gate(2, (unsigned)isr2, 0x08, 0x8E);
            idt::set_gate(3, (unsigned)isr3, 0x08, 0x8E);
            idt::set_gate(4, (unsigned)isr4, 0x08, 0x8E);
            idt::set_gate(5, (unsigned)isr5, 0x08, 0x8E);
            idt::set_gate(6, (unsigned)isr6, 0x08, 0x8E);
            idt::set_gate(7, (unsigned)isr7, 0x08, 0x8E);

            idt::set_gate(8, (unsigned)isr8, 0x08, 0x8E);
            idt::set_gate(9, (unsigned)isr9, 0x08, 0x8E);
            idt::set_gate(10, (unsigned)isr10, 0x08, 0x8E);
            idt::set_gate(11, (unsigned)isr11, 0x08, 0x8E);
            idt::set_gate(12, (unsigned)isr12, 0x08, 0x8E);
            idt::set_gate(13, (unsigned)isr13, 0x08, 0x8E);
            idt::set_gate(14, (unsigned)isr14, 0x08, 0x8E);
            idt::set_gate(15, (unsigned)isr15, 0x08, 0x8E);

            idt::set_gate(16, (unsigned)isr16, 0x08, 0x8E);
            idt::set_gate(17, (unsigned)isr17, 0x08, 0x8E);
            idt::set_gate(18, (unsigned)isr18, 0x08, 0x8E);
            idt::set_gate(19, (unsigned)isr19, 0x08, 0x8E);
            idt::set_gate(20, (unsigned)isr20, 0x08, 0x8E);
            idt::set_gate(21, (unsigned)isr21, 0x08, 0x8E);
            idt::set_gate(22, (unsigned)isr22, 0x08, 0x8E);
            idt::set_gate(23, (unsigned)isr23, 0x08, 0x8E);

            idt::set_gate(24, (unsigned)isr24, 0x08, 0x8E);
            idt::set_gate(25, (unsigned)isr25, 0x08, 0x8E);
            idt::set_gate(26, (unsigned)isr26, 0x08, 0x8E);
            idt::set_gate(27, (unsigned)isr27, 0x08, 0x8E);
            idt::set_gate(28, (unsigned)isr28, 0x08, 0x8E);
            idt::set_gate(29, (unsigned)isr29, 0x08, 0x8E);
            idt::set_gate(30, (unsigned)isr30, 0x08, 0x8E);
            idt::set_gate(31, (unsigned)isr31, 0x08, 0x8E);
        }

        extern "C" void fault_handler(cpu::regs* r)
        {
            core::panic(r);
        }
    } // !namespace
} // !namespace