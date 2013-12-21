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
#include <system/core/panic.hpp>
#include <util/string.hpp>

namespace mirus
{
    namespace core
    {
        //
        // exception_messages - all intel messages
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
        //
        void panic(cpu::regs* r)
        {
            if (r->int_no < 32)
            {
                asm volatile("cli");

                screen::terminal::clear();

                kprintf("SYSTEM PANIC: %s\n\n", exception_messages[r->int_no]);
                kprintf("gs: %x\tfs: %x\n", r->gs, r->fs);
                kprintf("rs: %x\tds: %x\n", r->es, r->ds);
                kprintf("edi: %x\tesi: %x\n", r->edi, r->esi);
                kprintf("ebp: %x\tesp: %x\n", r->ebp, r->esp);
                kprintf("ebx: %x\tedx: %x\n", r->ebx, r->edx);
                kprintf("ecx: %x\teax: %x\n", r->ecx, r->eax);
                kprintf("int_no: %d\terr_code: %d\n", r->int_no, r->err_code);
                kprintf("eip: %x\tcs: %x\n", r->eip, r->cs);
                kprintf("eflags: %x\nuseresp: %x\n", r->eflags, r->useresp);
                kprintf("ss: %x\n", r->ss);

                ktrace(trace_level::emerg, "KERNEL PANIC\n");

                while (true);
            }
        }
    } // !namespace
} // !namespace