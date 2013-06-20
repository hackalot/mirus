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

#include <cpu/idt.hpp>

namespace mirus {
    extern "C" {
        void idt_load();
        mirus::idt_ptr idtp;
    }
}

static mirus::idt_entry _idt[256];

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void mirus::idt::set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    using namespace mirus;

    /* The interrupt routine's base address */
    _idt[num].base_lo = (base & 0xFFFF);
    _idt[num].base_hi = (base >> 16) & 0xFFFF;

    /* The segment or 'selector' that this IDT entry will use
    *  is set here, along with any access flags */
    _idt[num].sel = sel;
    _idt[num].always0 = 0;
    _idt[num].flags = flags;
}

/* Installs the IDT */
void mirus::idt::install() {
    using namespace mirus;

    #ifdef _DEBUG_ON
        mirus::debugger::write("Installing IDT\n");
    #endif

    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    idtp.limit = (sizeof(idt_entry) * 256) - 1;
    idtp.base = (unsigned long)&_idt;

    /* Clear out the entire IDT, initializing it to zeros */
    mirus::memset((unsigned char *)&_idt, 0, sizeof(idt_entry) * 256);

    /* Add any new ISRs to the IDT here using idt_set_gate */

    /* Points the processor's internal register to the new IDT */
    idt_load();
}
