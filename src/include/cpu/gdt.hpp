#ifndef _MIRUS_KERNEL_CPU_GDT_H_
#define _MIRUS_KERNEL_CPU_GDT_H_

#include <mem/memory.hpp>

namespace mirus {
    // entry in the gdt
    class gdt_entry {
    public:
        unsigned short limit_low;
        unsigned short base_low;
        unsigned char base_middle;
        unsigned char access;
        unsigned char granularity;
        unsigned char base_high;
    };

    // ptr to the gdt
    class gdt_ptr {
    public:
        unsigned short limit;
        unsigned int base;
    };

    // simple 3 entry gdt
    static gdt_entry gdt[3];

    // methods and variables used in the asm file
    extern "C" {
        void gdt_flush();
        gdt_ptr gp;
    }

    void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
    void gdt_install();
}

#endif