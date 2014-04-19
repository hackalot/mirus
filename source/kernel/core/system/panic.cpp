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
// panic.cpp - Bad stuff, man
//

#include <lib/stdio.h>
#include <kernel/panic.h>

namespace mirus
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

    void panic(regs* r)
    {
        if (r->int_no < 32)
        {
            kprintf("SYSTEM PANIC: %s\n", exception_messages[r->int_no]);
            kprintf("\tgs: %x\tfs: %x\n", r->gs, r->fs);
            kprintf("\trs: %x\tds: %x\n", r->es, r->ds);
            kprintf("\tedi: %x\tesi: %x\n", r->edi, r->esi);
            kprintf("\tebp: %x\tesp: %x\n", r->ebp, r->esp);
            kprintf("\tebx: %x\tedx: %x\n", r->ebx, r->edx);
            kprintf("\tecx: %x\teax: %x\n", r->ecx, r->eax);
            kprintf("\tint_no: %d\terr_code: %d\n", r->int_no, r->err_code);
            kprintf("\teip: %x\tcs: %x\n", r->eip, r->cs);
            kprintf("\teflags: %x\n\tuseresp: %x\n", r->eflags, r->useresp);
            kprintf("\tss: %x\n", r->ss);

            while (true);
        }
    }
}