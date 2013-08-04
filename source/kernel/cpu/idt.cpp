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

#include <cpu/idt.hpp>

namespace mirus
{
    extern "C"
    {
        void idt_load();
        mirus::idt_ptr idtp;
    }
}

static mirus::idt_entry _idt[256];

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void mirus::idt::set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
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
void mirus::idt::install()
{
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
