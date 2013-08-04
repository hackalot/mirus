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

#include <sys/panic.hpp>

const char *exception_messages[] =
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

void mirus::panic(regs *r)
{
    if (r->int_no < 32)
    {
        // Do kernel panic here
#ifdef _DEBUG_ON
        mirus::debugger::write("Catostrophic system error - Resulted in panic.\n");
#endif

        mirus::terminal_setcolor(mirus::make_color(COLOR_LIGHT_RED, COLOR_BLACK));
        mirus::terminal_clear();

        printf("System Panic\r\r");
        
        // TODO: print regs
        // TODO: prettier
        // TODO: dump to debug as well

        //    printf("eax=0x%x ebx=0x%x\r", r->eax, r->ebx);
        // printf("ecx=0x%x edx=0x%x\r", r->ecx, r->edx);
        // printf("esp=0x%x ebp=0x%x\r", r->esp, r->ebp);
        // printf("Error code: 0x%x\r",  r->err_code);
        // printf("EFLAGS:     0x%x\r",  r->eflags);
        // printf("User ESP:   0x%x\r",  r->useresp);
        // printf("eip=0x%x\r\r",          r->eip);

        printf(exception_messages[r->int_no]);
        printf(" Exception, system halted!\r");

        for (;;);
    }
}
