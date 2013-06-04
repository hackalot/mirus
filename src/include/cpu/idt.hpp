#ifndef _MIRUS_KERNEL_IDT_H_
#define _MIRUS_KERNEL_IDT_H_

#include <mem/memory.hpp>

namespace mirus {
    /* Defines an IDT entry */
    class idt_entry {
    public:
        unsigned short base_lo;
        unsigned short sel;        /* Our kernel segment goes here! */
        unsigned char always0;     /* This will ALWAYS be set to 0! */
        unsigned char flags;       /* Set using the above table! */
        unsigned short base_hi;
    } __attribute__ ((__packed__));

    class idt_ptr {
    public:
        unsigned short limit;
        unsigned int base;
    } __attribute__ ((__packed__));

    void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
    void idt_install();
}

#endif