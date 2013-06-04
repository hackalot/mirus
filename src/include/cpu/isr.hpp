#ifndef _MIRUS_KERNEL_ISR_H_
#define _MIRUS_KERNEL_ISR_H_

#include <cpu/register.hpp>
#include <cpu/idt.hpp>
#include <misc/printf.hpp>

namespace mirus {
    void isrs_install();
    extern "C" void fault_handler(struct regs* r);
}

#endif