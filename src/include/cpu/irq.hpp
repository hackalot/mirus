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

#ifndef _MIRUS_KERNEL_IRQ_H_
#define _MIRUS_KERNEL_IRQ_H_

#include <cpu/register.hpp>
#include <core/ioport.hpp>
#include <cpu/idt.hpp>

#define IRQ_OFF { asm volatile ("cli"); }
#define IRQ_RES { asm volatile ("sti"); }

namespace mirus {
    typedef void (*irq_handler_t) (struct regs *);

    extern "C" {
        void irq0();
        void irq1();
        void irq2();
        void irq3();
        void irq4();
        void irq5();
        void irq6();
        void irq7();
        void irq8();
        void irq9();
        void irq10();
        void irq11();
        void irq12();
        void irq13();
        void irq14();
        void irq15();
    }

    class irq {
    public:
        static void install_handler();
        static void uninstall_handler();

        static void remap();
        static void gates();

        static void install();
        static void ack(int irq_no);
    };

    extern "C" void irq_handler(struct regs* r);
}















// namespace mirus {
//     typedef void (*irq_handler_t) (struct regs *);

//     extern "C" {
//         void irq0();
//         void irq1();
//         void irq2();
//         void irq3();
//         void irq4();
//         void irq5();
//         void irq6();
//         void irq7();
//         void irq8();
//         void irq9();
//         void irq10();
//         void irq11();
//         void irq12();
//         void irq13();
//         void irq14();
//         void irq15();
//     }

//     void irq_install_handler(int irq, irq_handler_t handler);
//     void irq_uninstall_handler(int irq);
//     void irq_remap();
//     void irq_gates();
//     void irq_install();
//     void irq_ack(int irq_no);

//     extern "C" void irq_handler(struct regs* r);
// }

#endif