// Copyright (c) 2013 Joshua Beitler, Mirus contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

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
