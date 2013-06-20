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

#include <cpu/irq.hpp>

static mirus::irq_handler_t irq_routines[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

void mirus::irq::install_handler(int irq, irq_handler_t handler) {
    irq_routines[irq] = handler;
}

void mirus::irq::uninstall_handler(int irq) {
    irq_routines[irq] = 0;
}

void mirus::irq::remap() {
    mirus::outb(0x20, 0x11);
    mirus::outb(0xA0, 0x11);
    mirus::outb(0x21, 0x20);
    mirus::outb(0xA1, 0x28);
    mirus::outb(0x21, 0x04);
    mirus::outb(0xA1, 0x02);
    mirus::outb(0x21, 0x01);
    mirus::outb(0xA1, 0x01);
    mirus::outb(0x21, 0x0);
    mirus::outb(0xA1, 0x0);
}

void mirus::irq::gates() {
    mirus::idt::set_gate(32, (unsigned long)irq0, 0x08, 0x8E);
    mirus::idt::set_gate(33, (unsigned long)irq1, 0x08, 0x8E);
    mirus::idt::set_gate(34, (unsigned long)irq2, 0x08, 0x8E);
    mirus::idt::set_gate(35, (unsigned long)irq3, 0x08, 0x8E);
    mirus::idt::set_gate(36, (unsigned long)irq4, 0x08, 0x8E);
    mirus::idt::set_gate(37, (unsigned long)irq5, 0x08, 0x8E);
    mirus::idt::set_gate(38, (unsigned long)irq6, 0x08, 0x8E);
    mirus::idt::set_gate(39, (unsigned long)irq7, 0x08, 0x8E);
    mirus::idt::set_gate(40, (unsigned long)irq8, 0x08, 0x8E);
    mirus::idt::set_gate(41, (unsigned long)irq9, 0x08, 0x8E);
    mirus::idt::set_gate(42, (unsigned long)irq10, 0x08, 0x8E);
    mirus::idt::set_gate(43, (unsigned long)irq11, 0x08, 0x8E);
    mirus::idt::set_gate(44, (unsigned long)irq12, 0x08, 0x8E);
    mirus::idt::set_gate(45, (unsigned long)irq13, 0x08, 0x8E);
    mirus::idt::set_gate(46, (unsigned long)irq14, 0x08, 0x8E);
    mirus::idt::set_gate(47, (unsigned long)irq15, 0x08, 0x8E);
}

void mirus::irq::install() {
    #ifdef _DEBUG_ON
        mirus::debugger::write("Installing IRQ handlers\n");
    #endif

    irq::remap();
    irq::gates();

    //IRQ_RES;
}

void mirus::irq::ack(int irq_no) {
    if (irq_no >= 12) {
        mirus::outb(0xA0, 0x20);
    }

    mirus::outb(0x20, 0x20);
}

extern "C" void mirus::irq_handler(struct regs *r) {
    void (*handler)(struct regs *r);

    if (r->int_no > 47 || r->int_no < 32) {
        handler = 0;
    } else {
        handler = irq_routines[r->int_no - 32];
    }

    if (handler) {
        handler(r);
    } else {
        irq::ack(r->int_no - 32);
    }
}