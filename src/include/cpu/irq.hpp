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

    void irq_install_handler(int irq, irq_handler_t handler);
    void irq_uninstall_handler(int irq);
    void irq_remap();
    void irq_gates();
    void irq_install();
    void irq_ack(int irq_no);

    extern "C" void irq_handler(struct regs* r);
}

#endif