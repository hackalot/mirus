#include <cpu/gdt.hpp>

// methods and variables used in the asm file
namespace mirus {
    extern "C" {
        void gdt_flush();
        mirus::gdt_ptr gp;
    }
}

static mirus::gdt_entry gdt[6];

void mirus::gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
    using namespace mirus;

    // descriptor base address
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    // limits
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    // flags + granularity
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void mirus::gdt_install() {
    using namespace mirus;

    gp.limit = (sizeof(gdt_entry) * 6) - 1;
    gp.base = (unsigned long)&gdt;

    // Null descriptor
    gdt_set_gate(0, 0, 0, 0, 0);

    // code seg
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // data seg
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // user code
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    // user data
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    // flush it
    gdt_flush();
}