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

#include <cpu/gdt.hpp>

// methods and variables used in the asm file
namespace mirus {
    extern "C" {
        void gdt_flush();
        mirus::gdt_ptr gp;
    }
}

static mirus::gdt_entry _gdt[6];

void mirus::gdt::set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
    using namespace mirus;

    // descriptor base address
    _gdt[num].base_low = (base & 0xFFFF);
    _gdt[num].base_middle = (base >> 16) & 0xFF;
    _gdt[num].base_high = (base >> 24) & 0xFF;

    // limits
    _gdt[num].limit_low = (limit & 0xFFFF);
    _gdt[num].granularity = ((limit >> 16) & 0x0F);

    // flags + granularity
    _gdt[num].granularity |= (gran & 0xF0);
    _gdt[num].access = access;
}

void mirus::gdt::install() {
    using namespace mirus;

    #ifdef _DEBUG_ON
        mirus::debugger::write("Installing GDT\n");
    #endif

    gp.limit = (sizeof(gdt_entry) * 6) - 1;
    gp.base = (unsigned long)&_gdt;

    // Null descriptor
    gdt::set_gate(0, 0, 0, 0, 0);

    // code seg
    gdt::set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // data seg
    gdt::set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // user code
    gdt::set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    // user data
    gdt::set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    // flush it
    gdt_flush();
}