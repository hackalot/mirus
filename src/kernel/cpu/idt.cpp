#include <cpu/idt.hpp>

namespace mirus {
    extern "C" {
        void idt_load();
        mirus::idt_ptr idtp;
    }
}

static mirus::idt_entry idt[256];

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void mirus::idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    using namespace mirus;

    /* The interrupt routine's base address */
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    /* The segment or 'selector' that this IDT entry will use
    *  is set here, along with any access flags */
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

/* Installs the IDT */
void mirus::idt_install() {
    using namespace mirus;

    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    idtp.limit = (sizeof(idt_entry) * 256) - 1;
    idtp.base = (unsigned long)&idt;

    /* Clear out the entire IDT, initializing it to zeros */
    mirus::memset((unsigned char *)&idt, 0, sizeof(idt_entry) * 256);

    /* Add any new ISRs to the IDT here using idt_set_gate */

    /* Points the processor's internal register to the new IDT */
    idt_load();
}
